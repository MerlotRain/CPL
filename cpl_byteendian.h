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

#pragma once

#include <cpl_exports.h>
#include <memory>
#include <type_traits>
#include <vector>

namespace CPL {


// GNU libc offers the helpful header <endian.h> which defines
// __BYTE_ORDER
#if defined (__GLIBC__)
# include <endian.h>
# if (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define CPL_LITTLE_ENDIAN
# elif (__BYTE_ORDER == __BIG_ENDIAN)
#  define CPL_BIG_ENDIAN
# elif (__BYTE_ORDER == __PDP_ENDIAN)
#  define CPL_PDP_ENDIAN
# else
#  error Unknown machine endianness detected.
# endif
# define CPL_BYTE_ORDER __BYTE_ORDER
#elif defined(_BIG_ENDIAN)
# define CPL_BIG_ENDIAN
# define CPL_BYTE_ORDER 4321
#elif defined(_LITTLE_ENDIAN)
# define CPL_LITTLE_ENDIAN
# define CPL_BYTE_ORDER 1234
#elif defined(_LITTLE_ENDIAN) && defined(_BIG_ENDIAN) 
# define CPL_LITTLE_ENDIAN
# define CPL_BYTE_ORDER 1234

#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__)
# define CPL_BIG_ENDIAN
# define CPL_BYTE_ORDER 4321
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(__arm64) || defined(__arm64__) \
   || defined(_M_X64)
# define CPL_LITTLE_ENDIAN
# define CPL_BYTE_ORDER 1234
#else
# error The file cpl_byteendian.h needs to be set up for your CPU type.
#endif


/// @class EndianConverter
/// @brief Abstract base class for converting between primitive types and their byte representations.
class CPL_API EndianConverter
{
public:
    /// @brief Default constructor.
    EndianConverter() = default;

    /// @brief Converts a char value to its byte representation.
    /// @param value The char value to convert.
    /// @return A vector of bytes representing the char value.
    std::vector<unsigned char> GetBytes(char value);

    /// @brief Converts a short value to its byte representation.
    /// @param value The short value to convert.
    /// @return A vector of bytes representing the short value.
    std::vector<unsigned char> GetBytes(short value);

    /// @brief Converts an unsigned short value to its byte representation.
    /// @param value The unsigned short value to convert.
    /// @return A vector of bytes representing the unsigned short value.
    std::vector<unsigned char> GetBytes(unsigned short value);

    /// @brief Converts an int value to its byte representation.
    /// @param value The int value to convert.
    /// @return A vector of bytes representing the int value.
    std::vector<unsigned char> GetBytes(int value);

    /// @brief Converts an unsigned int value to its byte representation.
    /// @param value The unsigned int value to convert.
    /// @return A vector of bytes representing the unsigned int value.
    std::vector<unsigned char> GetBytes(unsigned int value);

    /// @brief Converts a long long value to its byte representation.
    /// @param value The long long value to convert.
    /// @return A vector of bytes representing the long long value.
    std::vector<unsigned char> GetBytes(long long value);

    /// @brief Converts an unsigned long long value to its byte representation.
    /// @param value The unsigned long long value to convert.
    /// @return A vector of bytes representing the unsigned long long value.
    std::vector<unsigned char> GetBytes(unsigned long long value);

    /// @brief Converts a double value to its byte representation.
    /// @param value The double value to convert.
    /// @return A vector of bytes representing the double value.
    std::vector<unsigned char> GetBytes(double value);

    /// @brief Converts a float value to its byte representation.
    /// @param value The float value to convert.
    /// @return A vector of bytes representing the float value.
    std::vector<unsigned char> GetBytes(float value);

    /// @brief Converts a byte array to a char value.
    /// @param bytes The byte array.
    /// @return The resulting char value.
    char ToChar(const unsigned char *bytes);

    /// @brief Converts a byte array to a 16-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting 16-bit integer.
    int16_t ToInt16(const unsigned char *bytes);

    /// @brief Converts a byte array to an unsigned 16-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting unsigned 16-bit integer.
    uint16_t ToUInt16(const unsigned char *bytes);

    /// @brief Converts a byte array to a 32-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting 32-bit integer.
    int32_t ToInt32(const unsigned char *bytes);

    /// @brief Converts a byte array to an unsigned 32-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting unsigned 32-bit integer.
    uint32_t ToUint32(const unsigned char *bytes);

    /// @brief Converts a byte array to a 64-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting 64-bit integer.
    int64_t ToInt64(const unsigned char *bytes);

    /// @brief Converts a byte array to an unsigned 64-bit integer.
    /// @param bytes The byte array.
    /// @return The resulting unsigned 64-bit integer.
    uint64_t ToUInt64(const unsigned char *bytes);

    /// @brief Converts a byte array to a float value.
    /// @param bytes The byte array.
    /// @return The resulting float value.
    float ToFloat(const unsigned char *bytes);

    /// @brief Converts a byte array to a double value.
    /// @param bytes The byte array.
    /// @return The resulting double value.
    double ToDouble(const unsigned char *bytes);

    /// @brief Converts a value to its byte representation.
    /// @tparam T The type of the value.
    /// @param value The value to convert.
    /// @return A vector of bytes representing the value.
    template<class T>
    std::vector<unsigned char> GetBytes(T value)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer;
        buffer.resize(sz);
        byteswap(buffer.data(), sz);
        memcpy(buffer.data(), &value, sz);
        return buffer;
    }

    /// @brief Converts a byte array to a value.
    /// @tparam T The type of the value.
    /// @param bytes The byte array.
    /// @return The resulting value.
    template<class T>
    T FromBytes(const unsigned char *bytes)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer;
        buffer.resize(sz);
        std::memcpy(buffer.data(), bytes, sz);
        byteswap(buffer.data(), sz);
        T value;
        std::memcpy(&value, buffer.data(), sz);
        return value;
    }

protected:
    /// @brief Abstract method for byte-swapping.
    /// @param buffer The buffer to be byte-swapped.
    /// @param length The length of the buffer.
    virtual void byteswap(unsigned char *buffer, size_t length) = 0;
};

/// @class BigEndianConverter
/// @brief Converter for big-endian byte order.
class CPL_API BigEndianConverter : public EndianConverter
{
public:
    /// @brief Default constructor.
    BigEndianConverter() = default;

    /// @brief Default destructor.
    ~BigEndianConverter() = default;

    /// @brief Creates a singleton instance of BigEndianConverter.
    /// @return A unique pointer to a BigEndianConverter instance.
    static std::unique_ptr<EndianConverter> Instance();
};

/// @class LittleEndianConverter
/// @brief Converter for little-endian byte order.
class CPL_API LittleEndianConverter : public EndianConverter
{
public:
    /// @brief Default constructor.
    LittleEndianConverter() = default;

    /// @brief Default destructor.
    ~LittleEndianConverter() = default;

    /// @brief Creates a singleton instance of LittleEndianConverter.
    /// @return A unique pointer to a LittleEndianConverter instance.
    static std::unique_ptr<EndianConverter> Instance();
};

}// namespace CPL