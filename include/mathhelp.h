/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file mathhelp.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"
#include <math.h>


namespace Lite {
namespace Utility {
namespace Math {

/// @brief 与 π 相关的常数值，21 位有效数字
/// @details http://www.cppfans.com/cbknowledge/reference/cmath/m_pi.asp

/// @brief π
static constexpr double PI = 3.14159265358979323846;
/// @brief e
static constexpr double E = 2.7182818284590452354;
/// @brief 2 的平方根，std::sqrt(2)
static constexpr double SQRT2 = 1.41421356237309504880;
/// @brief 3 的平方根，std::sqrt(3)
static constexpr double SQRT3 = 1.732050807568877;
/// @brief 常用的屏幕换算单位
/// @brief 1英寸转毫米值
static constexpr double M_Inch2MM = 25.4;
/// @brief 1毫米转英寸值
static constexpr double M_MM2Inch = 0.03937007874;


/// @brief QT sin表
/// @details https://blog.csdn.net/maple_2014/article/details/115057482
static constexpr int SINE_TABLE_SIZE = 256;
extern const double sine_table[SINE_TABLE_SIZE];

/// @brief 快速正弦
/// @param x
/// @return
inline double FastSin(double x)
{
    int si = int(x * (0.5 * SINE_TABLE_SIZE / PI));
    double d = x - si * (2.0 * PI / SINE_TABLE_SIZE);
    int ci = si + SINE_TABLE_SIZE / 4;
    si &= SINE_TABLE_SIZE - 1;
    ci &= SINE_TABLE_SIZE - 1;
    return sine_table[si] + (sine_table[ci] - 0.5 * sine_table[si] * d) * d;
}

/// @brief 快速余弦
/// @param x
/// @return
inline double FastCos(double x)
{
    int ci = int(x * (0.5 * SINE_TABLE_SIZE / PI));
    double d = x - ci * (2.0 * PI / SINE_TABLE_SIZE);
    int si = ci + SINE_TABLE_SIZE / 4;
    si &= SINE_TABLE_SIZE - 1;
    ci &= SINE_TABLE_SIZE - 1;
    return sine_table[si] - (sine_table[ci] + 0.5 * sine_table[si] * d) * d;
}

/// @brief 度转弧度
/// @param degrees
/// @return
constexpr inline float DegreesToRadians(float degrees)
{
    return degrees * float(PI / 180);
}

/// @brief 度转弧度
/// @param degrees
/// @return
constexpr inline double DegreesToRadians(double degrees)
{
    return degrees * (PI / 180);
}

/// @brief 弧度转度
/// @param radians
/// @return
constexpr inline float RadiansToDegrees(float radians)
{
    return radians * float(180 / PI);
}

/// @brief 弧度转度
/// @param radians
/// @return
constexpr inline double RadiansToDegrees(double radians)
{
    return radians * (180 / PI);
}

/// @brief 获取大于值的最近二次方数
/// @param v
/// @return
inline unsigned int NextPowerOfTwo(unsigned int v)
{
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    ++v;
    return v;
}

/// @brief 获取大于值的最近二次方数
/// @param v
/// @return
inline unsigned long long NextPowerOfTwo(unsigned long long v)
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

/// @brief 获取大于值的最近二次方数
/// @param v
/// @return
constexpr inline int NextPowerOfTwo(int v)
{
    return NextPowerOfTwo((unsigned int) (v));
}

/// @brief 获取大于值的最近二次方数
/// @param v
/// @return
constexpr inline long long NextPowerOfTwo(long long v)
{
    return NextPowerOfTwo((unsigned long long) (v));
}

/// @brief 求两者最小值
/// @tparam T
/// @param a
/// @param b
/// @return
template<typename T>
constexpr inline const T &Min(const T &a, const T &b)
{
    return (a < b) ? a : b;
}

/// @brief 求三者之间的最小值
/// @tparam T
/// @param a
/// @param b
/// @param c
/// @return
template<typename T>
constexpr inline const T &Min3(const T &a, const T &b, const T &c)
{
    return ((a < b && a < c) ? a : (b < c ? b : c));
}

/// @brief 求两者最大值
/// @tparam T
/// @param a
/// @param b
/// @return
template<typename T>
constexpr inline const T &Max(const T &a, const T &b)
{
    return (a < b) ? b : a;
}

/// @brief 求三者之间的最大值
/// @tparam T
/// @param a
/// @param b
/// @param c
/// @return
template<typename T>
constexpr inline const T &Max3(const T &a, const T &b, const T &c)
{
    return ((a > b && a > c) ? a : (b > c ? b : c));
}


/// @brief 求三者中间值
/// @tparam T
/// @param min
/// @param val
/// @param max
/// @return
template<typename T>
constexpr inline const T &Bound(const T &min, const T &val, const T &max)
{
    return Max(min, Min(max, val));
}

/// @brief 四舍五入
/// @param d
/// @return
constexpr inline int Round(double d)
{
    return d >= 0.0 ? int(d + 0.5) : int(d - double(int(d - 1)) + 0.5) + int(d - 1);
}
constexpr inline int Round(float d)
{
    return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d - 1)) + 0.5f) + int(d - 1);
}
constexpr inline long long Round64(double d)
{
    return d >= 0.0 ? (long long) (d + 0.5) : (long long) (d - double((long long) (d - 1)) + 0.5) + (long long) (d - 1);
}
constexpr inline long long Round64(float d)
{
    return d >= 0.0f ? (long long) (d + 0.5f) : (long long) (d - float((long long) (d - 1)) + 0.5f) + (long long) (d - 1);
}

