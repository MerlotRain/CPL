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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_MATH_H_
#define M2_MATH_H_

#include <cmath>
#include <float.h>

namespace m2 {

inline int qCeil(double v)
{
    using std::ceil;
    return int(ceil(v));
}

inline int qFloor(double v)
{
    using std::floor;
    return int(floor(v));
}

inline double qFabs(double v)
{
    using std::fabs;
    return fabs(v);
}

inline double qSin(double v)
{
    using std::sin;
    return sin(v);
}

inline double qCos(double v)
{
    using std::cos;
    return cos(v);
}

inline double qTan(double v)
{
    using std::tan;
    return tan(v);
}

inline double qAcos(double v)
{
    using std::acos;
    return acos(v);
}

inline double qAsin(double v)
{
    using std::asin;
    return asin(v);
}

inline double qAtan(double v)
{
    using std::atan;
    return atan(v);
}

inline double qAtan2(double y, double x)
{
    using std::atan2;
    return atan2(y, x);
}

inline double qSqrt(double v)
{
    using std::sqrt;
    return sqrt(v);
}

inline double qLn(double v)
{
    using std::log;
    return log(v);
}

inline double qExp(double v)
{
    using std::exp;
    return exp(v);
}

inline double qPow(double x, double y)
{
    using std::pow;
    return pow(x, y);
}


#ifndef M_E
#define M_E (2.7182818284590452354)
#endif

#ifndef M_LOG2E
#define M_LOG2E (1.4426950408889634074)
#endif

#ifndef M_LOG10E
#define M_LOG10E (0.43429448190325182765)
#endif

#ifndef M_LN2
#define M_LN2 (0.69314718055994530942)
#endif

#ifndef M_LN10
#define M_LN10 (2.30258509299404568402)
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_PI_2
#define M_PI_2 (1.57079632679489661923)
#endif

#ifndef M_PI_4
#define M_PI_4 (0.78539816339744830962)
#endif

#ifndef M_1_PI
#define M_1_PI (0.31830988618379067154)
#endif

#ifndef M_2_PI
#define M_2_PI (0.63661977236758134308)
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI (1.12837916709551257390)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237309504880)
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 (0.70710678118654752440)
#endif

#ifndef M_Inch2MM
#define M_Inch2MM (25.4)
#endif

#ifndef M_MM2Inch
#define M_MM2Inch (0.03937007874)
#endif


static constexpr int SINE_TABLE_SIZE = 256;
extern const double sine_table[SINE_TABLE_SIZE];

inline double fastSin(double x)
{
    int si = int(x * (0.5 * SINE_TABLE_SIZE / M_PI));
    double d = x - si * (2.0 * M_PI / SINE_TABLE_SIZE);
    int ci = si + SINE_TABLE_SIZE / 4;
    si &= SINE_TABLE_SIZE - 1;
    ci &= SINE_TABLE_SIZE - 1;
    return sine_table[si] + (sine_table[ci] - 0.5 * sine_table[si] * d) * d;
}


inline double fastCos(double x)
{
    int ci = int(x * (0.5 * SINE_TABLE_SIZE / M_PI));
    double d = x - ci * (2.0 * M_PI / SINE_TABLE_SIZE);
    int si = ci + SINE_TABLE_SIZE / 4;
    si &= SINE_TABLE_SIZE - 1;
    ci &= SINE_TABLE_SIZE - 1;
    return sine_table[si] - (sine_table[ci] + 0.5 * sine_table[si] * d) * d;
}

constexpr inline float degreesToRadians(float degrees)
{
    return degrees * float(M_PI / 180);
}

constexpr inline double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180);
}

constexpr inline float radiansToDegrees(float radians)
{
    return radians * float(180 / M_PI);
}

constexpr inline double radiansToDegrees(double radians)
{
    return radians * (180 / M_PI);
}

inline unsigned int nextPowerOfTwo(unsigned int v)
{
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    ++v;
    return v;
}

inline unsigned long long nextPowerOfTwo(unsigned long long v)
{
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    ++v;
    return v;
}

