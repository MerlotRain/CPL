#include <m2_color.h>
#include <m2_math.h>

namespace m2 {

/*******************************************************************************
 * Rgb32 functions
 *******************************************************************************/

// masks RGB values
constexpr Rgb32 RGB_MASK = 0xffffffff;

// get red part of RGB
inline constexpr int qRed(Rgb32 rgb) { return ((rgb >> 16) & 0xff); }

// get green part of RGB
inline constexpr int qGreen(Rgb32 rgb) { return ((rgb >> 8) & 0xff); }

// get blue part of RGB
inline constexpr int qBlue(Rgb32 rgb) { return (rgb & 0xff); }

// get alpha part of RGBA
inline constexpr int qAlpha(Rgb32 rgb) { return rgb >> 24; }

// set RGB value
inline constexpr Rgb32 qRgb(int r, int g, int b)
{
    return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) |
           (b & 0xffu);
}

// set RGBA value
inline constexpr Rgb32 qRgba(int r, int g, int b, int a)
{
    return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) |
           (b & 0xffu);
}

// convert R,G,B to gray 0..255
inline constexpr int qGray(int r, int g, int b)
{
    return (r * 11 + g * 16 + b * 5) / 32;
}

// convert RGB to gray 0..255
inline constexpr int qGray(Rgb32 rgb)
{
    return qGray(qRed(rgb), qGreen(rgb), qBlue(rgb));
}

inline constexpr bool qIsGray(Rgb32 rgb)
{
    return qRed(rgb) == qGreen(rgb) && qRed(rgb) == qBlue(rgb);
}

inline constexpr Rgb32 qPremultiply(Rgb32 x)
{
    const uint32_t a = qAlpha(x);
    uint32_t t = (x & 0xff00ff) * a;
    t = (t + ((t >> 8) & 0xff00ff) + 0x800080) >> 8;
    t &= 0xff00ff;

    x = ((x >> 8) & 0xff) * a;
    x = (x + ((x >> 8) & 0xff) + 0x80);
    x &= 0xff00;
    return x | t | (a << 24);
}

/*******************************************************************************
 * Class Color help functions
 *******************************************************************************/

static uint32_t m2_div_257_floor(uint32_t x) { return (x - (x >> 8)) >> 8; }
static uint32_t m2_div_257(uint32_t x) { return m2_div_257_floor(x + 128); }

#define COLOR_INT_RANGE_CHECK(var)                                   \
    do {                                                             \
        if (var < 0 || var > 255) { var = qMax(0, qMin(var, 255)); } \
    } while (0)

#define COLOR_REAL_RANGE_CHECK(var)                        \
    do {                                                   \
        if (var < float(0.0) || var > float(1.0))          \
        {                                                  \
            var = qMax(float(0.0), qMin(var, float(1.0))); \
        }                                                  \
    } while (0)

/*******************************************************************************
 * Class Color functions
 *******************************************************************************/

/**
 * @brief Construct a new Color:: Color object
 * 
 */
Color::Color() noexcept : cspec(Invalid), cs(USHRT_MAX, 0, 0, 0, 0) {}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param c 
 */
Color::Color(Rgb32 c) noexcept
{
    cspec = Rgb;
    cs.argb.alpha = qAlpha(c) * 0x101;
    cs.argb.red = qRed(c) * 0x101;
    cs.argb.green = qGreen(c) * 0x101;
    cs.argb.blue = qBlue(c) * 0x101;
    cs.argb.pad = 0;
}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 */
Color::Color(int r, int g, int b, int a) noexcept
    : cspec(isRgbaValid(r, g, b, a) ? Rgb : Invalid),
      cs(uint16_t(cspec == Rgb ? a * 0x0101 : 0),
         uint16_t(cspec == Rgb ? r * 0x0101 : 0),
         uint16_t(cspec == Rgb ? g * 0x0101 : 0),
         uint16_t(cspec == Rgb ? b * 0x0101 : 0), 0)
{
}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param name 
 */
Color::Color(const String &name) : Color(fromString(name)) {}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param color 
 */
Color::Color(const Color &color) noexcept {}

/**
 * @brief 
 * 
 * @param color 
 * @return Color& 
 */
Color &Color::operator=(const Color &color) noexcept
{
    // TODO: insert return statement here
}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param color 
 */
Color::Color(Color &&color) noexcept {}

/**
 * @brief 
 * 
 * @param color 
 * @return Color& 
 */
Color &Color::operator=(Color &&color) noexcept
{
    // TODO: insert return statement here
}

/**
 * @brief Generate a random color
 * 
 * @return Color 
 */
Color Color::random() { return Color(); }

/**
 * @brief 
 * @return String 
 */
String Color::name() const
{
    uint32_t n = rgba() | M2_INT64_C(0x100000000);
    return u"#" + String::toString(n, 16).right(8);
}

/**
 * @brief 
 * @return Color::Spec 
 */
Color::Spec Color::spec() const noexcept { return cspec; }

/**
 * @brief 
 * @return int 
 */
int Color::alpha() const noexcept { return m2_div_257(cs.argb.alpha); }

/**
 * @brief 
 * @param  alpha            
 */
void Color::setAlpha(int alpha)
{
    COLOR_INT_RANGE_CHECK(alpha);
    cs.argb.alpha = alpha * 0x101;
}

/**
 * @brief 
 * @return float 
 */
