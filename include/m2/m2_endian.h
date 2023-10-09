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

#include "preconfig.h"

namespace m2 {
namespace EndianConverter {

/// @brief 字节序枚举
enum class Endian
{
    BigEndian,
    LittleEndian,
};

/// @brief 判断字节序类型
/// @return
inline Endian OsEndian()
{
#if (__CPP_LIB_ENDIAN == BIG_ENDIAN)
    return Endian::BigEndian;
#elif (__CPP_LIB_ENDIAN == LITTLE_ENDIAN)
    return Endian::LittleEndian;
#endif
}
/// @brief 是否是高字节序
inline bool IsBigEndian()
{
    return OsEndian() == Endian::BigEndian;
}
/// @brief 是否是低字节序
inline bool IsLittleEndian()
{
    return OsEndian() == Endian::LittleEndian;
}

template<typename T>
GS_ALWAYS_INLINE void ToUnaligned(const T src, void *dest)
{
    const size_t size = sizeof(T);
    memcpy(dest, &src, size);
}

template<typename T>
GS_ALWAYS_INLINE T FromUnaligned(const void *src)
{
    T dest;
    const size_t size = sizeof(T);
    memcpy(&dest, src, size);
    return dest;
}


template<typename T>
T ByteSwap(T source);
template<>
inline uint64_t ByteSwap<uint64_t>(uint64_t source)
{
    return 0 |
           ((source & GS_UINT64_C(0x00000000000000ff)) << 56) |
           ((source & GS_UINT64_C(0x000000000000ff00)) << 40) |
           ((source & GS_UINT64_C(0x0000000000ff0000)) << 24) |
           ((source & GS_UINT64_C(0x00000000ff000000)) << 8) |
           ((source & GS_UINT64_C(0x000000ff00000000)) >> 8) |
           ((source & GS_UINT64_C(0x0000ff0000000000)) >> 24) |
           ((source & GS_UINT64_C(0x00ff000000000000)) >> 40) |
           ((source & GS_UINT64_C(0xff00000000000000)) >> 56);
}
template<>
inline uint32_t ByteSwap<uint32_t>(uint32_t source)
{
    return 0 |
           ((source & 0x000000ff) << 24) |
           ((source & 0x0000ff00) << 8) |
           ((source & 0x00ff0000) >> 8) |
           ((source & 0xff000000) >> 24);
}
template<>
inline uint16_t ByteSwap<uint16_t>(uint16_t source)
{
    return uint16_t(0 |
                    ((source & 0x00ff) << 8) |
                    ((source & 0xff00) >> 8));
}
template<>
inline uint8_t ByteSwap<uint8_t>(uint8_t source)
{
    return source;
}
template<>
inline int64_t ByteSwap<int64_t>(int64_t source)
{
    return ByteSwap<uint64_t>(uint64_t(source));
}
template<>
inline int32_t ByteSwap<int32_t>(int32_t source)
{
    return ByteSwap<uint32_t>(uint32_t(source));
}
template<>
inline int16_t ByteSwap<int16_t>(int16_t source)
{
    return ByteSwap<uint16_t>(uint16_t(source));
}
template<>
inline int8_t ByteSwap<int8_t>(int8_t source)
{
    return source;
}

inline float ByteSwap(float source)
{
    auto temp = FromUnaligned<uint32_t>(&source);
    temp = ByteSwap(temp);
    return FromUnaligned<float>(&temp);
}

inline double ByteSwap(double source)
{
    auto temp = FromUnaligned<uint64_t>(&source);
    temp = ByteSwap(temp);
    return FromUnaligned<double>(&temp);
}

template<typename T>
inline void ByteSwap(const T src, void *dest)
{
    ToUnaligned<T>(ByteSwap(src), dest);
}

template<int Size>
void *ByteSwap(const void *source, int64_t count, void *dest) noexcept;
template<>
inline void *ByteSwap<1>(const void *source, int64_t count, void *dest) noexcept
{
    return source != dest ? memcpy(dest, source, size_t(count)) : dest;
}
template<>
void *ByteSwap<2>(const void *source, int64_t count, void *dest) noexcept;
template<>
void *ByteSwap<4>(const void *source, int64_t count, void *dest) noexcept;
template<>
void *ByteSwap<8>(const void *source, int64_t count, void *dest) noexcept;


//大端序处理
#if (__CPP_LIB_ENDIAN == BIG_ENDIAN)

template<typename T>
inline T ToBigEndian(T source)
{
    return source;
}
template<typename T>
inline T FromBigEndian(T source)
{
    return source;
}
template<typename T>
inline T ToLittleEndian(T source)
{
    return ByteSwap(source);
}
template<typename T>
inline T FromLittleEndian(T source)
{
    return ByteSwap(source);
}
template<typename T>
inline void ToBigEndian(T src, void *dest)
{
    ToUnaligned<T>(src, dest);
}
template<typename T>
inline void ToLittleEndian(T src, void *dest)
{
    ByteSwap<T>(src, dest);
}

template<typename T>
inline void ToBigEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void ToLittleEndian(const void *source, int64_t count, void *dest)
{
    ByteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void FromBigEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void FromLittleEndian(const void *source, int64_t count, void *dest)
{
    ByteSwap<sizeof(T)>(source, count, dest);
}

#elif (__CPP_LIB_ENDIAN == LITTLE_ENDIAN)//小端序处理

template<typename T>
inline T ToBigEndian(T source)
{
    return ByteSwap(source);
}
template<typename T>
inline T FromBigEndian(T source)
{
    return ByteSwap(source);
}
template<typename T>
inline T ToLittleEndian(T source)
{
    return source;
}
template<typename T>
inline T FromLittleEndian(T source)
{
    return source;
}
template<typename T>
inline void ToBigEndian(T src, void *dest)
{
    ByteSwap<T>(src, dest);
}
template<typename T>
inline void ToLittleEndian(T src, void *dest)
{
    ToUnaligned<T>(src, dest);
}

template<typename T>
inline void ToBigEndian(const void *source, int64_t count, void *dest)
{
    ByteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void ToLittleEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void FromBigEndian(const void *source, int64_t count, void *dest)
{
    ByteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void FromLittleEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
#endif


template<typename T>
inline T FromLittleEndian(const void *src)
{
    return FromLittleEndian(qFromUnaligned<T>(src));
}

template<>
inline uint8_t FromLittleEndian<uint8_t>(const void *src)
{
    return static_cast<const uint8_t *>(src)[0];
}
template<>
inline int8_t FromLittleEndian<int8_t>(const void *src)
{
    return static_cast<const int8_t *>(src)[0];
}


template<class T>
inline T FromBigEndian(const void *src)
{
    return FromBigEndian(qFromUnaligned<T>(src));
}

template<>
inline uint8_t FromBigEndian<uint8_t>(const void *src)
{
    return static_cast<const uint8_t *>(src)[0];
}
template<>
inline int8_t FromBigEndian<int8_t>(const void *src)
{
    return static_cast<const int8_t *>(src)[0];
}

}// namespace EndianConverter
}// namespace m2
