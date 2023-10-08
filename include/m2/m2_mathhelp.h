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

#include "memorymanager.h"
#include "preconfig.h"


namespace m2 {

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

GS_REQUIRED_RESULT inline bool IsEqual(double a, double b, double epsilon = 4 * DBL_EPSILON) noexcept
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


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/// @brief UUID构造
struct UTILITY_EXPORT GsUUID
{
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned short Data4[8];

    enum UUIDVariant
    {
        VarUnknown = -1,
        NCS = 0,      // 0 - -
        DCE = 2,      // 1 0 -
        Microsoft = 6,// 1 1 0
        Reserved = 7  // 1 1 1
    };

    enum StringFormat
    {
        /// @brief 32的数字连字符分隔
        /// @details 00000000-0000-0000-0000-000000000000
        eHyphens32 = 'D',
        /// @brief 32位数
        /// @details 00000000000000000000000000000000
        eNumber32 = 'N',
        /// @brief 32的数字连字符分隔包含在大括号中
        /// @details {00000000-0000-0000-0000-000000000000}
        eHyphensBraces = 'B',
        /// @brief 32的数字连字符分隔包含在圆括号中
        /// @details (00000000-0000-0000-0000-000000000000)
        eHyphensParentheses = 'P'
    };

    enum UUIDVersion
    {
        /// @brief 未知的版本
        VerUnknown = -1,
        /// @brief timestamp + MAC地址。
        Time = 1,
        /// @brief 基于 v1 的基础上优化了下，更安全。
        EmbeddedPOSIX = 2,
        /// @brief 基于 namespace + 输入内容 进行MD5
        Md5 = 3,
        Name = Md5,
        /// @brief 基于随机数
        Random = 4,
        /// @brief 使用SHA1计算
        Sha1 = 5
        ///
    };

    /// @brief 默认使用随机数生成Uuid
    /// @param version
    GsUUID() noexcept;
    GsUUID(unsigned int l, unsigned short w1, unsigned short w2, unsigned char b1, unsigned char b2, unsigned char b3,
           unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7, unsigned char b8);

    /// @brief 拷贝构造
    /// @param
    GsUUID(const GsUUID &) noexcept;

    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsUUID &operator=(const GsUUID &) noexcept;

    /// @brief 判断两个uuid是否相等
    /// @param ths
    /// @return
    bool operator==(const GsUUID &ths) const noexcept;
    /// @brief 判断两个uuid不相等
    /// @param orig
    /// @return
    bool operator!=(const GsUUID &orig) const noexcept;
    /// @brief 比较两个uuid
    /// @param other
    /// @return
    bool operator<(const GsUUID &other) const noexcept;
    bool operator>(const GsUUID &other) const noexcept;

    /// @brief 创建基于随机数的UUID
    /// @return
    static GsUUID CreateUuid();

    /// @brief 创建基于MD5算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static GsUUID CreateUuidV3(const GsUUID &ns, const GsString &baseData);

    /// @brief 创建基于SHA1算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static GsUUID CreateUuidV5(const GsUUID &ns, const GsString &baseData);

    /// @brief 转换为字符串
    /// @param format
    /// @return
    GsString ToString(StringFormat format = StringFormat::eHyphens32);

    bool IsNull() const noexcept;

    GsUUID::UUIDVariant Variant() const noexcept;
    GsUUID::UUIDVersion Version() const noexcept;

    GsByteBuffer ToRfc4122() const;
    static GsUUID FromRfc4122(const GsByteBuffer &);
};

inline bool operator<=(const GsUUID &lhs, const GsUUID &rhs) noexcept
{
    return !(rhs < lhs);
}
inline bool operator>=(const GsUUID &lhs, const GsUUID &rhs) noexcept
{
    return !(lhs < rhs);
}


/// @brief 伪随机数生成器，参考glibc drand48算法实现
/// @details https://elixir.bootlin.com/glibc/latest/source/stdlib/drand48.c
/// @details
class GsRandom
{
    unsigned short int m_Seed[7];

public:
    /// @brief 默认构造，使用time_t作为随机种子
    GsRandom();