float Color::alphaF() const noexcept
{
    return cs.argb.alpha / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  alpha            
 */
void Color::setAlphaF(float alpha)
{
    COLOR_REAL_RANGE_CHECK(alpha);
    float tmp = alpha * USHRT_MAX;
    cs.argb.alpha = qRound(tmp);
}

/**
 * @brief 
 * @return int 
 */
int Color::red() const noexcept
{
    if (cspec != Invalid && cspec != Rgb) return toRgb().red();
    return m2_div_257(cs.argb.red);
}

/**
 * @brief 
 * @return int 
 */
int Color::green() const noexcept
{
    if (cspec != Invalid && cspec != Rgb) return toRgb().green();
    return m2_div_257(cs.argb.green);
}

/**
 * @brief 
 * @return int 
 */
int Color::blue() const noexcept
{
    if (cspec != Invalid && cspec != Rgb) return toRgb().blue();
    return m2_div_257(cs.argb.blue);
}

/**
 * @brief 
 * @param  red              
 */
void Color::setRed(int red)
{
    COLOR_INT_RANGE_CHECK(red);
    if (cspec != Rgb) setRgb(red, green(), blue(), alpha());
    else
        cs.argb.red = red * 0x101;
}

/**
 * @brief 
 * @param  green            
 */
void Color::setGreen(int green)
{
    COLOR_INT_RANGE_CHECK(green);
    if (cspec != Rgb) setRgb(red(), green, blue(), alpha());
    else
        cs.argb.green = green * 0x101;
}

/**
 * @brief 
 * @param  blue             
 */
void Color::setBlue(int blue)
{
    COLOR_INT_RANGE_CHECK(blue);
    if (cspec != Rgb) setRgb(red(), green(), blue, alpha());
    else
        cs.argb.blue = blue * 0x101;
}

/**
 * @brief 
 * @return float 
 */
float Color::redF() const noexcept
{
    if (cspec == Rgb || cspec == Invalid) return cs.argb.red / float(USHRT_MAX);
    return toRgb().redF();
}

/**
 * @brief 
 * @return float 
 */
float Color::greenF() const noexcept
{
    if (cspec == Rgb || cspec == Invalid)
        return cs.argb.green / float(USHRT_MAX);
    return toRgb().greenF();
}

/**
 * @brief 
 * @return float 
 */
float Color::blueF() const noexcept
{
    if (cspec == Rgb || cspec == Invalid)
        return cs.argb.blue / float(USHRT_MAX);
    return toRgb().blueF();
}

/**
 * @brief 
 * @param  red              
 */
void Color::setRedF(float red)
{
    if (cspec == Rgb && red >= float(0.0) && red <= float(1.0))
        cs.argb.red = qRound(red * USHRT_MAX);
    else
        setRgbF(red, greenF(), blueF(), alphaF());
}

/**
 * @brief 
 * @param  green            
 */
void Color::setGreenF(float green)
{
    if (cspec == Rgb && green >= float(0.0) && green <= float(1.0))
        cs.argb.green = qRound(green * USHRT_MAX);
    else
        setRgbF(redF(), green, blueF(), alphaF());
}

/**
 * @brief 
 * @param  blue             
 */
void Color::setBlueF(float blue)
{
    if (cspec == Rgb && blue >= float(0.0) && blue <= float(1.0))
        cs.argb.blue = qRound(blue * USHRT_MAX);
    else
        setRgbF(redF(), greenF(), blue, alphaF());
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 */
void Color::getRgb(int *r, int *g, int *b, int *a) const
{
    if (!r || !g || !b) return;

    if (cspec != Invalid && cspec != Rgb)
    {
        toRgb().getRgb(r, g, b, a);
        return;
    }

    *r = m2_div_257(cs.argb.red);
    *g = m2_div_257(cs.argb.green);
    *b = m2_div_257(cs.argb.blue);

    if (a) *a = m2_div_257(cs.argb.alpha);
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 */
void Color::setRgb(int r, int g, int b, int a)
{
    if (!isRgbaValid(r, g, b, a))
    {
        invalidate();
        return;
    }

    cspec = Rgb;
    cs.argb.alpha = a * 0x101;
    cs.argb.red = r * 0x101;
    cs.argb.green = g * 0x101;
    cs.argb.blue = b * 0x101;
    cs.argb.pad = 0;
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 */
void Color::getRgbF(float *r, float *g, float *b, float *a) const
{
    if (!r || !g || !b) return;

    if (cspec == Invalid) return;

    if (cspec != Rgb)
    {
        toRgb().getRgbF(r, g, b, a);
        return;
    }

    *r = cs.argb.red / float(USHRT_MAX);
    *g = cs.argb.green / float(USHRT_MAX);
    *b = cs.argb.blue / float(USHRT_MAX);
    if (a) *a = cs.argb.alpha / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 */
void Color::setRgbF(float r, float g, float b, float a)
{
    if (a < float(0.0) || a > float(1.0))
    {
        invalidate();
        return;
    }
    cspec = Rgb;
    cs.argb.red = qRound(r * USHRT_MAX);
    cs.argb.green = qRound(g * USHRT_MAX);
    cs.argb.blue = qRound(b * USHRT_MAX);
    cs.argb.alpha = qRound(a * USHRT_MAX);
    cs.argb.pad = 0;
}

/**
 * @brief 
 * @return Rgb32 
 */
Rgb32 Color::rgba() const noexcept
{
    if (cspec != Invalid && cspec != Rgb) return toRgb().rgba();
    return qRgba(m2_div_257(cs.argb.red), m2_div_257(cs.argb.green),
                 m2_div_257(cs.argb.blue), m2_div_257(cs.argb.alpha));
}

/**
 * @brief 
 * @param  rgba             
 */
void Color::setRgba(Rgb32 rgba) noexcept
{
    cspec = Rgb;
    cs.argb.alpha = qAlpha(rgba) * 0x101;
    cs.argb.red = qRed(rgba) * 0x101;
    cs.argb.green = qGreen(rgba) * 0x101;
    cs.argb.blue = qBlue(rgba) * 0x101;
    cs.argb.pad = 0;
}

/**
 * @brief 
 * @return Rgb32 
 */
Rgb32 Color::rgb() const noexcept
{
    if (cspec != Invalid && cspec != Rgb) return toRgb().rgb();
    return qRgb(m2_div_257(cs.argb.red), m2_div_257(cs.argb.green),
                m2_div_257(cs.argb.blue));
}

/**
 * @brief 
 * @param  rgb              
 */
void Color::setRgb(Rgb32 rgb) noexcept
{
    cspec = Rgb;
    cs.argb.alpha = 0xffff;
    cs.argb.red = qRed(rgb) * 0x101;
    cs.argb.green = qGreen(rgb) * 0x101;
    cs.argb.blue = qBlue(rgb) * 0x101;
    cs.argb.pad = 0;
}

/**
 * @brief 
 * @return int 
 */
int Color::hue() const noexcept { return hsvHue(); }

/**
 * @brief 
 * @return int 
 */
int Color::saturation() const noexcept { return hsvSaturation(); }

/**
 * @brief 
 * @return int 
 */
int Color::hsvHue() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().hue();
    return cs.ahsv.hue == USHRT_MAX ? -1 : cs.ahsv.hue / 100;
}

/**
 * @brief 
 * @return int 
 */
int Color::hsvSaturation() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().saturation();
    return m2_div_257(cs.ahsv.saturation);
}

/**
 * @brief 
 * @return int 
 */
int Color::value() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().value();
    return m2_div_257(cs.ahsv.value);
}

/**
 * @brief 
 * @return float 
 */
float Color::hueF() const noexcept { return hsvHueF(); }

/**
 * @brief 
 * @return float 
 */
float Color::saturationF() const noexcept { return hsvSaturationF(); }

/**
 * @brief 
 * @return float 
 */
float Color::hsvHueF() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().hueF();
    return cs.ahsv.hue == USHRT_MAX ? float(-1.0)
                                    : cs.ahsv.hue / float(36000.0);
}

/**
 * @brief 
 * @return float 
 */
float Color::hsvSaturationF() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().saturationF();
    return cs.ahsv.saturation / float(USHRT_MAX);
}

