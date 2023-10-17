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

#ifndef M2_BIGDECIMAL_H_
#define M2_BIGDECIMAL_H_

#include <m2_string.h>

namespace m2 {

class M2_API BigDecimal
{
public:
    BigDecimal() noexcept;
    explicit BigDecimal(const BigDecimal &rhs) noexcept;
    explicit BigDecimal(const char *v);
    BigDecimal(String v);
    explicit BigDecimal(int v) noexcept;
    explicit BigDecimal(long long v) noexcept;
    explicit BigDecimal(unsigned int v) noexcept;
    explicit BigDecimal(unsigned long long v) noexcept;
    explicit BigDecimal(float v) noexcept;
    explicit BigDecimal(double v) noexcept;
    explicit BigDecimal(long double v) noexcept;

    BigDecimal operator+(const BigDecimal &rhs);
    BigDecimal operator-(const BigDecimal &rhs);
    BigDecimal operator*(const BigDecimal &rhs);
    BigDecimal operator/(const BigDecimal &rhs);
    BigDecimal operator%(const BigDecimal &rhs);
    BigDecimal operator^(const BigDecimal &rhs);

    void operator+=(const BigDecimal &rhs);
    void operator-=(const BigDecimal &rhs);
    void operator*=(const BigDecimal &rhs);
    void operator/=(const BigDecimal &rhs);
    void operator^=(const BigDecimal &rhs);
    bool operator>(const BigDecimal &rhs);
    bool operator>=(const BigDecimal &rhs);
    bool operator==(const BigDecimal &rhs);
    bool operator<(const BigDecimal &rhs);
    bool operator<=(const BigDecimal &rhs);

    int toInt();
    unsigned int toUInt();
    long long toLongLong();
    unsigned long long toULongLong();
    long double toLongDouble();
    double toDouble();
    float toFloat();
    String toString();
    void round(int scale);
    String integerPart();
    String decimalPart();

    static void scale(int scale);
    static String divide(const String &lhs, const String &rhs,
                         int scale = INT_MIN);
    static String modulus(const String &lhs, const String &rhs,
                          int scale = INT_MIN);
    static String pow(const String &lhs, const String &rhs,
                      int scale = INT_MIN);
    static String add(const String &lhs, const String &rhs,
                      int scale = INT_MIN);
    static String subtract(const String &lhs, const String &rhs,
                           int scale = INT_MIN);
    static String multiply(const String &lhs, const String &rhs,
                           int scale = INT_MIN);
    static String round(const String &lhs, int scale = INT_MIN);
    static int compareTo(const String &lhs, const String &rhs,
                         int scale = INT_MIN);
    static String log2(const String &lhs, int scale = INT_MIN);
    static String ln(const String &lhs, int scale = INT_MIN);
    static String log(const String &lhs, int scale = INT_MIN);
    static String sin(const String &lhs, int scale = INT_MIN);
    static String stringToHex(String &lhs, int caps = 0);

private:
    String value;
};

}// namespace m2

#endif//M2_BIGDECIMAL_H_