    /// @brief Seed random number generator.
    /// @param seed
    GsRandom(int seed);
    GsRandom(unsigned short seed[7]);
    /// @brief 拷贝构造
    GsRandom(const GsRandom &rhs);
    /// @brief 移动构造
    GsRandom(GsRandom &&rhs);
    /// @brief 赋值移动构造
    GsRandom &operator=(GsRandom &&rhs);
    /// @brief 赋值复制构造
    GsRandom &operator=(const GsRandom &rhs);
    /// @brief 默认析构
    ~GsRandom();
    /// @brief 交换
    void Swap(GsRandom &rhs);

public:
    /// @brief 设置长度为3的种子，伪构造
    /// @param seed
    void XSeed(unsigned short seed[3]);
    /// @brief 完整种子数据指针，长度7
    const unsigned short *Seed() const;
    /// @brief XSeed种子数据指针，长度3
    const unsigned short *XSeed() const;

public:
    /// @brief Return non-negative, long integer in [0,2^31).
    int LRand48() noexcept;
    int NRand48(unsigned short xseed[3]) noexcept;

    /// @brief Return signed, long integers in [-2^31,2^31).
    int MRand48() noexcept;
    int JRand48(unsigned short xseed[3]) noexcept;

    /// @brief Return non-negative, double-precision floating-point value in [0.0,1.0)
    double DRand48() noexcept;
    double ERand48(unsigned short xseed[3]) noexcept;


    /// @brief 获取[0, 2^31)之间的随机数
    int Next();
    /// @brief 返回在指定范围内的任意整数。[minValue,maxValue)
    int Next(int minValue, int maxValue);
    /// @brief 返回在指定范围内的任意整数。[minValue,maxValue)
    double Next(double minValue, double maxValue);
    /// @brief 获取[0.0, 1.0)之间浮点数随机数
    double NextDouble();
    /// @brief 用随机数填充指定字节数组的元素
    void NextBytes(unsigned char *bytes, int nLen);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/// @brief Java like BigInteger
/// @details
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

/// @brief Java like BigDecimal
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


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


class GsVector3D;
/// @brief 二维向量类
class UTILITY_EXPORT GsVector2D
{
public:
    /// @brief 默认构造
    GsVector2D() = default;

    /// @brief 根据二维向量的X,Y分量构造
    /// @param x
    /// @param y
    GsVector2D(double x, double y);

    /// @brief 获取向量的反向量
    /// @return
    GsVector2D operator-() const;

    /// @brief 向量扩展
    /// @param scalar
    /// @return
    GsVector2D operator*(double scalar) const;

    /// @brief 向量缩小
    /// @param scalar
    /// @return
    GsVector2D operator/(double scalar) const;
    /// @brief
    /// @param v
    /// @return
    double operator*(GsVector2D v) const;

