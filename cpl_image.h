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

#pragma once

#include <cpl_exports.h>
#include <string>

namespace CPL {

/// \brief PorterDuff blend color blending modes.
/// \details A - represents the pixel's transparency (alpha channel).
/// \details s - represents the source pixel to be blended.
/// \details d - represents the destination pixel to blend with.
/// \details r - represents the resulting blended pixel.
/// \details F - represents the factor applied to either C or A channels.
enum class PorterDuffModel
{
    /// \brief Fs = Fd = 0
    /// \details The source and destination pixels are completely transparent. No color is blended.
    eCLEAR,

    /// \brief Fs = 1, Fd = 0
    /// \details The source pixel is fully visible while the destination is fully transparent.
    eSRC,

    /// \brief Fs = 0, Fd = 1
    /// \details The destination pixel is fully visible while the source is fully transparent.
    eDST,

    /// \brief Fs = 1, Fd = (1 - As)
    /// \details The source is fully visible, and the destination is blended by its transparency.
    eSRC_OVER,

    /// \brief Fs = (1 - Ad), Fd = 1
    /// \details The destination is fully visible, and the source is blended by its transparency.
    eDST_OVER,

    /// \brief Fs = Ad, Fd = 0
    /// \details The source is blended by the destination's alpha, with no destination color.
    eSRC_IN,

    /// \brief Fs = 0, Fd = As
    /// \details The destination is blended by the source's alpha, with no source color.
    eDST_IN,

    /// \brief Fs = (1 - Ad), Fd = 0
    /// \details The source is blended by the inverse of the destination's alpha, with no destination color.
    eSRC_OUT,

    /// \brief Fs = 0, Fd = (1 - As)
    /// \details The destination is blended by the inverse of the source's alpha, with no source color.
    eDST_OUT,

    /// \brief Fs = Ad, Fd = (1 - As)
    /// \details The source and destination are blended by each other's transparency.
    eSRC_ATOP,

    /// \brief Fs = (1 - Ad), Fd = As
    /// \details The destination is blended by the source's alpha, and the source by the destination's alpha.
    eDST_ATOP,

    /// \brief Fs = (1 - Ad), Fd = (1 - As)
    /// \details The source and destination are blended by the inverse of each other's alpha.
    eXOR,

    /// \brief [As + Ad - As * Ad, Cs * (1 - Ad) + Cd * (1 - As) + min(Cs, Cd)]
    /// \details Darken mode: picks the darker of the two source and destination pixels based on their color channels.
    eDARKEN,

    /// \brief [As + Ad - As * Ad, Cs * (1 - Ad) + Cd * (1 - As) + max(Cs, Cd)]
    /// \details Lighten mode: picks the lighter of the two source and destination pixels based on their color channels.
    eLIGHTEN,

    /// \brief [As * Ad, Cs * Cd]
    /// \details Multiply mode: multiplies the source and destination color values to darken the result.
    eMULTIPLY,

    /// \brief [As + Ad - As * Ad, Cs + Cd - Cs * Cd]
    /// \details Screen mode: inverts, multiplies, and then inverts again to lighten the result.
    eSCREEN,
};

/// \brief A color struct that holds RGBA or ARGB color data and provides various methods for color manipulation.
struct CPL_API Color
{
    /// \brief Default constructor.
    /// \details Initializes the color to fully transparent (0,0,0,0).
    Color();

    /// \brief Constructs a color from a 32-bit integer.
    /// \param c The 32-bit integer representing the color value.
    Color(unsigned int c);

    /// \brief Constructs a color from a signed 32-bit integer.
    /// \param c The signed 32-bit integer representing the color value.
    Color(int c);

    /// \brief Constructs a color from individual RGBA components.
    /// \param r Red channel [0, 255]
    /// \param g Green channel [0, 255]
    /// \param b Blue channel [0, 255]
    /// \param a Alpha (opacity) channel [0, 255], defaults to 255 (opaque).
    Color(unsigned char r, unsigned char g, unsigned char b,
          unsigned char a = 255);

