/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include "delegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

template<typename Return, typename... Args>
class Delegate;

template<typename Return, typename... Args>
class Delegate<Return(Args...)>
{
    typedef std::shared_ptr<DelegateT<Return, Args...>> ptr;
    std::vector<ptr> invoke_delegates;
    std::mutex _mutex;

public:
    Delegate() = default;
    ~Delegate() { Clear(); }
    void Clear() { invoke_delegates.clear(); }

    template<typename Fun>
    void Add(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        ptr oneDelegate(new_delegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get())) { return; }
            }
            invoke_delegates.emplace_back(oneDelegate);
        }
    }

    template<typename T, typename Fun>
    void Add(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        ptr oneDelegate(new_delegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get())) { return; }
            }
            invoke_delegates.emplace_back(oneDelegate);
        }
    }

    template<typename Fun>
    void Remove(Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        ptr oneDelegate(new_delegate(_fun));
        if (oneDelegate)
        {
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    invoke_delegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    template<typename T, typename Fun>
    void Remove(T *_object, Fun _fun)
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        ptr oneDelegate(new_delegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    invoke_delegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    std::vector<Return> operator()(Args... args)
    {
        std::vector<Return> vecRt;
        for (auto &_invokeObj: invoke_delegates)
        {
            if (_invokeObj && _invokeObj->canInvoke())
            {
                vecRt.push_back(
                        _invokeObj->invoke(std::forward<Args>(args)...));
            }
        }
        return vecRt;
    }
};

template<typename... Args>
class Delegate<void(Args...)>
{
    typedef std::shared_ptr<DelegateT<void, Args...>> ptr;
    std::vector<ptr> invoke_delegates;
    std::mutex _mutex;

public:
    Delegate() = default;
    ~Delegate() { Clear(); }

    void Clear() { invoke_delegates.clear(); }

    template<typename Fun>
    void Add(Fun &&_fun)
    {
        _mutex.lock();
        ptr oneDelegate(new_delegate(_fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            invoke_delegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    template<typename T, typename Fun>
    void Add(T *_object, Fun &&_fun)
    {
        _mutex.lock();
        ptr oneDelegate(new_delegate(_object, _fun));
        if (oneDelegate)
        {
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            invoke_delegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    template<typename Fun>
    void Remove(Fun &&_fun)
    {
        _mutex.lock();
        ptr oneDelegate(new_delegate(_fun));
        if (oneDelegate)
        {
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it.get()))
                {
                    invoke_delegates.erase(it);
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
        ptr oneDelegate(new_delegate(_object, _fun));
        if (oneDelegate)
        {
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    invoke_delegates.erase(it);
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
        for (auto &_invokeObj: invoke_delegates)
        {
            if (_invokeObj && _invokeObj->canInvoke())
            {
                _invokeObj->invoke(std::forward<Args>(args)...);
            }
        }
    }
};