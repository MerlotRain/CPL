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

#ifndef M2_BIGINTEGER_H_
#define M2_BIGINTEGER_H_

#include <m2_string.h>

namespace m2 {

class M2_API GsBigInteger
{
public:
    explicit GsBigInteger(String number);
    explicit GsBigInteger(long long v);
    explicit GsBigInteger(int v) noexcept;
    explicit GsBigInteger(long long v) noexcept;
    explicit GsBigInteger(unsigned int v) noexcept;
    explicit GsBigInteger(unsigned long long v) noexcept;

    GsBigInteger &operator=(const GsBigInteger &rhs);
    GsBigInteger &operator=(const long long &rhs);
    GsBigInteger &operator=(const String &rhs);
    GsBigInteger &operator+=(const GsBigInteger &rhs);
    GsBigInteger &operator+=(const long long &rhs);
    GsBigInteger &operator+=(const String &rhs);
    GsBigInteger &operator-=(const GsBigInteger &rhs);
    GsBigInteger &operator-=(const long long &rhs);
    GsBigInteger &operator-=(const String &rhs);
    GsBigInteger &operator*=(const GsBigInteger &rhs);
    GsBigInteger &operator*=(const long long &rhs);
    GsBigInteger &operator*=(const String &rhs);
    GsBigInteger &operator/=(const GsBigInteger &rhs);
    GsBigInteger &operator/=(const long long &rhs);
    GsBigInteger &operator/=(const String &rhs);

    GsBigInteger &operator++();
    const GsBigInteger operator++(int);
    GsBigInteger &operator--();
    const GsBigInteger operator--(int);

    unsigned int operator[](int index);

    friend GsBigInteger operator+(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator+(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator+(GsBigInteger b1, const String &b2);
    friend GsBigInteger operator-(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator-(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator-(GsBigInteger b1, const String &b2);
    friend GsBigInteger operator*(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator*(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator*(GsBigInteger b1, const String &b2);
    friend GsBigInteger operator/(GsBigInteger b1, const GsBigInteger &b2);
    friend GsBigInteger operator/(GsBigInteger b1, const long long &b2);
    friend GsBigInteger operator/(GsBigInteger b1, const String &b2);
    friend GsBigInteger operator^(GsBigInteger b1, const int &b2);
    friend bool operator==(GsBigInteger b1, const GsBigInteger &b2);
    friend bool operator==(GsBigInteger b1, const long long &b2);
    friend bool operator==(GsBigInteger b1, const String &b2);
    friend bool operator>(GsBigInteger b1, const GsBigInteger &b2);
    friend bool operator<(GsBigInteger b1, const GsBigInteger &b2);
    friend bool operator>=(GsBigInteger b1, const GsBigInteger &b2);
    friend bool operator<=(GsBigInteger b1, const GsBigInteger &b2);

    GsBigInteger add(GsBigInteger rhs);
    GsBigInteger subtract(GsBigInteger rhs);
    GsBigInteger multiply(GsBigInteger rhs);
    GsBigInteger divide(GsBigInteger rhs);
    GsBigInteger pow(int exponent);

    String toString();
    GsBigInteger setString(const String &newStr);
    GsBigInteger negate();
    GsBigInteger trimLeadingZeros();

    bool equals(const GsBigInteger &rhs) const;
    bool equals(const long long &rhs) const;
    bool equals(const String &rhs) const;
    unsigned int digits();
    bool isNegative() const;
    bool isPositive() const;
    bool IsEven() const;
    bool IsOdd() const;
    GsBigInteger abs() const;


private:
    GsBigInteger addll(const long long &rhs);
    GsBigInteger addstr(const String &rhs);
    GsBigInteger subtractll(const long long &rhs);
    GsBigInteger subtractstr(const String &rhs);
    GsBigInteger multiplyll(const long long &rhs);
    GsBigInteger multiplystr(const String &rhs);
    GsBigInteger dividell(const long long &rhs);
    GsBigInteger dividestr(const String &rhs);

private:
    String value;
};

}// namespace m2

#endif//M2_BIGINTEGER_H_