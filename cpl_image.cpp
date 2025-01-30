/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "cpl_image.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

namespace CPL {

struct CaseInsensitiveHash
{
    size_t operator()(const std::string &str) const
    {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                       ::tolower);
        return std::hash<std::string>()(lower_str);
    }
};

struct CaseInsensitiveEqual
{
    bool operator()(const std::string &str1, const std::string &str2) const
    {
        return std::equal(
                str1.begin(), str1.end(), str2.begin(), str2.end(),
                [](char c1, char c2) { return tolower(c1) == tolower(c2); });
    }
};

/// w3c color: https://www.w3.org/TR/css-color-3/#named-colors
static std::unordered_map<std::string, Color, CaseInsensitiveHash,
                          CaseInsensitiveEqual>
        g_w3c_colors = {
                {           "AliceBlue",            Color::AliceBlue},
                {        "AntiqueWhite",         Color::AntiqueWhite},
                {                "Aqua",                 Color::Aqua},
                {          "Aquamarine",           Color::Aquamarine},
                {               "Azure",                Color::Azure},
                {               "Beige",                Color::Beige},
                {              "Bisque",               Color::Bisque},
                {               "Black",                Color::Black},
                {      "BlanchedAlmond",       Color::BlanchedAlmond},
                {                "Blue",                 Color::Blue},
                {          "BlueViolet",           Color::BlueViolet},
                {               "Brown",                Color::Brown},
                {           "BurlyWood",            Color::BurlyWood},
                {           "CadetBlue",            Color::CadetBlue},
                {          "Chartreuse",           Color::Chartreuse},
                {           "Chocolate",            Color::Chocolate},
                {               "Coral",                Color::Coral},
                {      "CornflowerBlue",       Color::CornflowerBlue},
                {            "Cornsilk",             Color::Cornsilk},
                {             "Crimson",              Color::Crimson},
                {                "Cyan",                 Color::Cyan},
                {            "DarkBlue",             Color::DarkBlue},
                {            "DarkCyan",             Color::DarkCyan},
                {       "DarkGoldenrod",        Color::DarkGoldenrod},
                {            "DarkGray",             Color::DarkGray},
                {           "DarkGreen",            Color::DarkGreen},
                {           "DarkKhaki",            Color::DarkKhaki},
                {         "DarkMagenta",          Color::DarkMagenta},
                {      "DarkOliveGreen",       Color::DarkOliveGreen},
                {          "DarkOrange",           Color::DarkOrange},
                {          "DarkOrchid",           Color::DarkOrchid},
                {             "DarkRed",              Color::DarkRed},
                {          "DarkSalmon",           Color::DarkSalmon},
                {        "DarkSeaGreen",         Color::DarkSeaGreen},
                {       "DarkSlateBlue",        Color::DarkSlateBlue},
                {       "DarkSlateGray",        Color::DarkSlateGray},
                {       "DarkTurquoise",        Color::DarkTurquoise},
                {          "DarkViolet",           Color::DarkViolet},
                {            "DeepPink",             Color::DeepPink},
                {         "DeepSkyBlue",          Color::DeepSkyBlue},
                {             "DimGray",              Color::DimGray},
                {          "DodgerBlue",           Color::DodgerBlue},
                {            "Feldspar",             Color::Feldspar},
                {           "Firebrick",            Color::Firebrick},
                {         "FloralWhite",          Color::FloralWhite},
                {         "ForestGreen",          Color::ForestGreen},
                {             "Fuchsia",              Color::Fuchsia},
                {           "Gainsboro",            Color::Gainsboro},
                {          "GhostWhite",           Color::GhostWhite},
                {                "Gold",                 Color::Gold},
                {           "Goldenrod",            Color::Goldenrod},
                {                "Gray",                 Color::Gray},
                {               "Green",                Color::Green},
                {         "GreenYellow",          Color::GreenYellow},
                {            "Honeydew",             Color::Honeydew},
                {             "HotPink",              Color::HotPink},
                {           "IndianRed",            Color::IndianRed},
                {              "Indigo",               Color::Indigo},
                {               "Ivory",                Color::Ivory},
                {               "Khaki",                Color::Khaki},
                {            "Lavender",             Color::Lavender},
                {       "LavenderBlush",        Color::LavenderBlush},
                {           "LawnGreen",            Color::LawnGreen},
                {        "LemonChiffon",         Color::LemonChiffon},
                {           "LightBlue",            Color::LightBlue},
                {          "LightCoral",           Color::LightCoral},
                {           "LightCyan",            Color::LightCyan},
                {"LightGoldenrodYellow", Color::LightGoldenrodYellow},
                {           "LightGray",            Color::LightGray},
                {          "LightGreen",           Color::LightGreen},
                {           "LightPink",            Color::LightPink},
                {         "LightSalmon",          Color::LightSalmon},
                {       "LightSeaGreen",        Color::LightSeaGreen},
                {        "LightSkyBlue",         Color::LightSkyBlue},
                {      "LightSlateBlue",       Color::LightSlateBlue},
                {      "LightSlateGray",       Color::LightSlateGray},
                {      "LightSteelBlue",       Color::LightSteelBlue},
                {         "LightYellow",          Color::LightYellow},
                {                "Lime",                 Color::Lime},
                {           "LimeGreen",            Color::LimeGreen},
                {               "Linen",                Color::Linen},
                {             "Magenta",              Color::Magenta},
                {              "Maroon",               Color::Maroon},
                {    "MediumAquamarine",     Color::MediumAquamarine},
                {          "MediumBlue",           Color::MediumBlue},
                {        "MediumOrchid",         Color::MediumOrchid},
                {        "MediumPurple",         Color::MediumPurple},
                {      "MediumSeaGreen",       Color::MediumSeaGreen},
                {     "MediumSlateBlue",      Color::MediumSlateBlue},
                {   "MediumSpringGreen",    Color::MediumSpringGreen},
                {     "MediumTurquoise",      Color::MediumTurquoise},
                {     "MediumVioletRed",      Color::MediumVioletRed},
                {        "MidnightBlue",         Color::MidnightBlue},
                {           "MintCream",            Color::MintCream},
                {           "MistyRose",            Color::MistyRose},
                {            "Moccasin",             Color::Moccasin},
                {         "NavajoWhite",          Color::NavajoWhite},
                {                "Navy",                 Color::Navy},
                {             "OldLace",              Color::OldLace},
                {               "Olive",                Color::Olive},
                {           "OliveDrab",            Color::OliveDrab},
                {              "Orange",               Color::Orange},
                {           "OrangeRed",            Color::OrangeRed},
                {              "Orchid",               Color::Orchid},
                {       "PaleGoldenrod",        Color::PaleGoldenrod},
                {           "PaleGreen",            Color::PaleGreen},
                {       "PaleTurquoise",        Color::PaleTurquoise},
                {       "PaleVioletRed",        Color::PaleVioletRed},
                {          "PapayaWhip",           Color::PapayaWhip},
                {           "PeachPuff",            Color::PeachPuff},
                {                "Peru",                 Color::Peru},
                {                "Pink",                 Color::Pink},
                {                "Plum",                 Color::Plum},
                {          "PowderBlue",           Color::PowderBlue},
                {              "Purple",               Color::Purple},
                {                 "Red",                  Color::Red},
                {           "RosyBrown",            Color::RosyBrown},
                {           "RoyalBlue",            Color::RoyalBlue},
                {         "SaddleBrown",          Color::SaddleBrown},
                {              "Salmon",               Color::Salmon},
                {          "SandyBrown",           Color::SandyBrown},
                {            "SeaGreen",             Color::SeaGreen},
                {            "SeaShell",             Color::SeaShell},
                {              "Sienna",               Color::Sienna},
                {              "Silver",               Color::Silver},
                {             "SkyBlue",              Color::SkyBlue},
                {           "SlateBlue",            Color::SlateBlue},
                {           "SlateGray",            Color::SlateGray},
                {                "Snow",                 Color::Snow},
                {         "SpringGreen",          Color::SpringGreen},
                {           "SteelBlue",            Color::SteelBlue},
                {                 "Tan",                  Color::Tan},
                {                "Teal",                 Color::Teal},
                {             "Thistle",              Color::Thistle},
                {              "Tomato",               Color::Tomato},
                {         "Transparent",          Color::Transparent},
                {           "Turquoise",            Color::Turquoise},
                {              "Violet",               Color::Violet},
                {           "VioletRed",            Color::VioletRed},
                {               "Wheat",                Color::Wheat},
                {               "White",                Color::White},
                {          "WhiteSmoke",           Color::WhiteSmoke},
                {              "Yellow",               Color::Yellow},
                {         "YellowGreen",          Color::YellowGreen}
};

