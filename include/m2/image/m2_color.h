/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_COLOR_H_
#define M2_COLOR_H_

#include <preconfig.h>

namespace m2 {

class String;
typedef unsigned int rgb32;
class M2_API Color
{
public:
    enum Spec
    {
        Invalid,
        Rgb,
        Hsv,
        Cmyk,
        Hsl,
        ExtendedRgb
    };

    Color() noexcept;
    Color(rgb32 c) noexcept;
    Color(int r, int g, int b, int a = 255) noexcept;
    Color(const char *name);

    Color(const Color &color) noexcept;
    Color &operator=(const Color &color) noexcept;
    Color(Color &&color) noexcept;
    Color &operator=(Color &&color) noexcept;

    static Color random();

    String name() const;
    Spec spec() const noexcept;

    int alpha() const noexcept;
    void setAlpha(int alpha);

    float alphaF() const noexcept;
    void setAlphaF(float alpha);

    int red() const noexcept;
    int green() const noexcept;
    int blue() const noexcept;
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    float redF() const noexcept;
    float greenF() const noexcept;
    float blueF() const noexcept;
    void setRedF(float red);
    void setGreenF(float green);
    void setBlueF(float blue);

    void getRgb(int *r, int *g, int *b, int *a = nullptr) const;
    void setRgb(int r, int g, int b, int a = 255);

    void getRgbF(float *r, float *g, float *b, float *a = nullptr) const;
    void setRgbF(float r, float g, float b, float a = 1.0);


    rgb32 rgba() const noexcept;
    void setRgba(rgb32 rgba) noexcept;

    rgb32 rgb() const noexcept;
    void setRgb(rgb32 rgb) noexcept;

    int hue() const noexcept;
    int saturation() const noexcept;
    int hsvHue() const noexcept;
    int hsvSaturation() const noexcept;
    int value() const noexcept;

    float hueF() const noexcept;
    float saturationF() const noexcept;
    float hsvHueF() const noexcept;
    float hsvSaturationF() const noexcept;
    float valueF() const noexcept;

    void getHsv(int *h, int *s, int *v, int *a = nullptr) const;
    void setHsv(int h, int s, int v, int a = 255);

    void getHsvF(float *h, float *s, float *v, float *a = nullptr) const;
    void setHsvF(float h, float s, float v, float a = 1.0);

    int cyan() const noexcept;
    int magenta() const noexcept;
    int yellow() const noexcept;
    int black() const noexcept;

    float cyanF() const noexcept;
    float magentaF() const noexcept;
    float yellowF() const noexcept;
    float blackF() const noexcept;

    void getCmyk(int *c, int *m, int *y, int *k, int *a = nullptr) const;
    void setCmyk(int c, int m, int y, int k, int a = 255);

    void getCmykF(float *c, float *m, float *y, float *k,
                  float *a = nullptr) const;
    void setCmykF(float c, float m, float y, float k, float a = 1.0);

    int hslHue() const noexcept;
    int hslSaturation() const noexcept;
    int lightness() const noexcept;

    float hslHueF() const noexcept;
    float hslSaturationF() const noexcept;
    float lightnessF() const noexcept;

    void getHsl(int *h, int *s, int *l, int *a = nullptr) const;
    void setHsl(int h, int s, int l, int a = 255);

    void getHslF(float *h, float *s, float *l, float *a = nullptr) const;
    void setHslF(float h, float s, float l, float a = 1.0);

    Color toRgb() const noexcept;
    Color toHsv() const noexcept;
    Color toCmyk() const noexcept;
    Color toHsl() const noexcept;
    Color toExtendedRgb() const noexcept;

    static Color fromRgb(rgb32 rgb) noexcept;
    static Color fromRgba(rgb32 rgba) noexcept;

    static Color fromRgb(int r, int g, int b, int a = 255);
    static Color fromRgbF(float r, float g, float b, float a = 1.0);

    static Color fromHsv(int h, int s, int v, int a = 255);
    static Color fromHsvF(float h, float s, float v, float a = 1.0);

    static Color fromCmyk(int c, int m, int y, int k, int a = 255);
    static Color fromCmykF(float c, float m, float y, float k, float a = 1.0);

