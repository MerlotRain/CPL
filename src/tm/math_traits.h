#pragma once

#include <type_traits>

// clang-format off

template<int> struct IntegerSize;
template<> struct IntegerSize<1> { typedef uint8_t Unsigned; typedef int8_t Signed; };
template<> struct IntegerSize<2> { typedef uint16_t Unsigned; typedef int16_t Signed; };
template<> struct IntegerSize<4> { typedef uint32_t Unsigned; typedef int32_t Signed; };
template<> struct IntegerSize<8> { typedef uint64_t Unsigned; typedef int64_t Signed; };

// clang-format on

template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value, bool>::type add_overflow(T v1, T v2, T *r)
{
    // unsigned additions are well-defined
    *r = v1 + v2;
    return v1 > T(v1 + v2);
}

template<typename T>
inline typename std::enable_if<std::is_signed<T>::value, bool>::type add_overflow(T v1, T v2, T *r)
{
    // Here's how we calculate the overflow:
    // 1) unsigned addition is well-defined, so we can always execute it
    // 2) conversion from unsigned back to signed is implementation-
    //    defined and in the implementations we use, it's a no-op.
    // 3) signed integer overflow happens if the sign of the two input operands
    //    is the same but the sign of the result is different. In other words,
    //    the sign of the result must be the same as the sign of either
    //    operand.

    using U = typename std::make_unsigned<T>::type;
    *r = T(U(v1) + U(v2));

    // If int is two's complement, assume all integer types are too.
    if (std::is_same<int32_t, int>::value)
    {
        // Two's complement equivalent (generates slightly shorter code):
        //  x ^ y             is negative if x and y have different signs
        //  x & y             is negative if x and y are negative
        // (x ^ z) & (y ^ z)  is negative if x and z have different signs
        //                    AND y and z have different signs
        return ((v1 ^ *r) & (v2 ^ *r)) < 0;
    }

    bool s1 = (v1 < 0);
    bool s2 = (v2 < 0);
    bool sr = (*r < 0);
    return s1 != sr && s2 != sr;
    // also: return s1 == s2 && s1 != sr;
}

template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value, bool>::type sub_overflow(T v1, T v2, T *r)
{
    // unsigned subtractions are well-defined
    *r = v1 - v2;
    return v1 < v2;
}

template<typename T>
inline typename std::enable_if<std::is_signed<T>::value, bool>::type sub_overflow(T v1, T v2, T *r)
{
    // See above for explanation. This is the same with some signs reversed.
    // We can't use add_overflow(v1, -v2, r) because it would be UB if
    // v2 == std::numeric_limits<T>::min().

    using U = typename std::make_unsigned<T>::type;
    *r = T(U(v1) - U(v2));

    if (std::is_same<int32_t, int>::value)
        return ((v1 ^ *r) & (~v2 ^ *r)) < 0;

    bool s1 = (v1 < 0);
    bool s2 = !(v2 < 0);
    bool sr = (*r < 0);
    return s1 != sr && s2 != sr;
    // also: return s1 == s2 && s1 != sr;
}

template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value || std::is_signed<T>::value, bool>::type
mul_overflow(T v1, T v2, T *r)
{
    // use the next biggest type
    // Note: for 64-bit systems where __int128 isn't supported, this will cause an error.
    using LargerInt = IntegerSize<sizeof(T) * 2>;
    using Larger = typename std::conditional<std::is_signed<T>::value, typename LargerInt::Signed,
                                             typename LargerInt::Unsigned>::type;
    Larger lr = Larger(v1) * Larger(v2);
    *r = T(lr);
    return lr > std::numeric_limits<T>::max() || lr < std::numeric_limits<T>::min();
}