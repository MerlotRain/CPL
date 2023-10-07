/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file bigdecimal.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/


#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {


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


}// namespace Utility
}// namespace Lite
