#pragma once

#include "object.h"
#include <type_traits>

namespace Lite {
namespace Utility {
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


}// namespace Utility
}// namespace Lite