    /// \brief Copy constructor.
    /// \param rhs The color to copy.
    Color(const Color &rhs);

    /// \brief Constructs a new color with a modified alpha channel.
    /// \param rhs The original color to copy.
    /// \param a The new alpha value.
    Color(const Color &rhs, unsigned char a);

    /// \brief Swaps the Red and Blue channels in the RGB color model.
    /// \details This is commonly used for changing between different color formats.
    void FlipRGB();

    /// \brief Constructs a color from a CSS color string (e.g., "#RRGGBB").
    /// \param csscolor The CSS color string.
    /// \return A Color object representing the specified color.
    static Color FromCSS(const char *csscolor);

#ifdef _WIN32
    /// \brief Constructs a color from a Win32 RGB color value.
    /// \param rgb The RGB value in Win32 format.
    /// \return A Color object representing the RGB color.
    static Color FromCOLORREF(unsigned int rgb);

    /// \brief Sets the color from a Win32 RGB color value.
    /// \param rgb The RGB color value.
    /// \param a The alpha value, defaults to 255 (opaque).
    void SetCOLORREF(unsigned int rgb, unsigned char a = 255);

    /// \brief Converts the color to a Win32 RGB color value.
    /// \return A Win32 RGB color value representing the color.
    unsigned int ToCOLORREF() const;
#endif

    /// \brief Constructs a color from individual ARGB components.
    /// \param r Red channel [0, 255]
    /// \param g Green channel [0, 255]
    /// \param b Blue channel [0, 255]
    /// \param a Alpha (opacity) channel [0, 255], defaults to 255 (opaque).
    /// \return A Color object representing the ARGB color.
    static Color FromARGB(unsigned char r, unsigned char g, unsigned char b,
                          unsigned char a = 255);

    /// \brief Constructs a color from CMYK components.
    /// \param c Cyan channel [0, 100]
    /// \param m Magenta channel [0, 100]
    /// \param y Yellow channel [0, 100]
    /// \param k Black channel [0, 100]
    /// \return A Color object representing the CMYK color.
    static Color FromCMYK(unsigned char c, unsigned char m, unsigned char y,
                          unsigned char k);

    /// \brief Constructs a color from floating-point RGBA components.
    /// \param r Red channel [0.0, 1.0]
    /// \param g Green channel [0.0, 1.0]
    /// \param b Blue channel [0.0, 1.0]
    /// \param a Alpha (opacity) channel [0.0, 1.0], defaults to 1.0 (opaque).
    /// \return A Color object representing the floating-point RGBA color.
    static Color FromARGBF(float r, float g, float b, float a = 1.0f);

    /// \brief Modifies the alpha of an existing color.
    /// \param rhs The color to modify.
    /// \param a The new alpha value.
    /// \return A new Color object with the same RGB channels but modified alpha.
    static Color FromColor(const Color &rhs, unsigned char a);

    /// \brief Modifies the alpha of an existing color.
    /// \param rhs The color to modify.
    /// \param a The new alpha value in floating-point [0.0, 1.0].
    /// \return A new Color object with the same RGB channels but modified alpha.
    static Color FromColorF(const Color &rhs, float a);

    /// \brief Constructs a color from a known color name.
    /// \param strName The name of a known color (e.g., "red", "blue").
    /// \return A Color object representing the known color.
    static Color FromName(const char *strName);

    /// \brief Returns the name of the color if it is a known color.
    /// \return The name of the color (e.g., "red", "blue") if known, or an empty string if not.
    std::string Name() const;

    /// \brief Checks if the color is one of the known colors.
    /// \return True if the color is known, otherwise false.
    bool IsKnownColor() const;

    /// \brief Generates a random color.
    /// \return A randomly generated Color object.
    static Color Random();

    /// \brief Constructs a color from HSV components.
    /// \param h Hue [0, 360] (degrees)
    /// \param s Saturation [0, 1.0]
    /// \param v Value (brightness) [0, 1.0]
    /// \param a Alpha (opacity) channel [0, 255], defaults to 255 (opaque).
    /// \return A Color object representing the HSV color.
    static Color FromHSV(float h, float s, float v, unsigned char a = 255);

