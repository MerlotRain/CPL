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

/// @brief Java like BigInteger
class UTILITY_EXPORT GsBigInteger
{
public:
    /// @brief 默认构造
    /// @param number
    GsBigInteger(GsString number);
    /// @brief 有64为有符号整型构造
    /// @param number
    GsBigInteger(long long number);

    /// @brief 两数相加
    /// @param other
    /// @return
    GsBigInteger Add(GsBigInteger other);

    /// @brief 两数相减
    /// @param other
    /// @return
    GsBigInteger Subtract(GsBigInteger other);

    /// @brief 两数相乘
    /// @param other
    /// @return
    GsBigInteger Multiply(GsBigInteger other);

    /// @brief 两数相除
    /// @param other
    /// @return
    GsBigInteger Divide(GsBigInteger other);

    /// @brief 将当前数提升为指数的幂
    /// @param exponent
    /// @return
    GsBigInteger Pow(int exponent);

    /// @brief 获取字符串值
    /// @return
    GsString ToString();

    /// @brief 替换字符串值
    /// @param newStr
    /// @return
    GsBigInteger SetString(const GsString &newStr);

    /// @brief 求当前值的相反数
    /// @return
    GsBigInteger Negate();

    /// @brief 清理前置无效零
    /// @return
    GsBigInteger TrimLeadingZeros();

    /// @brief 判断两个数是否相等
    /// @param other
    /// @return
    bool Equals(const GsBigInteger &other);
    bool Equals(const long long &other);
    bool Equals(const GsString &other);

    /// @brief 获取当前数的位数
    /// @return
    unsigned int Digits();

    /// @brief 判断当前数是否是负数
    /// @return
    bool IsNegative() const;

    /// @brief 判断当前数是否是正数
    /// @return
    bool isPositive();

    /// @brief 判断当前数是否为偶数
    /// @return
    bool IsEven();

    /// @brief 判断当前数是否为奇数
    /// @return
    bool IsOdd();

    /// @brief 当前数求绝对值
    /// @return
    GsBigInteger Abs() const;

    /// @brief 重载+运算符
    /// @param b1
    /// @param b2
    /// @return
    friend GsBigInteger operator+(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator+(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator+(GsBigInteger b1, const GsString &b2);

    /// @brief 重载-运算符
    /// @param b1
    /// @param b2
    /// @return
    friend GsBigInteger operator-(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator-(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator-(GsBigInteger b1, const GsString &b2);

    /// @brief 重载*运算符
    /// @param b1
    /// @param b2
    /// @return
    friend GsBigInteger operator*(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator*(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator*(GsBigInteger b1, const GsString &b2);

    /// @brief 重载/运算符
    /// @param b1
    /// @param b2
    /// @return
    friend GsBigInteger operator/(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator/(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator/(GsBigInteger b1, const GsString &b2);

    /// @brief 重载^运算符
    /// @param b1
    /// @param b2
    /// @return
    friend GsBigInteger operator^(GsBigInteger b1, const int &b2);

    /// @brief 重载==运算符
    /// @param b1
    /// @param b2
    /// @return
    friend bool operator==(GsBigInteger b1, const GsBigInteger &b2);
    friend bool operator==(GsBigInteger b1, const long long &b2);
    friend bool operator==(GsBigInteger b1, const GsString &b2);

    /// @brief 重载>运算符
    /// @param b1
    /// @param b2
    /// @return
    friend bool operator>(GsBigInteger b1, const GsBigInteger &b2);

    /// @brief 重载<运算符
    /// @param b1
    /// @param b2
    /// @return
    friend bool operator<(GsBigInteger b1, const GsBigInteger &b2);

    /// @brief 重载>=运算符
    /// @param b1
    /// @param b2
    /// @return
    friend bool operator>=(GsBigInteger b1, const GsBigInteger &b2);

    /// @brief 重载<=运算符
    /// @param b1
    /// @param b2
    /// @return
    friend bool operator<=(GsBigInteger b1, const GsBigInteger &b2);

    /// @brief 赋值复制构造
    /// @param other
    /// @return
    GsBigInteger &operator=(const GsBigInteger &other);
    GsBigInteger &operator=(const long long &other);
    GsBigInteger &operator=(const GsString &other);

    /// @brief 重载+=运算符
    /// @param other
    /// @return
    GsBigInteger &operator+=(const GsBigInteger &other);
    GsBigInteger &operator+=(const long long &other);
    GsBigInteger &operator+=(const GsString &other);

    /// @brief 重载-=运算符
    /// @param other
    /// @return
    GsBigInteger &operator-=(const GsBigInteger &other);
    GsBigInteger &operator-=(const long long &other);
    GsBigInteger &operator-=(const GsString &other);

    /// @brief 重载*=运算符
    /// @param other
    /// @return
    GsBigInteger &operator*=(const GsBigInteger &other);
    GsBigInteger &operator*=(const long long &other);
    GsBigInteger &operator*=(const GsString &other);

    /// @brief 重载/=运算符
    /// @param other
    /// @return
    GsBigInteger &operator/=(const GsBigInteger &other);
    GsBigInteger &operator/=(const long long &other);
    GsBigInteger &operator/=(const GsString &other);

    /// @brief 重载++运算符
    /// @return
    GsBigInteger &operator++();
    const GsBigInteger operator++(int);

    /// @brief 重载--运算符
    /// @return
    GsBigInteger &operator--();
    const GsBigInteger operator--(int);
    /// @brief 重载[]运算符
    /// @param index
    /// @return
    unsigned int operator[](int index);

private:
    GsString m_Value;

    GsBigInteger Addll(const long long &other);
    GsBigInteger Addstr(const GsString &other);
    GsBigInteger Subtractll(const long long &other);
    GsBigInteger Subtractstr(const GsString &other);
    GsBigInteger Multiplyll(const long long &other);
    GsBigInteger Multiplystr(const GsString &other);
    GsBigInteger Dividell(const long long &other);
    GsBigInteger Dividestr(const GsString &other);
};


}// namespace m2
