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

#include <type_traits>

namespace m2 {

/// @brief 位标志
class GsFlag
{
    int i;

public:
    constexpr inline explicit GsFlag(int val) noexcept : i(val) {}
    constexpr inline explicit operator int() const noexcept { return i; }
};


/// @brief 枚举标志模板
/// @tparam Enum
template<typename Enum>
class GsFlags
{
    static_assert(sizeof(Enum) <= sizeof(int), "Enum value is overflows");
    static_assert((std::is_enum<Enum>::value), "GsFlags is only usable on enumeration types");

public:
    typedef Enum enum_type;

    typedef typename std::conditional<
            std::is_unsigned<typename std::underlying_type<Enum>::type>::value,
            unsigned int,
            signed int>::type Integer;

    constexpr inline GsFlags() noexcept : i(0) {}
    constexpr inline explicit GsFlags(Enum flags) noexcept : i(Integer(flags)) {}
    constexpr inline explicit GsFlags(GsFlag flag) noexcept : i(flag) {}

    constexpr inline GsFlags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end())) {}

    constexpr inline GsFlags &operator&=(int mask) const noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline GsFlags &operator&=(unsigned int mask) const noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline GsFlags &operator&=(Enum mask) const noexcept
    {
        i &= Integer(mask);
        return *this;
    }
    constexpr inline GsFlags &operator|=(GsFlags other) const noexcept
    {
        i |= other.i;
        return *this;
    }
    constexpr inline GsFlags &operator|=(Enum other) const noexcept
    {
        i |= Integer(other);
        return *this;
    }
    constexpr inline GsFlags &operator^=(GsFlags other) const noexcept
    {
        i ^= other.i;
        return *this;
    }
    constexpr inline GsFlags &operator^=(Enum other) const noexcept
    {
        i ^= Integer(other);
        return *this;
    }

    constexpr inline operator Integer() const noexcept { return i; }
    constexpr inline GsFlags operator|(GsFlags other) const noexcept { return GsFlags(GsFlag(i | other.i)); }
    constexpr inline GsFlags operator|(Enum other) const noexcept { return GsFlags(GsFlag(i | Integer(other))); }
    constexpr inline GsFlags operator^(GsFlags other) const noexcept { return GsFlags(GsFlag(i ^ other.i)); }
    constexpr inline GsFlags operator^(Enum other) const noexcept { return GsFlags(GsFlag(i ^ Integer(other))); }
    constexpr inline GsFlags operator&(int mask) const noexcept { return GsFlags(GsFlag(i & mask)); }
    constexpr inline GsFlags operator&(unsigned int mask) const noexcept { return GsFlags(GsFlag(i & mask)); }
    constexpr inline GsFlags operator&(Enum other) const noexcept { return GsFlags(GsFlag(i & Integer(other))); }
    constexpr inline GsFlags operator~() const noexcept { return GsFlags(GsFlag(~i)); }

    constexpr inline bool operator!() const noexcept { return !i; }

    constexpr inline bool TestFlag(Enum flag) const noexcept { return (i & Integer(flag)) == Integer(flag) && (Integer(flag) != 0 || i == Integer(flag)); }
    constexpr inline GsFlags &SetFlag(Enum flag, bool on = true) const noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Integer(flag));
    }

private:
    constexpr static inline Integer initializer_list_helper(typename std::initializer_list<Enum>::const_iterator it,
                                                            typename std::initializer_list<Enum>::const_iterator end) noexcept
    {
        return (it == end ? Integer(0) : (Integer(*it) | initializer_list_helper(it + 1, end)));
    }

private:
    Integer i;
};
#define GS_DECLARE_FLAGS(flags, Enum) typedef Lite::Utility::GsFlags<Enum> flags;


