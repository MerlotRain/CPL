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

/// @brief 平台
#if defined(_WIN32)
#define GS_OS_WIN 1
#define GS_OS_STRING "windows"
#elif defined(__ANDROID__)
#define GS_OS_ANDROID 1
#define GS_OS_LINUX 1
#define GS_OS_POSIX 1
#define GS_OS_STRING "android"
#elif defined(__APPLE__)
#define GS_OS_POSIX 1
#define GS_OS_BSD 1
#define GS_OS_DARWIN 1
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define GS_OS_IOS 1
#define GS_OS_STRING "ios"
#else
#define GS_OS_MACOS 1
#define GS_OS_STRING "macos"
#endif
#elif defined(__CYGWIN__)
#define GS_OS_CYGWIN 1
#define GS_OS_POSIX 1
#define GS_OS_STRING "cygwin"
#elif defined(__linux__)
#define GS_OS_LINUX 1
#define GS_OS_POSIX 1
#define GS_OS_STRING "linux"
#endif


// 定义导出头
#ifdef GS_OS_WIN
#define GS_DECL_EXPORT __declspec(dllexport)
#define GS_DECL_IMPORT __declspec(dllimport)
#else
#define GS_DECL_EXPORT __attribute__((visibility("default")))
#define GS_DECL_IMPORT __attribute__((visibility("default")))
#endif

// utility模块
#if defined(UTILITY_LIBRARY)
#define UTILITY_EXPORT GS_DECL_EXPORT
#else
#define UTILITY_EXPORT GS_DECL_IMPORT
#endif

// kernel模块
#if defined(KERNEL_LIBRARY)
#define KERNEL_EXPORT GS_DECL_EXPORT
#else
#define KERNEL_EXPORT GS_DECL_IMPORT
#endif

// carto模块
#if defined(CARTO_LIBRARY)
#define CARTO_EXPORT GS_DECL_EXPORT
#else
#define CARTO_EXPORT GS_DECL_IMPORT
#endif


#ifdef __GNUC__
#define GS_DEPRECATED(id) id __attribute__((deprecated))
#elif defined(_MSC_VER)
#define GS_DEPRECATED(id) __declspec(deprecated) id
#else
#define GS_DEPRECATED(id) id
#endif


#if defined(__GNUC__)
#define GS_DEBUG_PACKED __attribute__((__packed__))
#define GS_DEBUG_BEGIN_PACKED
#define GS_DEBUG_PACKED_ALIGN_N(N) __attribute__((packed, aligned(N)))
#define GS_DEBUG_BEGIN_PACKED_ALIGN_N(N)
#define GS_DEBUG_END_PACKED
#else
#define GS_DEBUG_PACKED
#define GS_DEBUG_BEGIN_PACKED __pragma(pack(push, 1))
#define GS_DEBUG_BEGIN_PACKED_ALIGN_N(N) __pragma(pack(push, N))
#define GS_DEBUG_END_PACKED __pragma(pack(pop))
#define GS_DEBUG_PACKED_ALIGN_N(N)
#endif


#define GS_ENUM_STRING(x)


#if __has_cpp_attribute(nodiscard) >= 201603L
#undef GS_REQUIRED_RESULT
#define GS_REQUIRED_RESULT [[nodiscard]]
#else
#define GS_REQUIRED_RESULT
#endif


/// @brief 处理器和字节序
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

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
#define __CPP_LIB_ENDIAN LITTLE_ENDIAN
#elif defined(__arm64__) || defined(__arm64) || defined(_M_ARM64)
#define GS_ARCH GS_ARCH_ARM64
#if defined(__ARMEB__)
#define __CPP_LIB_ENDIAN BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __CPP_LIB_ENDIAN BIG_ENDIAN
#else
#define __CPP_LIB_ENDIAN LITTLE_ENDIAN
#endif
#endif

#ifndef __FLOAT_WORD_ORDER
#define __FLOAT_WORD_ORDER __CPP_LIB_ENDIAN
#endif

// clang-format off
#if defined(GS_OS_WIN) && !defined(__GNU__)
#define GS_INT64_C(c) c ## i64
#define GS_UINT64_C(c) c ## ui64
#else
#ifdef __cplusplus
#  define GS_INT64_C(c) static_cast<long long>(c ## LL)     /* signed 64 bit constant */
#  define GS_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */
#else
#define GS_INT64_C (c)      ((long long)(c ## LL))
#define GS_UINT64_C (c)     ((unsigned long long)(c ## LL))
#endif
#endif
// clang-format on




#ifdef _MSC_VER
#define GS_NEVER_INLINE __declspec(noinline)
#define GS_ALWAYS_INLINE __forceinline
#elif __GNUC__
#define GS_NEVER_INLINE __attribute__((noinline))
#define GS_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define GS_NEVER_INLINE
#define GS_ALWAYS_INLINE inline
#endif


#define GS_DISABLE_COPY(Class)     \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;

#define GS_DISABLE_COPY_MOVE(Class) \
    GS_DISABLE_COPY(Class)          \
    Class(Class &&) = delete;       \
    Class &operator=(Class &&) = delete;


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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
