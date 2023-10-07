/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file delegate.h
 * @brief
 * @details
 * @date 2023-06-18
 * @author
 *
 ******************************************************************************/

#pragma once

#include "delegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>


namespace Lite {
namespace Utility {


template<typename Return, typename... Args>
class GsDelegate;


/// @brief 带返回值的函数委托
/// @tparam Return
/// @tparam ...Args
template<typename Return, typename... Args>
class GsDelegate<Return(Args...)>
{
    typedef std::shared_ptr<DelegateT<Return, Args...>> DelegateTPtr;
    std::vector<DelegateTPtr> _invokeDelegates;
    std::mutex _mutex;

public:
    GsDelegate() = default;
    ~GsDelegate() { Clear(); }

    /// @brief 清空所有绑定的委托
    void Clear() { _invokeDelegates.clear(); }

    /// @brief 绑定静态函数委托
    /// @tparam Fun
    /// @param _fun
    template<typename Fun>
    void Add(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->Compare(_invokeObj.get())) { return; }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
    }

    /// @brief 绑定成员函数类型的函数委托
    /// @tparam T 类的类型
    /// @tparam Fun 成员函数名称
    /// @param _object 类对象
    /// @param _fun 类对象的函数指针
    template<typename T, typename Fun>
    void Add(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->Compare(_invokeObj.get())) { return; }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
    }

    /// @brief 解绑静态函数委托
    /// @tparam Fun
    /// @param _fun
    template<typename Fun>
    void Remove(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->Compare(it.get()))
                {
                    _invokeDelegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    /// @brief 解绑成员函数类型的函数委托
    /// @tparam T
    /// @tparam Fun
    /// @param _object
    /// @param _fun
    template<typename T, typename Fun>
    void Remove(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->Compare(it.get()))
                {
                    _invokeDelegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    /// @brief 执行函数委托
    /// @param ...args
    /// @return
    std::vector<Return> operator()(Args... args)
    {
        std::vector<Return> vecRt;
        for (auto &_invokeObj: _invokeDelegates)
        {
            if (_invokeObj && _invokeObj->CanInvoke())
            {
                vecRt.push_back(_invokeObj->Invoke(std::forward<Args>(args)...));
            }
        }
        return vecRt;
    }
};


/// @brief 特例化无返回值的函数委托
/// @tparam ...Args
template<typename... Args>
class GsDelegate<void(Args...)>
{
    typedef std::shared_ptr<DelegateT<void, Args...>> DelegateTPtr;
    std::vector<DelegateTPtr> _invokeDelegates;
    std::mutex _mutex;

public:
    GsDelegate() = default;
    ~GsDelegate() { clear(); }

    void clear() { _invokeDelegates.clear(); }

    template<typename Fun>
    void Add(Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->Compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    template<typename T, typename Fun>
    void Add(T *_object, Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->Compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    template<typename Fun>
    void Remove(Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->Compare(it.get()))
                {
                    _invokeDelegates.erase(it);
                    _mutex.unlock();
                    return;
                }
                ++it;
            }
        }
        _mutex.unlock();
    }

    template<typename T, typename Fun>
    void Remove(T *_object, Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->Compare(it->get()))
                {
                    _invokeDelegates.erase(it);
                    _mutex.unlock();
                    return;
                }
                ++it;
            }
        }
        _mutex.unlock();
    }

    void operator()(Args... args)
    {
        for (auto &_invokeObj: _invokeDelegates)
        {
            if (_invokeObj && _invokeObj->CanInvoke())
            {
                _invokeObj->Invoke(std::forward<Args>(args)...);
            }
        }
    }
};

}// namespace Utility
}// namespace Lite
