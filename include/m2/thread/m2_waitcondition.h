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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_WAITCONDITION_H_
#define M2_WAITCONDITION_H_

#include <m2_mutex.h>

namespace m2 {

class WaitEvent;
class LIBM2_EXPORT WaitCondition
{
public:
    WaitCondition();
    ~WaitCondition();
    WaitCondition(const WaitCondition &) noexcept;
    WaitCondition &operator=(const WaitCondition &) noexcept;
    WaitCondition(WaitCondition &&) noexcept;
    WaitCondition &operator=(WaitCondition &&) noexcept;

    template<class M>
    void wait(M &mtx)
    {
        ScopedLock<M> l(mtx);
        WaitEvent event;
        {
            ScopedLock<RecursiveMutex> l(m_mutex);
            mtx.unlock();
            enqueue(event);
        }
        event.wait();
    };

    template<class M>
    void waitUntil(M &mtx, int milliseconds)
    {
        if (!tryWaitUntil(mtx, milliseconds))
            throw std::runtime_error("wait for condition failed");
    }

    template<class M>
    bool tryWaitUntil(M &mtx, int milliseconds)
    {
        ScopedLock<M> l(mtx);
        WaitEvent event;
        {
            ScopedLock<RecursiveMutex> l(m_mutex);
            mtx.unlock();
            Enqueue(event);
        }
        if (!event.TryWait(milliseconds))
        {
            ScopedLock<RecursiveMutex> l(m_mutex);
            dequeue(event);
            return false;
        }
        return true;
    }

    void notify();
    void notifyAll();

protected:
    void enqueue(WaitEvent &event);
    void dequeue();
    void dequeue(WaitEvent &event);

private:
    RecursiveMutex m_mutex;
    std::deque<WaitEvent *> m_waits;
};


}// namespace m2

#endif//M2_WAITCONDITION_H_