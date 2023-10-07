/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file color.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"

namespace Lite {
namespace Utility {

struct UTILITY_EXPORT GsColor
{
    /// @brief 默认构造
    GsColor() noexcept;
    /// @brief 根据无符号32位整型构造
    /// @param c
    GsColor(unsigned int c) noexcept;
    /// @brief 根据有符号32位整型构造
    /// @param c
    GsColor(int c) noexcept;
    /// @brief 根据R，G，B，A通道构造
    /// @param r 红色通道[0,255]
    /// @param g 绿色通道[0,255]
    /// @param b 蓝色通道[0,255]
    /// @param a 透明通道[0,255]
    GsColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) noexcept;
    /// @brief 拷贝构造
    /// @param color
    GsColor(const GsColor &color) noexcept;
    /// @brief 改变颜色的透明度
    /// @param rhs
    /// @param a
    GsColor(const GsColor &rhs, unsigned char a);
    /// @brief 拷贝构造
    /// @param color
    /// @return
    GsColor &operator=(const GsColor &color) noexcept;

    /// @brief 随机颜色
    /// @details 随机RGB值，生成颜色可能过亮
    /// @return
    static GsColor Random();

    /// @brief 随机颜色
    /// @details 使用HSV模型获取随机值，颜色更为柔和，所有渲染颜色都调用此接口获取随机值
    /// @return
    static GsColor RandomHSV();

    /// @brief 从CSS颜色描述构造
    /// @param css
    /// @return
    static GsColor FromCSS(const char *css);

    /// @brief 根据R，G，B，A通道构造
    /// @param r 红色通道[0,255]
    /// @param g 绿色通道[0,255]
    /// @param b 蓝色通道[0,255]
    /// @param a 透明通道[0,255]
    /// @return
    static GsColor FromARGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

    /// @brief 从浮点R，G，B，A通道构造
    /// @param r 红色通道[0,1]
    /// @param g 绿色通道[0,1]
    /// @param b 蓝色通道[0,1]
    /// @param a 透明通道[0,1]
    /// @return
    static GsColor FromARGBF(double r, double g, double b, double a = 1.0f);

    /// @brief 根据C，M，Y，K通道构造
    /// @param c 青色通道[0,100]
    /// @param m 品红色通道[0,100]
    /// @param y 黄色通道[0,100]
    /// @param k 黑色通道[0,100]
    /// @return
    static GsColor FromCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);

    /// @brief 根据浮点C，M，Y，K通道构造
    /// @param c 青色通道[0,1]
    /// @param m 品红色通道[0,1]
    /// @param y 黄色通道[0,1]
    /// @param k 黑色通道[0,1]
    /// @return
    static GsColor FromCMYKF(double c, double m, double y, double k);
    /// @brief 从HSV颜色构造
    /// @param h  Hue  色调				h 范围[0, 360] (int)
    /// @param s  Saturation 饱和度		s 范围[0, 255](int)
    /// @param v  Value 亮度			v 范围[0, 255](int)
    /// @param a  透明度
    /// @return
    static GsColor FromHSV(int h, int s, int v, unsigned char a = 255);

    /// @brief 从HSV颜色构造
    /// @param h  Hue  色调				h 范围[0, 360] (float,取值为int)
    /// @param s  Saturation 饱和度		s 范围[0, 1.0](float)
    /// @param v  Value 亮度			v 范围[0, 1.0](float)
    /// @param a  透明度
    /// @return
    static GsColor FromHSV(float h, float s, float v, float a = 1.0);
    /// @brief 颜色转灰度值
    /// @param r  红色通道[0,255]
    /// @param g  绿色通道[0,255]
    /// @param b  蓝色通道[0,255]
    /// @return
    static int ToGray(unsigned char r, unsigned char g, unsigned char b);

    /// @brief 获取float类型的hsv颜色值
    /// @param h 色调范围[0, 360] (float,取值为int)
    /// @param s 饱和度范围[0, 1.0](float)
    /// @param v 亮度范围[0, 1.0](float)
    /// @return
    bool ToHSV(float *h, float *s, float *v) const;
    /// @brief 获取C，M，Y，K通道值
    /// @param c 青色通道[0,100]
    /// @param m 品红色通道[0,100]
    /// @param y 黄色通道[0,100]
    /// @param k 黑色通道[0,100]
    /// @return
    bool ToCMKY(unsigned int *c, unsigned int *m, unsigned int *y, unsigned int *k) const;
    /// @brief 获取H，S，L通道值
    /// @param h 色相范围[0, 360]
    /// @param s 饱和度范围[0, 100]
    /// @param l 亮度范围[0, 100]
    /// @param a 透明度范围[0, 255]
    /// @return
    bool ToHSL(float *h, float *s, float *l, int *a = nullptr) const;

