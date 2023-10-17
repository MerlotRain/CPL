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

#ifndef M2_ENUMMASKFLAG_H_
#define M2_ENUMMASKFLAG_H_

#include <bitset>
#include <type_traits>

namespace m2 {

template<typename Enum>
class EnumMaskFlag
{
    static_assert((std::is_enum<Enum>::value),
                  "EnumMaskFlag is only usable on enumeration types");

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
    static_assert((std::is_enum<Enum>::value),
                  "BitMaskFlag is only usable on enumeration types");
    unsigned long long m_BitMask = 0;

public:
    BitMaskFlag() = default;
    explicit BitMaskFlag(Enum flag) { MarkFlag(flag); }
    explicit BitMaskFlag(unsigned long long bitmask) : m_BitMask(bitmask) {}
    BitMaskFlag(const BitMaskFlag<Enum> &r) { m_BitMask = r.m_BitMask; }
    BitMaskFlag(BitMaskFlag<Enum> &&r) noexcept { swap(r); }
    void swap(BitMaskFlag<Enum> &flag) { std::swap(m_BitMask, flag.m_BitMask); }

    BitMaskFlag<Enum> &operator=(Enum enumVal);
    BitMaskFlag<Enum> &operator=(const BitMaskFlag<Enum> &flag);
    BitMaskFlag<Enum> &operator=(BitMaskFlag<Enum> &&flag) noexcept;
    BitMaskFlag<Enum> operator+(Enum enumVal);
    BitMaskFlag<Enum> operator-(Enum enumVal);
    BitMaskFlag<Enum> &operator+=(Enum enumVal);
    BitMaskFlag<Enum> &operator-=(Enum enumVal);

    explicit operator Enum() const;
    explicit operator unsigned long long() const;
    unsigned long long bitMask() const;

    BitMaskFlag<Enum> &operator=(unsigned long long mask);

    BitMaskFlag<Enum> &attach(const BitMaskFlag<Enum> &mask);
    BitMaskFlag<Enum> &attach(unsigned long long mask);

    virtual bool markFlag(Enum enumVal);
    virtual bool eraseMarkFlag(Enum enumVal);
    virtual bool testFlag(Enum enumVal) const;

    virtual int markDataByteLength() const { return 8; }
    virtual const unsigned char *markData() const;

    virtual int assign(const unsigned char *markData, int nLen);
};

template<class Enum, const int LEN = 128>
class LongBitMaskFlag : public EnumMaskFlag<Enum>
{
    static_assert((std::is_enum<Enum>::value),
                  "LongBitMaskFlag is only usable on enumeration types");
    std::bitset<LEN> m_MarkData;

public:
    LongBitMaskFlag() = default;
    explicit LongBitMaskFlag(Enum flag);
    LongBitMaskFlag(const LongBitMaskFlag<Enum, LEN> &flag);
    LongBitMaskFlag(LongBitMaskFlag<Enum, LEN> &&flag) noexcept;
    void swap(LongBitMaskFlag<Enum, LEN> &flag);
    virtual const unsigned char *markData() const;

    LongBitMaskFlag<Enum, LEN> &
    operator=(const LongBitMaskFlag<Enum, LEN> &flag);
    LongBitMaskFlag<Enum, LEN> &operator=(LongBitMaskFlag<Enum, LEN> &&flag);

    virtual bool markFlag(Enum enumVal);
    virtual bool eraseMarkFlag(Enum enumVal);
    virtual bool testFlag(Enum enumVal) const;

