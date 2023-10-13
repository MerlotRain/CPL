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

#ifndef M2_FLAGS_H_
#define M2_FLAGS_H_

#include <type_traits>

namespace m2 {

class Flag
{
    int i;

public:
    constexpr inline explicit Flag(int val) noexcept : i(val) {}
    constexpr inline explicit operator int() const noexcept { return i; }
};

template<typename Enum>
class Flags
{
    static_assert(sizeof(Enum) <= sizeof(int), "Enum value is overflows");
    static_assert((std::is_enum<Enum>::value),
                  "Flags is only usable on enumeration types");

public:
    typedef Enum enum_type;

    typedef typename std::conditional<
            std::is_unsigned<typename std::underlying_type<Enum>::type>::value,
            unsigned int, signed int>::type Integer;

    constexpr inline Flags() noexcept : i(0) {}
    constexpr inline explicit Flags(Enum flags) noexcept : i(Integer(flags)) {}
    constexpr inline explicit Flags(Flag flag) noexcept : i(flag) {}

    constexpr inline Flags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end()))
    {
    }

    constexpr inline Flags &operator&=(int mask) const noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(unsigned int mask) const noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(Enum mask) const noexcept
    {
        i &= Integer(mask);
        return *this;
    }
    constexpr inline Flags &operator|=(Flags other) const noexcept
    {
        i |= other.i;
        return *this;
    }
    constexpr inline Flags &operator|=(Enum other) const noexcept
    {
        i |= Integer(other);
        return *this;
    }
    constexpr inline Flags &operator^=(Flags other) const noexcept
    {
        i ^= other.i;
        return *this;
    }
    constexpr inline Flags &operator^=(Enum other) const noexcept
    {
        i ^= Integer(other);
        return *this;
    }

    constexpr inline operator Integer() const noexcept { return i; }
    constexpr inline Flags operator|(Flags other) const noexcept
    {
        return Flags(Flag(i | other.i));
    }
    constexpr inline Flags operator|(Enum other) const noexcept
    {
        return Flags(Flag(i | Integer(other)));
    }
    constexpr inline Flags operator^(Flags other) const noexcept
    {
        return Flags(Flag(i ^ other.i));
    }
    constexpr inline Flags operator^(Enum other) const noexcept
    {
        return Flags(Flag(i ^ Integer(other)));
    }
    constexpr inline Flags operator&(int mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }
    constexpr inline Flags operator&(unsigned int mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }
    constexpr inline Flags operator&(Enum other) const noexcept
    {
        return Flags(Flag(i & Integer(other)));
    }
    constexpr inline Flags operator~() const noexcept
    {
        return Flags(Flag(~i));
    }

    constexpr inline bool operator!() const noexcept { return !i; }

    constexpr inline bool testFlag(Enum flag) const noexcept
    {
        return (i & Integer(flag)) == Integer(flag) &&
               (Integer(flag) != 0 || i == Integer(flag));
    }
    constexpr inline Flags &setFlag(Enum flag, bool on = true) const noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Integer(flag));
    }

private:
    constexpr static inline Integer initializer_list_helper(
            typename std::initializer_list<Enum>::const_iterator it,
            typename std::initializer_list<Enum>::const_iterator end) noexcept
    {
        return (it == end ? Integer(0)
                          : (Integer(*it) |
                             initializer_list_helper(it + 1, end)));
    }

private:
    Integer i;
};
#define M2_DECLARE_FLAGS(flags, Enum) typedef m2::Flags<Enum> flags;

}// namespace m2

#endif//M2_FLAGS_H_