/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file delegateT.h
 * @brief
 * @details
 * @date 2023-06-18
 * @author
 *
 ******************************************************************************/

#pragma once

namespace Lite {
namespace Utility {

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

}// namespace Utility
}// namespace Lite
