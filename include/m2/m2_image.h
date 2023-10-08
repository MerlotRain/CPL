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

#pragma once

#include "matrix.h"
#include "memorymanager.h"
#include "object.h"

namespace m2 {

/// @brief 颜色模型
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


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/// @brief int点结构
struct UTILITY_EXPORT GsPT
{
    int X;
    int Y;

    /// @brief 默认构造
    GsPT();
    /// @brief 由x,y坐标构造
    /// @param xpos
    /// @param ypos
    GsPT(int xpos, int ypos);
    /// @brief 是否为空
    /// @return
    inline bool IsNull() const;
    /// @brief 获取点的曼哈顿距离
    /// @return
    inline int ManhattanLength() const;
    /// @brief 坐标转置
    /// @return
    GsPT Transposed() const noexcept { return {Y, X}; }

    /// @brief 重载+=操作符
    /// @param p
    /// @return
    inline GsPT &operator+=(const GsPT &p);
    /// @brief 重载-=操作符
    /// @param p
    /// @return
    inline GsPT &operator-=(const GsPT &p);

    /// @brief 重载*=操作符
    /// @param factor
    /// @return
    inline GsPT &operator*=(float factor);
    inline GsPT &operator*=(int factor);

    /// @brief 重载/=操作符
    /// @param divisor
    /// @return
    inline GsPT &operator/=(float c);
    /// @brief 求两点点积
    /// @param p1
    /// @param p2
    /// @return
    static inline int DotProduct(const GsPT &p1, const GsPT &p2);

    friend inline bool operator==(const GsPT &, const GsPT &);
    friend inline bool operator!=(const GsPT &, const GsPT &);
    friend inline const GsPT operator+(const GsPT &, const GsPT &);
    friend inline const GsPT operator-(const GsPT &, const GsPT &);
    friend inline const GsPT operator*(const GsPT &, float);
    friend inline const GsPT operator*(float, const GsPT &);
    friend inline const GsPT operator*(const GsPT &, float);
    friend inline const GsPT operator*(float, const GsPT &);
    friend inline const GsPT operator*(const GsPT &, int);
    friend inline const GsPT operator*(int, const GsPT &);
    friend inline const GsPT operator+(const GsPT &);
    friend inline const GsPT operator-(const GsPT &);
    friend inline const GsPT operator/(const GsPT &, float);
};


/// @brief float点结构
struct UTILITY_EXPORT GsPTF
{
    float X;
    float Y;

    /// @brief 默认构造
    GsPTF();
    /// @brief 由整型点结构构造
    /// @param p
    explicit GsPTF(const GsPT &p);
    /// @brief 由x，y坐标构造
    /// @param xpos
    /// @param ypos
    GsPTF(float xpos, float ypos);
    /// @brief 获取点的曼哈顿距离
    /// @return
    inline float ManhattanLength() const;
    /// @brief 是否为空
    /// @return
    inline bool IsNull() const;

    /// @brief 坐标转置
    /// @return
    GsPTF Transposed() const noexcept { return {Y, X}; }

    inline GsPTF &operator+=(const GsPTF &p);
    inline GsPTF &operator-=(const GsPTF &p);
    inline GsPTF &operator*=(float c);
    inline GsPTF &operator/=(float divisor);

    /// @brief 求两点点积
    /// @param p1
    /// @param p2
    /// @return
    static inline float DotProduct(const GsPTF &p1, const GsPTF &p2);

    friend inline bool operator==(const GsPTF &, const GsPTF &);
    friend inline bool operator!=(const GsPTF &, const GsPTF &);
    friend inline const GsPTF operator+(const GsPTF &, const GsPTF &);
    friend inline const GsPTF operator-(const GsPTF &, const GsPTF &);
    friend inline const GsPTF operator*(float, const GsPTF &);
    friend inline const GsPTF operator*(const GsPTF &, float);
    friend inline const GsPTF operator+(const GsPTF &);
    friend inline const GsPTF operator-(const GsPTF &);
    friend inline const GsPTF operator/(const GsPTF &, float);

