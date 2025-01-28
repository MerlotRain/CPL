/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <cpl_byteendian.h>

namespace CPL {

std::vector<unsigned char> EndianConverter::GetBytes(char value)
{
    return GetBytes<char>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(short value)
{
    return GetBytes<short>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(unsigned short value)
{
    return GetBytes<unsigned short>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(int value)
{
    return GetBytes<int>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(unsigned int value)
{
    return GetBytes<unsigned int>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(long long value)
{
    return GetBytes<long long>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(unsigned long long value)
{
    return GetBytes<unsigned long long>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(double value)
{
    return GetBytes<double>(value);
}

std::vector<unsigned char> EndianConverter::GetBytes(float value)
{
    return GetBytes<float>(value);
}

char EndianConverter::ToChar(const unsigned char *bytes)
{
    return FromBytes<char>(bytes);
}

int16_t EndianConverter::ToInt16(const unsigned char *bytes)
{
    return FromBytes<int16_t>(bytes);
}

uint16_t EndianConverter::ToUInt16(const unsigned char *bytes)
{
    return FromBytes<uint16_t>(bytes);
}

int32_t EndianConverter::ToInt32(const unsigned char *bytes)
{
    return FromBytes<int32_t>(bytes);
}

uint32_t EndianConverter::ToUint32(const unsigned char *bytes)
{
    return FromBytes<uint32_t>(bytes);
}

int64_t EndianConverter::ToInt64(const unsigned char *bytes)
{
    return FromBytes<int64_t>(bytes);
}

uint64_t EndianConverter::ToUInt64(const unsigned char *bytes)
{
    return FromBytes<uint64_t>(bytes);
}

float EndianConverter::ToFloat(const unsigned char *bytes)
{
    return FromBytes<float>(bytes);
}

double EndianConverter::ToDouble(const unsigned char *bytes)
{
    return FromBytes<double>(bytes);
}

class DefaultEndianConverter : public EndianConverter
{
public:
    DefaultEndianConverter() = default;
    ~DefaultEndianConverter() = default;

protected:
    void byteswap(unsigned char *buffer, size_t length) override {}
};

class InverseConverter : public EndianConverter
{
public:
    InverseConverter() = default;
    ~InverseConverter() = default;

protected:
    void byteswap(unsigned char *buffer, size_t length) override
    {
        unsigned char *swap = new unsigned char[length];
        for (size_t i = 0; i < length; ++i)
        {
            swap[i] = buffer[length - 1 - i];
        }
        std::memcpy(buffer, swap, length);
        delete[] swap;
    }
};

std::unique_ptr<EndianConverter> BigEndianConverter::Instance()
{
#ifdef CPL_BIG_ENDIAN
    return std::unique_ptr<EndianConverter>(new DefaultEndianConverter());
#else
    return std::unique_ptr<EndianConverter>(new InverseConverter());
#endif
}

std::unique_ptr<EndianConverter> LittleEndianConverter::Instance()
{
#ifdef CPL_BIG_ENDIAN
    return std::unique_ptr<EndianConverter>(new InverseConverter());
#else
    return std::unique_ptr<EndianConverter>(new DefaultEndianConverter());
#endif
}

}// namespace CPL