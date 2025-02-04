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
#include <string>

namespace CPL {

/// \brief Globally Unique Identifier (GUID)
/// \details A GUID is a unique identifier used for various purposes, such as identifying objects, databases, or resources across systems.
struct CPL_API Guid
{
    union
    {
        struct
        {
            unsigned int Data1;    ///< First part of the GUID (32 bits)
            unsigned short Data2;  ///< Second part of the GUID (16 bits)
            unsigned short Data3;  ///< Third part of the GUID (16 bits)
            unsigned char Data4[8];///< Fourth part of the GUID (8 bytes)
        } Data128;
        unsigned char Data[16];///< Array of 16 bytes representing the GUID
    };

    /// \brief Formatting modes for GUID-to-string conversion
    enum class Format
    {
        /// \brief 32-digit number with hyphens separating sections
        /// \details Format: 00000000-0000-0000-0000-000000000000
        eHyphens32 = 'D',

        /// \brief 32-digit number with no hyphens
        /// \details Format: 00000000000000000000000000000000
        eNumber32 = 'N',

        /// \brief 32-digit number with hyphens and enclosed in braces
        /// \details Format: {00000000-0000-0000-0000-000000000000}
        eHyphensBraces = 'B',

        /// \brief 32-digit number with hyphens and enclosed in parentheses
        /// \details Format: (00000000-0000-0000-0000-000000000000)
        eHyphensParentheses = 'P',

        /// \brief Four hexadecimal values enclosed in braces
        /// \details Format: {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
        eHexadecimalBraces = 'X',
    };

public:
    /// \brief Default constructor
    /// \details Initializes a GUID to a new unique value.
    Guid();

    /// \brief Copy constructor
    /// \param rhs The GUID to copy from
    /// \details Copies the GUID value from another `Guid` object.
    Guid(const Guid &rhs);

    /// \brief Move constructor
    /// \param rhs The GUID to move from
    /// \details Moves the GUID value from another `Guid` object.
    Guid(Guid &&rhs) noexcept;

    /// \brief Equality comparison
    /// \param guid The GUID to compare to
    /// \return True if the GUIDs are equal, false otherwise
    bool operator==(const Guid &guid) const;

    /// \brief Assignment operator
    /// \param guid The GUID to assign
    /// \return A reference to this `Guid` object
    Guid &operator=(const Guid &guid);

    /// \brief Move assignment operator
    /// \param guid The GUID to move
    /// \return A reference to this `Guid` object
    Guid &operator=(Guid &&guid) noexcept;

    /// \brief Swap two GUIDs
    /// \param guid The GUID to swap with
    /// \details Swaps the contents of the current GUID with the provided GUID.
    void Swap(Guid &guid);

    /// \brief Converts the GUID to a formatted string
    /// \param formatType The format in which to return the string
    /// \return A string representing the GUID in the specified format
    std::string ToString(Format formatType = Format::eHyphens32) const;
};

/// \brief UUID is a universally unique identifier (equivalent to GUID)
/// \details This typedef is just an alias for `Guid`, both represent the same concept.
typedef Guid Uuid;

/// \brief A class containing various mathematical utility functions.
class CPL_API Math
{
public:
    /// \brief Generates a random number between the specified range.
    /// \param min The minimum value of the range.
    /// \param max The maximum value of the range.
    /// \return A random value between `min` and `max`.
    template<class T>
    static T Random(T min, T max)
    {
        int n = rand();
        return min + n * 1.0 * (max - min) / INT_MAX;
    }

    /// \brief Returns the maximum of two values.
    /// \param a The first value.
    /// \param b The second value.
    /// \return The greater of `a` and `b`.
    template<class U, class V>
    static U Max(U a, V b)
    {
        return a > b ? a : b;
    }

    /// \brief Returns the minimum of two values.
    /// \param a The first value.
    /// \param b The second value.
    /// \return The smaller of `a` and `b`.
    template<class U, class V>
    static U Min(U a, V b)
    {
        return a < b ? a : b;
    }

    /// \brief Rounds up an integer to the next power of 2.
    /// \param n The integer to round up.
    /// \return The next power of 2 greater than or equal to `n`.
    static unsigned int RoundUpPowerOf2(unsigned int n);

    /// \brief Returns the next power of 2 greater than or equal to `v`.
    /// \param v The value to round up.
    /// \return The next power of 2 greater than or equal to `v`.
    static unsigned int NextPowerOfTwo(unsigned int v);

    /// \brief Returns the next power of 2 greater than or equal to `v` for 64-bit integers.
    /// \param v The value to round up.
    /// \return The next power of 2 greater than or equal to `v`.
    static unsigned long long NextPowerOfTwo(unsigned long long v);

    /// \brief Checks if a number is a power of 2.
    /// \param n The number to check.
    /// \return `true` if `n` is a power of 2, otherwise `false`.
    static bool IsPowerOfTwo(unsigned long long n);