    /// \brief Converts the color to a hex string in the form #RRGGBB.
    /// \return A string representing the color in HTML format.
    std::string ToHtml() const;

    /// \brief Converts the color to a CSS rgba() string.
    /// \return A string representing the color in CSS rgba() format.
    std::string ToHtmlRGBA() const;

    /// \brief Converts the color to a 32-bit unsigned integer.
    /// \return A 32-bit unsigned integer representing the color.
    unsigned int ToUInt() const;

    /// \brief Converts the color to HSV format and then back to RGB.
    /// \param h The hue, in the range [0, 360) (float).
    /// \param s The saturation, in the range [0, 1.0] (float).
    /// \param v The brightness, in the range [0, 1.0] (float).
    /// \return True if the conversion was successful.
    bool ToHSV(float *h, float *s, float *v) const;

    /// \brief Converts the color to a 32-bit signed integer.
    /// \return A 32-bit signed integer representing the color.
    int ToInt() const;

    /// \brief Sets the color from individual ARGB components.
    /// \param r Red channel [0, 255]
    /// \param g Green channel [0, 255]
    /// \param b Blue channel [0, 255]
    /// \param a Alpha channel [0, 255], defaults to 255 (opaque).
    void SetARGB(unsigned char r, unsigned char g, unsigned char b,
                 unsigned char a = 255);

    /// \brief Sets the color from individual ARGB components in floating-point values.
    /// \param r Red channel [0.0, 1.0]
    /// \param g Green channel [0.0, 1.0]
    /// \param b Blue channel [0.0, 1.0]
    /// \param a Alpha channel [0.0, 1.0], defaults to 1.0 (opaque).
    void SetARGBF(float r, float g, float b, float a = 1.0f);

    /// \brief Sets the color from a 32-bit ARGB value.
    /// \param argb The ARGB value.
    void SetARGB(unsigned int argb);

    /// \brief Sets the color from HSV components.
    /// \param h Hue [0, 360] (degrees)
    /// \param s Saturation [0, 1.0]
    /// \param v Value (brightness) [0, 1.0]
    /// \param a Alpha channel [0, 255], defaults to 255 (opaque).
    void SetHSV(float h, float s, float v, unsigned char a = 255);

    /// \brief Gets the red channel as a floating-point value.
    /// \return The red channel value in the range [0.0, 1.0].
    float RedF() const;

    /// \brief Gets the green channel as a floating-point value.
    /// \return The green channel value in the range [0.0, 1.0].
    float GreenF() const;

    /// \brief Gets the alpha (opacity) channel as a floating-point value.
    /// \return The alpha value in the range [0.0, 1.0].
    float AlphaF() const;

    /// \brief Gets the blue channel as a floating-point value.
    /// \return The blue channel value in the range [0.0, 1.0].
    float BlueF() const;

    /// \brief Sets the red channel as a floating-point value.
    /// \return A reference to this Color object for chaining.
    Color &RedF(float r);

    /// \brief Sets the green channel as a floating-point value.
    /// \return A reference to this Color object for chaining.
    Color &GreenF(float g);

    /// \brief Sets the alpha (opacity) channel as a floating-point value.
    /// \return A reference to this Color object for chaining.
    Color &AlphaF(float a);

    /// \brief Sets the blue channel as a floating-point value.
    /// \return A reference to this Color object for chaining.
    Color &BlueF(float b);

    /// \brief Blends the source color into this color using the specified PorterDuff mode.
    /// \param source The source color to blend.
    /// \param model The PorterDuff blending model to use.
    /// \return A reference to this Color object after blending.
    Color &Blend(const Color &source, PorterDuffModel model);

    /// \brief Assignment operator.
    /// \param argb The ARGB color value to assign.
    /// \return A reference to this Color object for chaining.
    Color &operator=(unsigned int &argb);

    /// \brief Assignment operator.
    /// \param argb The signed ARGB color value to assign.
    /// \return A reference to this Color object for chaining.
    Color &operator=(int &argb);

