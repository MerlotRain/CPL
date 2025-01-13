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

/// \brief Atomic operations for numeric types
class LIBDWG_API Interlocked
{
public:
    /// \brief Reads and modifies a 1-byte integer value atomically
    /// \param target Pointer to the target integer
    /// \return The value of the integer before modification
    static char Read(const volatile char *target);

    /// \brief Reads and modifies a 2-byte integer value atomically
    /// \param target Pointer to the target integer
    /// \return The value of the integer before modification
    static short Read(const volatile short *target);

    /// \brief Reads and modifies a 4-byte integer value atomically
    /// \param target Pointer to the target integer
    /// \return The value of the integer before modification
    static int Read(const volatile int *target);

    /// \brief Reads and modifies an 8-byte integer value atomically
    /// \param target Pointer to the target integer
    /// \return The value of the integer before modification
    static long long Read(const volatile long long *target);

    /// \brief Atomically exchanges a 1-byte integer value
    /// \param target Pointer to the target integer
    /// \param value The value to exchange
    /// \return The value of the integer before the exchange
    static char Exchange(volatile char *target, char value);

    /// \brief Atomically exchanges a 2-byte integer value
    /// \param target Pointer to the target integer
    /// \param value The value to exchange
    /// \return The value of the integer before the exchange
    static short Exchange(volatile short *target, short value);

    /// \brief Atomically exchanges a 4-byte integer value
    /// \param target Pointer to the target integer
    /// \param value The value to exchange
    /// \return The value of the integer before the exchange
    static int Exchange(volatile int *target, int value);

    /// \brief Atomically exchanges an 8-byte integer value
    /// \param target Pointer to the target integer
    /// \param value The value to exchange
    /// \return The value of the integer before the exchange
    static long long Exchange(volatile long long *target, long long value);

    /// \brief Atomically increments a 1-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static char Increment(volatile char *target);

    /// \brief Atomically increments a 2-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static short Increment(volatile short *target);

    /// \brief Atomically increments a 4-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static int Increment(volatile int *target);

    /// \brief Atomically increments an 8-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static long long Increment(volatile long long *target);

    /// \brief Atomically decrements a 1-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static char Decrement(volatile char *target);

    /// \brief Atomically decrements a 2-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static short Decrement(volatile short *target);

    /// \brief Atomically decrements a 4-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static int Decrement(volatile int *target);

    /// \brief Atomically decrements an 8-byte integer value
    /// \param target Pointer to the target integer
    /// \return The modified value of the integer
    static long long Decrement(volatile long long *target);

    /// \brief Atomically adds a value to a 1-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to add
    /// \return The modified value of the integer
    static char Add(volatile char *target, char value);

    /// \brief Atomically adds a value to a 2-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to add
    /// \return The modified value of the integer
    static short Add(volatile short *target, short value);

    /// \brief Atomically adds a value to a 4-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to add
    /// \return The modified value of the integer
    static int Add(volatile int *target, int value);

    /// \brief Atomically adds a value to an 8-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to add
    /// \return The modified value of the integer
    static long long Add(volatile long long *target, long long value);

    /// \brief Atomically performs an OR operation on a 1-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to OR with
    /// \return The modified value of the integer
    static char Or(volatile char *target, char value);

    /// \brief Atomically performs an OR operation on a 2-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to OR with
    /// \return The modified value of the integer
    static short Or(volatile short *target, short value);

    /// \brief Atomically performs an OR operation on a 4-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to OR with
    /// \return The modified value of the integer
    static int Or(volatile int *target, int value);

    /// \brief Atomically performs an OR operation on an 8-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to OR with
    /// \return The modified value of the integer
    static long long Or(volatile long long *target, long long value);

    /// \brief Atomically performs an XOR operation on a 1-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to XOR with
    /// \return The modified value of the integer
    static char Xor(volatile char *target, char value);

    /// \brief Atomically performs an XOR operation on a 2-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to XOR with
    /// \return The modified value of the integer
    static short Xor(volatile short *target, short value);

    /// \brief Atomically performs an XOR operation on a 4-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to XOR with
    /// \return The modified value of the integer
    static int Xor(volatile int *target, int value);

    /// \brief Atomically performs an XOR operation on an 8-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to XOR with
    /// \return The modified value of the integer
    static long long Xor(volatile long long *target, long long value);

    /// \brief Atomically performs an AND operation on a 1-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to AND with
    /// \return The modified value of the integer
    static char And(volatile char *target, char value);

    /// \brief Atomically performs an AND operation on a 2-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to AND with
    /// \return The modified value of the integer
    static short And(volatile short *target, short value);

    /// \brief Atomically performs an AND operation on a 4-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to AND with
    /// \return The modified value of the integer
    static int And(volatile int *target, int value);

    /// \brief Atomically performs an AND operation on an 8-byte integer
    /// \param target Pointer to the target integer
    /// \param value The value to AND with
    /// \return The modified value of the integer
    static long long And(volatile long long *target, long long value);
};


/// \brief Template class for atomic operations on integer values
/// \tparam T The type of the integer (e.g., char, short, int, long long)
template<class T>
class Atomic
{
    volatile T m_Value;///< The atomic integer value

public:
    /// \brief Constructor that initializes the atomic value
    /// \param val Initial value of the atomic integer
    Atomic(const T &val) : m_Value(val) {}

    /// \brief Default constructor that initializes the atomic value to zero
    Atomic() : m_Value(0) {}

    /// \brief Destructor
    ~Atomic() {}

    /// \brief Atomically adds a value to the atomic integer
    /// \param val The value to add
    /// \return The value of the integer after the addition
    T Add(const T &val) { return Interlocked::Add(&m_Value, val); }

    /// \brief Atomically reads the value of the atomic integer
    /// \return The current value of the integer
    T Read() const { return Interlocked::Read(&m_Value); }

    /// \brief Atomically writes a value to the atomic integer
    /// \param val The value to write
    void Write(const T &val) { Interlocked::Exchange(&m_Value, val); }

    /// \brief Atomically increments the atomic integer by 1
    /// \return The value of the integer after the increment
    T Increment() { return Interlocked::Increment(&m_Value); }

    /// \brief Atomically decrements the atomic integer by 1
    /// \return The value of the integer after the decrement
    T Decrement() { return Interlocked::Decrement(&m_Value); }

    /// \brief Overloaded assignment operator to set the atomic value
    /// \param value The value to assign
    /// \return The previous value of the atomic integer
    T operator=(const T &value)
    {
        return Interlocked::Exchange(&m_Value, value);
    }

    /// \brief Postfix increment operator (++), increments the integer atomically
    /// \return The value of the integer before the increment
    T operator++(int)
    {
        T val = m_Value;
        Interlocked::Increment(&m_Value);
        return val;
    }

    /// \brief Prefix increment operator (++), increments the integer atomically
    /// \return The value of the integer after the increment
    T operator++() { return Interlocked::Increment(&m_Value); }

    /// \brief Postfix decrement operator (--), decrements the integer atomically
    /// \return The value of the integer before the decrement
    T operator--(int)
    {
        T val = m_Value;
        Interlocked::Decrement(&m_Value);
        return val;
    }

    /// \brief Prefix decrement operator (--), decrements the integer atomically
    /// \return The value of the integer after the decrement
    T operator--() { return Interlocked::Decrement(&m_Value); }

    /// \brief Conversion operator to implicitly cast the atomic object to its value
    /// \return The current value of the atomic integer
    operator T() const { return Interlocked::Read(&m_Value); }
};
