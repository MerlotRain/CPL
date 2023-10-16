#include "m2_color.h"

namespace m2 {
/**
 * @brief Construct a new Color:: Color object
 * 
 */
Color::Color() noexcept {}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param c 
 */
Color::Color(rgb32 c) noexcept {}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 */
Color::Color(int r, int g, int b, int a) noexcept {}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param name 
 */
Color::Color(const char *name) {}

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

rgb32 Color::rgba() const noexcept { return rgb32(); }

void Color::setRgba(rgb32 rgba) noexcept {}

rgb32 Color::rgb() const noexcept { return rgb32(); }

void Color::setRgb(rgb32 rgb) noexcept {}

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

Color Color::fromRgb(rgb32 rgb) noexcept { return Color(); }

Color Color::fromRgba(rgb32 rgba) noexcept { return Color(); }

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

bool Color::operator==(const Color &c) const noexcept { return false; }

bool Color::operator!=(const Color &c) const noexcept { return false; }

}// namespace m2