    /// @brief
    /// @param other
    /// @return
    GsVector2D operator+(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    GsVector2D &operator+=(GsVector2D other);

    /// @brief
    /// @param other
    /// @return
    GsVector2D operator-(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    GsVector2D &operator-=(GsVector2D other);

    /// @brief
    /// @return
    double Length() const;
    /// @brief
    /// @return
    double LengthSquared() const;

    /// @brief
    /// @return
    double X() const;
    /// @brief
    /// @return
    double Y() const;

    /// @brief
    /// @return
    GsVector2D PerpVector() const;

    /// @brief
    /// @return
    double Angle() const;
    /// @brief
    /// @param v
    /// @return
    double Angle(GsVector2D v) const;
    /// @brief 向量
    /// @param v
    /// @return
    double CrossProduct(GsVector2D v) const;

    /// @brief
    /// @param rot
    /// @return
    GsVector2D RotateBy(double rot) const;
    /// @brief
    /// @return
    GsVector2D Normalized() const;

    /// @brief
    /// @param other
    /// @return
    bool operator==(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    bool operator!=(GsVector2D other) const;

private:
    double m_X = 0.0;
    double m_Y = 0.0;
};

/// @brief 三维向量类
class UTILITY_EXPORT GsVector3D
{
public:
    GsVector3D() = default;
    /// @brief
    /// @param x
    /// @param y
    /// @param z
    GsVector3D(double x, double y, double z);
    /// @brief
    /// @return
    bool IsNull() const;
    /// @brief 获取X分量
    /// @return
    double X() const;
    /// @brief 获取Y分量
    /// @return
    double Y() const;
    /// @brief 获取Z分量
    /// @return
    double Z() const;
    /// @brief 设置X分量
    /// @param x
    void X(double x);
    /// @brief 设置Y分量
    /// @param y
    void Y(double y);
    /// @brief 设置Z分量
    /// @param z
    void Z(double z);
    /// @brief 设置向量的分量值
    /// @param x
    /// @param y
    /// @param z
    void Set(double x, double y, double z);
    /// @brief 判断向量是否相等
    /// @param other
    /// @return
    bool operator==(const GsVector3D &other) const;
    /// @brief 判断向量是否不等
    /// @param other
    /// @return
    bool operator!=(const GsVector3D &other) const;
    /// @brief 向量相加
    /// @param other
    /// @return
    GsVector3D operator+(const GsVector3D &other) const;
    /// @brief 向量相减
    /// @param other
    /// @return
    GsVector3D operator-(const GsVector3D &other) const;
    /// @brief 向量扩展
    /// @param factor
    /// @return
    GsVector3D operator*(const double factor) const;
    /// @brief 向量缩小
    /// @param factor
    /// @return
    GsVector3D operator/(const double factor) const;
    /// @brief 向量点积
    /// @param v1
    /// @param v2
    /// @return
    static double DotProduct(const GsVector3D &v1, const GsVector3D &v2);
    /// @brief 向量叉乘
    /// @param v1
    /// @param v2
    /// @return
    static GsVector3D CrossProduct(const GsVector3D &v1, const GsVector3D &v2);
    /// @brief 向量长度
    /// @return
    double Length() const;
    /// @brief
    void Normalize();

    /// @brief
    /// @param other
    /// @return
    double Distance(const GsVector3D &other) const;
    /// @brief
    /// @param v1
    /// @param v2
    /// @param vp
    /// @return
    static GsVector3D PerpendicularPoint(const GsVector3D &v1, const GsVector3D &v2, const GsVector3D &vp);

private:
    double m_X = 0, m_Y = 0, m_Z = 0;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/// @brief 长度单位
enum class GsLengthUnits
{
    eKilometer,   //!< 千米
    eMeter,       //!< 米
    eDecimetre,   //!< 分米
    eCentimeter,  //!< 厘米
    eMillimeter,  //!< 毫米
    eMicron,      //!< 微米
    eNanometer,   //!< 纳米
    eInche,       //!< 英寸
    eMile,        //!< 英里
    eFeet,        //!< 英尺
    eYard,        //!< 码
    eNauticalMile,//!< 海里
    eZhang,       //!< 中国长度单位丈，≈3.33米
    eChi,         //!< 中国长度单位尺，≈3.33分米
    eCun,         //!< 中国长度单位寸，≈3.33厘米
    eFen,         //!< 中国长度单位分，≈3.33毫米
#ifdef SPATIAL_FEATURE
    eDegrees,//!< 度，用于空间参考测量使用，仅提供经验值，准确计算空间坐标换算相关模块处理
#endif
};


/// @brief 长度单位换算
struct UTILITY_EXPORT GsLength
{
    double Length = 0.0;
    GsLengthUnits Unit = GsLengthUnits::eMeter;

    /// @brief 默认构造
    GsLength() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsLength(const GsLength &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsLength &operator=(const GsLength &) noexcept;
    /// @brief 使用长度和单位构造
    /// @param len
    /// @param unit
    GsLength(double len, GsLengthUnits unit) noexcept;

    /// @brief 移动构造
    /// @param len
    GsLength(GsLength &&len) noexcept;
    /// @brief 赋值移动构造
    /// @param
    /// @return
    GsLength &operator=(GsLength &&) noexcept;
    /// @brief 交换
    /// @param l
    void Swap(GsLength &l) noexcept;

    /// @brief 重载==操作符
    /// @param
    /// @return
    bool operator==(const GsLength &) const noexcept;
    /// @brief 重载!=操作符
    /// @param
    /// @return
    bool operator!=(const GsLength &) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsLength &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsLength &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsLength &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsLength &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsLength operator-(const GsLength &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsLength operator+(const GsLength &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsLength &operator+=(const GsLength &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsLength &operator-=(const GsLength &) noexcept;

    /// @brief 重载 double 操作符
    operator double() const;

    /// @brief 转换成米单位
    /// @return
    inline GsLength ToMeter() const
    {
        return GsLength::ToMeter(Length, Unit);
    }
    /// @brief 转换成米单位
    /// @param len
    /// @param units
    /// @return
    static GsLength ToMeter(double len, GsLengthUnits units);
    /// @brief 单位换算
    /// @param units
    /// @return
    inline GsLength ConvertTo(GsLengthUnits units) const
    {
        return GsLength::ConvertTo(Length, Unit, units);
    }
    /// @brief 将一段长度从一个单位换算成另一个单位
    /// @param len
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsLength ConvertTo(double len, GsLengthUnits srcUnit, GsLengthUnits tagUnit);
    /// @brief 从一个长度单位转换到另一个长度单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsLengthUnits from, GsLengthUnits to);
};


/// @brief 面积单位换算
enum class GsAreaUnits
{
    eKilometer2, //!< 平方千米km²
    eMeter2,     //!< 平方米m²
    ehm2,        //!< 公顷hm²
    eAre,        //!< 公亩
    eDecimetre2, //!< 平方分米dm²
    eCentimeter2,//!< 平方厘米cm²
    eMillimeter2,//!< 平方毫米mm²
    eAcre,       //!< 英亩
    eMile2,      //!< 平方英里mile²
    eYard2,      //!< 平方码yd²
    eFeet2,      //!< 平方英尺ft²
    eInche2,     //!< 平方英寸in²
    eRd2,        //!< 平方竿
    eQing,       //!< 中国面积单位顷
    eMu,         //!< 中国面积单位亩
    eFen,        //!< 中国面积单位分
#ifdef SPATIAL_FEATURE
    eDegrees,//!< 平方度，用于空间参考测量使用，仅提供经验值，准确计算空间坐标换算相关模块处理
#endif
};


/// @brief 面积单位换算
struct UTILITY_EXPORT GsArea
{
    double Area = 0.0;
    GsAreaUnits Unit = GsAreaUnits::eMeter2;

    /// @brief 默认构造
    GsArea() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsArea(const GsArea &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsArea &operator=(const GsArea &) noexcept;
    /// @brief 根据面积和单位构造
    /// @param a
    /// @param uint
    GsArea(double a, GsAreaUnits uint) noexcept;
    /// @brief 移动构造
    /// @param rhs
    GsArea(GsArea &&rhs) noexcept;
    /// @brief 复制移动构造
    /// @param rhs
    /// @return
    GsArea &operator=(GsArea &&rhs) noexcept;

    /// @brief 交换
    /// @param rhs
    void Swap(GsArea &rhs) noexcept;

    /// @brief 重载==操作符
    /// @param rhs
    /// @return
    bool operator==(const GsArea &rhs) const noexcept;
    /// @brief 重载!=操作符
    /// @param rhs
    /// @return
    bool operator!=(const GsArea &rhs) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsArea &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsArea &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsArea &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsArea &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsArea operator-(const GsArea &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsArea operator+(const GsArea &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsArea &operator+=(const GsArea &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsArea &operator-=(const GsArea &) noexcept;

    /// @brief 重载double操作符
    operator double() const;

    /// @brief 转化为平方米单位
    /// @return
    GsArea ToMeter2() const
    {
        return GsArea::ToMeter2(Area, Unit);
    }
    /// @brief 转换为平方米单位
    /// @param a
    /// @param units
    /// @return
    static GsArea ToMeter2(double a, GsAreaUnits units);
    /// @brief 转换为特定单位的面积
    /// @param units
    /// @return
    inline GsArea ConvertTo(GsAreaUnits units) const
    {
        return GsArea::ConvertTo(Area, Unit, units);
    }
    /// @brief 转换为特定单位的面积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsArea ConvertTo(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit);
    /// @brief 平方米的面积
    /// @return
    inline double Meter2Area() const
    {
        return GsArea::Meter2Area(Area, Unit, GsAreaUnits::eMeter2);
    }
    /// @brief 平方米的面积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static double Meter2Area(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit);

    /// @brief 从一个面积单位转换到另一个面积单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsAreaUnits from, GsAreaUnits to);
};


/// @brief 常见体积单位
enum class GsVolumeUnits
{
    eCubicKilometers,//!< 立方千米
    eCubicMeters,    //!< 立方米
    eCubicDecimeter, //!< 立方分米
    eCubicCentimeter,//!< 立方厘米
    eCubicMillimeter,//!< 立方毫米
    eLiter,          //!< 升
    eDeciLiter,      //!< 分升
    eMillLiter,      //!< 毫升
    eAcreFoot,       //!< 亩英尺
    eCubicYard,      //!< 立方码
    eCubicFeet,      //!< 立方英尺
    eCubicInch,      //!< 立方英寸
    eBarrel,         //!< 桶
    eGallonUS,       //!< 加仑
};

/// @brief 体积
struct UTILITY_EXPORT GsVolume
{
    double Volume = 0.0;
    GsVolumeUnits Unit = GsVolumeUnits::eCubicMeters;

    /// @brief 默认构造
    GsVolume() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsVolume(const GsVolume &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsVolume &operator=(const GsVolume &) noexcept;
    /// @brief 根据体积和单位构造
    /// @param vol
    /// @param uints
    GsVolume(double vol, GsVolumeUnits uints) noexcept;
    /// @brief 移动构造
    /// @param vol
    GsVolume(GsVolume &&vol) noexcept;
    /// @brief 赋值移动构造
    /// @param
    /// @return
    GsVolume &operator=(GsVolume &&) noexcept;
    /// @brief 交换
    /// @param l
    void Swap(GsVolume &l) noexcept;

    /// @brief 重载==操作符
    /// @param
    /// @return
    bool operator==(const GsVolume &) const noexcept;
    /// @brief 重载!=操作符
    /// @param
    /// @return
    bool operator!=(const GsVolume &) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsVolume &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsVolume &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsVolume &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsVolume &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsVolume operator-(const GsVolume &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsVolume operator+(const GsVolume &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsVolume &operator+=(const GsVolume &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsVolume &operator-=(const GsVolume &) noexcept;

    /// @brief 重载double操作符
    operator double() const;
    /// @brief 转换成立方体单位
    /// @return
    GsVolume ToCubicMeters() const
    {
        return GsVolume::ToCubicMeters(Volume, Unit);
    }
    /// @brief 转换成立方体单位
    /// @param vol
    /// @param units
    /// @return
    static GsVolume ToCubicMeters(double vol, GsVolumeUnits units);

    /// @brief 从当前单位转换为指定单位
    /// @param units
    /// @return
    inline GsVolume ConvertTo(GsVolumeUnits units) const
    {
        return GsVolume::ConvertTo(Volume, Unit, units);
    }
    /// @brief 从当前单位转换为指定单位
    /// @param vol
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsVolume ConvertTo(double vol, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit);

    /// @brief 转换成立方米的体积
    /// @return
    inline double Meter3Volume() const
    {
        return GsVolume::Meter3Volume(Volume, Unit, GsVolumeUnits::eCubicMeters);
    }
    /// @brief 转换成立方米的体积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static double Meter3Volume(double a, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit);
    /// @brief 从一个体积单位转换到另一个体积单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsVolumeUnits from, GsVolumeUnits to);
};


}// namespace m2
