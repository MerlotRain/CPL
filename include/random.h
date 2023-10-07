/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file random.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

namespace Lite {
namespace Utility {


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


}// namespace Utility
}// namespace Lite