    virtual int markDataByteLength() const;
    virtual int assign(const unsigned char *markData, int nLen);
};

/*****************************************************************************
  BitMaskFlag inline functions
 *****************************************************************************/

template<typename Enum>
inline BitMaskFlag<Enum> &BitMaskFlag<Enum>::operator=(Enum enumVal)
{
    markFlag(enumVal);
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> &
BitMaskFlag<Enum>::operator=(const BitMaskFlag<Enum> &flag)
{
    m_BitMask = flag.m_BitMask;
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> &
BitMaskFlag<Enum>::operator=(BitMaskFlag<Enum> &&flag) noexcept
{
    swap(flag);
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> BitMaskFlag<Enum>::operator+(Enum enumVal)
{
    BitMaskFlag<Enum> m(m_BitMask);
    m += enumVal;
    return m;
}

template<typename Enum>
inline BitMaskFlag<Enum> BitMaskFlag<Enum>::operator-(Enum enumVal)
{
    BitMaskFlag<Enum> m(m_BitMask);
    m -= enumVal;
    return m;
}

template<typename Enum>
inline BitMaskFlag<Enum> &BitMaskFlag<Enum>::operator+=(Enum enumVal)
{
    markFlag(enumVal);
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> &BitMaskFlag<Enum>::operator-=(Enum enumVal)
{
    eraseMarkFlag(enumVal);
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum>::operator Enum() const
{
    return static_cast<Enum>(bitMask());
}

template<typename Enum>
inline BitMaskFlag<Enum>::operator unsigned long long() const
{
    return bitMask();
}

template<typename Enum>
inline unsigned long long BitMaskFlag<Enum>::bitMask() const
{
    return m_BitMask;
}

template<typename Enum>
inline BitMaskFlag<Enum> &BitMaskFlag<Enum>::operator=(unsigned long long mask)
{
    m_BitMask = mask;
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> &
BitMaskFlag<Enum>::attach(const BitMaskFlag<Enum> &mask)
{
    m_BitMask = mask.m_BitMask;
    return *this;
}

template<typename Enum>
inline BitMaskFlag<Enum> &BitMaskFlag<Enum>::attach(unsigned long long mask)
{
    m_BitMask = mask;
    return *this;
}

template<typename Enum>
inline bool BitMaskFlag<Enum>::markFlag(Enum enumVal)
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= sizeof(m_BitMask) * 8) { return false; }
    m_BitMask |= (1ull << val);
    return true;
}

template<typename Enum>
inline bool BitMaskFlag<Enum>::eraseMarkFlag(Enum enumVal)
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= sizeof(m_BitMask) * 8) { return false; }
    m_BitMask &= ~(1ull << val);
    return true;
}

template<typename Enum>
inline bool BitMaskFlag<Enum>::testFlag(Enum enumVal) const
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= sizeof(m_BitMask) * 8) { return false; }
    return m_BitMask & (1ull << val) ? true : false;
}

template<typename Enum>
inline const unsigned char *BitMaskFlag<Enum>::markData() const
{
    return (const unsigned char *) &m_BitMask;
}

template<typename Enum>
inline int BitMaskFlag<Enum>::assign(const unsigned char *markData, int nLen)
{
    if (!markData || nLen <= 0) { return 0; }
    nLen = std::min(nLen, 8);
    memcpy(&m_BitMask, markData, nLen);
    return nLen;
}

/*****************************************************************************
  LongBitMaskFlag inline functions
 *****************************************************************************/

template<class Enum, int LEN>
inline LongBitMaskFlag<Enum, LEN>::LongBitMaskFlag(Enum flag)
{
    markFlag(flag);
}

template<class Enum, int LEN>
inline LongBitMaskFlag<Enum, LEN>::LongBitMaskFlag(
        const LongBitMaskFlag<Enum, LEN> &flag)
{
    m_MarkData = flag.m_MarkData;
}

template<class Enum, int LEN>
inline LongBitMaskFlag<Enum, LEN>::LongBitMaskFlag(
        LongBitMaskFlag<Enum, LEN> &&flag) noexcept
{
    swap(flag);
}

template<class Enum, int LEN>
inline void LongBitMaskFlag<Enum, LEN>::swap(LongBitMaskFlag<Enum, LEN> &flag)
{
    std::swap(m_MarkData, flag.m_MarkData);
}

template<class Enum, int LEN>
inline const unsigned char *LongBitMaskFlag<Enum, LEN>::markData() const
{
    return (const unsigned char *) &m_MarkData;
}

template<class Enum, int LEN>
inline LongBitMaskFlag<Enum, LEN> &
LongBitMaskFlag<Enum, LEN>::operator=(const LongBitMaskFlag<Enum, LEN> &flag)
{
    m_MarkData = flag.m_MarkData;
    return *this;
}

template<class Enum, int LEN>
inline LongBitMaskFlag<Enum, LEN> &
LongBitMaskFlag<Enum, LEN>::operator=(LongBitMaskFlag<Enum, LEN> &&flag)
{
    swap(flag);
    return *this;
}

template<class Enum, int LEN>
inline bool LongBitMaskFlag<Enum, LEN>::markFlag(Enum enumVal)
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= LEN) { return false; }
    m_MarkData.set(val, true);
    return true;
}

template<class Enum, int LEN>
inline bool LongBitMaskFlag<Enum, LEN>::eraseMarkFlag(Enum enumVal)
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= LEN) { return false; }
    m_MarkData.set(val, false);
    return true;
}

template<class Enum, int LEN>
inline bool LongBitMaskFlag<Enum, LEN>::testFlag(Enum enumVal) const
{
    int val = static_cast<int>(enumVal);
    if (val < 0 || val >= LEN) { return false; }
    return m_MarkData.test(val);
}

template<class Enum, int LEN>
inline int LongBitMaskFlag<Enum, LEN>::markDataByteLength() const
{
    int nLen = LEN / 8;
    if (LEN & 8) { nLen++; }
    return nLen;
}

template<class Enum, int LEN>
inline int LongBitMaskFlag<Enum, LEN>::assign(const unsigned char *markData,
                                              int nLen)
{
    if (!markData || nLen <= 0) { return 0; }
    nLen = std::min(nLen, markDataByteLength());
    memcpy(&m_MarkData, markData, nLen);
    return nLen;
}

}// namespace m2

#endif//M2_ENUMMASKFLAG_H_