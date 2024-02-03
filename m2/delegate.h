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