    GsPT ToPoint() const;
};


/// @brief 缩放横纵比例的变化
enum GsAspectRatioMode
{
    /// @brief 忽略横纵比例，自由缩放
    /// @details 图形可能会产生形变
    eIgnoreAspectRatio,
    /// @brief 大小被缩放为给定矩形内尽可能大的矩形，以保持纵横比
    /// @details 图形不会产生形变，将尽可能保持最大
    eKeepAspectRatio,
    /// @brief 大小被缩放到给定矩形之外尽可能小的矩形，以保持纵横比
    /// @details 图形不会产生形变，将尽可能保持最小
    eKeepAspectRatioByExpanding
};


/// @brief int边距结构
/// @details 在size,rect缩放过程中，需要主动指示正负值，Margins旨在于简化这个操作
/// @details 其中四周边距都是正数，调用ExpandedTo和BoundedTo函数可以快速获取缩放后的结果
struct UTILITY_EXPORT GsMargins
{
    int Left;
    int Top;
    int Right;
    int Bottom;

    /// @brief 默认构造
    GsMargins() noexcept;
    /// @brief 由四周边距构造
    /// @param left
    /// @param top
    /// @param right
    /// @param bottom
    GsMargins(int left, int top, int right, int bottom) noexcept;

    /// @brief 是否为null
    /// @return
    bool IsNull() const noexcept;

    GsMargins &operator+=(const GsMargins &margins) noexcept;
    GsMargins &operator-=(const GsMargins &margins) noexcept;
    GsMargins &operator+=(int) noexcept;
    GsMargins &operator-=(int) noexcept;
    GsMargins &operator*=(int) noexcept;
    GsMargins &operator/=(int);
    GsMargins &operator*=(float) noexcept;
    GsMargins &operator/=(float);

    friend inline bool operator==(const GsMargins &, const GsMargins &) noexcept;
    friend inline bool operator!=(const GsMargins &, const GsMargins &) noexcept;
};

/// @brief float类型边距结构
struct UTILITY_EXPORT GsMarginsF
{
    float Left;
    float Top;
    float Right;
    float Bottom;


    /// @brief 默认构造
    GsMarginsF() noexcept;
    /// @brief 由四周边距构造
    /// @param left
    /// @param top
    /// @param right
    /// @param bottom
    GsMarginsF(float left, float top, float right, float bottom) noexcept;
    /// @brief 由整型Mergins构造
    /// @param margins
    explicit GsMarginsF(const GsMargins &margins) noexcept;

    bool IsNull() const noexcept;

    GsMarginsF &operator+=(const GsMarginsF &margins) noexcept;
    GsMarginsF &operator-=(const GsMarginsF &margins) noexcept;
    GsMarginsF &operator+=(float addend) noexcept;
    GsMarginsF &operator-=(float subtrahend) noexcept;
    GsMarginsF &operator*=(float factor) noexcept;
    GsMarginsF &operator/=(float divisor);

    inline GsMargins toMargins() const noexcept;
};


/// @brief 创建int类型的尺寸结构
struct UTILITY_EXPORT GsSize
{
    int Width;
    int Height;

    /// @brief 默认构造
    GsSize() noexcept;
    /// @brief 由w,h构造
    /// @param w
    /// @param h
    GsSize(int w, int h) noexcept;

    /// @brief \a w 和 \a h 为0时判断为null
    /// @return
    inline bool IsNull() const noexcept;
    /// @brief \a w 和 \a h 其一小于1则判断为空
    /// @return
    inline bool IsEmpty() const noexcept;
    /// @brief \a w 和 \a h 必须都大于等于0
    /// @return
    inline bool IsValid() const noexcept;

    /// @brief 交换宽、高值
    void Transpose() noexcept;
    /// @brief 交换宽、高值，返回结果
    /// @return
    inline GsSize Transposed() const noexcept;

    /// @brief 尺寸缩放
    /// @param w
    /// @param h
    /// @param mode
    inline void Scale(int w, int h, GsAspectRatioMode mode) noexcept;
    inline void Scale(const GsSize &s, GsAspectRatioMode mode) noexcept;
    /// @brief 尺寸缩放，将结果返回
    /// @param w
    /// @param h
    /// @param mode
    /// @return
    GsSize Scaled(int w, int h, GsAspectRatioMode mode) const noexcept;
    GsSize Scaled(const GsSize &s, GsAspectRatioMode mode) const noexcept;

    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最小宽度和高度
    /// @param
    /// @return
    inline GsSize ExpandedTo(const GsSize &) const noexcept;
    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最大宽度和高度
    /// @param
    /// @return
    inline GsSize BoundedTo(const GsSize &) const noexcept;

