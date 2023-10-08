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

#include "delegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>


namespace m2 {


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

}// namespace m2