/**
 * @brief 
 * @return float 
 */
float Color::valueF() const noexcept
{
    if (cspec != Invalid && cspec != Hsv) return toHsv().valueF();
    return cs.ahsv.value / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 */
void Color::getHsv(int *h, int *s, int *v, int *a) const
{
    if (!h || !s || !v) return;

    if (cspec != Invalid && cspec != Hsv)
    {
        toHsv().getHsv(h, s, v, a);
        return;
    }

    *h = cs.ahsv.hue == USHRT_MAX ? -1 : cs.ahsv.hue / 100;
    *s = m2_div_257(cs.ahsv.saturation);
    *v = m2_div_257(cs.ahsv.value);

    if (a) *a = m2_div_257(cs.ahsv.alpha);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 */
void Color::setHsv(int h, int s, int v, int a)
{
    if (h < -1 || (uint32_t) s > 255 || (uint32_t) v > 255 ||
        (uint32_t) a > 255)
    {
        invalidate();
        return;
    }

    cspec = Hsv;
    cs.ahsv.alpha = a * 0x101;
    cs.ahsv.hue = h == -1 ? USHRT_MAX : (h % 360) * 100;
    cs.ahsv.saturation = s * 0x101;
    cs.ahsv.value = v * 0x101;
    cs.ahsv.pad = 0;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 */
void Color::getHsvF(float *h, float *s, float *v, float *a) const
{
    if (!h || !s || !v) return;

    if (cspec != Invalid && cspec != Hsv)
    {
        toHsv().getHsvF(h, s, v, a);
        return;
    }

    *h = cs.ahsv.hue == USHRT_MAX ? float(-1.0) : cs.ahsv.hue / float(36000.0);
    *s = cs.ahsv.saturation / float(USHRT_MAX);
    *v = cs.ahsv.value / float(USHRT_MAX);

    if (a) *a = cs.ahsv.alpha / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 */
void Color::setHsvF(float h, float s, float v, float a)
{
    if (((h < float(0.0) || h > float(1.0)) && h != float(-1.0)) ||
        (s < float(0.0) || s > float(1.0)) ||
        (v < float(0.0) || v > float(1.0)) ||
        (a < float(0.0) || a > float(1.0)))
    {
        return;
    }

    cspec = Hsv;
    cs.ahsv.alpha = qRound(a * USHRT_MAX);
    cs.ahsv.hue = h == float(-1.0) ? USHRT_MAX : qRound(h * 36000);
    cs.ahsv.saturation = qRound(s * USHRT_MAX);
    cs.ahsv.value = qRound(v * USHRT_MAX);
    cs.ahsv.pad = 0;
}

/**
 * @brief 
 * @return int 
 */
int Color::cyan() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().cyan();
    return m2_div_257(cs.acmyk.cyan);
}

/**
 * @brief 
 * @return int 
 */
int Color::magenta() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().magenta();
    return m2_div_257(cs.acmyk.magenta);
}

/**
 * @brief 
 * @return int 
 */
int Color::yellow() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().yellow();
    return m2_div_257(cs.acmyk.yellow);
}

/**
 * @brief 
 * @return int 
 */
int Color::black() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().black();
    return m2_div_257(cs.acmyk.black);
}

/**
 * @brief 
 * @return float 
 */
