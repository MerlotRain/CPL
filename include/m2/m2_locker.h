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

namespace m2 {


/// @brief 自动锁，在段结束时，锁自动释放
/// @tparam M
template<class M>
class GsScopedLock
{
private:
    M *m_lock;
    GsScopedLock(const GsScopedLock &) = delete;
    GsScopedLock &operator=(const GsScopedLock &) = delete;

public:
    explicit GsScopedLock(M &m) : m_lock(&m)
    {
        if (m_lock)
            m_lock->Lock();
    }
    explicit GsScopedLock(M *m) : m_lock(m)
    {
        if (m_lock)
            m_lock->Lock();
    }
    GsScopedLock(M &m, int milliseconds) : m_lock(&m)
    {
        if (m_lock)
            m_lock->Lock(milliseconds);
    }
    GsScopedLock(M *m, int milliseconds) : m_lock(m)
    {
        if (m_lock)
            m_lock->Lock(milliseconds);
    }
    ~GsScopedLock()
    {
        Unlock();
    }
    void Unlock()
    {
        if (m_lock)
            m_lock->Unlock();
        m_lock = NULL;
    }
};

/// @brief 自动反转锁，进入段时释放，离开时加锁
/// @tparam M
template<class M>
class GsReverseScopedLock
{
private:
    M *m_lock;
    GsReverseScopedLock(const GsReverseScopedLock &) = delete;
    GsReverseScopedLock &operator=(const GsReverseScopedLock &) = delete;

public:
    explicit GsReverseScopedLock(M &m) : m_lock(&m)
    {
        if (m_lock)
            m_lock->Unlock();
    }
    explicit GsReverseScopedLock(M *m) : m_lock(m)
    {
        if (m_lock)
            m_lock->Unlock();
    }
    ~GsReverseScopedLock()
    {
        if (m_lock)
            m_lock->Lock();
        m_lock = NULL;
    }
};

/// @brief 线程锁
class UTILITY_EXPORT GsMutex
{
public:
    GsMutex();
    ~GsMutex();

    /// @brief 加锁
    void Lock();
    /// @brief 等待一段时间后加锁
    /// @param milliseconds
    void Lock(long milliseconds);

    /// @brief 释放锁
    void Unlock();

    /// @brief 尝试加锁
    /// @return 是否加锁成功
    bool Trylock();
    /// @brief 等待一段时间后尝试加锁
    /// @param milliseconds
    /// @return
    bool Trylock(long milliseconds);

protected:
    void *m_Handle;

private:
    GsMutex(const GsMutex &) = delete;
    GsMutex &operator=(const GsMutex &) = delete;
};

/// @brief 可递归线程锁，同一线程可以多次调用不会阻塞
class UTILITY_EXPORT GsRecursiveMutex
{
public:
    GsRecursiveMutex();
    ~GsRecursiveMutex();

    /// @brief 锁定对象
    void Lock();
    void Lock(long milliseconds);

    /// @brief 释放锁定
    void Unlock();

    /// @brief 尝试加锁
    /// @return 是否加锁成功
    bool Trylock();
    bool Trylock(long milliseconds);

protected:
    void *m_Handle;
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


/// @brief 读写锁
/// @details 允许并发范围内，多个线程读，但只允许一个线程写
class UTILITY_EXPORT GsRWLock
{
public:
    GsRWLock();
    ~GsRWLock();