    /// \brief Checks if two double-precision floating point numbers are equal.
    /// \param d1 The first value.
    /// \param d2 The second value.
    /// \return `true` if `d1` and `d2` are equal, otherwise `false`.
    static bool IsEqual(double d1, double d2);

    /// \brief Checks if two single-precision floating point numbers are equal.
    /// \param f1 The first value.
    /// \param f2 The second value.
    /// \return `true` if `f1` and `f2` are equal, otherwise `false`.
    static bool IsEqual(float f1, float f2);

    /// \brief Checks if two double-precision floating point numbers are approximately equal within a tolerance.
    /// \param d1 The first value.
    /// \param d2 The second value.
    /// \param tol The tolerance.
    /// \return `true` if `d1` and `d2` are approximately equal, otherwise `false`.
    static bool IsEqual(double d1, double d2, double tol);

    /// \brief Checks if two single-precision floating point numbers are approximately equal within a tolerance.
    /// \param f1 The first value.
    /// \param f2 The second value.
    /// \param tol The tolerance.
    /// \return `true` if `f1` and `f2` are approximately equal, otherwise `false`.
    static bool IsEqual(float f1, float f2, float tol);

    /// \brief Rounds a double to the nearest integer or specified decimal place.
    /// \param r The value to round.
    /// \param place The number of decimal places to round to.
    /// \return The rounded value.
    static double Round(double r, unsigned int place = 0);

    /// \brief Rounds a float to the nearest integer or specified decimal place.
    /// \param r The value to round.
    /// \param place The number of decimal places to round to.
    /// \return The rounded value.
    static float Round(float r, unsigned int place = 0);

    /// \brief Converts degrees to radians.
    /// \param degree The angle in degrees.
    /// \return The angle in radians.
    static double ToRadian(double degree);

    /// \brief Converts radians to degrees.
    /// \param radian The angle in radians.
    /// \return The angle in degrees.
    static double ToDegree(double radian);

    /// \brief Returns a "Not-a-Number" (NaN) value for double-precision floating point numbers.
    /// \details NaN represents an invalid result (e.g., 0/0).
    /// \return A NaN value.
    static double NaN();

    /// \brief Returns a "Not-a-Number" (NaN) value for single-precision floating point numbers.
    /// \details NaN represents an invalid result (e.g., 0/0).
    /// \return A NaN value.
    static float NaNF();

    /// \brief Checks if a double-precision floating point value is NaN.
    /// \param val The value to check.
    /// \return `true` if `val` is NaN, otherwise `false`.
    static bool IsNaN(double val);

    /// \brief Returns the mathematical constant Pi.
    /// \return The value of Pi.
    static double Pi();

    /// \brief Generates a new GUID in the format `E1F17786-DABD-4C0B-9679-514E6566E8B2`.
    /// \return A newly generated GUID as a string.
    static std::string NewGUID();

    /// \brief Returns the natural logarithm (base e) of a value.
    /// \param val The value to compute the logarithm for.
    /// \return The natural logarithm of `val`.
    static double Log(double val);

    /// \brief Clamps a value between a minimum and a maximum range.
    /// \param v The value to clamp.
    /// \param minimum The minimum value of the range.
    /// \param maximum The maximum value of the range.
    /// \return `v` clamped between `minimum` and `maximum`.
    template<typename T>
    static T ClampTo(T v, T minimum, T maximum)
    {
        return v < minimum ? minimum : v > maximum ? maximum : v;
    }

    /// \brief Clamps a value to a minimum value.
    /// \param v The value to clamp.
    /// \param minimum The minimum value.
    /// \return `v` clamped to be no less than `minimum`.
    template<typename T>
    static T ClampAbove(T v, T minimum)
    {
        return v < minimum ? minimum : v;
    }

    /// \brief Clamps a value to a maximum value.
    /// \param v The value to clamp.
    /// \param maximum The maximum value.
    /// \return `v` clamped to be no greater than `maximum`.
    template<typename T>
    static T ClampBelow(T v, T maximum)
    {
        return v > maximum ? maximum : v;
    }

    /// \brief A shorthand for `ClampTo`.
    /// \param v The value to clamp.
    /// \param minimum The minimum value.
    /// \param maximum The maximum value.
    /// \return `v` clamped between `minimum` and `maximum`.
    template<typename T>
    static T ClampBetween(T v, T minimum, T maximum)
    {
        return ClampBelow(ClampAbove(v, minimum), maximum);
    }

    /// \brief Returns the sign of a number.
    /// \param v The value to evaluate.
    /// \return `-1` if `v` is less than zero, `1` if `v` is greater than zero, and `0` if `v` is zero.
    template<typename T>
    static T Sign(T v)
    {
        return v < (T) 0 ? (T) -1 : (T) 1;
    }

