#include <color.h>
#include <mathhelp.h>

namespace m2 {
Color::Color() noexcept
{
    A = 0xff;
    R = 00;
    G = 00;
    B = 00;
}

Color::Color(unsigned int c) noexcept
{
    A = 0xff;
    R = c >> 16;
    G = c >> 8;
    B = c & 0xff;
}

Color::Color(int c) noexcept
{
    A = c >> 24;
    R = c >> 16;
    G = c >> 8;
    B = c & 0xff;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept
{
    R = r;
    G = g;
    B = b;
    A = a;
}

Color::Color(const Color &color) noexcept
{
    Argb = color.Argb;
}

Color &Color::operator=(const Color &color) noexcept
{
    Argb = color.Argb;
    return *this;
}

Color Color::Random()
{
    return Color();
}

Color Color::RandomHSV()
{
    return Color();
}

Color Color::FromCSS(const char *css)
{
    return Color();
}

Color Color::FromARGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    Color col;
    col.R = r;
    col.G = g;
    col.B = b;
    col.A = a;
    return col;
}

Color Color::FromARGBF(double r, double g, double b, double a)
{
    Color color;
    if (a < 0.0 || a > 1.0)
    {
        return Color::White;
    }

    color.R = Math::Round(r * 0xff);
    color.G = Math::Round(g * 0xff);
    color.B = Math::Round(b * 0xff);
    color.A = Math::Round(a * 0xff);

    return color;
}

Color Color::FromCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k)
{
    if (c < 0 || c > 255 || m < 0 || m > 255 || y < 0 || y > 255 || k < 0 || k > 255)
    {
        return Color();
    }
    // 换算成0-1.0
    const double cyan = c / double(0xff);
    const double magenta = m / double(0xff);
    const double yellow = y / double(0xff);
    const double black = k / double(0xff);

    Color color;
    color.R = Math::Round((double(1.0) - (cyan * (double(1.0) - black) + black)) * 0xff);
    color.G = Math::Round((double(1.0) - (magenta * (double(1.0) - black) + black)) * 0xff);
    color.B = Math::Round((double(1.0) - (yellow * (double(1.0) - black) + black)) * 0xff);
    color.A = 0xff;
    return color;
}

Color Color::FromCMYKF(double c, double m, double y, double k)
{
    if (c < double(0.0) || c > double(1.0) || m < double(0.0) || m > double(1.0) || y < double(0.0) ||
        y > double(1.0) || k < double(0.0) || k > double(1.0))
    {
        return Color();
    }

    // 换算成255
    const unsigned char _cyan = Math::Round(c * 0xff);
    const unsigned char _magenta = Math::Round(m * 0xff);
    const unsigned char _yellow = Math::Round(y * 0xff);
    const unsigned char _black = Math::Round(k * 0xff);

    // 重新规划为0-1.0
    const double cyan = _cyan / double(0xff);
    const double magenta = _magenta / double(0xff);
    const double yellow = _yellow / double(0xff);
    const double black = _black / double(0xff);

    Color color;
    color.R = Math::Round((double(1.0) - (cyan * (double(1.0) - black) + black)) * 0xff);
    color.G = Math::Round((double(1.0) - (magenta * (double(1.0) - black) + black)) * 0xff);
    color.B = Math::Round((double(1.0) - (yellow * (double(1.0) - black) + black)) * 0xff);
    color.A = 0xff;
    return color;
}

Color Color::FromHSV(int h, int s, int v, unsigned char a)
{
    if (((h < 0 || h >= 360) && h != -1) || s < 0 || s > 255 || v < 0 || v > 255 || a < 0 || a > 255)
    {
        return Color();
    }

    unsigned char _alpha = a;
    unsigned char _hue = h == -1 ? 0xff : (h % 360) * 100;
    unsigned char _saturation = s;
    unsigned char _value = v;
}

Color Color::FromHSV(float h, float s, float v, float a)
{
    if (((h < double(0.0) || h > double(1.0)) && h != double(-1.0)) ||
        (s < double(0.0) || s > double(1.0)) || (v < double(0.0) || v > double(1.0)) ||
        (a < double(0.0) || a > double(1.0)))
    {
        return Color();
    }

    unsigned char _alpha = Math::Round(a * 0xff);
    unsigned char _hue = h == double(-1.0) ? 0xff : Math::Round(h * 36000);
    unsigned char _saturation = Math::Round(s * 0xff);
    unsigned char _value = Math::Round(v * 0xff);
}

int Color::ToGray(unsigned char r, unsigned char g, unsigned char b)
{
    return (r * 11 + g * 16 + b * 5) / 32;
}