    static Color fromHsl(int h, int s, int l, int a = 255);
    static Color fromHslF(float h, float s, float l, float a = 1.0);

    [[nodiscard]] Color lighter(int f = 150) const noexcept;
    [[nodiscard]] Color darker(int f = 200) const noexcept;

    bool operator==(const Color &c) const noexcept;
    bool operator!=(const Color &c) const noexcept;

    // clang-format off
    enum
    {
        AliceBlue            = 0xFFF0F8FF,
        AntiqueWhite         = 0xFFFAEBD7,
        Aqua                 = 0xFF00FFFF,
        Aquamarine           = 0xFF7FFFD4,
        Azure                = 0xFFF0FFFF,
        Beige                = 0xFFF5F5DC,
        Bisque               = 0xFFFFE4C4,
        Black                = 0xFF000000,
        BlanchedAlmond       = 0xFFFFEBCD,
        Blue                 = 0xFF0000FF,
        BlueViolet           = 0xFF8A2BE2,
        Brown                = 0xFFA52A2A,
        BurlyWood            = 0xFFDEB887,
        CadetBlue            = 0xFF5F9EA0,
        Chartreuse           = 0xFF7FFF00,
        Chocolate            = 0xFFD2691E,
        Coral                = 0xFFFF7F50,
        CornflowerBlue       = 0xFF6495ED,
        Cornsilk             = 0xFFFFF8DC,
        Crimson              = 0xFFDC143C,
        Cyan                 = 0xFF00FFFF,
        DarkBlue             = 0xFF00008B,
        DarkCyan             = 0xFF008B8B,
        DarkGoldenRod        = 0xFFB8860B,
        DarkGray             = 0xFFA9A9A9,
        DarkGreen            = 0xFF006400,
        DarkKhaki            = 0xFFBDB76B,
        DarkMagenta          = 0xFF8B008B,
        DarkOliveGreen       = 0xFF556B2F,
        Darkorange           = 0xFFFF8C00,
        DarkOrchid           = 0xFF9932CC,
        DarkRed              = 0xFF8B0000,
        DarkSalmon           = 0xFFE9967A,
        DarkSeaGreen         = 0xFF8FBC8F,
        DarkSlateBlue        = 0xFF483D8B,
        DarkSlateGray        = 0xFF2F4F4F,
        DarkTurquoise        = 0xFF00CED1,
        DarkViolet           = 0xFF9400D3,
        DeepPink             = 0xFFFF1493,
        DeepSkyBlue          = 0xFF00BFFF,
        DimGray              = 0xFF696969,
        DimGrey              = 0xFF696969,
        DodgerBlue           = 0xFF1E90FF,
        FireBrick            = 0xFFB22222,
        FloralWhite          = 0xFFFFFAF0,
        ForestGreen          = 0xFF228B22,
        Fuchsia              = 0xFFFF00FF,
        Gainsboro            = 0xFFDCDCDC,
        GhostWhite           = 0xFFF8F8FF,
        Gold                 = 0xFFFFD700,
        GoldenRod            = 0xFFDAA520,
        Gray                 = 0xFF808080,
        Green                = 0xFF008000,
        GreenYellow          = 0xFFADFF2F,
        HoneyDew             = 0xFFF0FFF0,
        HotPink              = 0xFFFF69B4,
        IndianRed            = 0xFFCD5C5C,
        Indigo               = 0xFF4B0082,
        Ivory                = 0xFFFFFFF0,
        Khaki                = 0xFFF0E68C,
        Lavender             = 0xFFE6E6FA,
        LavenderBlush        = 0xFFFFF0F5,
        LawnGreen            = 0xFF7CFC00,
        LemonChiffon         = 0xFFFFFACD,
        LightBlue            = 0xFFADD8E6,
        LightCoral           = 0xFFF08080,
        LightCyan            = 0xFFE0FFFF,
        LightGoldenRodYellow = 0xFFFAFAD2,
        LightGray            = 0xFFD3D3D3,
        LightGreen           = 0xFF90EE90,
        LightPink            = 0xFFFFB6C1,
        LightSalmon          = 0xFFFFA07A,
        LightSeaGreen        = 0xFF20B2AA,
        LightSkyBlue         = 0xFF87CEFA,
        LightSlateGray       = 0xFF778899,
        LightSteelBlue       = 0xFFB0C4DE,
        LightYellow          = 0xFFFFFFE0,
        Lime                 = 0xFF00FF00,
        LimeGreen            = 0xFF32CD32,
        Linen                = 0xFFFAF0E6,
        Magenta              = 0xFFFF00FF,
        Maroon               = 0xFF800000,
        MediumAquaMarine     = 0xFF66CDAA,
        MediumBlue           = 0xFF0000CD,
        MediumOrchid         = 0xFFBA55D3,
        MediumPurple         = 0xFF9370DB,
        MediumSeaGreen       = 0xFF3CB371,
        MediumSlateBlue      = 0xFF7B68EE,
        MediumSpringGreen    = 0xFF00FA9A,
        MediumTurquoise      = 0xFF48D1CC,
        MediumVioletRed      = 0xFFC71585,
        MidnightBlue         = 0xFF191970,
        MintCream            = 0xFFF5FFFA,
        MistyRose            = 0xFFFFE4E1,
        Moccasin             = 0xFFFFE4B5,
        NavajoWhite          = 0xFFFFDEAD,
        Navy                 = 0xFF000080,
        OldLace              = 0xFFFDF5E6,
        Olive                = 0xFF808000,
        OliveDrab            = 0xFF6B8E23,
        Orange               = 0xFFFFA500,
        OrangeRed            = 0xFFFF4500,
        Orchid               = 0xFFDA70D6,
        PaleGoldenRod        = 0xFFEEE8AA,
        PaleGreen            = 0xFF98FB98,
        PaleTurquoise        = 0xFFAFEEEE,
        PaleVioletRed        = 0xFFDB7093,
        PapayaWhip           = 0xFFFFEFD5,
        PeachPuff            = 0xFFFFDAB9,
        Peru                 = 0xFFCD853F,
        Pink                 = 0xFFFFC0CB,
        Plum                 = 0xFFDDA0DD,
        PowderBlue           = 0xFFB0E0E6,
        Purple               = 0xFF800080,
        Red                  = 0xFFFF0000,
        RosyBrown            = 0xFFBC8F8F,
        RoyalBlue            = 0xFF4169E1,
        SaddleBrown          = 0xFF8B4513,
        Salmon               = 0xFFFA8072,
        SandyBrown           = 0xFFF4A460,
        SeaGreen             = 0xFF2E8B57,
        SeaShell             = 0xFFFFF5EE,
        Sienna               = 0xFFA0522D,
        Silver               = 0xFFC0C0C0,
        SkyBlue              = 0xFF87CEEB,
        SlateBlue            = 0xFF6A5ACD,
        SlateGray            = 0xFF708090,
        Snow                 = 0xFFFFFAFA,
        SpringGreen          = 0xFF00FF7F,
        SteelBlue            = 0xFF4682B4,
        Tan                  = 0xFFD2B48C,
        Teal                 = 0xFF008080,
        Thistle              = 0xFFD8BFD8,
        Tomato               = 0xFFFF6347,
        Turquoise            = 0xFF40E0D0,
        Violet               = 0xFFEE82EE,
        Wheat                = 0xFFF5DEB3,
        White                = 0xFFFFFFFF,
        WhiteSmoke           = 0xFFF5F5F5,
        Yellow               = 0xFFFFFF00,
        YellowGreen          = 0xFF9ACD32
    };