/// @brief 求绝对值
/// @tparam T
/// @param t
/// @return
template<typename T>
constexpr inline T Abs(const T &t)
{
    return t >= 0 ? t : -t;
}

/// @brief 浮点比较
/// @param d1
/// @param d2
/// @return
GS_REQUIRED_RESULT constexpr static inline bool FuzzyCompare(double d1, double d2)
{
    return (Abs(d1 - d2) * 1000000000000. <= Min(Abs(d1), Abs(d2)));
}
GS_REQUIRED_RESULT constexpr static inline bool FuzzyCompare(float d1, float d2)
{
    return (Abs(d1 - d2) * 100000.f <= Min(Abs(d1), Abs(d2)));
}
/// @brief 判断浮点数是否为空
/// @param d
/// @return
GS_REQUIRED_RESULT constexpr static inline bool FuzzyIsNull(double d)
{
    return Abs(d) <= 0.000000000001;
}
GS_REQUIRED_RESULT constexpr static inline bool FuzzyIsNull(float f)
{
    return Abs(f) <= 0.00001f;
}

/// @brief 四舍五入的除法操作
/// @tparam Int
/// @param a
/// @param b
/// @return
template<typename Int>
GS_REQUIRED_RESULT constexpr inline Int Div(Int a, unsigned b)
{
    return (a - (a < 0 ? int(b - 1) : 0)) / int(b);
}

/// @brief 四舍五入的取模操作
/// @tparam Int
/// @param a
/// @param b
/// @return
template<typename Int>
GS_REQUIRED_RESULT constexpr inline Int Mod(Int a, unsigned b)
{
    return a - Div(a, b) * b;
}

/// @brief 判断数值是否为空
GS_REQUIRED_RESULT constexpr static inline bool IsNull(double x) noexcept
{
    return x == 0.0;
}
GS_REQUIRED_RESULT constexpr static inline bool IsNull(float x) noexcept
{
    return x == 0.0f;
}

GS_REQUIRED_RESULT inline bool IsEqual(double a, double b, double epsilon = 4 * std::numeric_limits<double>::epsilon()) noexcept
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan)
    {
        return aIsNan && bIsNan;
    }

    const double diff = a - b;
    return diff > -epsilon && diff <= epsilon;
}

GS_REQUIRED_RESULT inline bool IsEqual(float a, float b, float epsilon = 4 * FLT_EPSILON) noexcept
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan)
    {
        return aIsNan && bIsNan;
    }

    const float diff = a - b;
    return diff > -epsilon && diff <= epsilon;
}

GS_REQUIRED_RESULT inline bool IsEqualSignificant(double a, double b, int significantDigits = 10)
{
    const bool aIsNan = std::isnan(a);
    const bool bIsNan = std::isnan(b);
    if (aIsNan || bIsNan)
    {
        return aIsNan && bIsNan;
    }

    int aexp, bexp;
    const double ar = std::frexp(a, &aexp);
    const double br = std::frexp(b, &bexp);

    return aexp == bexp && std::round(ar * std::pow(10.0, significantDigits)) == std::round(br * std::pow(10.0, significantDigits));
}

}// namespace Math
}// namespace Utility
}// namespace Lite