    /// @brief 返回按边距增大此大小所产生的大小
    /// @param m
    /// @return
    GsSize GrownBy(GsMargins m) const noexcept;
    /// @brief 返回按边距缩小此大小的结果
    /// @param m
    /// @return
    GsSize ShrunkBy(GsMargins m) const noexcept;

    /// @brief 尺寸代表的面积
    /// @return
    int Area() const;

    inline GsSize &operator+=(const GsSize &) noexcept;
    inline GsSize &operator-=(const GsSize &) noexcept;
    inline GsSize &operator*=(float c) noexcept;
    inline GsSize &operator/=(float c);

    friend inline bool operator==(const GsSize &, const GsSize &) noexcept;
    friend inline bool operator!=(const GsSize &, const GsSize &) noexcept;
    friend inline const GsSize operator+(const GsSize &, const GsSize &) noexcept;
    friend inline const GsSize operator-(const GsSize &, const GsSize &) noexcept;
    friend inline const GsSize operator*(const GsSize &, float) noexcept;
    friend inline const GsSize operator*(float, const GsSize &) noexcept;
    friend inline const GsSize operator/(const GsSize &, float);
};


/// @brief 创建float类型的尺寸结构
struct UTILITY_EXPORT GsSizeF
{
    float Width;
    float Height;

    /// @brief 默认构造
    GsSizeF() noexcept;
    /// @brief 由整型尺寸构造
    /// @param sz
    explicit GsSizeF(const GsSize &sz) noexcept;
    /// @brief 由宽、高构造
    /// @param w
    /// @param h
    GsSizeF(float w, float h) noexcept;

    inline bool IsNull() const noexcept;
    inline bool IsEmpty() const noexcept;
    inline bool IsValid() const noexcept;

    /// @brief 交换宽、高值
    void Transpose() noexcept;
    /// @brief 交换宽、高值，返回结果
    /// @return
    inline GsSizeF Transposed() const noexcept;

    /// @brief 尺寸缩放
    /// @param w
    /// @param h
    /// @param mode
    inline void Scale(float w, float h, GsAspectRatioMode mode) noexcept;
    inline void Scale(const GsSizeF &s, GsAspectRatioMode mode) noexcept;
    /// @brief 尺寸缩放，将结果返回
    /// @param w
    /// @param h
    /// @param mode
    /// @return
    GsSizeF Scaled(float w, float h, GsAspectRatioMode mode) const noexcept;
    GsSizeF Scaled(const GsSizeF &s, GsAspectRatioMode mode) const noexcept;

    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最小宽度和高度
    /// @param
    /// @return
    inline GsSizeF ExpandedTo(const GsSizeF &) const noexcept;
    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最大宽度和高度
    /// @param
    /// @return
    inline GsSizeF BoundedTo(const GsSizeF &) const noexcept;

    /// @brief 返回按边距增大此大小所产生的大小
    /// @param m
    /// @return
    GsSizeF GrownBy(GsMarginsF m) const noexcept;
    /// @brief 返回按边距缩小此大小的结果
    /// @param m
    /// @return
    GsSizeF ShrunkBy(GsMarginsF m) const noexcept;


    /// @brief 尺寸代表的面积
    /// @return
    float Area() const;

    inline GsSizeF &operator+=(const GsSizeF &) noexcept;
    inline GsSizeF &operator-=(const GsSizeF &) noexcept;
    inline GsSizeF &operator*=(float c) noexcept;
    inline GsSizeF &operator/=(float c);

    friend inline bool operator==(const GsSizeF &, const GsSizeF &) noexcept;
    friend inline bool operator!=(const GsSizeF &, const GsSizeF &) noexcept;
    friend inline const GsSizeF operator+(const GsSizeF &, const GsSizeF &) noexcept;
    friend inline const GsSizeF operator-(const GsSizeF &, const GsSizeF &) noexcept;
    friend inline const GsSizeF operator*(const GsSizeF &, float) noexcept;
    friend inline const GsSizeF operator*(float, const GsSizeF &) noexcept;
    friend inline const GsSizeF operator/(const GsSizeF &, float);