/// @brief 长枚举标记
/// @details 适用于枚举选项过长，使用移位处理时，最大枚举值已经超过了int的最大范围
/// @details 该类将每个枚举值放在一个二进制位，通过ON和OFF判断枚举是否启用
/// @tparam Enum
template<typename Enum>
class GsEnumMaskFlag
{
    static_assert((std::is_enum<Enum>::value), "GsEnumMaskFlag is only usable on enumeration types");

public:
    /// @brief 设置位掩码标识
    virtual bool MarkFlag(Enum enumVal) = 0;
    /// @brief 清除一个位掩码标识
    virtual bool EraseMarkFlag(Enum enumVal) = 0;
    /// @brief 测试一个位掩码是否被标识
    virtual bool TestFlag(Enum enumVal) const = 0;
    /// @brief 标记数据的字节长度
    virtual int MarkDataByteLength() const = 0;
    /// @brief 获取标记数据
    virtual const unsigned char *MarkData() const = 0;
    /// @brief 赋值标记数据
    /// @return 返回实际赋值的字节长度
    virtual int Assign(const unsigned char *markData, int nLen) = 0;
};


/// @brief 位掩码标识
/// @details 将连续存储的枚举类型存储为位掩码形式。最多支持64掩码位，即枚举值数字范围为[0~63]
template<typename Enum>
class GsBitMaskFlag : public GsEnumMaskFlag<Enum>
{
    static_assert((std::is_enum<Enum>::value), "GsBitMaskFlag is only usable on enumeration types");
    unsigned long long m_BitMask = 0;

public:
    /// @brief 空构造
    GsBitMaskFlag() = default;

    /// @brief 从一个枚举构造
    explicit GsBitMaskFlag(Enum flag)
    {
        MarkFlag(flag);
    }
    /// @brief 从已有的位掩码构造
    explicit GsBitMaskFlag(unsigned long long bitmask) : m_BitMask(bitmask)
    {
    }
    /// @brief 拷贝构造
    GsBitMaskFlag(const GsBitMaskFlag<Enum> &r)
    {
        m_BitMask = r.m_BitMask;
    }
    /// @brief 移动构造
    GsBitMaskFlag(GsBitMaskFlag<Enum> &&r) noexcept
    {
        Swap(r);
    }
    /// @brief 对枚举的赋值，等价MarkFlag方法
    GsBitMaskFlag<Enum> &operator=(Enum enumVal)
    {
        MarkFlag(enumVal);
        return *this;
    }
    /// @brief 赋值
    GsBitMaskFlag<Enum> &operator=(const GsBitMaskFlag<Enum> &flag)
    {
        m_BitMask = flag.m_BitMask;
        return *this;
    }
    /// @brief 移动赋值
    GsBitMaskFlag<Enum> &operator=(GsBitMaskFlag<Enum> &&flag) noexcept
    {
        Swap(flag);
        return *this;
    }
    /// @brief 交换
    void Swap(GsBitMaskFlag<Enum> &flag)
    {
        std::swap(m_BitMask, flag.m_BitMask);
    }

    /// @brief 加操作符，等价拷贝+MarkFlag
    GsBitMaskFlag<Enum> operator+(Enum enumVal)
    {
        GsBitMaskFlag<Enum> m(m_BitMask);
        m += enumVal;
        return m;
    }
    /// @brief 减操作符，等价拷贝+EraseMarkFlag
    GsBitMaskFlag<Enum> operator-(Enum enumVal)
    {
        GsBitMaskFlag<Enum> m(m_BitMask);
        m -= enumVal;
        return m;
    }
    /// @brief 复合加操作符，等价MarkFlag
    GsBitMaskFlag<Enum> &operator+=(Enum enumVal)
    {
        MarkFlag(enumVal);
        return *this;
    }
    /// @brief 复合减操作符，等价EraseMarkFlag
    GsBitMaskFlag<Enum> &operator-=(Enum enumVal)
    {
        EraseMarkFlag(enumVal);
        return *this;
    }

    /// @brief 操作符重载获取位掩码,以枚举的类型返回位掩码值
    explicit operator Enum() const
    {
        return static_cast<Enum>(BitMask());
    }
    /// @brief 操作符重载获取位掩码
    explicit operator unsigned long long() const
    {
        return BitMask();
    }
    /// @brief 设置位掩码
    GsBitMaskFlag<Enum> &operator=(unsigned long long mask)
    {
        m_BitMask = mask;
        return *this;
    }
    /// @brief 设置位掩码
    GsBitMaskFlag<Enum> &Attach(const GsBitMaskFlag<Enum> &mask)
    {
        m_BitMask = mask.m_BitMask;
        return *this;
    }
    /// @brief 设置位掩码
    GsBitMaskFlag<Enum> &Attach(unsigned long long mask)
    {
        m_BitMask = mask;
        return *this;
    }


