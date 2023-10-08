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

#include "object.h"
#include <type_traits>

namespace m2 {
namespace GlobalStatic {

enum GuardValues
{
    Destroyed = -2,
    Initialized = -1,
    Uninitialized = 0,
    Initializing = 1
};

template<typename GS>
union Holder
{
    using Type = typename GS::GS_Type;
    using PlainType = std::remove_cv<Type>::type;

    static constexpr bool ConstructionIsNoexcept = noexcept(GS::innerFunction(nullptr));
    static inline std::atomic_int8_t guard = {GlobalStatic::Uninitialized};

    PlainType storage;

    Holder() noexcept(ConstructionIsNoexcept)
    {
        GS::innerFunction(pointer());
        guard.store(GlobalStatic::Initialized, std::memory_order_relaxed);
    }

    ~Holder()
    {
        pointer()->~PlainType();
        std::atomic_thread_fence(
                std::memory_order_acquire);// avoid mixing stores to guard and *pointer()
        guard.store(GlobalStatic::Destroyed, std::memory_order_relaxed);
    }

    PlainType *pointer() noexcept
    {
        return &storage;
    }

    Holder(const Holder &) = delete;
    Holder(Holder &&) = default;
    Holder &operator=(const Holder &) = delete;
    Holder &operator=(Holder &&) = delete;
};
}// namespace GlobalStatic

template<typename Holder>
struct GsGlobalStatic
{
    using Type = typename Holder::Type;

    bool isDestroyed() const noexcept
    {
        return guardValue() <= GlobalStatic::Destroyed;
    }
    bool exists() const noexcept
    {
        return guardValue() == GlobalStatic::Initialized;
    }
    operator Type *()
    {
        if (isDestroyed())
        {
            return nullptr;
        }
        return instance();
    }
    Type *operator()()
    {
        if (isDestroyed())
        {
            return nullptr;
        }
        return instance();
    }
    Type *operator->()
    {
        static_cast(!isDestroyed(), "The global static was used after being destroyed");
        return instance();
    }
    Type &operator*()
    {
        static_cast(!isDestroyed(), "The global static was used after being destroyed");
        return *instance();
    }

protected:
    static Type *instance() noexcept(Holder::ConstructionIsNoexcept)
    {
        static Holder holder;
        return holder.pointer();
    }
    static GlobalStatic::GuardValues guardValue() noexcept
    {
        return GlobalStatic::GuardValues(Holder::guard.loadAcquire());
    }
};

#define GS_GLOBAL_STATIC_WITH_ARGS(TYPE, NAME, ARGS)                                                \
    namespace {                                                                                     \
    struct GS_##NAME                                                                                \
    {                                                                                               \
        typedef TYPE GS_Type;                                                                       \
        static void innerFunction(void *pointer) noexcept(noexcept(std::remove_cv_t<GS_Type> ARGS)) \
        {                                                                                           \
            new (pointer) GS_Type ARGS;                                                             \
        }                                                                                           \
    };                                                                                              \
    }                                                                                               \
    Q_CONSTINIT static GsGlobalStatic<GlobalStatic::Holder<GS_##NAME>> NAME;


#define GS_GLOBAL_STATIC(TYPE, NAME, ...) GS_GLOBAL_STATIC_WITH_ARGS(TYPE, NAME, (__VA_ARGS__))


}// namespace m2