    enum
    {
        Arc_ArcticWhite      = 0xFFFFFFFF,
        Arc_RoseQuartz       = 0xFFFFBEBE,
        Arc_SaharaSand       = 0xFFFFEBBE,
        Arc_TopazSand        = 0xFFFFEBAF,
        Arc_YuccaYellow      = 0xFFFFFFBE,
        Arc_OlivineYellow    = 0xFFE9FFBE,
        Arc_TzavoriteGreen   = 0xFFD3FFBE,
        Arc_IndicoliteGreen  = 0xFFBEFFE8,
        Arc_SodaliteBlue     = 0xFFBEE8FF,
        Arc_SugiliteSky      = 0xFFBED2FF,
        Arc_LepidoliteLilac  = 0xFFE8BEFF,
        Arc_RhodoliteRose    = 0xFFFFBEE8,
        Arc_Gray10           = 0xFFE1E1E1,
        Arc_MediumCoralLight = 0xFFFF7F7F,
        Arc_Cantaloupe       = 0xFFFFA77F,
        Arc_Mango            = 0xFFFFD37F,
        Arc_AutuniteYellow   = 0xFFFFFF73,
        Arc_Lemongrass       = 0xFFD1FF73,
        Arc_LightApple       = 0xFFA3FF73,
        Arc_BerylGreen       = 0xFF73FFDF,
        Arc_ApatiteBlue      = 0xFF73DFFF,
        Arc_YogoBlue         = 0xFF73B2FF,
        Arc_Heliotrope       = 0xFFDF73FF,
        Arc_FushiaPink       = 0xFFFF73DF,
        Arc_Gray20           = 0xFFCCCCCC,
        Arc_MarsRed          = 0xFFFF0000,
        Arc_FireRed          = 0xFFFF5500,
        Arc_ElectronGold     = 0xFFFFAA00,
        Arc_SolarYellow      = 0xFFFFFF00,
        Arc_PeridotGreen     = 0xFFAAFF00,
        Arc_MediumApple      = 0xFF55FF00,
        Arc_TourmalineGreen  = 0xFF00FFC5,
        Arc_BigSkyBlue       = 0xFF00C5FF,
        Arc_CreteanBlue      = 0xFF0082FF,
        Arc_Amethyst         = 0xFFC500FF,
        Arc_GingerPink       = 0xFFFF00C5,
        Arc_Gray30           = 0xFFB2B2B2,
        Arc_PoinsettiaRed    = 0xFFE60000,
        Arc_FlameRed         = 0xFFE64C00,
        Arc_SevilleOrange    = 0xFFE69800,
        Arc_CitroenYellow    = 0xFFE6E600,
        Arc_MacawGreen       = 0xFF98E600,
        Arc_QuetzelGreen     = 0xFF4CE600,
        Arc_Chrysophase      = 0xFF00E6A9,
        Arc_MooreaBlue       = 0xFF00A9E6,
        Arc_LapisLazuli      = 0xFF005CE6,
        Arc_AnemoneViolet    = 0xFFA900E6,
        Arc_PeonyPink        = 0xFFE600A9,
        Arc_Gray40           = 0xFF9C9C9C,
        Arc_TuscanRed        = 0xFFA80000,
        Arc_CherryCola       = 0xFFA83800,
        Arc_RawUmber         = 0xFFA87000,
        Arc_OliveniteGreen   = 0xFFA8A800,
        Arc_TarragonGreen    = 0xFF70A800,
        Arc_LeafGreen        = 0xFF38A800,
        Arc_MalachiteGreen   = 0xFF00A884,
        Arc_DelftBlue        = 0xFF0084A8,
        Arc_UltraBlue        = 0xFF004DA8,
        Arc_DarkAmethyst     = 0xFF8400A8,
        Arc_CattleyaOrchid   = 0xFFA80084,
        Arc_Gray50           = 0xFF828282,
        Arc_DarkUmber        = 0xFF730000,
        Arc_CherrywoodBrown  = 0xFF732600,
        Arc_BurntUmber       = 0xFF734C00,
        Arc_DarkOlivenite    = 0xFF737300,
        Arc_SpruceGreen      = 0xFF4C7300,
        Arc_FirGreen         = 0xFF267300,
        Arc_PeacockGreen     = 0xFF00734C,
        Arc_SteelBlue        = 0xFF004C73,
        Arc_DarkNavy         = 0xFF002673,
        Arc_Ultramarine      = 0xFF4C0073,
        Arc_PurpleHeart      = 0xFF73004C,
        Arc_Gray60           = 0xFF686868,
        Arc_RoseDust         = 0xFFD79E9E,
        Arc_SoapstoneDust    = 0xFFD7B09E,
        Arc_TecateDust       = 0xFFD7C29E,
        Arc_LimeDust         = 0xFFD7D79E,
        Arc_AppleDust        = 0xFFC7D79E,
        Arc_SageDust         = 0xFFB4D79E,
        Arc_TurquoiseDust    = 0xFF9ED7C2,
        Arc_BlueGrayDust     = 0xFF9EBBD7,
        Arc_VioletDust       = 0xFF9EAAD7,
        Arc_LilacDust        = 0xFFC29ED7,
        Arc_TudorRoseDust    = 0xFFD69DBC,
        Arc_Gray70           = 0xFF4E4E4E,
        Arc_MediumCoral      = 0xFFF57A7A,
        Arc_OrangeDust       = 0xFFF5A27A,
        Arc_MediumSand       = 0xFFF5CA7A,
        Arc_MediumYellow     = 0xFFF5F57A,
        Arc_MediumLime       = 0xFFCDF57A,
        Arc_MediumKeyLime    = 0xFFA5F57A,
        Arc_LightVert        = 0xFF7AF5CA,
        Arc_OxideBlue        = 0xFF7AB6F5,
        Arc_MediumAzul       = 0xFF7A8EF5,
        Arc_MediumLilac      = 0xFFCA7AF5,
        Arc_MediumFushia     = 0xFFF57AB6,
        Arc_Gray80           = 0xFF343434,
        Arc_TulipPink        = 0xFFCD6666,
        Arc_NubuckTan        = 0xFFCD8966,
        Arc_LightSienna      = 0xFFCDAA66,
        Arc_LightOlivenite   = 0xFFCDCD66,
        Arc_MediumOlivenite  = 0xFFABCD66,
        Arc_FernGreen        = 0xFF89CD66,
        Arc_Jadeite          = 0xFF66CDAB,
        Arc_AtlanticBlue     = 0xFF6699CD,
        Arc_PacificBlue      = 0xFF6677CD,
        Arc_AsterPurple      = 0xFFAA66CD,
        Arc_ProteaPink       = 0xFFCD6699,
        Arc_Black            = 0xFF000000,
        Arc_CordovanBrown    = 0xFF894444,
        Arc_CocoaBrown       = 0xFF895A44,
        Arc_LeatherBrown     = 0xFF897044,
        Arc_LichenGreen      = 0xFF898944,
        Arc_MossGreen        = 0xFF728944,
        Arc_LotusPondGreen   = 0xFF5C8944,
        Arc_DeepForest       = 0xFF448970,
        Arc_LarkspurBlue     = 0xFF446589,
        Arc_GlacierBlue      = 0xFF264F89,
        Arc_Blackberry       = 0xFF704489,
        Arc_Cabernet         = 0xFF894465,
    };

    // clang-format on

private:
    Spec cspec;
    union CS
    {
        CS() {}
        constexpr explicit CS(uint16_t a1, uint16_t a2, uint16_t a3,
                              uint16_t a4, uint16_t a5) noexcept
            : array{a1, a2, a3, a4, a5}
        {
        }

        struct
        {
            uint16_t alpha;
            uint16_t red;
            uint16_t green;
            uint16_t blue;
            uint16_t pad;
        } argb;
        struct
        {
            uint16_t alpha;
            uint16_t hue;
            uint16_t saturation;
            uint16_t value;
            uint16_t pad;

        } ahsv;
        struct
        {
            uint16_t alpha;
            uint16_t cyan;
            uint16_t magenta;
            uint16_t yellow;
            uint16_t black;
        } acmyk;
        struct
        {
            uint16_t alpha;
            uint16_t hue;
            uint16_t saturation;
            uint16_t lightness;
            uint16_t pad;
        } ahsl;
        struct
        {
            uint16_t alphaF16;
            uint16_t redF16;
            uint16_t greenF16;
            uint16_t blueF16;
            uint16_t pad;
        } argbExtended;

        uint16_t array[5];
    } cs;
};

}// namespace m2

#endif//M2_COLOR_H_