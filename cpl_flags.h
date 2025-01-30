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

#include <type_traits>

namespace CPL {

// Class representing a flag, stores an integer value.
class Flag
{
    int i;

public:
    // Constructor that initializes the flag with a specific value.
    constexpr inline Flag(int value) noexcept : i(value) {}

    // Conversion operator to convert a Flag to an integer.
    constexpr inline operator int() const noexcept { return i; }
};

// Template class for handling multiple flags.
template<typename Enum>
class Flags
{
    // Ensures that the enum fits into an integer.
    static_assert((sizeof(Enum) <= sizeof(int)),
                  "Flags uses an int as storage, so an enum with underlying "
                  "long long will overflow.");

    // Ensures that the template type is an enum type.
    static_assert((std::is_enum<Enum>::value),
                  "Flags is only usable on enumeration types.");

public:
    typedef int Int;       // Defines Int as the storage type for flags.
    typedef Enum enum_type;// Alias for the enum type.

    // Default constructor, initializes the internal integer to zero.
    constexpr inline Flags() noexcept : i(0) {}

    // Constructor that initializes the flag from an enum value.
    constexpr inline Flags(Enum flags) noexcept : i(Int(flags)) {}

    // Constructor that initializes the flag from a Flag object.
    constexpr inline Flags(Flag flag) noexcept : i(flag) {}

    // Constructor that initializes the flag using an initializer list of enums.
    constexpr inline Flags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end()))
    {
    }

    // Static method to create Flags from an integer value.
    constexpr static inline Flags FromInt(Int i) noexcept
    {
        return Flags(Flag(i));
    }

    // Converts the Flags object to an integer.
    constexpr inline Int ToInt() const noexcept { return i; }

    // Bitwise AND assignment operator, works with int, Flags, or Enum.
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

    // Bitwise OR assignment operator, works with Flags or Enum.
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

    // Bitwise XOR assignment operator, works with Flags or Enum.
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

    // Converts the Flags object to an integer using conversion operator.
    constexpr inline operator Int() const noexcept { return i; }

    // Logical NOT operator, returns true if the flag is zero.
    constexpr inline bool operator!() const noexcept { return !i; }

    // Bitwise OR operator, works with Flags or Enum.
    constexpr inline Flags operator|(Flags other) const noexcept
    {
        return Flags(Flag(i | other.i));
    }
    constexpr inline Flags operator|(Enum other) const noexcept
    {
        return Flags(Flag(i | Int(other)));
    }

    // Bitwise XOR operator, works with Flags or Enum.
    constexpr inline Flags operator^(Flags other) const noexcept
    {
        return Flags(Flag(i ^ other.i));
    }
    constexpr inline Flags operator^(Enum other) const noexcept
    {
        return Flags(Flag(i ^ Int(other)));
    }

    // Bitwise AND operator, works with int, Flags, or Enum.
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

    // Bitwise NOT operator, inverts all flags.
    constexpr inline Flags operator~() const noexcept
    {
        return Flags(Flag(~i));
    }

    // Delete operator+ and operator- to prevent their usage.
    constexpr inline void operator+(Flags other) const noexcept = delete;
    constexpr inline void operator+(Enum other) const noexcept = delete;
    constexpr inline void operator+(int other) const noexcept = delete;
    constexpr inline void operator-(Flags other) const noexcept = delete;
    constexpr inline void operator-(Enum other) const noexcept = delete;
    constexpr inline void operator-(int other) const noexcept = delete;

    // Test if a particular flag is set.
    constexpr inline bool TestFlag(Enum flag) const noexcept
    {
        return TestFlags(flag);
    }

    // Test if all flags in the given Flags object are set.
    constexpr inline bool TestFlags(Flags flags) const noexcept
    {
        return flags.i ? ((i & flags.i) == flags.i) : i == Int(0);
    }

    // Test if any flag is set from the given flag.
    constexpr inline bool TestAnyFlag(Enum flag) const noexcept
    {
        return TestAnyFlag(flag);
    }

    // Test if any flag is set in the given Flags object.
    constexpr inline bool TestAnyFlag(Flags flags) const noexcept
    {
        return (i & flags.i) != Int(0);
    }

    // Set or clear a specific flag (default is to set).
    constexpr inline Flags &SetFlag(Enum flag, bool on = true) noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Flags(flag));
    }

    // Comparison operators for equality and inequality with Flags and Enum.
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
    // Helper function to combine multiple flags in an initializer list.
    constexpr static inline Int initializer_list_helper(
            typename std::initializer_list<Enum>::const_iterator it,
            typename std::initializer_list<Enum>::const_iterator end) noexcept
    {
        return (it == end ? Int(0)
                          : (Int(*it) | initializer_list_helper(it + 1, end)));
    }

    Int i;// Stores the flags as an integer.
};

}// namespace CPL

#define CPL_DECLARE_FLAGS(F, E) typedef CPL::Flags<E> F;