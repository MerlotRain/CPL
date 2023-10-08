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

#include <bitset>
#include <type_traits>

namespace m2 {

template<typename Enum>
class EnumMaskFlag
{
    static_assert((std::is_enum<Enum>::value), "EnumMaskFlag is only usable on enumeration types");

public:
    virtual bool markFlag(Enum enumVal) = 0;
    virtual bool eraseMarkFlag(Enum enumVal) = 0;
    virtual bool testFlag(Enum enumVal) const = 0;
    virtual int markDataByteLength() const = 0;
    virtual const unsigned char *markData() const = 0;
    virtual int assign(const unsigned char *markData, int nLen) = 0;
};


template<typename Enum>
class BitMaskFlag : public EnumMaskFlag<Enum>
{
    static_assert((std::is_enum<Enum>::value), "BitMaskFlag is only usable on enumeration types");
    unsigned long long m_BitMask = 0;

public:
    BitMaskFlag() = default;
    explicit BitMaskFlag(Enum flag) { MarkFlag(flag); }
    explicit BitMaskFlag(unsigned long long bitmask) : m_BitMask(bitmask) {}
    BitMaskFlag(const BitMaskFlag<Enum> &r) { m_BitMask = r.m_BitMask; }
    BitMaskFlag(BitMaskFlag<Enum> &&r) noexcept { swap(r); }
    void swap(BitMaskFlag<Enum> &flag) { std::swap(m_BitMask, flag.m_BitMask); }

    BitMaskFlag<Enum> &operator=(Enum enumVal)
    {
        MarkFlag(enumVal);
        return *this;
    }
    BitMaskFlag<Enum> &operator=(const BitMaskFlag<Enum> &flag)
    {
        m_BitMask = flag.m_BitMask;
        return *this;
    }
    BitMaskFlag<Enum> &operator=(BitMaskFlag<Enum> &&flag) noexcept
    {
        swap(flag);
        return *this;
    }
    BitMaskFlag<Enum> operator+(Enum enumVal)
    {
        BitMaskFlag<Enum> m(m_BitMask);
        m += enumVal;
        return m;
    }
    BitMaskFlag<Enum> operator-(Enum enumVal)
    {
        BitMaskFlag<Enum> m(m_BitMask);
        m -= enumVal;
        return m;
    }
    BitMaskFlag<Enum> &operator+=(Enum enumVal)
    {
        MarkFlag(enumVal);
        return *this;
    }
    BitMaskFlag<Enum> &operator-=(Enum enumVal)
    {
        EraseMarkFlag(enumVal);
        return *this;
    }
    explicit operator Enum() const { return static_cast<Enum>(BitMask()); }
    explicit operator unsigned long long() const { return BitMask(); }
    unsigned long long bitMask() const { return m_BitMask; }

    BitMaskFlag<Enum> &operator=(unsigned long long mask)
    {
        m_BitMask = mask;
        return *this;
    }
    BitMaskFlag<Enum> &attach(const BitMaskFlag<Enum> &mask)
    {
        m_BitMask = mask.m_BitMask;
        return *this;
    }
    BitMaskFlag<Enum> &attach(unsigned long long mask)
    {
        m_BitMask = mask;
        return *this;
    }
    virtual bool markFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        m_BitMask |= (1ull << val);
        return true;
    }
    virtual bool eraseMarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        m_BitMask &= ~(1ull << val);
        return true;
    }
    virtual bool testFlag(Enum enumVal) const
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= sizeof(m_BitMask) * 8)
        {
            return false;
        }
        return m_BitMask & (1ull << val) ? true : false;
    }

    virtual int markDataByteLength() const { return 8; }
    virtual const unsigned char *markData() const { return (const unsigned char *) &m_BitMask; }

    virtual int assign(const unsigned char *markData, int nLen)
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
class LongBitMaskFlag : public EnumMaskFlag<Enum>
{
    static_assert((std::is_enum<Enum>::value), "LongBitMaskFlag is only usable on enumeration types");
    std::bitset<LEN> m_MarkData;

public:
    LongBitMaskFlag() = default;
    explicit LongBitMaskFlag(Enum flag) { markFlag(flag); }
    LongBitMaskFlag(const LongBitMaskFlag<Enum, LEN> &flag) { m_MarkData = flag.m_MarkData; }
    LongBitMaskFlag(LongBitMaskFlag<Enum, LEN> &&flag) noexcept { swap(flag); }
    void swap(LongBitMaskFlag<Enum, LEN> &flag) { std::swap(m_MarkData, flag.m_MarkData); }
    virtual const unsigned char *markData() const { return (const unsigned char *) &m_MarkData; }

    LongBitMaskFlag<Enum, LEN> &operator=(const LongBitMaskFlag<Enum, LEN> &flag)
    {
        m_MarkData = flag.m_MarkData;
        return *this;
    }
    LongBitMaskFlag<Enum, LEN> &operator=(LongBitMaskFlag<Enum, LEN> &&flag)
    {
        swap(flag);
        return *this;
    }
    virtual bool markFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        m_MarkData.set(val, true);
        return true;
    }
    virtual bool eraseMarkFlag(Enum enumVal)
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        m_MarkData.set(val, false);
        return true;
    }
    virtual bool testFlag(Enum enumVal) const
    {
        int val = static_cast<int>(enumVal);
        if (val < 0 || val >= LEN)
        {
            return false;
        }
        return m_MarkData.test(val);
    }

    virtual int markDataByteLength() const
    {
        int nLen = LEN / 8;
        if (LEN & 8)
        {
            nLen++;
        }
        return nLen;
    }
    virtual int assign(const unsigned char *markData, int nLen)
    {
        if (!markData || nLen <= 0)
        {
            return 0;
        }
        nLen = std::min(nLen, markDataByteLength());
        memcpy(&m_MarkData, markData, nLen);
        return nLen;
    }
};

}// namespace m2
