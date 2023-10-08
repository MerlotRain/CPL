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

#include <typeinfo>

namespace m2 {

template<typename Return, typename... Args>
class StaticDelegateT;

template<typename T, typename Return, typename... Args>
class ClassMemberDelegateT;

template<typename Return, typename... Args>
class DelegateT
{
public:
    DelegateT() = default;
    virtual ~DelegateT() = default;
    virtual bool IsType(const std::type_info &_type) = 0;
    virtual bool CanInvoke() const = 0;
    virtual Return Invoke(Args... args) = 0;
    virtual bool Compare(DelegateT<Return, Args...> *_delegate) const = 0;
};

template<typename Return, typename... Args>
class StaticDelegateT<Return (*)(Args...)> : public DelegateT<Return, Args...>
{

public:
    typedef Return (*InvokeFun)(Args...);
    explicit StaticDelegateT(InvokeFun _fun) : m_invokefun(_fun) {}
    virtual ~StaticDelegateT() = default;
    bool IsType(const std::type_info &_type) override
    {
        return typeid(StaticDelegateT<Return (*)(Args...)>) == _type;
    }
    Return Invoke(Args... args) override
    {
        return m_invokefun(std::forward<Args>(args)...);
    }
    bool Compare(DelegateT<Return, Args...> *_delegate) const override
    {
        if (!_delegate || !_delegate->IsType(typeid(StaticDelegateT<Return (*)(Args...)>)))
        {
            return false;
        }

        auto *cast = dynamic_cast<StaticDelegateT<Return (*)(Args...)> *>(_delegate);

        return m_invokefun == cast->m_invokefun;
    }
    bool CanInvoke() const override
    {
        return m_invokefun;
    }

private:
    InvokeFun m_invokefun = nullptr;
};

template<typename T, typename Return, typename... Args>
class ClassMemberDelegateT<T, Return (T::*)(Args...)> : public DelegateT<Return, Args...>
{
public:
    typedef Return (T::*memInvokeFun)(Args...);

    ClassMemberDelegateT(T *_object, memInvokeFun _memfun) : obj(_object), m_invokefun(_memfun) {}
    virtual bool IsType(const std::type_info &_type)
    {
        return typeid(ClassMemberDelegateT<T, Return (T::*)(Args...)>) == _type;
    }
    Return Invoke(Args... args) override
    {
        return (obj->*m_invokefun)(std::forward<Args>(args)...);
    }
    bool Compare(DelegateT<Return, Args...> *_delegate) const override
    {
        if (!_delegate || !_delegate->IsType(typeid(ClassMemberDelegateT<T, Return (T::*)(Args...)>)))
        {
            return false;
        }

        auto *cast = dynamic_cast<ClassMemberDelegateT<T, Return (T::*)(Args...)> *>(_delegate);
        return m_invokefun == cast->m_invokefun && obj == cast->obj;
    }
    virtual bool CanInvoke() const
    {
        return obj && m_invokefun;
    }

private:
    memInvokeFun m_invokefun = nullptr;
    T *obj = nullptr;
};

template<typename Fun>
inline StaticDelegateT<Fun> *_newDelegate(Fun _fun)
{
    return new StaticDelegateT<Fun>(_fun);
}

template<typename T, typename Fun>
inline ClassMemberDelegateT<T, Fun> *_newDelegate(T *_object, Fun _fun)
{
    return new ClassMemberDelegateT<T, Fun>(_object, _fun);
}

}// namespace m2