    inline GsSize toSize() const noexcept;
};


/// @brief int类型矩形结构
struct UTILITY_EXPORT GsRect
{
    int Left;
    int Top;
    int Right;
    int Bottom;

    /// @brief 默认构造
    GsRect() noexcept;
    /// @brief 由左上角点和右下角点构造
    /// @param topleft
    /// @param bottomright
    GsRect(const GsPT &topleft, const GsPT &bottomright) noexcept;
    /// @brief 由左上角点和尺寸构造
    /// @param topleft
    /// @param size
    GsRect(const GsPT &topleft, const GsSize &size) noexcept;
    /// @brief 由左上角点坐标和矩形宽高构造
    /// @param left
    /// @param top
    /// @param width
    /// @param height
    GsRect(int left, int top, int width, int height) noexcept;

    inline bool IsNull() const noexcept;
    inline bool IsEmpty() const noexcept;
    inline bool IsValid() const noexcept;

    /// @brief 矩形正则化
    /// @details 返回一个标准化的矩形,即具有非负宽度和高度的矩形
    /// @return
    GsRect Normalized() const noexcept;

    /// @brief 设置左上角点
    /// @param p
    inline void TopLeft(const GsPT &p) noexcept;
    /// @brief 设置右下角点
    /// @param p
    inline void BottomRight(const GsPT &p) noexcept;
    /// @brief 设置右上角点
    /// @param p
    inline void TopRight(const GsPT &p) noexcept;
    /// @brief 设置左下角点
    /// @param p
    inline void BottomLeft(const GsPT &p) noexcept;

    /// @brief 获取左上角点
    /// @return
    inline GsPT TopLeft() const noexcept;
    /// @brief 获取右下角点
    /// @return
    inline GsPT BottomRight() const noexcept;
    /// @brief 获取右上角点
    /// @return
    inline GsPT TopRight() const noexcept;
    /// @brief 获取左下角点
    /// @return
    inline GsPT BottomLeft() const noexcept;
    /// @brief 获取中心点
    /// @return
    inline GsPT Center() const noexcept;

