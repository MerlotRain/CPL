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

#ifndef M2_ENDIAN_H_
#define M2_ENDIAN_H_

#include <preconfig.h>

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
inline Endian osEndian()
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
    return osEndian() == Endian::BigEndian;
}
/// @brief 是否是低字节序
inline bool isLittleEndian()
{
    return osEndian() == Endian::LittleEndian;
}

template<typename T>
M2_ALWAYS_INLINE void toUnaligned(const T src, void *dest)
{
    const size_t size = sizeof(T);
    memcpy(dest, &src, size);
}

template<typename T>
M2_ALWAYS_INLINE T fromUnaligned(const void *src)
{
    T dest;
    const size_t size = sizeof(T);
    memcpy(&dest, src, size);
    return dest;
}


template<typename T>
T byteSwap(T source);
template<>
inline uint64_t byteSwap<uint64_t>(uint64_t source)
{
    return 0 |
           ((source & M2_UINT64_C(0x00000000000000ff)) << 56) |
           ((source & M2_UINT64_C(0x000000000000ff00)) << 40) |
           ((source & M2_UINT64_C(0x0000000000ff0000)) << 24) |
           ((source & M2_UINT64_C(0x00000000ff000000)) << 8) |
           ((source & M2_UINT64_C(0x000000ff00000000)) >> 8) |
           ((source & M2_UINT64_C(0x0000ff0000000000)) >> 24) |
           ((source & M2_UINT64_C(0x00ff000000000000)) >> 40) |
           ((source & M2_UINT64_C(0xff00000000000000)) >> 56);
}
template<>
inline uint32_t byteSwap<uint32_t>(uint32_t source)
{
    return 0 |
           ((source & 0x000000ff) << 24) |
           ((source & 0x0000ff00) << 8) |
           ((source & 0x00ff0000) >> 8) |
           ((source & 0xff000000) >> 24);
}
template<>
inline uint16_t byteSwap<uint16_t>(uint16_t source)
{
    return uint16_t(0 |
                    ((source & 0x00ff) << 8) |
                    ((source & 0xff00) >> 8));
}
template<>
inline uint8_t byteSwap<uint8_t>(uint8_t source)
{
    return source;
}
template<>
inline int64_t byteSwap<int64_t>(int64_t source)
{
    return byteSwap<uint64_t>(uint64_t(source));
}
template<>
inline int32_t byteSwap<int32_t>(int32_t source)
{
    return byteSwap<uint32_t>(uint32_t(source));
}
template<>
inline int16_t byteSwap<int16_t>(int16_t source)
{
    return byteSwap<uint16_t>(uint16_t(source));
}
template<>
inline int8_t byteSwap<int8_t>(int8_t source)
{
    return source;
}

inline float byteSwap(float source)
{
    auto temp = fromUnaligned<uint32_t>(&source);
    temp = byteSwap(temp);
    return fromUnaligned<float>(&temp);
}

inline double byteSwap(double source)
{
    auto temp = fromUnaligned<uint64_t>(&source);
    temp = byteSwap(temp);
    return fromUnaligned<double>(&temp);
}

template<typename T>
inline void byteSwap(const T src, void *dest)
{
    toUnaligned<T>(byteSwap(src), dest);
}

template<int Size>
void *byteSwap(const void *source, int64_t count, void *dest) noexcept;
template<>
inline void *byteSwap<1>(const void *source, int64_t count, void *dest) noexcept
{
    return source != dest ? memcpy(dest, source, size_t(count)) : dest;
}
template<>
void *byteSwap<2>(const void *source, int64_t count, void *dest) noexcept;
template<>
void *byteSwap<4>(const void *source, int64_t count, void *dest) noexcept;
template<>
void *byteSwap<8>(const void *source, int64_t count, void *dest) noexcept;


//大端序处理
#if (__CPP_LIB_ENDIAN == BIG_ENDIAN)

template<typename T>
inline T toBigEndian(T source)
{
    return source;
}
template<typename T>
inline T fromBigEndian(T source)
{
    return source;
}
template<typename T>
inline T toLittleEndian(T source)
{
    return byteSwap(source);
}
template<typename T>
inline T fromLittleEndian(T source)
{
    return byteSwap(source);
}
template<typename T>
inline void toBigEndian(T src, void *dest)
{
    toUnaligned<T>(src, dest);
}
template<typename T>
inline void toLittleEndian(T src, void *dest)
{
    byteSwap<T>(src, dest);
}

template<typename T>
inline void toBigEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void toLittleEndian(const void *source, int64_t count, void *dest)
{
    byteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void fromBigEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void fromLittleEndian(const void *source, int64_t count, void *dest)
{
    byteSwap<sizeof(T)>(source, count, dest);
}

#elif (__CPP_LIB_ENDIAN == LITTLE_ENDIAN)//小端序处理

template<typename T>
inline T toBigEndian(T source)
{
    return byteSwap(source);
}
template<typename T>
inline T fromBigEndian(T source)
{
    return byteSwap(source);
}
template<typename T>
inline T toLittleEndian(T source)
{
    return source;
}
template<typename T>
inline T fromLittleEndian(T source)
{
    return source;
}
template<typename T>
inline void toBigEndian(T src, void *dest)
{
    byteSwap<T>(src, dest);
}
template<typename T>
inline void toLittleEndian(T src, void *dest)
{
    toUnaligned<T>(src, dest);
}

template<typename T>
inline void toBigEndian(const void *source, int64_t count, void *dest)
{
    byteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void toLittleEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
template<typename T>
inline void fromBigEndian(const void *source, int64_t count, void *dest)
{
    byteSwap<sizeof(T)>(source, count, dest);
}
template<typename T>
inline void fromLittleEndian(const void *source, int64_t count, void *dest)
{
    if (source != dest)
    {
        memcpy(dest, source, count * sizeof(T));
    }
}
#endif


template<typename T>
inline T fromLittleEndian(const void *src)
{
    return fromLittleEndian(qFromUnaligned<T>(src));
}

template<>
inline uint8_t fromLittleEndian<uint8_t>(const void *src)
{
    return static_cast<const uint8_t *>(src)[0];
}
template<>
inline int8_t fromLittleEndian<int8_t>(const void *src)
{
    return static_cast<const int8_t *>(src)[0];
}


template<class T>
inline T fromBigEndian(const void *src)
{
    return fromBigEndian(qFromUnaligned<T>(src));
}

template<>
inline uint8_t fromBigEndian<uint8_t>(const void *src)
{
    return static_cast<const uint8_t *>(src)[0];
}
template<>
inline int8_t fromBigEndian<int8_t>(const void *src)
{
    return static_cast<const int8_t *>(src)[0];
}

}// namespace EndianConverter
}// namespace m2

#endif//M2_ENDIAN_H_