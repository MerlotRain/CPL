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

#include "m2_delegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace m2 {

template<typename Return, typename... Args>
class Delegate;

template<typename Return, typename... Args>
class Delegate<Return(Args...)>
{
    typedef std::shared_ptr<DelegateT<Return, Args...>> DelegateTPtr;
    std::vector<DelegateTPtr> _invokeDelegates;
    std::mutex _mutex;

public:
    Delegate() = default;
    ~Delegate() { clear(); }
    void clear() { _invokeDelegates.clear(); }

    template<typename Fun>
    void add(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->compare(_invokeObj.get())) { return; }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
    }

    template<typename T, typename Fun>
    void add(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->compare(_invokeObj.get())) { return; }
            }
            _invokeDelegates.emplace_back(oneDelegate);
        }
    }

    template<typename Fun>
    void remove(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->compare(it.get()))
                {
                    _invokeDelegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    template<typename T, typename Fun>
    void remove(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->compare(it.get()))
                {
                    _invokeDelegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    std::vector<Return> operator()(Args... args)
    {
        std::vector<Return> vecRt;
        for (auto &_invokeObj: _invokeDelegates)
        {
            if (_invokeObj && _invokeObj->canInvoke())
            {
                vecRt.push_back(_invokeObj->invoke(std::forward<Args>(args)...));
            }
        }
        return vecRt;
    }
};

template<typename... Args>
class Delegate<void(Args...)>
{
    typedef std::shared_ptr<DelegateT<void, Args...>> DelegateTPtr;
    std::vector<DelegateTPtr> _invokeDelegates;
    std::mutex _mutex;

public:
    Delegate() = default;
    ~Delegate() { clear(); }

    void clear() { _invokeDelegates.clear(); }

    template<typename Fun>
    void add(Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
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
    void add(T *_object, Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: _invokeDelegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
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
    void remove(Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->compare(it.get()))
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
    void remove(T *_object, Fun &&_fun)
    {
        _mutex.lock();
        DelegateTPtr oneDelegate(_newDelegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = _invokeDelegates.begin();
            while (it != _invokeDelegates.end())
            {
                if (oneDelegate->compare(it->get()))
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
            if (_invokeObj && _invokeObj->canInvoke())
            {
                _invokeObj->invoke(std::forward<Args>(args)...);
            }
        }
    }
};

}// namespace m2
