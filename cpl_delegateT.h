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

#include <typeinfo>

namespace CPL {

// Forward declarations for different delegate types.
template<typename Return, typename... Args>
class StaticDelegateT;

template<typename T, typename Return, typename... Args>
class ClassMemberDelegateT;

// Base delegate class template with common functionality for all delegates.
template<typename Return, typename... Args>
class DelegateT
{
public:
    // Default constructor and virtual destructor.
    DelegateT() = default;
    virtual ~DelegateT() = default;

    // Pure virtual method to check if the delegate is of a specific type.
    virtual bool isType(const std::type_info &_type) = 0;

    // Pure virtual method to check if the delegate can be invoked.
    virtual bool canInvoke() const = 0;

    // Pure virtual method to invoke the delegate with the provided arguments.
    virtual Return invoke(Args... args) = 0;

    // Pure virtual method to compare this delegate with another.
    virtual bool compare(DelegateT<Return, Args...> *_delegate) const = 0;
};

// Template specialization for static function pointers as delegates.
template<typename Return, typename... Args>
class StaticDelegateT<Return (*)(Args...)> : public DelegateT<Return, Args...>
{
public:
    // Type alias for the function pointer type.
    typedef Return (*InvokeFun)(Args...);

    // Constructor to initialize with a function pointer.
    explicit StaticDelegateT(InvokeFun _fun) : invoke_fun_(_fun) {}

    // Destructor
    virtual ~StaticDelegateT() = default;

    // Check if the delegate type matches the given type.
    bool isType(const std::type_info &_type) override
    {
        return typeid(StaticDelegateT<Return (*)(Args...)>) == _type;
    }

    // Invoke the stored function with the provided arguments.
    Return invoke(Args... args) override
    {
        return invoke_fun_(std::forward<Args>(args)...);
    }

    // Compare this delegate with another for equality.
    bool compare(DelegateT<Return, Args...> *_delegate) const override
    {
        if (!_delegate ||
            !_delegate->isType(typeid(StaticDelegateT<Return (*)(Args...)>)))
        {
            return false;
        }

        auto *cast =
                dynamic_cast<StaticDelegateT<Return (*)(Args...)> *>(_delegate);

        return invoke_fun_ == cast->invoke_fun_;
    }

    // Check if the function pointer is valid (i.e., can be invoked).
    bool canInvoke() const override { return invoke_fun_; }

private:
    // Function pointer to the static function to be invoked.
    InvokeFun invoke_fun_ = nullptr;
};

// Template specialization for class member function pointers as delegates.
template<typename T, typename Return, typename... Args>
class ClassMemberDelegateT<T, Return (T::*)(Args...)>
    : public DelegateT<Return, Args...>
{
public:
    // Type alias for the member function pointer type.
    typedef Return (T::*memInvokeFun)(Args...);

    // Constructor to initialize with an object and a member function pointer.
    ClassMemberDelegateT(T *_object, memInvokeFun _memfun)
        : obj(_object), invoke_fun_(_memfun)
    {
    }

    // Check if the delegate type matches the given type.
    virtual bool isType(const std::type_info &_type) override
    {
        return typeid(ClassMemberDelegateT<T, Return (T::*)(Args...)>) == _type;
    }

    // Invoke the member function on the stored object with the provided arguments.
    Return invoke(Args... args) override
    {
        return (obj->*invoke_fun_)(std::forward<Args>(args)...);
    }

    // Compare this delegate with another for equality.
    bool compare(DelegateT<Return, Args...> *_delegate) const override
    {
        if (!_delegate ||
            !_delegate->isType(
                    typeid(ClassMemberDelegateT<T, Return (T::*)(Args...)>)))
        {
            return false;
        }

        auto *cast =
                dynamic_cast<ClassMemberDelegateT<T, Return (T::*)(Args...)> *>(
                        _delegate);
        return invoke_fun_ == cast->invoke_fun_ && obj == cast->obj;
    }

    // Check if the object and member function pointer are valid (i.e., can be invoked).
    virtual bool canInvoke() const override { return (obj && invoke_fun_); }

private:
    // Member function pointer to be invoked on the stored object.
    memInvokeFun invoke_fun_ = nullptr;

    // Pointer to the object to invoke the member function on.
    T *obj = nullptr;
};

// Factory function to create a static delegate (i.e., function pointer delegate).
template<typename Fun>
inline StaticDelegateT<Fun> *new_delegate(Fun _fun)
{
    return new StaticDelegateT<Fun>(_fun);
}

// Factory function to create a class member delegate.
template<typename T, typename Fun>
inline ClassMemberDelegateT<T, Fun> *new_delegate(T *_object, Fun _fun)
{
    return new ClassMemberDelegateT<T, Fun>(_object, _fun);
}

}// namespace CPL