    /// \brief Assignment operator.
    /// \param rhs The color to copy.
    /// \return A reference to this Color object for chaining.
    Color &operator=(const Color &rhs);

    /// \brief Equality comparison operator.
    /// \param c The color to compare to.
    /// \return True if the colors are equal, otherwise false.
    bool operator==(const Color &c) const;

    /// \brief Inequality comparison operator.
    /// \param c The color to compare to.
    /// \return True if the colors are not equal, otherwise false.
    bool operator!=(const Color &c) const;

    /// \brief Converts the color to an unsigned integer.
    /// \return A 32-bit unsigned integer representing the color.
    operator unsigned int() const;

    /// \brief Converts the color to a signed integer.
    /// \return A 32-bit signed integer representing the color.
    operator int() const;

    /// \brief Union to represent the color in ARGB or RGBA format.
    union
    {
        /// \brief ARGB color value.
        unsigned int Argb;

        /// \brief Separate channels: Blue, Green, Red, and Alpha.
        struct
        {
            unsigned char B, G, R, A;
        };
    };

    enum
    {
        AliceBlue = 0xFFF0F8FF,
        AntiqueWhite = 0xFFFAEBD7,
        Aqua = 0xFF00FFFF,
        Aquamarine = 0xFF7FFFD4,
        Azure = 0xFFF0FFFF,
        Beige = 0xFFF5F5DC,
        Bisque = 0xFFFFE4C4,
        Black = 0xFF000000,
        BlanchedAlmond = 0xFFFFEBCD,
        Blue = 0xFF0000FF,
        BlueViolet = 0xFF8A2BE2,
        Brown = 0xFFA52A2A,
        BurlyWood = 0xFFDEB887,
        CadetBlue = 0xFF5F9EA0,
        Chartreuse = 0xFF7FFF00,
        Chocolate = 0xFFD2691E,
        Coral = 0xFFFF7F50,
        CornflowerBlue = 0xFF6495ED,
        Cornsilk = 0xFFFFF8DC,
        Crimson = 0xFFDC143C,
        Cyan = 0xFF00FFFF,
        DarkBlue = 0xFF00008B,
        DarkCyan = 0xFF008B8B,
        DarkGoldenrod = 0xFFB8860B,
        DarkGray = 0xFFA9A9A9,
        DarkGreen = 0xFF006400,
        DarkKhaki = 0xFFBDB76B,
        DarkMagenta = 0xFF8B008B,
        DarkOliveGreen = 0xFF556B2F,
        DarkOrange = 0xFFFF8C00,
        DarkOrchid = 0xFF9932CC,
        DarkRed = 0xFF8B0000,
        DarkSalmon = 0xFFE9967A,
        DarkSeaGreen = 0xFF8FBC8B,
        DarkSlateBlue = 0xFF483D8B,
        DarkSlateGray = 0xFF2F4F4F,
        DarkTurquoise = 0xFF00CED1,
        DarkViolet = 0xFF9400D3,
        DeepPink = 0xFFFF1493,
        DeepSkyBlue = 0xFF00BFFF,
        DimGray = 0xFF696969,
        DodgerBlue = 0xFF1E90FF,
        Feldspar = 0xFFD19275,
        Firebrick = 0xFFB22222,
        FloralWhite = 0xFFFFFAF0,
        ForestGreen = 0xFF228B22,
        Fuchsia = 0xFFFF00FF,
        Gainsboro = 0xFFDCDCDC,
        GhostWhite = 0xFFF8F8FF,
        Gold = 0xFFFFD700,
        Goldenrod = 0xFFDAA520,
        Gray = 0xFF808080,
        Green = 0xFF00FF00,
        GreenYellow = 0xFFADFF2F,
        Honeydew = 0xFFF0FFF0,
        HotPink = 0xFFFF69B4,
        IndianRed = 0xFFCD5C5C,
        Indigo = 0xFF4B0082,
        Ivory = 0xFFFFFFF0,
        Khaki = 0xFFF0E68C,
        Lavender = 0xFFE6E6FA,
        LavenderBlush = 0xFFFFF0F5,
        LawnGreen = 0xFF7CFC00,
        LemonChiffon = 0xFFFFFACD,
        LightBlue = 0xFFADD8E6,
        LightCoral = 0xFFF08080,
        LightCyan = 0xFFE0FFFF,
        LightGoldenrodYellow = 0xFFFAFAD2,
        LightGray = 0xFFD3D3D3,
        LightGrey = 0xFFD3D3D3,
        LightGreen = 0xFF90EE90,
        LightPink = 0xFFFFB6C1,
        LightSalmon = 0xFFFFA07A,
        LightSeaGreen = 0xFF20B2AA,
        LightSkyBlue = 0xFF87CEFA,
        LightSlateBlue = 0xFF8470FF,
        LightSlateGray = 0xFF778899,
        LightSteelBlue = 0xFFB0C4DE,
        LightYellow = 0xFFFFFFE0,
        Lime = 0xFF00FF00,
        LimeGreen = 0xFF32CD32,
        Linen = 0xFFFAF0E6,
        Magenta = 0xFFFF00FF,
        Maroon = 0xFF800000,
        MediumAquamarine = 0xFF66CDAA,
        MediumBlue = 0xFF0000CD,
        MediumOrchid = 0xFFBA55D3,
        MediumPurple = 0xFF9370DB,
        MediumSeaGreen = 0xFF3CB371,
        MediumSlateBlue = 0xFF7B68EE,
        MediumSpringGreen = 0xFF00FA9A,
        MediumTurquoise = 0xFF48D1CC,
        MediumVioletRed = 0xFFC71585,
        MidnightBlue = 0xFF191970,
        MintCream = 0xFFF5FFFA,
        MistyRose = 0xFFFFE4E1,
        Moccasin = 0xFFFFE4B5,
        NavajoWhite = 0xFFFFDEAD,
        Navy = 0xFF000080,
        OldLace = 0xFFFDF5E6,
        Olive = 0xFF808000,
        OliveDrab = 0xFF6B8E23,
        Orange = 0xFFFFA500,
        OrangeRed = 0xFFFF4500,
        Orchid = 0xFFDA70D6,
        PaleGoldenrod = 0xFFEEE8AA,
        PaleGreen = 0xFF98FB98,
        PaleTurquoise = 0xFFAFEEEE,
        PaleVioletRed = 0xFFDB7093,
        PapayaWhip = 0xFFFFEFD5,
        PeachPuff = 0xFFFFDAB9,
        Peru = 0xFFCD853F,
        Pink = 0xFFFFC0CB,
        Plum = 0xFFDDA0DD,
        PowderBlue = 0xFFB0E0E6,
        Purple = 0xFF800080,
        Red = 0xFFFF0000,
        RosyBrown = 0xFFBC8F8F,
        RoyalBlue = 0xFF4169E1,
        SaddleBrown = 0xFF8B4513,
        Salmon = 0xFFFA8072,
        SandyBrown = 0xFFF4A460,
        SeaGreen = 0xFF2E8B57,
        SeaShell = 0xFFFFF5EE,
        Sienna = 0xFFA0522D,
        Silver = 0xFFC0C0C0,
        SkyBlue = 0xFF87CEEB,
        SlateBlue = 0xFF6A5ACD,
        SlateGray = 0xFF708090,
        Snow = 0xFFFFFAFA,
        SpringGreen = 0xFF00FF7F,
        SteelBlue = 0xFF4682B4,
        Tan = 0xFFD2B48C,
        Teal = 0xFF008080,
        Thistle = 0xFFD8BFD8,
        Tomato = 0xFFFF6347,
        Transparent = 0x00FFFFFF,
        Turquoise = 0xFF40E0D0,
        Violet = 0xFFEE82EE,
        VioletRed = 0xFFD02090,
        Wheat = 0xFFF5DEB3,
        White = 0xFFFFFFFF,
        WhiteSmoke = 0xFFF5F5F5,
        Yellow = 0xFFFFFF00,
        YellowGreen = 0xFF9ACD32,
    };
};

}// namespace CPL
