#include "m2_color.h"

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
    cs.argb.alpha = 0xffff;
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

String Color::name() const { return String(); }

Color::Spec Color::spec() const noexcept { return Spec(); }

int Color::alpha() const noexcept { return 0; }

void Color::setAlpha(int alpha) {}

float Color::alphaF() const noexcept { return 0.0f; }

void Color::setAlphaF(float alpha) {}

int Color::red() const noexcept { return 0; }

int Color::green() const noexcept { return 0; }

int Color::blue() const noexcept { return 0; }

void Color::setRed(int red) {}

void Color::setGreen(int green) {}

void Color::setBlue(int blue) {}

float Color::redF() const noexcept { return 0.0f; }

float Color::greenF() const noexcept { return 0.0f; }

float Color::blueF() const noexcept { return 0.0f; }

void Color::setRedF(float red) {}

void Color::setGreenF(float green) {}

void Color::setBlueF(float blue) {}

void Color::getRgb(int *r, int *g, int *b, int *a) const {}

void Color::setRgb(int r, int g, int b, int a) {}

void Color::getRgbF(float *r, float *g, float *b, float *a) const {}

void Color::setRgbF(float r, float g, float b, float a) {}

Rgb32 Color::rgba() const noexcept { return Rgb32(); }

void Color::setRgba(Rgb32 rgba) noexcept {}

Rgb32 Color::rgb() const noexcept { return Rgb32(); }

void Color::setRgb(Rgb32 rgb) noexcept {}

int Color::hue() const noexcept { return 0; }

int Color::saturation() const noexcept { return 0; }

int Color::hsvHue() const noexcept { return 0; }

int Color::hsvSaturation() const noexcept { return 0; }

int Color::value() const noexcept { return 0; }

float Color::hueF() const noexcept { return 0.0f; }

float Color::saturationF() const noexcept { return 0.0f; }

float Color::hsvHueF() const noexcept { return 0.0f; }

float Color::hsvSaturationF() const noexcept { return 0.0f; }

float Color::valueF() const noexcept { return 0.0f; }

void Color::getHsv(int *h, int *s, int *v, int *a) const {}

void Color::setHsv(int h, int s, int v, int a) {}

void Color::getHsvF(float *h, float *s, float *v, float *a) const {}

void Color::setHsvF(float h, float s, float v, float a) {}

int Color::cyan() const noexcept { return 0; }

int Color::magenta() const noexcept { return 0; }

int Color::yellow() const noexcept { return 0; }

int Color::black() const noexcept { return 0; }

float Color::cyanF() const noexcept { return 0.0f; }

float Color::magentaF() const noexcept { return 0.0f; }

float Color::yellowF() const noexcept { return 0.0f; }

float Color::blackF() const noexcept { return 0.0f; }

void Color::getCmyk(int *c, int *m, int *y, int *k, int *a) const {}

void Color::setCmyk(int c, int m, int y, int k, int a) {}

void Color::getCmykF(float *c, float *m, float *y, float *k, float *a) const {}

void Color::setCmykF(float c, float m, float y, float k, float a) {}

int Color::hslHue() const noexcept { return 0; }

int Color::hslSaturation() const noexcept { return 0; }

int Color::lightness() const noexcept { return 0; }

float Color::hslHueF() const noexcept { return 0.0f; }

float Color::hslSaturationF() const noexcept { return 0.0f; }

float Color::lightnessF() const noexcept { return 0.0f; }

void Color::getHsl(int *h, int *s, int *l, int *a) const {}

void Color::setHsl(int h, int s, int l, int a) {}

void Color::getHslF(float *h, float *s, float *l, float *a) const {}

void Color::setHslF(float h, float s, float l, float a) {}

Color Color::toRgb() const noexcept { return Color(); }

Color Color::toHsv() const noexcept { return Color(); }

Color Color::toCmyk() const noexcept { return Color(); }

Color Color::toHsl() const noexcept { return Color(); }

Color Color::toExtendedRgb() const noexcept { return Color(); }

Color Color::fromRgb(Rgb32 rgb) noexcept { return Color(); }

Color Color::fromRgba(Rgb32 rgba) noexcept { return Color(); }

Color Color::fromRgb(int r, int g, int b, int a) { return Color(); }

Color Color::fromRgbF(float r, float g, float b, float a) { return Color(); }

Color Color::fromHsv(int h, int s, int v, int a) { return Color(); }

Color Color::fromHsvF(float h, float s, float v, float a) { return Color(); }

Color Color::fromCmyk(int c, int m, int y, int k, int a) { return Color(); }

Color Color::fromCmykF(float c, float m, float y, float k, float a)
{
    return Color();
}

Color Color::fromHsl(int h, int s, int l, int a) { return Color(); }

Color Color::fromHslF(float h, float s, float l, float a) { return Color(); }

Color Color::lighter(int f) const noexcept { return Color(); }

Color Color::darker(int f) const noexcept { return Color(); }

Color Color::fromString(const String &name) noexcept { return Color(); }

bool Color::operator==(const Color &c) const noexcept { return false; }

bool Color::operator!=(const Color &c) const noexcept { return false; }

void Color::invalidate() noexcept {}

}// namespace m2