float Color::cyanF() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().cyanF();
    return cs.acmyk.cyan / float(USHRT_MAX);
}

/**
 * @brief 
 * @return float 
 */
float Color::magentaF() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().magentaF();
    return cs.acmyk.magenta / float(USHRT_MAX);
}

/**
 * @brief 
 * @return float 
 */
float Color::yellowF() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().yellowF();
    return cs.acmyk.yellow / float(USHRT_MAX);
}

/**
 * @brief 
 * @return float 
 */
float Color::blackF() const noexcept
{
    if (cspec != Invalid && cspec != Cmyk) return toCmyk().blackF();
    return cs.acmyk.black / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 */
void Color::getCmyk(int *c, int *m, int *y, int *k, int *a) const
{
    if (!c || !m || !y || !k) return;

    if (cspec != Invalid && cspec != Cmyk)
    {
        toCmyk().getCmyk(c, m, y, k, a);
        return;
    }

    *c = m2_div_257(cs.acmyk.cyan);
    *m = m2_div_257(cs.acmyk.magenta);
    *y = m2_div_257(cs.acmyk.yellow);
    *k = m2_div_257(cs.acmyk.black);

    if (a) *a = m2_div_257(cs.acmyk.alpha);
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 */
void Color::setCmyk(int c, int m, int y, int k, int a)
{
    if (c < 0 || c > 255 || m < 0 || m > 255 || y < 0 || y > 255 || k < 0 ||
        k > 255 || a < 0 || a > 255)
    {
        return;
    }

    cspec = Cmyk;
    cs.acmyk.alpha = a * 0x101;
    cs.acmyk.cyan = c * 0x101;
    cs.acmyk.magenta = m * 0x101;
    cs.acmyk.yellow = y * 0x101;
    cs.acmyk.black = k * 0x101;
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 */
void Color::getCmykF(float *c, float *m, float *y, float *k, float *a) const
{
    if (!c || !m || !y || !k) return;

    if (cspec != Invalid && cspec != Cmyk)
    {
        toCmyk().getCmykF(c, m, y, k, a);
        return;
    }

    *c = cs.acmyk.cyan / float(USHRT_MAX);
    *m = cs.acmyk.magenta / float(USHRT_MAX);
    *y = cs.acmyk.yellow / float(USHRT_MAX);
    *k = cs.acmyk.black / float(USHRT_MAX);

    if (a) *a = cs.acmyk.alpha / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 */
void Color::setCmykF(float c, float m, float y, float k, float a)
{
    if (c < float(0.0) || c > float(1.0) || m < float(0.0) || m > float(1.0) ||
        y < float(0.0) || y > float(1.0) || k < float(0.0) || k > float(1.0) ||
        a < float(0.0) || a > float(1.0))
    {
        return;
    }

    cspec = Cmyk;
    cs.acmyk.alpha = qRound(a * USHRT_MAX);
    cs.acmyk.cyan = qRound(c * USHRT_MAX);
    cs.acmyk.magenta = qRound(m * USHRT_MAX);
    cs.acmyk.yellow = qRound(y * USHRT_MAX);
    cs.acmyk.black = qRound(k * USHRT_MAX);
}

/**
 * @brief 
 * @return int 
 */
int Color::hslHue() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().hslHue();
    return cs.ahsl.hue == USHRT_MAX ? -1 : cs.ahsl.hue / 100;
}

/**
 * @brief 
 * @return int 
 */
int Color::hslSaturation() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().hslSaturation();
    return m2_div_257(cs.ahsl.saturation);
}

/**
 * @brief 
 * @return int 
 */
int Color::lightness() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().lightness();
    return m2_div_257(cs.ahsl.lightness);
}

/**
 * @brief 
 * @return float 
 */
float Color::hslHueF() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().hslHueF();
    return cs.ahsl.hue == USHRT_MAX ? float(-1.0)
                                    : cs.ahsl.hue / float(36000.0);
}

/**
 * @brief 
 * @return float 
 */
float Color::hslSaturationF() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().hslSaturationF();
    return cs.ahsl.saturation / float(USHRT_MAX);
}

/**
 * @brief 
 * @return float 
 */