static std::unordered_map<Color, std::string> g_w3c_colors_reverse = {
        {           Color::AliceBlue,            "AliceBlue"},
        {        Color::AntiqueWhite,         "AntiqueWhite"},
        {                Color::Aqua,                 "Aqua"},
        {          Color::Aquamarine,           "Aquamarine"},
        {               Color::Azure,                "Azure"},
        {               Color::Beige,                "Beige"},
        {              Color::Bisque,               "Bisque"},
        {               Color::Black,                "Black"},
        {      Color::BlanchedAlmond,       "BlanchedAlmond"},
        {                Color::Blue,                 "Blue"},
        {          Color::BlueViolet,           "BlueViolet"},
        {               Color::Brown,                "Brown"},
        {           Color::BurlyWood,            "BurlyWood"},
        {           Color::CadetBlue,            "CadetBlue"},
        {          Color::Chartreuse,           "Chartreuse"},
        {           Color::Chocolate,            "Chocolate"},
        {               Color::Coral,                "Coral"},
        {      Color::CornflowerBlue,       "CornflowerBlue"},
        {            Color::Cornsilk,             "Cornsilk"},
        {             Color::Crimson,              "Crimson"},
        {                Color::Cyan,                 "Cyan"},
        {            Color::DarkBlue,             "DarkBlue"},
        {            Color::DarkCyan,             "DarkCyan"},
        {       Color::DarkGoldenrod,        "DarkGoldenrod"},
        {            Color::DarkGray,             "DarkGray"},
        {           Color::DarkGreen,            "DarkGreen"},
        {           Color::DarkKhaki,            "DarkKhaki"},
        {         Color::DarkMagenta,          "DarkMagenta"},
        {      Color::DarkOliveGreen,       "DarkOliveGreen"},
        {          Color::DarkOrange,           "DarkOrange"},
        {          Color::DarkOrchid,           "DarkOrchid"},
        {             Color::DarkRed,              "DarkRed"},
        {          Color::DarkSalmon,           "DarkSalmon"},
        {        Color::DarkSeaGreen,         "DarkSeaGreen"},
        {       Color::DarkSlateBlue,        "DarkSlateBlue"},
        {       Color::DarkSlateGray,        "DarkSlateGray"},
        {       Color::DarkTurquoise,        "DarkTurquoise"},
        {          Color::DarkViolet,           "DarkViolet"},
        {            Color::DeepPink,             "DeepPink"},
        {         Color::DeepSkyBlue,          "DeepSkyBlue"},
        {             Color::DimGray,              "DimGray"},
        {          Color::DodgerBlue,           "DodgerBlue"},
        {            Color::Feldspar,             "Feldspar"},
        {           Color::Firebrick,            "Firebrick"},
        {         Color::FloralWhite,          "FloralWhite"},
        {         Color::ForestGreen,          "ForestGreen"},
        {             Color::Fuchsia,              "Fuchsia"},
        {           Color::Gainsboro,            "Gainsboro"},
        {          Color::GhostWhite,           "GhostWhite"},
        {                Color::Gold,                 "Gold"},
        {           Color::Goldenrod,            "Goldenrod"},
        {                Color::Gray,                 "Gray"},
        {               Color::Green,                "Green"},
        {         Color::GreenYellow,          "GreenYellow"},
        {            Color::Honeydew,             "Honeydew"},
        {             Color::HotPink,              "HotPink"},
        {           Color::IndianRed,            "IndianRed"},
        {              Color::Indigo,               "Indigo"},
        {               Color::Ivory,                "Ivory"},
        {               Color::Khaki,                "Khaki"},
        {            Color::Lavender,             "Lavender"},
        {       Color::LavenderBlush,        "LavenderBlush"},
        {           Color::LawnGreen,            "LawnGreen"},
        {        Color::LemonChiffon,         "LemonChiffon"},
        {           Color::LightBlue,            "LightBlue"},
        {          Color::LightCoral,           "LightCoral"},
        {           Color::LightCyan,            "LightCyan"},
        {Color::LightGoldenrodYellow, "LightGoldenrodYellow"},
        {           Color::LightGray,            "LightGray"},
        {          Color::LightGreen,           "LightGreen"},
        {           Color::LightPink,            "LightPink"},
        {         Color::LightSalmon,          "LightSalmon"},
        {       Color::LightSeaGreen,        "LightSeaGreen"},
        {        Color::LightSkyBlue,         "LightSkyBlue"},
        {      Color::LightSlateBlue,       "LightSlateBlue"},
        {      Color::LightSlateGray,       "LightSlateGray"},
        {      Color::LightSteelBlue,       "LightSteelBlue"},
        {         Color::LightYellow,          "LightYellow"},
        {                Color::Lime,                 "Lime"},
        {           Color::LimeGreen,            "LimeGreen"},
        {               Color::Linen,                "Linen"},
        {             Color::Magenta,              "Magenta"},
        {              Color::Maroon,               "Maroon"},
        {    Color::MediumAquamarine,     "MediumAquamarine"},
        {          Color::MediumBlue,           "MediumBlue"},
        {        Color::MediumOrchid,         "MediumOrchid"},
        {        Color::MediumPurple,         "MediumPurple"},
        {      Color::MediumSeaGreen,       "MediumSeaGreen"},
        {     Color::MediumSlateBlue,      "MediumSlateBlue"},
        {   Color::MediumSpringGreen,    "MediumSpringGreen"},
        {     Color::MediumTurquoise,      "MediumTurquoise"},
        {     Color::MediumVioletRed,      "MediumVioletRed"},
        {        Color::MidnightBlue,         "MidnightBlue"},
        {           Color::MintCream,            "MintCream"},
        {           Color::MistyRose,            "MistyRose"},
        {            Color::Moccasin,             "Moccasin"},
        {         Color::NavajoWhite,          "NavajoWhite"},
        {                Color::Navy,                 "Navy"},
        {             Color::OldLace,              "OldLace"},
        {               Color::Olive,                "Olive"},
        {           Color::OliveDrab,            "OliveDrab"},
        {              Color::Orange,               "Orange"},
        {           Color::OrangeRed,            "OrangeRed"},
        {              Color::Orchid,               "Orchid"},
        {       Color::PaleGoldenrod,        "PaleGoldenrod"},
        {           Color::PaleGreen,            "PaleGreen"},
        {       Color::PaleTurquoise,        "PaleTurquoise"},
        {       Color::PaleVioletRed,        "PaleVioletRed"},
        {          Color::PapayaWhip,           "PapayaWhip"},
        {           Color::PeachPuff,            "PeachPuff"},
        {                Color::Peru,                 "Peru"},
        {                Color::Pink,                 "Pink"},
        {                Color::Plum,                 "Plum"},
        {          Color::PowderBlue,           "PowderBlue"},
        {              Color::Purple,               "Purple"},
        {                 Color::Red,                  "Red"},
        {           Color::RosyBrown,            "RosyBrown"},
        {           Color::RoyalBlue,            "RoyalBlue"},
        {         Color::SaddleBrown,          "SaddleBrown"},
        {              Color::Salmon,               "Salmon"},
        {          Color::SandyBrown,           "SandyBrown"},
        {            Color::SeaGreen,             "SeaGreen"},
        {            Color::SeaShell,             "SeaShell"},
        {              Color::Sienna,               "Sienna"},
        {              Color::Silver,               "Silver"},
        {             Color::SkyBlue,              "SkyBlue"},
        {           Color::SlateBlue,            "SlateBlue"},
        {           Color::SlateGray,            "SlateGray"},
        {                Color::Snow,                 "Snow"},
        {         Color::SpringGreen,          "SpringGreen"},
        {           Color::SteelBlue,            "SteelBlue"},
        {                 Color::Tan,                  "Tan"},
        {                Color::Teal,                 "Teal"},
        {             Color::Thistle,              "Thistle"},
        {              Color::Tomato,               "Tomato"},
        {         Color::Transparent,          "Transparent"},
        {           Color::Turquoise,            "Turquoise"},
        {              Color::Violet,               "Violet"},
        {           Color::VioletRed,            "VioletRed"},
        {               Color::Wheat,                "Wheat"},
        {               Color::White,                "White"},
        {          Color::WhiteSmoke,           "WhiteSmoke"},
        {              Color::Yellow,               "Yellow"},
        {         Color::YellowGreen,          "YellowGreen"}
};


