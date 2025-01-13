/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/exports.h>
#include <memory>
#include <type_traits>
#include <vector>


struct byte_order
{
    static constexpr unsigned short value = 0x0102;
    static constexpr auto is_little_endian = (value & 0xFF) == 0x02;
};

constexpr bool is_little_endian = byte_order::is_little_endian;
constexpr bool is_big_endian = !byte_order::is_little_endian;


class LIBDWG_API EndianConverter
{
public:
    EndianConverter() = default;
    std::vector<unsigned char> GetBytes(char value);
    std::vector<unsigned char> GetBytes(short value);
    std::vector<unsigned char> GetBytes(unsigned short value);
    std::vector<unsigned char> GetBytes(int value);
    std::vector<unsigned char> GetBytes(unsigned int value);
    std::vector<unsigned char> GetBytes(long long value);
    std::vector<unsigned char> GetBytes(unsigned long long value);
    std::vector<unsigned char> GetBytes(double value);
    std::vector<unsigned char> GetBytes(float value);

    char ToChar(const unsigned char *bytes);
    int16_t ToInt16(const unsigned char *bytes);
    uint16_t ToUInt16(const unsigned char *bytes);
    int32_t ToInt32(const unsigned char *bytes);
    uint32_t ToUint32(const unsigned char *bytes);
    int64_t ToInt64(const unsigned char *bytes);
    uint64_t ToUInt64(const unsigned char *bytes);
    float ToFloat(const unsigned char *bytes);
    double ToDouble(const unsigned char *bytes);

    template<class T>
    std::vector<unsigned char> GetBytes(T value)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer(new unsigned char[sz]);
        byteswap(buffer.get(), sz);
        memcpy(buffer.get(), &value, sz);
        return buffer;
    }

    template<class T>
    T FromBytes(const unsigned char *bytes)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer(new unsigned char[sz]);
        std::memcpy(buffer.get(), bytes, sz);
        byteswap(buffer.get(), sz);
        T value;
        std::memcpy(&value, buffer.get(), sz);
        return value;
    }

protected:
    virtual void byteswap(unsigned char *buffer, size_t length) = 0;
};

class LIBDWG_API BigEndianConverter : public EndianConverter
{
public:
    BigEndianConverter() = default;
    ~BigEndianConverter() = default;
    static std::unique_ptr<EndianConverter> Instance();
};

class LIBDWG_API LittleEndianConverter : public EndianConverter
{
public:
    LittleEndianConverter() = default;
    ~LittleEndianConverter() = default;
    static std::unique_ptr<EndianConverter> Instance();
};