    /// @brief 用Win32 RGB颜色设置颜色值
    /// @param rgb
    /// @param a
    void SetCOLORREF(unsigned int rgb, unsigned char a = 255);
    /// @brief 转换为win32 RGB颜色值
    /// @return
    unsigned int ToCOLORREF() const;

    /// @brief 浮点数R通道值
    /// @return 返回R通道值[0,1]
    float RedF() const noexcept;
    /// @brief 浮点数G通道值
    /// @return 返回R通道值[0,1]
    float GreenF() const noexcept;
    /// @brief 浮点数B通道值
    /// @return 返回R通道值[0,1]
    float BlueF() const noexcept;
    /// @brief 浮点数A通道值
    /// @return 返回R通道值[0,1]
    float AlphaF() const noexcept;
    /// @brief 设置浮点数R通道值
    /// @return 返回自身的引用
    GsColor &RedF(float r) noexcept;
    /// @brief 设置浮点数G通道值
    /// @return 返回自身的引用
    GsColor &GreenF(float g) noexcept;
    /// @brief 设置浮点数A通道值
    /// @return 返回自身的引用
    GsColor &BlueF(float b) noexcept;
    /// @brief 设置浮点数B通道值
    /// @return 返回自身的引用
    GsColor &AlphaF(float a) noexcept;
    /// @brief 转换未灰度值[0,255]
    /// @return
    inline int ToGray() const
    {
        return GsColor::ToGray(R, G, B);
    }

    /// @brief 等号操作符
    /// @param argb
    /// @return
    GsColor &operator=(unsigned int &argb) noexcept;
    /// @brief 等号操作符
    /// @param argb
    /// @return
    GsColor &operator=(int &argb) noexcept;
    /// @brief 等号操作符
    /// @param rhs
    /// @return
    GsColor &operator=(GsColor &rhs) noexcept;
    bool operator==(const GsColor &color) const noexcept;
    bool operator!=(const GsColor &color) const noexcept;

    /// @brief 无符号整数重载操作符
    explicit operator unsigned int() const noexcept;
    /// @brief 整数重载操作符
    explicit operator int() const noexcept;

