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

#ifndef M2_UUID_H_
#define M2_UUID_H_

#include <m2_bytebuffer.h>
#include <preconfig.h>

namespace m2 {

class M2_API UUID
{
public:
    enum Variant
    {
        VarUnknown = -1,
        NCS = 0,
        DCE = 2,
        Microsoft = 6,
        Reserved = 7
    };

    enum Version
    {
        VerUnknown = -1,
        Time = 1,         // 0 0 0 1
        EmbeddedPOSIX = 2,// 0 0 1 0
        Md5 = 3,          // 0 0 1 1
        Random = 4,       // 0 1 0 0
        Sha1 = 5          // 0 1 0 1
    };

    enum StringFormat
    {
        WithBraces = 0,
        WithoutBraces = 1,
        Id128 = 3
    };

    constexpr UUID() noexcept;

    constexpr UUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b1, uint8_t b2,
                   uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
                   uint8_t b8) noexcept;

    String toString(StringFormat mode = WithBraces) const;
    ByteBuffer toByteArray(StringFormat mode = WithBraces) const;
    ByteBuffer toRfc4122() const;
    static UUID fromRfc4122(const ByteBuffer &);
    bool isNull() const noexcept;

    constexpr bool operator==(const UUID &orig) const noexcept;
    constexpr bool operator!=(const UUID &orig) const noexcept;
    bool operator<(const UUID &other) const noexcept;
    bool operator>(const UUID &other) const noexcept;

    static UUID createUuid();
    static inline UUID createUuidV5(const UUID &ns, const String &baseData);

    UUID::Variant variant() const noexcept;
    UUID::Version version() const noexcept;

private:
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
};


}// namespace m2

#endif//M2_UUID_H_