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

#include "stringhelp.h"

namespace m2 {


/// @brief 类Java BigDecimal，解决需要高精度处理数据的地方，例如金额
class UTILITY_EXPORT GsBigDecimal
{
public:
    /// @brief 默认构造
    GsBigDecimal() noexcept;

    /// @brief 拷贝构造
    /// @param v
    GsBigDecimal(const GsBigDecimal &rhs) noexcept;

    /// @brief 由字符串构造
    /// @param v
    GsBigDecimal(const char *v);

    /// @brief 由字符串构造
    /// @param v
    GsBigDecimal(GsString v);

    /// @brief 由32位有符号整型构造
    /// @param v
    GsBigDecimal(int v) noexcept;

    /// @brief 由64位有符号整型构造
    /// @param v
    GsBigDecimal(long long v) noexcept;

    /// @brief 由32位无符号整型构造
    /// @param v
    GsBigDecimal(unsigned int v) noexcept;

    /// @brief 由64位无符号整型构造
    /// @param v
    GsBigDecimal(unsigned long long v) noexcept;

    /// @brief 由float构造
    /// @param v
    GsBigDecimal(float v) noexcept;

    /// @brief 由double构造
    /// @param v
    GsBigDecimal(double v) noexcept;

    /// @brief 由长double构造
    /// @param v
    GsBigDecimal(long double v) noexcept;

    /// @brief 重载+运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator+(const GsBigDecimal &rhs);

    /// @brief 重载-运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator-(const GsBigDecimal &rhs);

    /// @brief 重载*运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator*(const GsBigDecimal &rhs);

    /// @brief 重载/运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator/(const GsBigDecimal &rhs);

    /// @brief 重载%运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator%(const GsBigDecimal &rhs);

    /// @brief 重载^运算符
    /// @param rhs
    /// @return
    GsBigDecimal operator^(const GsBigDecimal &rhs);

    /// @brief 重载+=运算符
    /// @param rhs
    void operator+=(const GsBigDecimal &rhs);

    /// @brief 重载-=运算符
    /// @param rhs
    void operator-=(const GsBigDecimal &rhs);

    /// @brief 重载*=运算符
    /// @param rhs
    void operator*=(const GsBigDecimal &rhs);

    /// @brief 重载/=运算符
    /// @param rhs
    void operator/=(const GsBigDecimal &rhs);

    /// @brief 重载^=运算符
    /// @param rhs
    void operator^=(const GsBigDecimal &rhs);

    /// @brief 重载>运算符
    /// @param rhs
    /// @return
    bool operator>(const GsBigDecimal &rhs);

    /// @brief 重载>=运算符
    /// @param rhs
    /// @return
    bool operator>=(const GsBigDecimal &rhs);

    /// @brief 重载==运算符
    /// @param rhs
    /// @return
    bool operator==(const GsBigDecimal &rhs);

    /// @brief 重载<运算符
    /// @param rhs
    /// @return
    bool operator<(const GsBigDecimal &rhs);

    /// @brief 重载<=运算符
    /// @param rhs
    /// @return
    bool operator<=(const GsBigDecimal &rhs);

    /// @brief 转换为有符号32位整型
    /// @return
    int ToInt();

    /// @brief 转换为无符号32位整型
    /// @return
    unsigned int ToUInt();

    /// @brief 转换为有符号64位整型
    /// @return
    long long ToLongLong();

    /// @brief 转换为无符号64位整型
    /// @return
    unsigned long long ToULongLong();

    /// @brief 转换为长double类型
    /// @return
    long double ToLongDouble();

    /// @brief 转换为double类型
    /// @return
    double ToDouble();

    /// @brief 转换为float类型
    /// @return
    float ToFloat();

    /// @brief 转换为字符串类型
    /// @return
    GsString ToString();

    /// @brief 四舍五入
    /// @param scale
    void Round(int scale);

    /// @brief 整数部分
    /// @return
    GsString IntPart();

    /// @brief 小数部分
    /// @return
    GsString DecPart();

    /// @brief 精度值
    /// @param scale
    static void Scale(int scale);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Divide(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Modulus(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Pow(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Add(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Subtract(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static GsString Multiply(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param scale
    /// @return
    static GsString Round(const GsString &lhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param rhs
    /// @param scale
    /// @return
    static int CompareTo(const GsString &lhs, const GsString &rhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param scale
    /// @return
    static GsString Log2(const GsString &lhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param scale
    /// @return
    static GsString Ln(const GsString &lhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param scale
    /// @return
    static GsString Log(const GsString &lhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param scale
    /// @return
    static GsString Sin(const GsString &lhs, int scale = INT_MIN);

    /// @brief
    /// @param lhs
    /// @param caps
    /// @return
    static GsString StringToHex(GsString &lhs, int caps = 0);

private:
    GsString m_Value;
};


}// namespace m2
