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

#pragma once

#include <libm2_global.h>

#if defined(_WIN32)
#define M2_OS_WIN 1
#define M2_OS_STRING "Windows"
#elif defined(__ANDROID__)
#define M2_OS_ANDROID 1
#define M2_OS_LINUX 1
#define M2_OS_POSIX 1
#define M2_OS_STRING "Android"
#elif defined(__APPLE__)
#define M2_OS_POSIX 1
#define M2_OS_BSD 1
#define M2_OS_DARWIN 1
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define M2_OS_IOS 1
#define M2_OS_STRING "IOS"
#else
#define M2_OS_MACOS 1
#define M2_OS_STRING "MacOS"
#endif
#elif defined(__linux__)
#define M2_OS_LINUX 1
#define M2_OS_POSIX 1
#define M2_OS_STRING "Linux"
#endif


#if defined(__GNUC__)
#define M2_DEBUG_PACKED __attribute__((__packed__))
#define M2_DEBUG_BEGIN_PACKED
#define M2_DEBUG_PACKED_ALIGN_N(N) __attribute__((packed, aligned(N)))
#define M2_DEBUG_BEGIN_PACKED_ALIGN_N(N)
#define M2_DEBUG_END_PACKED
#else
#define M2_DEBUG_PACKED
#define M2_DEBUG_BEGIN_PACKED __pragma(pack(push, 1))
#define M2_DEBUG_BEGIN_PACKED_ALIGN_N(N) __pragma(pack(push, N))
#define M2_DEBUG_END_PACKED __pragma(pack(pop))
#define M2_DEBUG_PACKED_ALIGN_N(N)
#endif


#if defined(__ORDER_BIG_ENDIAN__)
#define BIG_ENDIAN __ORDER_BIG_ENDIAN__
#else
#define BIG_ENDIAN 4321
#endif
#if defined(__ORDER_LITTLE_ENDIAN__)
#define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#else
#define LITTLE_ENDIAN 1234
#endif

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || \
        defined(_M_X64)
#define __CPP_LIB_ENDIAN LITTLE_ENDIAN
#elif defined(__arm64__) || defined(__arm64) || defined(_M_ARM64)
#define M2_ARCH M2_ARCH_ARM64
#if defined(__ARMEB__)
#define __CPP_LIB_ENDIAN BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && \
        __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __CPP_LIB_ENDIAN BIG_ENDIAN
#else
#define __CPP_LIB_ENDIAN LITTLE_ENDIAN
#endif
#endif

#ifndef __FLOAT_WORD_ORDER
#define __FLOAT_WORD_ORDER __CPP_LIB_ENDIAN
#endif


// clang-format off
#if defined(M2_OS_WIN) && !defined(__GNU__)
#define M2_INT64_C(c) c ## i64
#define M2_UINT64_C(c) c ## ui64
#else
#ifdef __cplusplus
#  define M2_INT64_C(c) static_cast<long long>(c ## LL)     /* signed 64 bit constant */
#  define M2_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */
#else
#define M2_INT64_C (c)      ((long long)(c ## LL))
#define M2_UINT64_C (c)     ((unsigned long long)(c ## LL))
#endif
#endif
// clang-format on


#ifdef _MSC_VER
#define M2_NEVER_INLINE __declspec(noinline)
#define M2_ALWAYS_INLINE __forceinline
#elif __GNUC__
#define M2_NEVER_INLINE __attribute__((noinline))
#define M2_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define M2_NEVER_INLINE
#define M2_ALWAYS_INLINE inline
#endif


#if defined(__cplusplus)
#if __has_cpp_attribute(clang::fallthrough)
#define M2_FALLTHROUGH() [[clang::fallthrough]]
#elif __has_cpp_attribute(gnu::fallthrough)
#define M2_FALLTHROUGH() [[gnu::fallthrough]]
#elif __has_cpp_attribute(fallthrough)
#define M2_FALLTHROUGH() [[fallthrough]]
#endif
#endif
#ifndef M2_FALLTHROUGH
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 700)
#define M2_FALLTHROUGH() __attribute__((fallthrough))
#else
#define M2_FALLTHROUGH() (void) 0
#endif
#endif


#ifdef _MSC_VER
#pragma warning(disable : 4018)

#pragma warning(disable : 4100)
#pragma warning(disable : 4101)
#pragma warning(disable : 4189)
#pragma warning(disable : 4192)

#pragma warning(disable : 4238)
#pragma warning(disable : 4239)
#pragma warning(disable : 4244)
#pragma warning(disable : 4245)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)

#pragma warning(disable : 4305)
#pragma warning(disable : 4311)
#pragma warning(disable : 4389)

#pragma warning(disable : 4482)
#pragma warning(disable : 4635)
#pragma warning(disable : 4701)

#pragma warning(disable : 4800)
#pragma warning(disable : 4996)

#endif


#include <algorithm>
#include <assert.h>
#include <atomic>
#include <bitset>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <cstdlib>
#include <deque>
#include <filesystem>
#include <float.h>
#include <forward_list>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <stdint.h>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
