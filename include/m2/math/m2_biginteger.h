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

class M2_API BigInteger
{
public:
    BigInteger(const String &);
    BigInteger(int v) noexcept;
    BigInteger(long long v) noexcept;
    BigInteger(unsigned int v) noexcept;
    BigInteger(unsigned long long v) noexcept;

    BigInteger &operator=(const BigInteger &rhs);
    BigInteger &operator=(const long long &rhs);
    BigInteger &operator=(const String &rhs);
    BigInteger &operator+=(const BigInteger &rhs);
    BigInteger &operator+=(const long long &rhs);
    BigInteger &operator+=(const String &rhs);
    BigInteger &operator-=(const BigInteger &rhs);
    BigInteger &operator-=(const long long &rhs);
    BigInteger &operator-=(const String &rhs);
    BigInteger &operator*=(const BigInteger &rhs);
    BigInteger &operator*=(const long long &rhs);
    BigInteger &operator*=(const String &rhs);
    BigInteger &operator/=(const BigInteger &rhs);
    BigInteger &operator/=(const long long &rhs);
    BigInteger &operator/=(const String &rhs);

    BigInteger &operator++();
    const BigInteger operator++(int);
    BigInteger &operator--();
    const BigInteger operator--(int);

    unsigned int operator[](int index);

    friend BigInteger operator+(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator+(BigInteger b1, const long long &b2);
    friend BigInteger operator+(BigInteger b1, const String &b2);
    friend BigInteger operator-(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator-(BigInteger b1, const long long &b2);
    friend BigInteger operator-(BigInteger b1, const String &b2);
    friend BigInteger operator*(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator*(BigInteger b1, const long long &b2);
    friend BigInteger operator*(BigInteger b1, const String &b2);
    friend BigInteger operator/(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator/(BigInteger b1, const long long &b2);
    friend BigInteger operator/(BigInteger b1, const String &b2);
    friend BigInteger operator^(BigInteger b1, const int &b2);
    friend bool operator==(BigInteger b1, const BigInteger &b2);
    friend bool operator==(BigInteger b1, const long long &b2);
    friend bool operator==(BigInteger b1, const String &b2);
    friend bool operator>(BigInteger b1, const BigInteger &b2);
    friend bool operator<(BigInteger b1, const BigInteger &b2);
    friend bool operator>=(BigInteger b1, const BigInteger &b2);
    friend bool operator<=(BigInteger b1, const BigInteger &b2);

    BigInteger add(BigInteger rhs);
    BigInteger subtract(BigInteger rhs);
    BigInteger multiply(BigInteger rhs);
    BigInteger divide(BigInteger rhs);
    BigInteger pow(int exponent);

    String toString() const;
    BigInteger setString(const String &newStr);
    BigInteger negative();
    BigInteger trimLeadingZeros();

    bool equals(const BigInteger &rhs) const;
    bool equals(const long long &rhs) const;
    bool equals(const String &rhs) const;
    unsigned int digits();
    bool isNegative() const;
    bool isPositive() const;
    bool isEven() const;
    bool isOdd() const;
    BigInteger abs() const;


private:
    BigInteger addll(const long long &rhs);
    BigInteger addstr(const String &rhs);
    BigInteger subtractll(const long long &rhs);
    BigInteger subtractstr(const String &rhs);
    BigInteger multiplyll(const long long &rhs);
    BigInteger multiplystr(const String &rhs);
    BigInteger dividell(const long long &rhs);
    BigInteger dividestr(const String &rhs);

private:
    String value;
};

}// namespace m2

#endif//M2_BIGINTEGER_H_