    /// @brief 获取位掩码
    unsigned long long BitMask() const
    {
        return m_BitMask;
    }
    /// @brief 设置位掩码标识
    virtual bool MarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        m_BitMask |= (1ull << val);
        return true;
    }
    /// @brief 清除一个位掩码标识
    virtual bool EraseMarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        m_BitMask &= ~(1ull << val);
        return true;
    }
    /// @brief 测试一个位掩码是否被标识
    virtual bool TestFlag(Enum enumVal) const
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        return m_BitMask & (1ull << val) ? true : false;
    }

    /// @brief 标记数据的字节长度
    virtual int MarkDataByteLength() const
    {
        return 8;
    }
    /// @brief 获取标记数据
    virtual const unsigned char *MarkData() const
    {
        return (const unsigned char *) &m_BitMask;
    }
    /// @brief 赋值标记数据
    /// @return 返回实际赋值的字节长度
    virtual int Assign(const unsigned char *markData, int nLen)
    {
        if (!markData || nLen <= 0)
        {
            return 0;
        }
        nLen = std::min(nLen, 8);
        memcpy(&m_BitMask, markData, nLen);
        return nLen;
    }
};

template<class Enum, const int LEN = 128>
class GsLongBitMaskFlag : public GsEnumMaskFlag<Enum>
{
    static_assert((std::is_enum<Enum>::value), "GsLongBitMaskFlag is only usable on enumeration types");
    std::bitset<LEN> m_MarkData;

public:
    GsLongBitMaskFlag() = default;
    explicit GsLongBitMaskFlag(Enum flag)
    {
        MarkFlag(flag);
    }
    GsLongBitMaskFlag(const GsLongBitMaskFlag<Enum, LEN> &flag)
    {
        m_MarkData = flag.m_MarkData;
    }
    GsLongBitMaskFlag(GsLongBitMaskFlag<Enum, LEN> &&flag) noexcept
    {
        Swap(flag);
    }
    void Swap(GsLongBitMaskFlag<Enum, LEN> &flag)
    {
        std::swap(m_MarkData, flag.m_MarkData);
    }
    GsLongBitMaskFlag<Enum, LEN> &operator=(const GsLongBitMaskFlag<Enum, LEN> &flag)
    {
        m_MarkData = flag.m_MarkData;
        return *this;
    }
    GsLongBitMaskFlag<Enum, LEN> &operator=(GsLongBitMaskFlag<Enum, LEN> &&flag)
    {
        Swap(flag);
        return *this;
    }
    /// @brief 设置位掩码标识
    virtual bool MarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        m_MarkData.set(val, true);
        return true;
    }
    /// @brief 清除一个位掩码标识
    virtual bool EraseMarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        m_MarkData.set(val, false);
        return true;
    }
    /// @brief 测试一个位掩码是否被标识
    virtual bool TestFlag(Enum enumVal) const
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        return m_MarkData.test(val);
    }

    /// @brief 标记数据的字节长度
    virtual int MarkDataByteLength() const
    {
        int nLen = LEN / 8;
        if (LEN & 8)
        {
            nLen++;
        }
        return nLen;
    }
    /// @brief 获取标记数据
    virtual const unsigned char *MarkData() const
    {
        return (const unsigned char *) &m_MarkData;
    }
    /// @brief 赋值标记数据
    /// @return 返回实际赋值的字节长度
    virtual int Assign(const unsigned char *markData, int nLen)
    {
        if (!markData || nLen <= 0)
        {
            return 0;
        }
        nLen = std::min(nLen, MarkDataByteLength());
        memcpy(&m_MarkData, markData, nLen);
        return nLen;
    }
};

}// namespace m2