    /// @brief 获取读取锁定
    /// @details 如果另一个线程持有写锁，等待写锁释放
    void ReadLock();
    /// @brief 尝试获取读取锁定
    /// @details 如果另一个线程持有写锁，则直接返回false，不等待
    bool TryReadLock();
    /// @brief 获取写入锁定
    /// @details 如果一个或多个其他线程当前持有锁，则等待直到释放所有锁
    void WriteLock();
    /// @brief 尝试获取写入锁定
    /// @return 如果一个或多个其他线程当前持有锁，则直接返回false，不等待
    bool TryWriteLock();
    /// @brief 释放读写锁
    void Unlock();

private:
    void *m_Handle;

private:
    GsRWLock(const GsRWLock &) = delete;
    GsRWLock &operator=(const GsRWLock &) = delete;
};

/// @brief 自动读写锁
/// @details 锁对象会主动释放
class UTILITY_EXPORT GsScopedRWLock
{
public:
    explicit GsScopedRWLock(GsRWLock &l, bool write = false);
    ~GsScopedRWLock();

private:
    GsRWLock &m_lock;
    GsScopedRWLock(const GsScopedRWLock &) = delete;
    GsScopedRWLock &operator=(const GsScopedRWLock &) = delete;
};

/// @brief 自动读锁
class UTILITY_EXPORT GsScopedReadRWLock : public GsScopedRWLock
{
public:
    explicit GsScopedReadRWLock(GsRWLock &l);
    ~GsScopedReadRWLock();
};

/// @brief 自动写锁
class UTILITY_EXPORT GsScopedWriteRWLock : public GsScopedRWLock
{
public:
    explicit GsScopedWriteRWLock(GsRWLock &l);
    ~GsScopedWriteRWLock();
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


/// @brief 等待事件
class GsWaitEvent;
/// @brief 条件变量
class UTILITY_EXPORT GsWaitCondition
{
public:
    GsWaitCondition();
    ~GsWaitCondition();

    /// @brief 等待
    /// @tparam M
    /// @param mtx
    template<class M>
    void Wait(M &mtx)
    {
        GsScopedLock<M> l(mtx);
        GsWaitEvent event;
        {
            GsScopedLock<GsRecursiveMutex> l(m_mutex);
            mtx.Unlock();
            Enqueue(event);
        }
        event.Wait();
    };

    /// @brief 等待一段时间
    /// @tparam M
    /// @param mtx
    /// @param milliseconds
    template<class M>
    void WaitUntil(M &mtx, int milliseconds)
    {
        if (!TryWaitUntil(mtx, milliseconds))
            throw std::runtime_error("wait for condition failed");
    }

    /// @brief 尝试等待一段时间
    /// @tparam M
    /// @param mtx
    /// @param milliseconds
    template<class M>
    bool TryWaitUntil(M &mtx, int milliseconds)
    {
        GsScopedLock<M> l(mtx);
        GsWaitEvent event;
        {
            GsScopedLock<GsRecursiveMutex> l(m_mutex);
            mtx.Unlock();
            Enqueue(event);
        }
        if (!event.TryWait(milliseconds))
        {
            GsScopedLock<GsRecursiveMutex> l(m_mutex);
            Dequeue(event);
            return false;
        }
        return true;
    }

    /// @brief 通知一个等待线程继续执行
    void Notify();
    /// @brief 通知所有的线程继续执行
    void NotifyAll();

protected:
    void Enqueue(GsWaitEvent &event);
    void Dequeue();
    void Dequeue(GsWaitEvent &event);

private:
    GsRecursiveMutex m_mutex;
    std::deque<GsWaitEvent *> m_waitDeque;
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


/// @brief 信号量
class UTILITY_EXPORT GsSemaphore
{
public:
    GsSemaphore(int n);
    GsSemaphore(int n, int max);
    ~GsSemaphore();

    void Acquire();
    void Wait();
    void Wait(int milliseconds);
    bool TryWait(int milliseconds);

private:
    GsSemaphore(const GsSemaphore &) = delete;
    GsSemaphore &operator=(const GsSemaphore &) = delete;

    void *m_Handle;
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


/// \brief 安全对象，组合锁对象形成安全的对象
template<class T, class L = GsRWLock>
class GsSafeObject : public T, public L
{
public:
    using T::operator=;

    /// @brief 锁定并访问对象
    template<class FUN>
    void LockOn(FUN f)
    {
        this->WriteLock();
        f(this);
        this->Unlock();
    }
};
/// \brief 安全类型，组合锁对象形成安全的类型，适用于轻量的对象
template<class T, class L = GsRWLock>
class GsSafeType : public L
{
public:
    GsSafeType()
    {
    }
    GsSafeType(T v) : Value(v)
    {
    }
    /// @brief 锁定并访问数据
    template<class FUN>
    void LockOn(FUN f)
    {
        this->WriteLock();
        f(Value);
        this->Unlock();
    }
    T Value;
};

}// namespace m2