Color::Color() : Argb(0xFF000000) {}

Color::Color(unsigned int c) : Argb(c) {}

Color::Color(int c) : Argb(static_cast<unsigned int>(c)) {}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : R(r), G(g), B(b), A(a)
{
}

Color::Color(const Color &rhs) : Argb(rhs.Argb) {}

Color::Color(const Color &rhs, unsigned char a)
    : R(rhs.R), G(rhs.G), B(rhs.B), A(a)
{
}

void Color::FlipRGB() { std::swap(R, B); }

Color Color::FromCSS(const char *csscolor)
{
    if (!csscolor || csscolor[0] != '#') { return Color(); }

    size_t len = std::strlen(csscolor);
    if (len == 7)
    {// #RRGGBB
        int r, g, b;
        if (std::sscanf(csscolor, "#%02x%02x%02x", &r, &g, &b) == 3)
        {
            return Color(r, g, b);
        }
    }
    else if (len == 4)
    {// #RGB
        int r, g, b;
        if (std::sscanf(csscolor, "#%1x%1x%1x", &r, &g, &b) == 3)
        {
            return Color(r * 17, g * 17, b * 17);
        }
    }

    return Color();
}

#ifdef _WIN32

Color Color::FromCOLORREF(unsigned int rgb) { return Color(); }

