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

#include <cpl_atomic.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace CPL {

char Interlocked::Read(const volatile char *target)
{
    return *target;
}

short Interlocked::Read(const volatile short *target)
{
    return *target;
}

int Interlocked::Read(const volatile int *target)
{
    return *target;
}

long long Interlocked::Read(const volatile long long *target)
{
    return *target;
}

char Interlocked::Exchange(volatile char *target, char value)
{
#ifdef _WIN32
    return _InterlockedExchange8(target, value);// Windows
#else
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

short Interlocked::Exchange(volatile short *target, short value)
{
#ifdef _WIN32
    return _InterlockedExchange16(target, value);// Windows
#else
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Exchange(volatile int *target, int value)
{
#ifdef _WIN32
    return _InterlockedExchange(reinterpret_cast<volatile LONG *>(target),
                                value);// Windows
#else
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

long long Interlocked::Exchange(volatile long long *target, long long value)
{
#ifdef _WIN32
    return _InterlockedExchange64(target, value);// Windows
#else
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::Increment(volatile char *target)
{
#ifdef _WIN32
    return static_cast<char>(
            _InterlockedIncrement(reinterpret_cast<volatile LONG *>(
                    const_cast<volatile char *>(target))));
#else
    return __atomic_add_fetch(target, 1, __ATOMIC_SEQ_CST);
#endif
}

short Interlocked::Increment(volatile short *target)
{
#ifdef _WIN32
    return _InterlockedIncrement16(target);// Windows
#else
    return __atomic_add_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Increment(volatile int *target)
{
#ifdef _WIN32
    return _InterlockedIncrement(
            reinterpret_cast<volatile LONG *>(target));// Windows
#else
    return __atomic_add_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

long long Interlocked::Increment(volatile long long *target)
{
#ifdef _WIN32
    return _InterlockedIncrement64(target);// Windows
#else
    return __atomic_add_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::Decrement(volatile char *target)
{
#ifdef _WIN32
    return static_cast<char>(
            _InterlockedDecrement(reinterpret_cast<volatile LONG *>(
                    const_cast<volatile char *>(target))));
#else
    return __atomic_sub_fetch(target, 1, __ATOMIC_SEQ_CST);
#endif
}


short Interlocked::Decrement(volatile short *target)
{
#ifdef _WIN32
    return _InterlockedDecrement16(target);// Windows
#else
    return __atomic_sub_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Decrement(volatile int *target)
{
#ifdef _WIN32
    return _InterlockedDecrement(
            reinterpret_cast<volatile LONG *>(target));// Windows
#else
    return __atomic_sub_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

long long Interlocked::Decrement(volatile long long *target)
{
#ifdef _WIN32
    return _InterlockedDecrement64(target);// Windows
#else
    return __atomic_sub_fetch(target, 1, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::Add(volatile char *target, char value)
{
#ifdef _WIN32
    return InterlockedAdd(reinterpret_cast<volatile LONG *>(target),
                          value);// Windows
#else
    return __atomic_add_fetch(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

short Interlocked::Add(volatile short *target, short value)
{
#ifdef _WIN32
    return InterlockedAdd(reinterpret_cast<volatile LONG *>(target),
                          value);// Windows
#else
    return __atomic_add_fetch(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Add(volatile int *target, int value)
{
#ifdef _WIN32
    return InterlockedAdd(reinterpret_cast<volatile LONG *>(target),
                          value);// Windows
#else
    return __atomic_add_fetch(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

long long Interlocked::Add(volatile long long *target, long long value)
{
#ifdef _WIN32
    return InterlockedAdd64(target, value);// Windows
#else
    return __atomic_add_fetch(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::Or(volatile char *target, char value)
{
#ifdef _WIN32
    return _InterlockedOr8(target, value);// Windows
#else
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

short Interlocked::Or(volatile short *target, short value)
{
#ifdef _WIN32
    return _InterlockedOr16(target, value);// Windows
#else
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Or(volatile int *target, int value)
{
#ifdef _WIN32
    return _InterlockedOr(reinterpret_cast<volatile LONG *>(target), value);
#else
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
#endif
}

long long Interlocked::Or(volatile long long *target, long long value)
{
#ifdef _WIN32
    return _InterlockedOr64(target, value);// Windows
#else
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::Xor(volatile char *target, char value)
{
#ifdef _WIN32
    return _InterlockedXor8(target, value);// Windows
#else
    return __atomic_fetch_xor(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

short Interlocked::Xor(volatile short *target, short value)
{
#ifdef _WIN32
    return _InterlockedXor16(target, value);// Windows
#else
    return __atomic_fetch_xor(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

int Interlocked::Xor(volatile int *target, int value)
{
#ifdef _WIN32
    return _InterlockedXor(reinterpret_cast<volatile LONG *>(target), value);
#else
    return __atomic_fetch_xor(target, value, __ATOMIC_SEQ_CST);
#endif
}

long long Interlocked::Xor(volatile long long *target, long long value)
{
#ifdef _WIN32
    return _InterlockedXor64(target, value);// Windows
#else
    return __atomic_fetch_xor(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

char Interlocked::And(volatile char *target, char value)
{
#ifdef _WIN32
    return _InterlockedAnd8(target, value);// Windows
#else
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

short Interlocked::And(volatile short *target, short value)
{
#ifdef _WIN32
    return _InterlockedAnd16(target, value);// Windows
#else
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}
int Interlocked::And(volatile int *target, int value)
{
#ifdef _WIN32
    return _InterlockedAnd(reinterpret_cast<volatile LONG *>(target), value);
#else
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
#endif
}

long long Interlocked::And(volatile long long *target, long long value)
{
#ifdef _WIN32
    return _InterlockedAnd64(target, value);// Windows
#else
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);// Linux/macOS
#endif
}

}// namespace CPL