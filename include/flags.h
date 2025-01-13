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

#include <type_traits>

class Flag
{
    int i;

public:
    constexpr inline Flag(int value) noexcept : i(value) {}
    constexpr inline operator int() const noexcept { return i; }
};

template<typename Enum>
class Flags
{
    static_assert((sizeof(Enum) <= sizeof(int)),
                  "Flags uses an int as storage, so an enum with underlying "
                  "long long will overflow.");
    static_assert((std::is_enum<Enum>::value),
                  "Flags is only usable on enumeration types.");

public:
    typedef int Int;
    typedef Enum enum_type;
    constexpr inline Flags() noexcept : i(0) {}
    constexpr inline Flags(Enum flags) noexcept : i(Int(flags)) {}
    constexpr inline Flags(Flag flag) noexcept : i(flag) {}

    constexpr inline Flags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end()))
    {
    }

    constexpr static inline Flags fromInt(Int i) noexcept
    {
        return Flags(Flag(i));
    }
    constexpr inline Int toInt() const noexcept { return i; }


    constexpr inline Flags &operator&=(int mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(unsigned mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(Flags mask) noexcept
    {
        i &= mask.i;
        return *this;
    }
    constexpr inline Flags &operator&=(Enum mask) noexcept
    {
        i &= Int(mask);
        return *this;
    }
    constexpr inline Flags &operator|=(Flags other) noexcept
    {
        i |= other.i;
        return *this;
    }
    constexpr inline Flags &operator|=(Enum other) noexcept
    {
        i |= Int(other);
        return *this;
    }
    constexpr inline Flags &operator^=(Flags other) noexcept
    {
        i ^= other.i;
        return *this;
    }
    constexpr inline Flags &operator^=(Enum other) noexcept
    {
        i ^= Int(other);
        return *this;
    }

    constexpr inline operator Int() const noexcept { return i; }
    constexpr inline bool operator!() const noexcept { return !i; }


    constexpr inline Flags operator|(Flags other) const noexcept
    {
        return Flags(Flag(i | other.i));
    }
    constexpr inline Flags operator|(Enum other) const noexcept
    {
        return Flags(Flag(i | Int(other)));
    }
    constexpr inline Flags operator^(Flags other) const noexcept
    {
        return Flags(Flag(i ^ other.i));
    }
    constexpr inline Flags operator^(Enum other) const noexcept
    {
        return Flags(Flag(i ^ Int(other)));
    }
    constexpr inline Flags operator&(int mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }
    constexpr inline Flags operator&(unsigned int mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }

    constexpr inline Flags operator&(Flags other) const noexcept
    {
        return Flags(Flag(i & other.i));
    }
    constexpr inline Flags operator&(Enum other) const noexcept
    {
        return Flags(Flag(i & Int(other)));
    }
    constexpr inline Flags operator~() const noexcept
    {
        return Flags(Flag(~i));
    }

    constexpr inline void operator+(Flags other) const noexcept = delete;
    constexpr inline void operator+(Enum other) const noexcept = delete;
    constexpr inline void operator+(int other) const noexcept = delete;
    constexpr inline void operator-(Flags other) const noexcept = delete;
    constexpr inline void operator-(Enum other) const noexcept = delete;
    constexpr inline void operator-(int other) const noexcept = delete;

    constexpr inline bool testFlag(Enum flag) const noexcept
    {
        return testFlags(flag);
    }
    constexpr inline bool testFlags(Flags flags) const noexcept
    {
        return flags.i ? ((i & flags.i) == flags.i) : i == Int(0);
    }
    constexpr inline bool testAnyFlag(Enum flag) const noexcept
    {
        return testAnyFlags(flag);
    }
    constexpr inline bool testAnyFlags(Flags flags) const noexcept
    {
        return (i & flags.i) != Int(0);
    }
    constexpr inline Flags &setFlag(Enum flag, bool on = true) noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Flags(flag));
    }

    friend constexpr inline bool operator==(Flags lhs, Flags rhs) noexcept
    {
        return lhs.i == rhs.i;
    }
    friend constexpr inline bool operator!=(Flags lhs, Flags rhs) noexcept
    {
        return lhs.i != rhs.i;
    }
    friend constexpr inline bool operator==(Flags lhs, Enum rhs) noexcept
    {
        return lhs == Flags(rhs);
    }
    friend constexpr inline bool operator!=(Flags lhs, Enum rhs) noexcept
    {
        return lhs != Flags(rhs);
    }
    friend constexpr inline bool operator==(Enum lhs, Flags rhs) noexcept
    {
        return Flags(lhs) == rhs;
    }
    friend constexpr inline bool operator!=(Enum lhs, Flags rhs) noexcept
    {
        return Flags(lhs) != rhs;
    }

private:
    constexpr static inline Int initializer_list_helper(
            typename std::initializer_list<Enum>::const_iterator it,
            typename std::initializer_list<Enum>::const_iterator end) noexcept
    {
        return (it == end ? Int(0)
                          : (Int(*it) | initializer_list_helper(it + 1, end)));
    }

    Int i;
};

#define DECLARE_FLAGS(F, E) typedef Flags<E> F;