void Color::SetCOLORREF(unsigned int rgb, unsigned char a) {}

unsigned int Color::ToCOLORREF() const { return 0; }

#endif

Color CPL::Color::FromARGB(unsigned char r, unsigned char g, unsigned char b,
                           unsigned char a)
{
    return Color(r, g, b, a);
}

Color CPL::Color::FromCMYK(unsigned char c, unsigned char m, unsigned char y,
                           unsigned char k)
{
    if (c > 255 || m > 255 || y > 255 || k > 255)
    {
        std::cerr << "Invalid CMYK values, returning default color (black).\n";
        return Color(0, 0, 0, 255);
    }

    unsigned char r = static_cast<unsigned char>(255 * (1.0 - c / 255.0) *
                                                 (1.0 - k / 255.0));
    unsigned char g = static_cast<unsigned char>(255 * (1.0 - m / 255.0) *
                                                 (1.0 - k / 255.0));
    unsigned char b = static_cast<unsigned char>(255 * (1.0 - y / 255.0) *
                                                 (1.0 - k / 255.0));
    return Color(r, g, b, 255);
}

Color Color::FromARGBF(float r, float g, float b, float a)
{
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;

    if (g < 0.0f) g = 0.0f;
    if (g > 1.0f) g = 1.0f;

    if (b < 0.0f) b = 0.0f;
    if (b > 1.0f) b = 1.0f;

    if (a < 0.0f) a = 0.0f;
    if (a > 1.0f) a = 1.0f;

    unsigned char ir = static_cast<unsigned char>(r * 255);
    unsigned char ig = static_cast<unsigned char>(g * 255);
    unsigned char ib = static_cast<unsigned char>(b * 255);
    unsigned char ia = static_cast<unsigned char>(a * 255);

    return Color(ir, ig, ib, ia);
}