float Color::lightnessF() const noexcept
{
    if (cspec != Invalid && cspec != Hsl) return toHsl().lightnessF();
    return cs.ahsl.lightness / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 */
void Color::getHsl(int *h, int *s, int *l, int *a) const
{
    if (!h || !s || !l) return;

    if (cspec != Invalid && cspec != Hsl)
    {
        toHsl().getHsl(h, s, l, a);
        return;
    }

    *h = cs.ahsl.hue == USHRT_MAX ? -1 : cs.ahsl.hue / 100;
    *s = m2_div_257(cs.ahsl.saturation);
    *l = m2_div_257(cs.ahsl.lightness);

    if (a) *a = m2_div_257(cs.ahsl.alpha);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 */
void Color::setHsl(int h, int s, int l, int a)
{
    if (h < -1 || (uint32_t) s > 255 || (uint32_t) l > 255 ||
        (uint32_t) a > 255)
    {
        invalidate();
        return;
    }

    cspec = Hsl;
    cs.ahsl.alpha = a * 0x101;
    cs.ahsl.hue = h == -1 ? USHRT_MAX : (h % 360) * 100;
    cs.ahsl.saturation = s * 0x101;
    cs.ahsl.lightness = l * 0x101;
    cs.ahsl.pad = 0;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 */
void Color::getHslF(float *h, float *s, float *l, float *a) const
{
    if (!h || !s || !l) return;

    if (cspec != Invalid && cspec != Hsl)
    {
        toHsl().getHslF(h, s, l, a);
        return;
    }

    *h = cs.ahsl.hue == USHRT_MAX ? float(-1.0) : cs.ahsl.hue / float(36000.0);
    *s = cs.ahsl.saturation / float(USHRT_MAX);
    *l = cs.ahsl.lightness / float(USHRT_MAX);

    if (a) *a = cs.ahsl.alpha / float(USHRT_MAX);
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 */
void Color::setHslF(float h, float s, float l, float a)
{
    if (((h < float(0.0) || h > float(1.0)) && h != float(-1.0)) ||
        (s < float(0.0) || s > float(1.0)) ||
        (l < float(0.0) || l > float(1.0)) ||
        (a < float(0.0) || a > float(1.0)))
    {
        return;
    }

    cspec = Hsl;
    cs.ahsl.alpha = qRound(a * USHRT_MAX);
    cs.ahsl.hue = h == float(-1.0) ? USHRT_MAX : qRound(h * 36000);
    cs.ahsl.saturation = qRound(s * USHRT_MAX);
    cs.ahsl.lightness = qRound(l * USHRT_MAX);
    cs.ahsl.pad = 0;
}

/**
 * @brief 
 * @return Color 
 */
Color Color::toRgb() const noexcept
{
    if (!isValid() || cspec == Rgb) return *this;

    Color color;
    color.cspec = Rgb;
    color.cs.argb.alpha = cs.argb.alpha;
    color.cs.argb.pad = 0;

    switch (cspec)
    {
        case Hsv:
            {
                if (cs.ahsv.saturation == 0 || cs.ahsv.hue == USHRT_MAX)
                {
                    // achromatic case
                    color.cs.argb.red = color.cs.argb.green =
                            color.cs.argb.blue = cs.ahsv.value;
                    break;
                }

                // chromatic case
                const float h = cs.ahsv.hue == 36000 ? 0 : cs.ahsv.hue / 6000.;
                const float s = cs.ahsv.saturation / float(USHRT_MAX);
                const float v = cs.ahsv.value / float(USHRT_MAX);
                const int i = int(h);
                const float f = h - i;
                const float p = v * (float(1.0) - s);

                if (i & 1)
                {
                    const float q = v * (float(1.0) - (s * f));

                    switch (i)
                    {
                        case 1:
                            color.cs.argb.red = qRound(q * USHRT_MAX);
                            color.cs.argb.green = qRound(v * USHRT_MAX);
                            color.cs.argb.blue = qRound(p * USHRT_MAX);
                            break;
                        case 3:
                            color.cs.argb.red = qRound(p * USHRT_MAX);
                            color.cs.argb.green = qRound(q * USHRT_MAX);
                            color.cs.argb.blue = qRound(v * USHRT_MAX);
                            break;
                        case 5:
                            color.cs.argb.red = qRound(v * USHRT_MAX);
                            color.cs.argb.green = qRound(p * USHRT_MAX);
                            color.cs.argb.blue = qRound(q * USHRT_MAX);
                            break;
                    }
                }
                else
                {
                    const float t = v * (float(1.0) - (s * (float(1.0) - f)));

                    switch (i)
                    {
                        case 0:
                            color.cs.argb.red = qRound(v * USHRT_MAX);
                            color.cs.argb.green = qRound(t * USHRT_MAX);
                            color.cs.argb.blue = qRound(p * USHRT_MAX);
                            break;
                        case 2:
                            color.cs.argb.red = qRound(p * USHRT_MAX);
                            color.cs.argb.green = qRound(v * USHRT_MAX);
                            color.cs.argb.blue = qRound(t * USHRT_MAX);
                            break;
                        case 4:
                            color.cs.argb.red = qRound(t * USHRT_MAX);
                            color.cs.argb.green = qRound(p * USHRT_MAX);
                            color.cs.argb.blue = qRound(v * USHRT_MAX);
                            break;
                    }
                }
                break;
            }
        case Hsl:
            {
                if (cs.ahsl.saturation == 0 || cs.ahsl.hue == USHRT_MAX)
                {
                    // achromatic case
                    color.cs.argb.red = color.cs.argb.green =
                            color.cs.argb.blue = cs.ahsl.lightness;
                }
                else if (cs.ahsl.lightness == 0)
                {
                    // lightness 0
                    color.cs.argb.red = color.cs.argb.green =
                            color.cs.argb.blue = 0;
                }
                else
                {
                    // chromatic case
                    const float h =
                            cs.ahsl.hue == 36000 ? 0 : cs.ahsl.hue / 36000.;
                    const float s = cs.ahsl.saturation / float(USHRT_MAX);
                    const float l = cs.ahsl.lightness / float(USHRT_MAX);

                    float temp2;
                    if (l < float(0.5)) temp2 = l * (float(1.0) + s);
                    else
                        temp2 = l + s - (l * s);

                    const float temp1 = (float(2.0) * l) - temp2;
                    float temp3[3] = {h + (float(1.0) / float(3.0)), h,
                                      h - (float(1.0) / float(3.0))};

                    for (int i = 0; i != 3; ++i)
                    {
                        if (temp3[i] < float(0.0)) temp3[i] += float(1.0);
                        else if (temp3[i] > float(1.0))
                            temp3[i] -= float(1.0);

                        const float sixtemp3 = temp3[i] * float(6.0);
                        if (sixtemp3 < float(1.0))
                            color.cs.array[i + 1] = qRound(
                                    (temp1 + (temp2 - temp1) * sixtemp3) *
                                    USHRT_MAX);
                        else if ((temp3[i] * float(2.0)) < float(1.0))
                            color.cs.array[i + 1] = qRound(temp2 * USHRT_MAX);
                        else if ((temp3[i] * float(3.0)) < float(2.0))
                            color.cs.array[i + 1] = qRound(
                                    (temp1 + (temp2 - temp1) *
                                                     (float(2.0) / float(3.0) -
                                                      temp3[i]) *
                                                     float(6.0)) *
                                    USHRT_MAX);
                        else
                            color.cs.array[i + 1] = qRound(temp1 * USHRT_MAX);
                    }
                    color.cs.argb.red =
                            color.cs.argb.red == 1 ? 0 : color.cs.argb.red;
                    color.cs.argb.green =
                            color.cs.argb.green == 1 ? 0 : color.cs.argb.green;
                    color.cs.argb.blue =
                            color.cs.argb.blue == 1 ? 0 : color.cs.argb.blue;
                }
                break;
            }
        case Cmyk:
            {
                const float c = cs.acmyk.cyan / float(USHRT_MAX);
                const float m = cs.acmyk.magenta / float(USHRT_MAX);
                const float y = cs.acmyk.yellow / float(USHRT_MAX);
                const float k = cs.acmyk.black / float(USHRT_MAX);

                color.cs.argb.red = qRound(
                        (float(1.0) - (c * (float(1.0) - k) + k)) * USHRT_MAX);
                color.cs.argb.green = qRound(
                        (float(1.0) - (m * (float(1.0) - k) + k)) * USHRT_MAX);
                color.cs.argb.blue = qRound(
                        (float(1.0) - (y * (float(1.0) - k) + k)) * USHRT_MAX);
                break;
            }
        default:
            break;
    }

    return color;
}

/**
 * @brief 
 * @return Color 
 */
Color Color::toHsv() const noexcept
{
    if (!isValid() || cspec == Hsv) return *this;

    if (cspec != Rgb) return toRgb().toHsv();

    Color color;
    color.cspec = Hsv;
    color.cs.ahsv.alpha = cs.argb.alpha;
    color.cs.ahsv.pad = 0;

    const float r = cs.argb.red / float(USHRT_MAX);
    const float g = cs.argb.green / float(USHRT_MAX);
    const float b = cs.argb.blue / float(USHRT_MAX);
    const float max = qMax3(r, g, b);
    const float min = qMin3(r, g, b);
    const float delta = max - min;
    color.cs.ahsv.value = qRound(max * USHRT_MAX);
    if (qFuzzyIsNull(delta))
    {
        // achromatic case, hue is undefined
        color.cs.ahsv.hue = USHRT_MAX;
        color.cs.ahsv.saturation = 0;
    }
    else
    {
        // chromatic case
        float hue = 0;
        color.cs.ahsv.saturation = qRound((delta / max) * USHRT_MAX);
        if (qFuzzyCompare(r, max)) { hue = ((g - b) / delta); }
        else if (qFuzzyCompare(g, max))
        {
            hue = (float(2.0) + (b - r) / delta);
        }
        else if (qFuzzyCompare(b, max))
        {
            hue = (float(4.0) + (r - g) / delta);
        }
        hue *= float(60.0);
        if (hue < float(0.0)) hue += float(360.0);
        color.cs.ahsv.hue = qRound(hue * 100);
    }

    return color;
}

/**
 * @brief 
 * @return Color 
 */
Color Color::toCmyk() const noexcept
{
    if (!isValid() || cspec == Cmyk) return *this;
    if (cspec != Rgb) return toRgb().toCmyk();

    Color color;
    color.cspec = Cmyk;
    color.cs.acmyk.alpha = cs.argb.alpha;

    if (!cs.argb.red && !cs.argb.green && !cs.argb.blue)
    {
        // Avoid div-by-0 below
        color.cs.acmyk.cyan = 0;
        color.cs.acmyk.magenta = 0;
        color.cs.acmyk.yellow = 0;
        color.cs.acmyk.black = USHRT_MAX;
    }
    else
    {
        // rgb -> cmy
        const float r = cs.argb.red / float(USHRT_MAX);
        const float g = cs.argb.green / float(USHRT_MAX);
        const float b = cs.argb.blue / float(USHRT_MAX);
        float c = float(1.0) - r;
        float m = float(1.0) - g;
        float y = float(1.0) - b;

        // cmy -> cmyk
        const float k = qMin(c, qMin(m, y));
        c = (c - k) / (float(1.0) - k);
        m = (m - k) / (float(1.0) - k);
        y = (y - k) / (float(1.0) - k);

        color.cs.acmyk.cyan = qRound(c * USHRT_MAX);
        color.cs.acmyk.magenta = qRound(m * USHRT_MAX);
        color.cs.acmyk.yellow = qRound(y * USHRT_MAX);
        color.cs.acmyk.black = qRound(k * USHRT_MAX);
    }

    return color;
}

/**
 * @brief 
 * @return Color 
 */
Color Color::toHsl() const noexcept
{
    if (!isValid() || cspec == Hsl) return *this;

    if (cspec != Rgb) return toRgb().toHsl();

    Color color;
    color.cspec = Hsl;
    color.cs.ahsl.alpha = cs.argb.alpha;
    color.cs.ahsl.pad = 0;

    const float r = cs.argb.red / float(USHRT_MAX);
    const float g = cs.argb.green / float(USHRT_MAX);
    const float b = cs.argb.blue / float(USHRT_MAX);
    const float max = qMax3(r, g, b);
    const float min = qMin3(r, g, b);
    const float delta = max - min;
    const float delta2 = max + min;
    const float lightness = float(0.5) * delta2;
    color.cs.ahsl.lightness = qRound(lightness * USHRT_MAX);
    if (qFuzzyIsNull(delta))
    {
        // achromatic case, hue is undefined
        color.cs.ahsl.hue = USHRT_MAX;
        color.cs.ahsl.saturation = 0;
    }
    else
    {
        // chromatic case
        float hue = 0;
        if (lightness < float(0.5))
            color.cs.ahsl.saturation = qRound((delta / delta2) * USHRT_MAX);
        else
            color.cs.ahsl.saturation =
                    qRound((delta / (float(2.0) - delta2)) * USHRT_MAX);
        if (qFuzzyCompare(r, max)) { hue = ((g - b) / delta); }
        else if (qFuzzyCompare(g, max))
        {
            hue = (float(2.0) + (b - r) / delta);
        }
        else if (qFuzzyCompare(b, max))
        {
            hue = (float(4.0) + (r - g) / delta);
        }
        hue *= float(60.0);
        if (hue < float(0.0)) hue += float(360.0);
        color.cs.ahsl.hue = qRound(hue * 100);
    }

    return color;
}

/**
 * @brief 
 * @param  rgb              
 * @return Color 
 */
Color Color::fromRgb(Rgb32 rgb) noexcept
{
    return fromRgb(qRed(rgb), qGreen(rgb), qBlue(rgb));
}

/**
 * @brief 
 * @param  rgba             
 * @return Color 
 */
Color Color::fromRgba(Rgb32 rgba) noexcept
{
    return fromRgb(qRed(rgba), qGreen(rgba), qBlue(rgba), qAlpha(rgba));
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 * @return Color 
 */
Color Color::fromRgb(int r, int g, int b, int a)
{
    if (!isRgbaValid(r, g, b, a)) { return Color(); }

    Color color;
    color.cspec = Rgb;
    color.cs.argb.alpha = a * 0x101;
    color.cs.argb.red = r * 0x101;
    color.cs.argb.green = g * 0x101;
    color.cs.argb.blue = b * 0x101;
    color.cs.argb.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  r                
 * @param  g                
 * @param  b                
 * @param  a                
 * @return Color 
 */
Color Color::fromRgbF(float r, float g, float b, float a)
{
    if (r < float(0.0) || r > float(1.0) || g < float(0.0) || g > float(1.0) ||
        b < float(0.0) || b > float(1.0) || a < float(0.0) || a > float(1.0))
    {
        return Color();
    }

    Color color;
    color.cspec = Rgb;
    color.cs.argb.alpha = qRound(a * USHRT_MAX);
    color.cs.argb.red = qRound(r * USHRT_MAX);
    color.cs.argb.green = qRound(g * USHRT_MAX);
    color.cs.argb.blue = qRound(b * USHRT_MAX);
    color.cs.argb.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 * @return Color 
 */
Color Color::fromHsv(int h, int s, int v, int a)
{
    if (((h < 0 || h >= 360) && h != -1) || s < 0 || s > 255 || v < 0 ||
        v > 255 || a < 0 || a > 255)
    {
        return Color();
    }

    Color color;
    color.cspec = Hsv;
    color.cs.ahsv.alpha = a * 0x101;
    color.cs.ahsv.hue = h == -1 ? USHRT_MAX : (h % 360) * 100;
    color.cs.ahsv.saturation = s * 0x101;
    color.cs.ahsv.value = v * 0x101;
    color.cs.ahsv.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  v                
 * @param  a                
 * @return Color 
 */
Color Color::fromHsvF(float h, float s, float v, float a)
{
    if (((h < float(0.0) || h > float(1.0)) && h != float(-1.0)) ||
        (s < float(0.0) || s > float(1.0)) ||
        (v < float(0.0) || v > float(1.0)) ||
        (a < float(0.0) || a > float(1.0)))
    {
        return Color();
    }

    Color color;
    color.cspec = Hsv;
    color.cs.ahsv.alpha = qRound(a * USHRT_MAX);
    color.cs.ahsv.hue = h == float(-1.0) ? USHRT_MAX : qRound(h * 36000);
    color.cs.ahsv.saturation = qRound(s * USHRT_MAX);
    color.cs.ahsv.value = qRound(v * USHRT_MAX);
    color.cs.ahsv.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 * @return Color 
 */
Color Color::fromCmyk(int c, int m, int y, int k, int a)
{
    if (c < 0 || c > 255 || m < 0 || m > 255 || y < 0 || y > 255 || k < 0 ||
        k > 255 || a < 0 || a > 255)
    {
        return Color();
    }

    Color color;
    color.cspec = Cmyk;
    color.cs.acmyk.alpha = a * 0x101;
    color.cs.acmyk.cyan = c * 0x101;
    color.cs.acmyk.magenta = m * 0x101;
    color.cs.acmyk.yellow = y * 0x101;
    color.cs.acmyk.black = k * 0x101;
    return color;
}

/**
 * @brief 
 * @param  c                
 * @param  m                
 * @param  y                
 * @param  k                
 * @param  a                
 * @return Color 
 */
Color Color::fromCmykF(float c, float m, float y, float k, float a)
{
    if (c < float(0.0) || c > float(1.0) || m < float(0.0) || m > float(1.0) ||
        y < float(0.0) || y > float(1.0) || k < float(0.0) || k > float(1.0) ||
        a < float(0.0) || a > float(1.0))
    {
        return Color();
    }

    Color color;
    color.cspec = Cmyk;
    color.cs.acmyk.alpha = qRound(a * USHRT_MAX);
    color.cs.acmyk.cyan = qRound(c * USHRT_MAX);
    color.cs.acmyk.magenta = qRound(m * USHRT_MAX);
    color.cs.acmyk.yellow = qRound(y * USHRT_MAX);
    color.cs.acmyk.black = qRound(k * USHRT_MAX);
    return color;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 * @return Color 
 */
Color Color::fromHsl(int h, int s, int l, int a)
{
    if (((h < 0 || h >= 360) && h != -1) || s < 0 || s > 255 || l < 0 ||
        l > 255 || a < 0 || a > 255)
    {
        return Color();
    }

    Color color;
    color.cspec = Hsl;
    color.cs.ahsl.alpha = a * 0x101;
    color.cs.ahsl.hue = h == -1 ? USHRT_MAX : (h % 360) * 100;
    color.cs.ahsl.saturation = s * 0x101;
    color.cs.ahsl.lightness = l * 0x101;
    color.cs.ahsl.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  h                
 * @param  s                
 * @param  l                
 * @param  a                
 * @return Color 
 */
Color Color::fromHslF(float h, float s, float l, float a)
{
    if (((h < float(0.0) || h > float(1.0)) && h != float(-1.0)) ||
        (s < float(0.0) || s > float(1.0)) ||
        (l < float(0.0) || l > float(1.0)) ||
        (a < float(0.0) || a > float(1.0)))
    {
        return Color();
    }

    Color color;
    color.cspec = Hsl;
    color.cs.ahsl.alpha = qRound(a * USHRT_MAX);
    color.cs.ahsl.hue = (h == float(-1.0)) ? USHRT_MAX : qRound(h * 36000);
    if (color.cs.ahsl.hue == 36000) color.cs.ahsl.hue = 0;
    color.cs.ahsl.saturation = qRound(s * USHRT_MAX);
    color.cs.ahsl.lightness = qRound(l * USHRT_MAX);
    color.cs.ahsl.pad = 0;
    return color;
}

/**
 * @brief 
 * @param  factor                
 * @return Color 
 */
Color Color::lighter(int factor) const noexcept
{
    if (factor <= 0)// invalid lightness factor
        return *this;
    else if (factor < 100)// makes color darker
        return darker(10000 / factor);

    Color hsv = toHsv();
    int s = hsv.cs.ahsv.saturation;
    uint32_t v = hsv.cs.ahsv.value;

    v = (factor * v) / 100;
    if (v > USHRT_MAX)
    {
        // overflow... adjust saturation
        s -= v - USHRT_MAX;
        if (s < 0) s = 0;
        v = USHRT_MAX;
    }

    hsv.cs.ahsv.saturation = s;
    hsv.cs.ahsv.value = v;

    // convert back to same color spec as original color
    return hsv.convertTo(cspec);
}

/**
 * @brief 
 * @param  factor                
 * @return Color 
 */
Color Color::darker(int factor) const noexcept
{
    if (factor <= 0)// invalid darkness factor
        return *this;
    else if (factor < 100)// makes color lighter
        return lighter(10000 / factor);

    Color hsv = toHsv();
    hsv.cs.ahsv.value = (hsv.cs.ahsv.value * 100) / factor;

    // convert back to same color spec as original color
    return hsv.convertTo(cspec);
}

/**
 * @brief 
 * @param  name             
 * @return Color 
 */
Color Color::fromString(const String &name) noexcept { return Color(); }

/**
 * @brief 
 * @param  color                
 * @return true 
 * @return false 
 */
bool Color::operator==(const Color &color) const noexcept
{
    if (cspec == Hsl && cspec == color.cspec)
    {
        return (cs.argb.alpha == color.cs.argb.alpha &&
                cs.ahsl.hue % 36000 == color.cs.ahsl.hue % 36000 &&
                (qAbs(cs.ahsl.saturation - color.cs.ahsl.saturation) < 50 ||
                 cs.ahsl.lightness == 0 || color.cs.ahsl.lightness == 0 ||
                 cs.ahsl.lightness == USHRT_MAX ||
                 color.cs.ahsl.lightness == USHRT_MAX) &&
                (qAbs(cs.ahsl.lightness - color.cs.ahsl.lightness)) < 50);
    }
    else if (cspec == color.cspec || cspec == Rgb || color.cspec == Rgb)
    {
        return qFuzzyCompare(alphaF(), color.alphaF()) &&
               qFuzzyCompare(redF(), color.redF()) &&
               qFuzzyCompare(greenF(), color.greenF()) &&
               qFuzzyCompare(blueF(), color.blueF());
    }
    else
    {
        return (cspec == color.cspec && cs.argb.alpha == color.cs.argb.alpha &&
                (((cspec == Color::Hsv) &&
                  ((cs.ahsv.hue % 36000) == (color.cs.ahsv.hue % 36000))) ||
                 (cs.ahsv.hue == color.cs.ahsv.hue)) &&
                cs.argb.green == color.cs.argb.green &&
                cs.argb.blue == color.cs.argb.blue &&
                cs.argb.pad == color.cs.argb.pad);
    }
}

/**
 * @brief 
 * @param  c                
 * @return true 
 * @return false 
 */
bool Color::operator!=(const Color &c) const noexcept { return !operator==(c); }

/**
 * @brief 
 */
void Color::invalidate() noexcept
{
    cspec = Invalid;
    cs.argb.alpha = USHRT_MAX;
    cs.argb.red = 0;
    cs.argb.green = 0;
    cs.argb.blue = 0;
    cs.argb.pad = 0;
}

Color Color::convertTo(Spec colorSpec) const noexcept
{
    if (colorSpec == cspec) return *this;
    switch (colorSpec)
    {
        case Rgb:
            return toRgb();
        case Hsv:
            return toHsv();
        case Cmyk:
            return toCmyk();
        case Hsl:
            return toHsl();
        case Invalid:
            break;
    }
    return Color();
}

}// namespace m2