    /// @brief w3s预设颜色值
    /// @details https://www.w3school.com.cn/tiy/color.asp
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
        DarkGoldenRod = 0xFFB8860B,
        DarkGray = 0xFFA9A9A9,
        DarkGreen = 0xFF006400,
        DarkKhaki = 0xFFBDB76B,
        DarkMagenta = 0xFF8B008B,
        DarkOliveGreen = 0xFF556B2F,
        Darkorange = 0xFFFF8C00,
        DarkOrchid = 0xFF9932CC,
        DarkRed = 0xFF8B0000,
        DarkSalmon = 0xFFE9967A,
        DarkSeaGreen = 0xFF8FBC8F,
        DarkSlateBlue = 0xFF483D8B,
        DarkSlateGray = 0xFF2F4F4F,
        DarkTurquoise = 0xFF00CED1,
        DarkViolet = 0xFF9400D3,
        DeepPink = 0xFFFF1493,
        DeepSkyBlue = 0xFF00BFFF,
        DimGray = 0xFF696969,
        DimGrey = 0xFF696969,
        DodgerBlue = 0xFF1E90FF,
        FireBrick = 0xFFB22222,
        FloralWhite = 0xFFFFFAF0,
        ForestGreen = 0xFF228B22,
        Fuchsia = 0xFFFF00FF,
        Gainsboro = 0xFFDCDCDC,
        GhostWhite = 0xFFF8F8FF,
        Gold = 0xFFFFD700,
        GoldenRod = 0xFFDAA520,
        Gray = 0xFF808080,
        Green = 0xFF008000,
        GreenYellow = 0xFFADFF2F,
        HoneyDew = 0xFFF0FFF0,
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
        LightGoldenRodYellow = 0xFFFAFAD2,
        LightGray = 0xFFD3D3D3,
        LightGreen = 0xFF90EE90,
        LightPink = 0xFFFFB6C1,
        LightSalmon = 0xFFFFA07A,
        LightSeaGreen = 0xFF20B2AA,
        LightSkyBlue = 0xFF87CEFA,
        LightSlateGray = 0xFF778899,
        LightSteelBlue = 0xFFB0C4DE,
        LightYellow = 0xFFFFFFE0,
        Lime = 0xFF00FF00,
        LimeGreen = 0xFF32CD32,
        Linen = 0xFFFAF0E6,
        Magenta = 0xFFFF00FF,
        Maroon = 0xFF800000,
        MediumAquaMarine = 0xFF66CDAA,
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
        PaleGoldenRod = 0xFFEEE8AA,
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
        Turquoise = 0xFF40E0D0,
        Violet = 0xFFEE82EE,
        Wheat = 0xFFF5DEB3,
        White = 0xFFFFFFFF,
        WhiteSmoke = 0xFFF5F5F5,
        Yellow = 0xFFFFFF00,
        YellowGreen = 0xFF9ACD32
    };

    /// @brief ArcGIS Pro预设颜色
    enum
    {
        Arc_ArcticWhite = 0xFFFFFFFF,
        Arc_RoseQuartz = 0xFFFFBEBE,
        Arc_SaharaSand = 0xFFFFEBBE,
        Arc_TopazSand = 0xFFFFEBAF,
        Arc_YuccaYellow = 0xFFFFFFBE,
        Arc_OlivineYellow = 0xFFE9FFBE,
        Arc_TzavoriteGreen = 0xFFD3FFBE,
        Arc_IndicoliteGreen = 0xFFBEFFE8,
        Arc_SodaliteBlue = 0xFFBEE8FF,
        Arc_SugiliteSky = 0xFFBED2FF,
        Arc_LepidoliteLilac = 0xFFE8BEFF,
        Arc_RhodoliteRose = 0xFFFFBEE8,
        Arc_Gray10 = 0xFFE1E1E1,
        Arc_MediumCoralLight = 0xFFFF7F7F,
        Arc_Cantaloupe = 0xFFFFA77F,
        Arc_Mango = 0xFFFFD37F,
        Arc_AutuniteYellow = 0xFFFFFF73,
        Arc_Lemongrass = 0xFFD1FF73,
        Arc_LightApple = 0xFFA3FF73,
        Arc_BerylGreen = 0xFF73FFDF,
        Arc_ApatiteBlue = 0xFF73DFFF,
        Arc_YogoBlue = 0xFF73B2FF,
        Arc_Heliotrope = 0xFFDF73FF,
        Arc_FushiaPink = 0xFFFF73DF,
        Arc_Gray20 = 0xFFCCCCCC,
        Arc_MarsRed = 0xFFFF0000,
        Arc_FireRed = 0xFFFF5500,
        Arc_ElectronGold = 0xFFFFAA00,
        Arc_SolarYellow = 0xFFFFFF00,
        Arc_PeridotGreen = 0xFFAAFF00,
        Arc_MediumApple = 0xFF55FF00,
        Arc_TourmalineGreen = 0xFF00FFC5,
        Arc_BigSkyBlue = 0xFF00C5FF,
        Arc_CreteanBlue = 0xFF0082FF,
        Arc_Amethyst = 0xFFC500FF,
        Arc_GingerPink = 0xFFFF00C5,
        Arc_Gray30 = 0xFFB2B2B2,
        Arc_PoinsettiaRed = 0xFFE60000,
        Arc_FlameRed = 0xFFE64C00,
        Arc_SevilleOrange = 0xFFE69800,
        Arc_CitroenYellow = 0xFFE6E600,
        Arc_MacawGreen = 0xFF98E600,
        Arc_QuetzelGreen = 0xFF4CE600,
        Arc_Chrysophase = 0xFF00E6A9,
        Arc_MooreaBlue = 0xFF00A9E6,
        Arc_LapisLazuli = 0xFF005CE6,
        Arc_AnemoneViolet = 0xFFA900E6,
        Arc_PeonyPink = 0xFFE600A9,
        Arc_Gray40 = 0xFF9C9C9C,
        Arc_TuscanRed = 0xFFA80000,
        Arc_CherryCola = 0xFFA83800,
        Arc_RawUmber = 0xFFA87000,
        Arc_OliveniteGreen = 0xFFA8A800,
        Arc_TarragonGreen = 0xFF70A800,
        Arc_LeafGreen = 0xFF38A800,
        Arc_MalachiteGreen = 0xFF00A884,
        Arc_DelftBlue = 0xFF0084A8,
        Arc_UltraBlue = 0xFF004DA8,
        Arc_DarkAmethyst = 0xFF8400A8,
        Arc_CattleyaOrchid = 0xFFA80084,
        Arc_Gray50 = 0xFF828282,
        Arc_DarkUmber = 0xFF730000,
        Arc_CherrywoodBrown = 0xFF732600,
        Arc_BurntUmber = 0xFF734C00,
        Arc_DarkOlivenite = 0xFF737300,
        Arc_SpruceGreen = 0xFF4C7300,
        Arc_FirGreen = 0xFF267300,
        Arc_PeacockGreen = 0xFF00734C,
        Arc_SteelBlue = 0xFF004C73,
        Arc_DarkNavy = 0xFF002673,
        Arc_Ultramarine = 0xFF4C0073,
        Arc_PurpleHeart = 0xFF73004C,
        Arc_Gray60 = 0xFF686868,
        Arc_RoseDust = 0xFFD79E9E,
        Arc_SoapstoneDust = 0xFFD7B09E,
        Arc_TecateDust = 0xFFD7C29E,
        Arc_LimeDust = 0xFFD7D79E,
        Arc_AppleDust = 0xFFC7D79E,
        Arc_SageDust = 0xFFB4D79E,
        Arc_TurquoiseDust = 0xFF9ED7C2,
        Arc_BlueGrayDust = 0xFF9EBBD7,
        Arc_VioletDust = 0xFF9EAAD7,
        Arc_LilacDust = 0xFFC29ED7,
        Arc_TudorRoseDust = 0xFFD69DBC,
        Arc_Gray70 = 0xFF4E4E4E,
        Arc_MediumCoral = 0xFFF57A7A,
        Arc_OrangeDust = 0xFFF5A27A,
        Arc_MediumSand = 0xFFF5CA7A,
        Arc_MediumYellow = 0xFFF5F57A,
        Arc_MediumLime = 0xFFCDF57A,
        Arc_MediumKeyLime = 0xFFA5F57A,
        Arc_LightVert = 0xFF7AF5CA,
        Arc_OxideBlue = 0xFF7AB6F5,
        Arc_MediumAzul = 0xFF7A8EF5,
        Arc_MediumLilac = 0xFFCA7AF5,
        Arc_MediumFushia = 0xFFF57AB6,
        Arc_Gray80 = 0xFF343434,
        Arc_TulipPink = 0xFFCD6666,
        Arc_NubuckTan = 0xFFCD8966,
        Arc_LightSienna = 0xFFCDAA66,
        Arc_LightOlivenite = 0xFFCDCD66,
        Arc_MediumOlivenite = 0xFFABCD66,
        Arc_FernGreen = 0xFF89CD66,
        Arc_Jadeite = 0xFF66CDAB,
        Arc_AtlanticBlue = 0xFF6699CD,
        Arc_PacificBlue = 0xFF6677CD,
        Arc_AsterPurple = 0xFFAA66CD,
        Arc_ProteaPink = 0xFFCD6699,
        Arc_Black = 0xFF000000,
        Arc_CordovanBrown = 0xFF894444,
        Arc_CocoaBrown = 0xFF895A44,
        Arc_LeatherBrown = 0xFF897044,
        Arc_LichenGreen = 0xFF898944,
        Arc_MossGreen = 0xFF728944,
        Arc_LotusPondGreen = 0xFF5C8944,
        Arc_DeepForest = 0xFF448970,
        Arc_LarkspurBlue = 0xFF446589,
        Arc_GlacierBlue = 0xFF264F89,
        Arc_Blackberry = 0xFF704489,
        Arc_Cabernet = 0xFF894465,
    };

    // https://photoblogstop.com/photoshop/photoshop-blend-modes-explained
    // https://www.jianshu.com/p/175631f45ec6
    enum PhotoShopColorBlendMode
    {
        PS_Normal,      //!< 正常 f(a,b) = a
        PS_Dissolve,    //!< 溶解 f(a,b) = random(a,b)
        PS_Darken,      //!< 变暗 f(a,b)=min(a,b)
        PS_Multiply,    //!< 正片叠底 f(a,b) = ab
        PS_ColorBurn,   //!< 颜色加深 f(a,b) = 1-(1-b)/a
        PS_LinearBurn,  //!< 线性加深 f(a,b)=a+b-1
        PS_DarkerColor, //!< 深色 f(a,b)=min(ar + ag + ab, br + bg +bb)
        PS_Lighten,     //!< 变亮 f(a,b)=max(a,b)
        PS_Screen,      //!< 滤色 f(a,b) = 1-(1-a)(1-b)
        PS_ColorDodge,  //!< 颜色减淡 f(a,b) = 1-(1-a)(1-b)
        PS_LinearDodge, //!< 线性减淡(添加)  f(a,b)=a+b
        PS_LighterColor,//!< 浅色 f(a,b)=max(ar + ag + ab, br + bg +bb)
        PS_Overlay,     //!< 叠加
        PS_SoftLight,   //!< 柔光
        PS_HardLight,   //!< 强光
        PS_VividLight,  //!< 亮光
        PS_LinearLight, //!< 线性光
        PS_PinLight,    //!< 点光
        PS_HardMix,     //!< 实色混合
        PS_Difference,  //!< 差值 f(a,b)= abs(b-a)
        PS_Exclusion,   //!< 排除 不详
        PS_Subtract,    //!< 减去 f(a,b)=b-a
        PS_Divide,      //!< 划分 f(a,b)=b/a
        PS_Hue,         //!< 色相 HcScBc = HaSbBb
        PS_Color,       //!< 饱和度 HcScBc = HaSaBb
        PS_Saturation,  //!< 饱和度 HcScBc = HbSaBb
        PS_Luminosity,  //!< 明度 HcScBc = HbSbBa
    };


    /// @brief PorterDuff颜色混合模式
    /// @details https://learn.microsoft.com/en-us/xamarin/xamarin-forms/user-interface/graphics/skiasharp/effects/blend-modes/porter-duff
    /// @details https://blog.csdn.net/hitzsf/article/details/108634044
    /// @details Sa：全称为Source alpha，表示源图的Alpha通道；
    /// @details Sc：全称为Source color，表示源图的颜色；
    /// @details Da：全称为Destination alpha，表示目标图的Alpha通道；
    /// @details Dc：全称为Destination color，表示目标图的颜色.
    enum PorterDuffBlendMode
    {
        eCLEAR,   //!< [0, 0]
        eSRC,     //!< [Sa, Sc]
        eDST,     //!< [Da, Dc]
        eSRC_OVER,//!< [Sa + (1 - Sa)*Da, Rc = Sc + (1 - Sa)*Dc]
        eDST_OVER,//!< [Sa + (1 - Sa)*Da, Rc = Dc + (1 - Da)*Sc]
        eSRC_IN,  //!< [Sa * Da, Sc * Da]
        eDST_IN,  //!< [Sa * Da, Sa * Dc]
        eSRC_OUT, //!< [Sa * (1 - Da), Sc * (1 - Da)]
        eDST_OUT, //!< [Da * (1 - Sa), Dc * (1 - Sa)]
        eSRC_ATOP,//!< [Da, Sc * Da + (1 - Sa) * Dc]
        eDST_ATOP,//!< [Sa, Sa * Dc + Sc * (1 - Da)]
        eXOR,     //!< [Sa + Da - 2 * Sa * Da, Sc * (1 - Da) + (1 - Sa) * Dc]
        eDARKEN,  //!< [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + min(Sc, Dc)]
        eLIGHTEN, //!< [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + max(Sc, Dc)]
        eMULTIPLY,//!< [Sa * Da, Sc * Dc]
        eSCREEN   //!< [Sa + Da - Sa * Da, Sc + Dc - Sc * Dc]
    };

    /// @brief 根据Porter-Duff模型混合颜色
    /// @param color
    /// @param mode
    /// @return
    GsColor &Blend(const GsColor &color, PorterDuffBlendMode mode);
    /// @brief 根据PS函数模型混合颜色
    /// @param color
    /// @param mode
    /// @return
    GsColor &Blend(const GsColor &color, PhotoShopColorBlendMode mode);

    union
    {
        unsigned int Argb;
        struct
        {
            unsigned char A, R, G, B;
        };
    };
};


}// namespace Utility
}// namespace Lite