Color Color::FromColor(const Color &rhs, unsigned char a)
{
    return Color(rhs.R, rhs.G, rhs.B, a);
}

Color Color::FromColorF(const Color &rhs, float a)
{
    if (a < 0.0f) a = 0.0f;
    if (a > 1.0f) a = 1.0f;

    return Color(rhs.R, rhs.G, rhs.B, static_cast<unsigned char>(a * 255));
}

Color Color::FromName(const char *strName)
{
    std::string name(strName);
    auto it = g_w3c_colors.find(name);
    if (it != g_w3c_colors.end()) { return it->second; }
    return Color::Black;
}

std::string Color::Name() const
{
    auto it = g_w3c_colors_reverse.find(Argb);
    if (it != g_w3c_colors_reverse.end()) return it->second;
    return "Unknown";
};

bool Color::IsKnownColor() const
{
    auto it = g_w3c_colors_reverse.find(Argb);
    if (it != g_w3c_colors_reverse.end()) { return true; }
    return false;
}

Color Color::Random()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, 255);
    return Color(dis(gen), dis(gen), dis(gen));
}

Color Color::FromHSV(float h, float s, float v, unsigned char a)
{
    h = std::fmod(h, 360.0f);
    if (h < 0) h += 360.0f;

    s = std::clamp(s, 0.0f, 1.0f);
    v = std::clamp(v, 0.0f, 1.0f);

    float c = v * s;
    float x = c * (1 - std::fabs(std::fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    float r_f = 0, g_f = 0, b_f = 0;
    if (h < 60) { r_f = c, g_f = x, b_f = 0; }
    else if (h < 120) { r_f = x, g_f = c, b_f = 0; }
    else if (h < 180) { r_f = 0, g_f = c, b_f = x; }
    else if (h < 240) { r_f = 0, g_f = x, b_f = c; }
    else if (h < 300) { r_f = x, g_f = 0, b_f = c; }
    else { r_f = c, g_f = 0, b_f = x; }

    return Color(static_cast<unsigned char>((r_f + m) * 255),
                 static_cast<unsigned char>((g_f + m) * 255),
                 static_cast<unsigned char>((b_f + m) * 255), a);
}

std::string Color::ToHtml() const
{
    std::stringstream ss;
    ss << "#" << std::setw(2) << std::setfill('0') << std::hex << (int) R
       << std::setw(2) << std::setfill('0') << std::hex << (int) G
       << std::setw(2) << std::setfill('0') << std::hex << (int) B;
    return ss.str();
}

std::string Color::ToHtmlRGBA() const
{
    std::stringstream ss;
    ss << "#" << std::setw(2) << std::setfill('0') << std::hex << (int) R
       << std::setw(2) << std::setfill('0') << std::hex << (int) G
       << std::setw(2) << std::setfill('0') << std::hex << (int) B
       << std::setw(2) << std::setfill('0') << std::hex << (int) A;
    return ss.str();
}

unsigned int Color::ToUInt() const { return Argb; }

bool Color::ToHSV(float *h, float *s, float *v) const { return false; }

int Color::ToInt() const { return static_cast<int>(Argb); }

void Color::SetARGB(unsigned char r, unsigned char g, unsigned char b,
                    unsigned char a)
{
    A = a;
    R = r;
    G = g;
    B = b;
}

void Color::SetARGBF(float r, float g, float b, float a) {}

void Color::SetARGB(unsigned int argb) { Argb = argb; }

void Color::SetHSV(float h, float s, float v, unsigned char a) {}

float Color::RedF() const { return 0.0f; }

float Color::GreenF() const { return 0.0f; }

float Color::AlphaF() const { return 0.0f; }

float Color::BlueF() const { return 0.0f; }

Color &Color::RedF(float r) { return *this; }

Color &Color::GreenF(float g) { return *this; }

Color &Color::AlphaF(float a) { return *this; }

Color &Color::BlueF(float b) { return *this; }

Color &Color::Blend(const Color &source, PorterDuffModel model)
{
    return *this;
}

Color &Color::operator=(unsigned int &argb) { return *this; }

Color &Color::operator=(int &argb) { return *this; }

Color &Color::operator=(const Color &rhs) { return *this; }

bool Color::operator==(const Color &c) const { return false; }

bool Color::operator!=(const Color &c) const { return !(*this == c); }

Color::operator unsigned int() const { return Argb; }

Color::operator int() const { return static_cast<int>(Argb); }

}// namespace CPL