    /// \brief Returns the sign of a number, or zero if the number is zero.
    /// \param v The value to evaluate.
    /// \return `-1` if `v` is less than zero, `1` if `v` is greater than zero, and `0` if `v` is zero.
    template<typename T>
    static T SignOrZero(T v)
    {
        return v < (T) 0 ? (T) -1 : (v > (T) 0 ? (T) 1 : 0);
    }

    /// \brief Returns the square of a value.
    /// \param v The value to square.
    /// \return The square of `v`.
    template<typename T>
    static T Square(T v)
    {
        return v * v;
    }

    /// \brief Returns the square of a value, ensuring the result is always non-negative.
    /// \param v The value to square.
    /// \return The signed square of `v`.
    template<typename T>
    static T SignedSquare(T v)
    {
        return v < (T) 0 ? -v * v : v * v;
    }
};

/// \brief Pseudo-random number generator
/// \details Based on drand48: https://www.man7.org/linux/man-pages/man3/drand48.3.html
class CPL_API Random
{
    unsigned short m_Seed[7];

public:
    /// \brief Default constructor with a random seed
    Random();

    /// \brief Constructs a random number generator with a 32-bit integer seed
    /// \param seed A 32-bit integer seed
    Random(int seed);

    /// \brief Constructs a random number generator with a full 48-bit seed
    /// \param seed A 7-element array representing the full seed
    Random(unsigned short seed[7]);

    /// \brief Copy constructor
    /// \param rhs The source Random object
    Random(const Random &rhs);

    /// \brief Move constructor
    /// \param rhs The source Random object to be moved
    Random(Random &&rhs) noexcept;

    /// \brief Swaps the internal state with another Random object
    /// \param rhs The Random object to swap with
    void Swap(Random &rhs);

    /// \brief Move assignment operator
    /// \param rhs The source Random object to be moved
    /// \return Reference to the assigned Random object
    Random &operator=(Random &&rhs) noexcept;

    /// \brief Copy assignment operator
    /// \param rhs The source Random object
    /// \return Reference to the assigned Random object
    Random &operator=(const Random &rhs);

    /// \brief Sets the XSeed value (first 3 elements of the seed)
    /// \param seed A 3-element array representing the XSeed
    void XSeed(unsigned short seed[3]);

    /// \brief Gets the full seed (7 elements)
    /// \return Pointer to the internal seed array
    const unsigned short *Seed() const;

    /// \brief Gets the XSeed value (first 3 elements of the seed)
    /// \return Pointer to the XSeed array
    const unsigned short *XSeed() const;

    /// \brief Generates a pseudo-random integer in the range [0, 2^31) using a given XSeed
    /// \param xseed A 3-element array representing the XSeed
    /// \return A random integer in the range [0, 2^31)
    int NRand(unsigned short xseed[3]);

    /// \brief Generates a pseudo-random integer in the range [0, 2^31)
    /// \return A random integer in the range [0, 2^31)
    int LRand();

    /// \brief Generates a pseudo-random integer in the range [-2^31, 2^31) using a given XSeed
    /// \param xseed A 3-element array representing the XSeed
    /// \return A random integer in the range [-2^31, 2^31)
    int JRand(unsigned short xseed[3]);

    /// \brief Generates a pseudo-random integer in the range [-2^31, 2^31)
    /// \return A random integer in the range [-2^31, 2^31)
    int MRand();

    /// \brief Generates a pseudo-random floating-point number in the range [0.0, 1.0) using a given XSeed
    /// \param xseed A 3-element array representing the XSeed
    /// \return A random floating-point number in the range [0.0, 1.0)
    double ERand(unsigned short xseed[3]);

    /// \brief Generates a pseudo-random floating-point number in the range [0.0, 1.0)
    /// \return A random floating-point number in the range [0.0, 1.0)
    double DRand();

    /// \brief Generates a pseudo-random integer in the range [0, 2^31)
    /// \return A random integer in the range [0, 2^31)
    int Next();

    /// \brief Generates a pseudo-random integer in the specified range [minValue, maxValue)
    /// \param minValue The lower bound (inclusive)
    /// \param maxValue The upper bound (exclusive)
    /// \return A random integer in the range [minValue, maxValue)
    int Next(int minValue, int maxValue);

    /// \brief Generates a pseudo-random floating-point number in the specified range [minValue, maxValue)
    /// \param minValue The lower bound (inclusive)
    /// \param maxValue The upper bound (exclusive)
    /// \return A random floating-point number in the range [minValue, maxValue)
    double Next(double minValue, double maxValue);

    /// \brief Fills the specified byte array with random values
    /// \param bytes Pointer to the byte array to be filled
    /// \param nLen The number of bytes to fill
    void NextBytes(unsigned char *bytes, int nLen);

    /// \brief Generates a pseudo-random floating-point number in the range [0.0, 1.0)
    /// \return A random floating-point number in the range [0.0, 1.0)
    double NextDouble();
};

}// namespace CPL