constexpr inline int nextPowerOfTwo(int v)
{
    return nextPowerOfTwo((unsigned int) (v));
}

constexpr inline long long nextPowerOfTwo(long long v)
{
    return nextPowerOfTwo((unsigned long long) (v));
}

template<typename T>
constexpr inline const T &qMin(const T &a, const T &b)
{
    return (a < b) ? a : b;
}

template<typename T>
constexpr inline const T &qMin3(const T &a, const T &b, const T &c)
{
    return ((a < b && a < c) ? a : (b < c ? b : c));
}

template<typename T>
constexpr inline const T &qMax(const T &a, const T &b)
{
    return (a < b) ? b : a;
}

template<typename T>
constexpr inline const T &qMax3(const T &a, const T &b, const T &c)
{
    return ((a > b && a > c) ? a : (b > c ? b : c));
}

template<typename T>
constexpr inline const T &qound(const T &min, const T &val, const T &max)
{
    return qMax(min, qMin(max, val));
}

constexpr inline int qRound(double d)
{
    return d >= 0.0 ? int(d + 0.5)
                    : int(d - double(int(d - 1)) + 0.5) + int(d - 1);
}
constexpr inline int qRound(float d)
{
    return d >= 0.0f ? int(d + 0.5f)
                     : int(d - float(int(d - 1)) + 0.5f) + int(d - 1);
}
constexpr inline long long qRound64(double d)
{
    return d >= 0.0 ? (long long) (d + 0.5)
                    : (long long) (d - double((long long) (d - 1)) + 0.5) +
                              (long long) (d - 1);
}
constexpr inline long long qRound64(float d)
{
    return d >= 0.0f ? (long long) (d + 0.5f)
                     : (long long) (d - float((long long) (d - 1)) + 0.5f) +
                               (long long) (d - 1);
}

template<typename T>
constexpr inline T qAbs(const T &t)
{
    return t >= 0 ? t : -t;
}

constexpr static inline bool qFuzzyCompare(double d1, double d2)
{
    return (qAbs(d1 - d2) * 1000000000000. <= qMin(qAbs(d1), qAbs(d2)));
}
constexpr static inline bool qFuzzyCompare(float d1, float d2)
{
    return (qAbs(d1 - d2) * 100000.f <= qMin(qAbs(d1), qAbs(d2)));
}

constexpr static inline bool qFuzzyIsNull(double d)
{
    return qAbs(d) <= 0.000000000001;
}
constexpr static inline bool qFuzzyIsNull(float f)
{
    return qAbs(f) <= 0.00001f;
}


template<typename Int>
constexpr inline Int qDiv(Int a, unsigned b)
{
    return (a - (a < 0 ? int(b - 1) : 0)) / int(b);
}


template<typename Int>
constexpr inline Int qMod(Int a, unsigned b)
{
    return a - qDiv(a, b) * b;
}

constexpr static inline bool qIsNull(double x) noexcept { return x == 0.0; }
constexpr static inline bool qIsNull(float x) noexcept { return x == 0.0f; }

inline bool qIsEqual(double a, double b,
                     double epsilon = 4 * DBL_EPSILON) noexcept
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan) { return aIsNan && bIsNan; }

    const double diff = a - b;
    return diff > -epsilon && diff <= epsilon;
}

inline bool qIsEqual(float a, float b, float epsilon = 4 * FLT_EPSILON) noexcept
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan) { return aIsNan && bIsNan; }

    const float diff = a - b;
    return diff > -epsilon && diff <= epsilon;
}

inline bool qIsEqualSignificant(double a, double b, int significantDigits = 10)
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan) { return aIsNan && bIsNan; }

    int aexp, bexp;
    const double ar = std::frexp(a, &aexp);
    const double br = std::frexp(b, &bexp);

    return aexp == bexp &&
           std::round(ar * std::pow(10.0, significantDigits)) ==
                   std::round(br * std::pow(10.0, significantDigits));
}

}// namespace m2

#endif//M2_MATH_H_