bool Color::ToHSV(float *h, float *s, float *v) const
{
    const double r = R / double(0xff);
    const double g = G / double(0xff);
    const double b = B / double(0xff);
    const double max = Math::Max3(r, g, b);
    const double min = Math::Min3(r, g, b);
    const double delta = max - min;

    unsigned char value = Math::Round(max * 0xff);
    unsigned char hue = 0;
    unsigned char saturation = 0;
    if (Math::FuzzyIsNull(delta))
    {
        hue = 0xff;
        saturation = 0;
    }
    else
    {
        double th = 0;
        saturation = Math::Round((delta / max) * 0xff);
        if (Math::FuzzyCompare(r, max))
            th = (g - b) / delta;
        else if (Math::FuzzyCompare(g, max))
            th = (double(2.0) + (b - r)) / delta;
        else if (Math::FuzzyCompare(b, max))
            th = (double(4.0) + (r - g)) / delta;
        th *= double(60.0);
        if (th < double(0.0))
            th += double(360.0);
        hue = Math::Round(th * 100);
    }

    *h = hue == 0xff ? double(-1.0) : hue / double(36000.0);
    *s = saturation / double(0xff);
    *v = value / double(0xff);

    return true;
}

static unsigned int div_257_floor(unsigned int x)
{
    return (x - (x >> 8)) >> 8;
}
static unsigned int div_257(unsigned int x)
{
    return div_257_floor(x + 128);
}

bool Color::ToCMKY(unsigned int *c, unsigned int *m, unsigned int *y, unsigned int *k) const
{
    unsigned short cyan, magenta, yellow, black;
    if (!R && !G && !B)
    {
        cyan = 0;
        magenta = 0;
        yellow = 0;
        black = 0xffff;
    }
    else
    {
        const double r = R / double(0xff);
        const double g = G / double(0xff);
        const double b = B / double(0xff);
        double c = double(1.0) - r;
        double m = double(1.0) - g;
        double y = double(1.0) - b;

        // cmy -> cmyk
        const double k = Math::Min(c, Math::Min(m, y));
        c = (c - k) / (double(1.0) - k);
        m = (m - k) / (double(1.0) - k);
        y = (y - k) / (double(1.0) - k);

        cyan = Math::Round(c * 0xff);
        magenta = Math::Round(m * 0xff);
        yellow = Math::Round(y * 0xff);
        black = Math::Round(k * 0xff);
    }

    *c = div_257(cyan);
    *m = div_257(magenta);
    *y = div_257(yellow);
    *k = div_257(black);

    return true;
}

bool Color::ToHSL(float *h, float *s, float *l, int *a) const
{
    return true;
}

void Color::SetCOLORREF(unsigned int rgb, unsigned char a)
{
}

unsigned int Color::ToCOLORREF() const
{
    return 0;
}

float Color::RedF() const noexcept
{
    return R / double(0xff);
}

float Color::GreenF() const noexcept
{
    return G / double(0xff);
}

float Color::BlueF() const noexcept
{
    return B / double(0xff);
}

float Color::AlphaF() const noexcept
{
    return A / double(0xff);
}

Color &Color::RedF(float r) noexcept
{
    if (r >= double(0.0) && r <= double(1.0))
    {
        R = Math::Round(r * 0xff);
    }
    return *this;
}

Color &Color::GreenF(float g) noexcept
{
    if (g >= double(0.0) && g <= double(1.0))
    {
        G = Math::Round(g * 0xff);
    }
    return *this;
}

Color &Color::BlueF(float b) noexcept
{
    if (b >= double(0.0) && b <= double(1.0))
    {
        B = Math::Round(b * 0xff);
    }
    return *this;
}

Color &Color::AlphaF(float a) noexcept
{
    if (a >= double(0.0) && a <= double(1.0))
    {
        A = Math::Round(a * 0xff);
    }
    return *this;
}

Color &Color::operator=(unsigned int &argb) noexcept
{
    A = 0xff;
    R = argb >> 16;
    G = argb >> 8;
    B = argb & 0xff;
    return *this;
}

Color &Color::operator=(int &argb) noexcept
{
    A = argb >> 24;
    R = argb >> 16;
    G = argb >> 8;
    B = argb & 0xff;
    return *this;
}

bool Color::operator==(const Color &color) const noexcept
{
    return Argb == color.Argb;
}

bool Color::operator!=(const Color &color) const noexcept
{
    return Argb != color.Argb;
}

Color::operator unsigned int() const noexcept
{
    return Argb;
}

Color::operator int() const noexcept
{
    return int(Argb);
}

Color &Color::Blend(const Color &color, PorterDuffBlendMode mode)
{
    switch (mode)
    {
        case eCLEAR:
            {
                break;
            }
        case eSRC:
            {
                break;
            }
        case eDST:
            {
                break;
            }
        case eSRC_OVER:
            {
                break;
            }
        case eDST_OVER:
            {
                break;
            }
        case eSRC_IN:
            {
                break;
            }
        case eDST_IN:
            {
                break;
            }
        case eSRC_OUT:
            {
                break;
            }
        case eDST_OUT:
            {
                break;
            }
        case eSRC_ATOP:
            {
                break;
            }
        case eDST_ATOP:
            {
                break;
            }
        case eXOR:
            {
                break;
            }
        case eDARKEN:
            {
                break;
            }
        case eLIGHTEN:
            {
                break;
            }
        case eMULTIPLY:
            {
                break;
            }
        case eSCREEN:
            {
                break;
            }

        default:
            break;
    }
    return *this;
}
Color &Color::Blend(const Color &color, PhotoShopColorBlendMode mode)
{
    return *this;
}

}// namespace m2