    /// @brief 水平移动矩形，使矩形的左边缘位于给定的x坐标处
    /// @param pos
    inline void MoveLeft(int pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的上边缘位于给定的y坐标处
    /// @param pos
    inline void MoveTop(int pos) noexcept;
    /// @brief 水平移动矩形，使矩形的右边缘位于给定的x坐标处
    /// @param pos
    inline void MoveRight(int pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的底边位于给定的y坐标处
    /// @param pos
    inline void MoveBottom(int pos) noexcept;
    /// @brief 移动矩形，将左上角留在指定位置
    /// @param p
    inline void MoveTopLeft(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    inline void MoveBottomRight(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右上角留在指定位置
    /// @param p
    inline void MoveTopRight(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    inline void MoveBottomLeft(const GsPT &p) noexcept;
    /// @brief 移动矩形，将中心点留在给定位置
    /// @param p
    inline void MoveCenter(const GsPT &p) noexcept;

    /// @brief 相对于当前位置，沿x轴移动矩形dx，沿y轴移动矩形dy
    /// @param dx
    /// @param dy
    inline void Translate(int dx, int dy) noexcept;
    inline void Translate(const GsPT &p) noexcept;
    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param dx
    /// @param dy
    /// @return
    inline GsRect Translated(int dx, int dy) const noexcept;
    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param p
    /// @return
    inline GsRect Translated(const GsPT &p) const noexcept;
    /// @brief 返回交换了宽度和高度的矩形的副本
    /// @return
    inline GsRect Transposed() const noexcept;

    /// @brief 移动矩形，将左上角留在给定位置
    /// @param x
    /// @param t
    inline void MoveTo(int x, int ay) noexcept;
    inline void MoveTo(const GsPT &p) noexcept;

    /// @brief 将矩形左上角的坐标设置为（x，y），并将其大小设置为给定的宽度和高度
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    inline void Rect(int x, int y, int w, int h) noexcept;
    /// @brief 将矩形左上角的位置提取为*x和*y，将其尺寸提取为*width和*height
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    inline void Rect(int *x, int *y, int *w, int *h) const;

    /// @brief 将矩形左上角的坐标设置为（x1，y1），右下角的坐标设定为（x2，y2）
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    inline void Coords(int x1, int y1, int x2, int y2) noexcept;
    /// @brief 将矩形左上角的位置提取为*x1和*y1，将右下角的位置抽取为*x2和*y2
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    inline void Coords(int *x1, int *y1, int *x2, int *y2) const;

    /// @brief 将dx1、dy1、dx2和dy2分别添加到矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    inline void Adjust(int x1, int y1, int x2, int y2) noexcept;
    /// @brief 返回一个新矩形，其中dx1、dy1、dx2和dy2分别添加到此矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    /// @return
    inline GsRect Adjusted(int x1, int y1, int x2, int y2) const noexcept;

    inline GsSize Size() const noexcept;
    inline void Size(const GsSize &s) noexcept;
    inline int Width() const noexcept;
    inline int Height() const noexcept;
    inline void Width(int w) noexcept;
    inline void Height(int h) noexcept;

    /// @brief 返回此矩形和给定矩形的边界矩形
    /// @param r
    /// @return
    GsRect operator|(const GsRect &r) const noexcept;
    /// @brief 返回此矩形与给定矩形的交集如果没有交集，则返回一个空矩形
    /// @param r
    /// @return
    GsRect operator&(const GsRect &r) const noexcept;
    inline GsRect &operator|=(const GsRect &r) noexcept;
    inline GsRect &operator&=(const GsRect &r) noexcept;

    /// @brief 如果给定点位于矩形内部或边缘，则返回true，否则返回false
    /// @details 如果 \a proper 为true，则仅当给定点在矩形内部（即，不在边上）时，此函数才返回true
    /// @param r
    /// @param proper
    /// @return
    bool Contains(const GsRect &r, bool proper = false) const noexcept;
    bool Contains(const GsPT &p, bool proper = false) const noexcept;
    inline bool Contains(int x, int y) const noexcept;
    inline bool Contains(int x, int y, bool proper) const noexcept;
    /// @brief 返回两个矩形合并之后的大矩形
    /// @param other
    /// @return
    inline GsRect United(const GsRect &other) const noexcept;
    /// @brief 返回两个矩形相交部分，如果不相交则返回空矩形
    /// @param other
    /// @return
    inline GsRect Intersected(const GsRect &other) const noexcept;
    /// @brief 判断两个几何是否相交
    /// @param r
    /// @return
    bool Intersects(const GsRect &r) const noexcept;

    /// @brief 返回按边距增长的矩形
    /// @param margins
    /// @return
    inline GsRect MarginsAdded(const GsMargins &margins) const noexcept;
    /// @brief 返回按边距减少的矩形
    /// @param margins
    /// @return
    inline GsRect MarginsRemoved(const GsMargins &margins) const noexcept;
    inline GsRect &operator+=(const GsMargins &margins) noexcept;
    inline GsRect &operator-=(const GsMargins &margins) noexcept;

    friend inline bool operator==(const GsRect &, const GsRect &) noexcept;
    friend inline bool operator!=(const GsRect &, const GsRect &) noexcept;
};


/// @brief float矩形结构
struct UTILITY_EXPORT GsRectF
{
    float Left;
    float Top;
    float Right;
    float Bottom;

    /// @brief 默认构造
    GsRectF() noexcept;
    /// @brief 由左上角点和右下角点构造
    /// @param topleft
    /// @param bottomRight
    GsRectF(const GsPTF &topleft, const GsPTF &bottomRight) noexcept;
    /// @brief 由左上角点和尺寸构造
    /// @param topleft
    /// @param size
    GsRectF(const GsPTF &topleft, const GsSizeF &size) noexcept;
    /// @brief 由左上角点坐标和矩形宽高构造
    /// @param left
    /// @param top
    /// @param width
    /// @param height
    GsRectF(float left, float top, float width, float height) noexcept;
    /// @brief 由整型矩形构造
    /// @param rect
    GsRectF(const GsRect &rect) noexcept;

    inline bool IsNull() const noexcept;
    inline bool IsEmpty() const noexcept;
    inline bool IsValid() const noexcept;

    /// @brief 矩形正则化
    /// @details 返回一个标准化的矩形,即具有非负宽度和高度的矩形
    /// @return
    GsRectF Normalized() const noexcept;

    /// @brief 获取左上角点
    /// @return
    inline GsPTF TopLeft() const noexcept;
    /// @brief 获取右下角点
    /// @return
    inline GsPTF BottomRight() const noexcept;
    /// @brief 获取右上角点
    /// @return
    inline GsPTF TopRight() const noexcept;
    /// @brief 获取左下角点
    /// @return
    inline GsPTF BottomLeft() const noexcept;
    /// @brief 获取中心点
    /// @return
    inline GsPTF Center() const noexcept;

    /// @brief 设置左上角点
    /// @param p
    inline void TopLeft(const GsPTF &p) noexcept;
    /// @brief 设置右下角点
    /// @param p
    inline void BottomRight(const GsPTF &p) noexcept;
    /// @brief 设置右上角点
    /// @param p
    inline void TopRight(const GsPTF &p) noexcept;
    /// @brief 设置左下角点
    /// @param p
    inline void BottomLeft(const GsPTF &p) noexcept;

    /// @brief 水平移动矩形，使矩形的左边缘位于给定的x坐标处
    /// @param pos
    inline void MoveLeft(float pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的上边缘位于给定的y坐标处
    /// @param pos
    inline void MoveTop(float pos) noexcept;
    /// @brief 水平移动矩形，使矩形的右边缘位于给定的x坐标处
    /// @param pos
    inline void MoveRight(float pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的底边位于给定的y坐标处
    /// @param pos
    inline void MoveBottom(float pos) noexcept;
    /// @brief 移动矩形，将左上角留在指定位置
    /// @param p
    inline void MoveTopLeft(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    inline void MoveBottomRight(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右上角留在指定位置
    /// @param p
    inline void MoveTopRight(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    inline void MoveBottomLeft(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将中心点留在给定位置
    /// @param p
    inline void MoveCenter(const GsPTF &p) noexcept;

    /// @brief 相对于当前位置，沿x轴移动矩形dx，沿y轴移动矩形dy
    /// @param dx
    /// @param dy
    inline void Translate(float dx, float dy) noexcept;
    inline void Translate(const GsPTF &p) noexcept;

    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param dx
    /// @param dy
    /// @return
    inline GsRectF Translated(float dx, float dy) const noexcept;
    inline GsRectF Translated(const GsPTF &p) const noexcept;
    inline GsRectF Transposed() const noexcept;

    /// @brief 返回交换了宽度和高度的矩形的副本
    /// @param x
    /// @param y
    inline void MoveTo(float x, float y) noexcept;
    inline void MoveTo(const GsPTF &p) noexcept;
    /// @brief 将矩形左上角的坐标设置为（x，y），并将其大小设置为给定的宽度和高度
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    inline void Rect(float x, float y, float w, float h) noexcept;
    /// @brief 将矩形左上角的位置提取为*x和*y，将其尺寸提取为*width和*height
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    inline void Rect(float *x, float *y, float *w, float *h) const;
    /// @brief 将矩形左上角的坐标设置为（x1，y1），右下角的坐标设定为（x2，y2）
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    inline void Coords(float x1, float y1, float x2, float y2) noexcept;
    inline void Coords(float *x1, float *y1, float *x2, float *y2) const;

    /// @brief 将dx1、dy1、dx2和dy2分别添加到矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    inline void Adjust(float x1, float y1, float x2, float y2) noexcept;
    /// @brief 返回一个新矩形，其中dx1、dy1、dx2和dy2分别添加到此矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    /// @return
    inline GsRectF Adjusted(float x1, float y1, float x2, float y2) const noexcept;

    inline GsSizeF Size() const noexcept;
    inline void Size(const GsSizeF &s) noexcept;
    inline float Width() const noexcept;
    inline float Height() const noexcept;
    inline void Width(float w) noexcept;
    inline void Height(float h) noexcept;

    /// @brief 返回此矩形和给定矩形的边界矩形
    /// @param r
    /// @return
    GsRectF operator|(const GsRectF &r) const noexcept;
    GsRectF operator&(const GsRectF &r) const noexcept;
    /// @brief 返回此矩形与给定矩形的交集如果没有交集，则返回一个空矩形
    /// @param r
    /// @return
    inline GsRectF &operator|=(const GsRectF &r) noexcept;
    inline GsRectF &operator&=(const GsRectF &r) noexcept;

    /// @brief 如果给定点位于矩形内部或边缘，则返回true，否则返回false
    /// @param r
    /// @return
    bool Contains(const GsRectF &r) const noexcept;
    bool Contains(const GsPTF &p) const noexcept;
    inline bool Contains(float x, float y) const noexcept;
    /// @brief 返回两个矩形合并之后的大矩形
    /// @param other
    /// @return
    inline GsRectF United(const GsRectF &other) const noexcept;
    /// @brief 返回两个矩形相交部分，如果不相交则返回空矩形
    /// @param other
    /// @return
    inline GsRectF Intersected(const GsRectF &other) const noexcept;
    /// @brief 判断两个几何是否相交
    /// @param r
    /// @return
    bool Intersects(const GsRectF &r) const noexcept;

    /// @brief 返回按边距增长的矩形
    /// @param margins
    /// @return
    inline GsRectF MarginsAdded(const GsMarginsF &margins) const noexcept;
    /// @brief 返回按边距减少的矩形
    /// @param margins
    /// @return
    inline GsRectF MarginsRemoved(const GsMarginsF &margins) const noexcept;
    inline GsRectF &operator+=(const GsMarginsF &margins) noexcept;
    inline GsRectF &operator-=(const GsMarginsF &margins) noexcept;

    friend inline bool operator==(const GsRectF &, const GsRectF &) noexcept;
    friend inline bool operator!=(const GsRectF &, const GsRectF &) noexcept;

    /// @brief 转换为整型矩形
    /// @return
    inline GsRect ToRect() const noexcept;
    GsRect ToAlignedRect() const noexcept;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/// @brief 颜色通道类型
enum GsImageColoType
{
    /// @brief 8bit的灰度图像
    eGRAY8Bit,
    /// @brief BGRA结构，每位占据一个char
    eBGRA32Bit,
    /// @brief ABGR结构，每位占据一个char
    eABGR32Bit,
    /// @brief RGBA结构，每位占据一个char
    eRGBA32Bit,
    /// @brief ARGB结构，每位占据一个char
    eARGB32Bit,
    /// @brief 24位真彩色。每个像素采用3个字节来表示
    eRGB24Bit,
    /// @brief 与RGB格式类似
    eBGR24Bit,
};

/// @brief 图像转换的模式
enum GsImageTransformationMode
{
    /// @brief 快速转换，优先考虑效率
    eFastTransformation,
    /// @brief 平滑转换，像素值变化更加平滑，效率较低
    eSmoothTransformation
};

/// @brief 常见的图像编码方式
/// @details https://docs.fileformat.com/image/
enum class GsImageFormat
{
    eUnknownType,
    ePNG,
    eBMP,
    eXPM,
    eXBM,
    ePPM,
    eDDS,
    eICNS,
    eJP2,
    eMNG,
    eTGA,
    eTIFF,
    eWEBP,
    eGIF,
    eICO,
    eJPEG,
};


/// @brief 图像基类
class UTILITY_EXPORT GsImage
{
public:
    /// @brief 默认析构
    virtual ~GsImage();
    /// @brief 拷贝图像
    /// @param pImage
    /// @return
    virtual bool CopyFrom(GsImage *pImage);
    /// @brief 拷贝外部数据到自身
    /// @param pBuff
    /// @param nLen
    /// @param type
    /// @return
    virtual bool FillImage(const unsigned char *pBuff, int nLen, GsImageColoType type);

    /// @brief 拷贝自身的数据到外部影像
    /// @param pBuff
    /// @param nLen
    /// @param type
    /// @return
    virtual int CopyTo(unsigned char *pBuff, int nLen, GsImageColoType type);

    /// @brief 将自身数据剪裁到目标图像中
    /// @param target 要存储数据的图像
    /// @param rect 要剪裁的数据范围
    /// @param offset 存储到目标数据的偏移位置
    /// @return
    virtual bool CropTo(GsImage *target, const GsRect &rect, const GsPT &offset);

    /// @brief 将自身数据剪裁到目标内存块中
    /// @param target 要存储数据的目标内存
    /// @param nStride 目标数据行字节长度
    /// @param extent 要剪裁的数据范围
    /// @param eType
    /// @return
    virtual bool CropTo(unsigned char *target, int nStride, const GsRect &extent, GsImageColoType eType = GsImageColoType::eRGBA32Bit);

    /// @brief 将自身数据剪裁到目标内存块中
    /// @param target 要存储数据的目标内存
    /// @param nStride 目标数据行字节长度
    /// @param extent 要剪裁的数据范围
    /// @param eType
    /// @return
    virtual bool CropTo(GsByteBuffer *target, int nStride, const GsRect &extent, GsImageColoType eType = GsImageColoType::eRGBA32Bit);

    /// @brief 获取图片颜色格式
    /// @return
    virtual GsImageColoType RGBAType();
    /// @brief 影像的宽和高
    virtual GsSize Size();

    /// @brief 获得宽度
    /// @return
    virtual unsigned int Width() = 0;
    /// @brief 获得高度
    /// @return
    virtual unsigned int Height() = 0;

    /// @brief 获取图像的字节数组，并非所有图像都能够成功
    /// @return
    virtual const unsigned char *Bit() = 0;

    /// @brief 图像缩放，内部会根据大小重采样
    /// @param w
    /// @param h
    /// @param eMode
    /// @return
    virtual GsImage *Scaled(int w, int h, GsImageTransformationMode eMode = GsImageTransformationMode::eFastTransformation);

    unsigned char *ScanLine(int);
    const unsigned char *ScanLine(int) const;
    long long BytesPerLine() const;

    bool Valid(int x, int y) const;
    bool Valid(const GsPT &pt) const;

    int PixelIndex(int x, int y) const;
    int PixelIndex(const GsPT &pt) const;

    GsColor Pixel(int x, int y) const;
    GsColor Pixel(const GsPT &pt) const;

    void Pixel(int x, int y, unsigned int index_or_rgb);
    void Pixel(const GsPT &pt, unsigned int index_or_rgb);

    GsColor PixelColor(int x, int y) const;
    GsColor PixelColor(const GsPT &pt) const;

    void PixelColor(int x, int y, const GsColor &c);
    void PixelColor(const GsPT &pt, const GsColor &c);

    void Fill(unsigned int pixel);
    void Fill(const GsColor &color);
};
GS_SMARTER_PTR(GsImage)


/// @brief 图像读写
class UTILITY_EXPORT GsImageIO
{
public:
    virtual bool CanRead(GsImage *image) = 0;
};

class UTILITY_EXPORT GsBmpImageIO : public GsImageIO
{
public:
    enum GsBmpFormat
    {
        eDibFromat,
        eBmpFormat
    };

    typedef void *BmpFileHeaderHandle;
    typedef void *BmpInfoHeaderHandle;

public:
    GsBmpImageIO(GsBmpFormat format = eBmpFormat);

private:
    GsBmpFormat m_format;
    BmpFileHeaderHandle fileHeader;
    BmpInfoHeaderHandle infoHeader;
    unsigned long long offset;
};

class UTILITY_EXPORT GsPNGImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsGifImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsWebpImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsSvgImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsTiffImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsPpmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsXbmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsXpmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsICOImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsDDSImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsTgaImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsWbmpImageIO : public GsImageIO
{
};

/// @brief 图像处理
class GsImageProcess
{
public:
    //高斯滤波
    //中值滤波
    //双边滤波

    //Sobel算子
    //Scharr算子
    //拉普拉斯算子
    //Canny算子

    //角点检测
    //ORB算法
    //SIFT算法
    //傅里叶变换
    //二值化
    //图像混合
};


}// namespace m2


#include "shape.inl"