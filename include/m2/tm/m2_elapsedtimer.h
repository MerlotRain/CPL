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

#ifndef M2_ELAPSEDTIMER_H_
#define M2_ELAPSEDTIMER_H_

namespace m2 {

class QElapsedTimer
{
public:
    enum ClockType
    {
        SystemTime,
        MonotonicClock,
        TickCounter,
        MachAbsoluteTime,
        PerformanceCounter
    };

    constexpr QElapsedTimer();

    static ClockType clockType() noexcept;
    static bool isMonotonic() noexcept;

    void start() noexcept;
    long long restart() noexcept;
    void invalidate() noexcept;
    bool isValid() const noexcept;

    long long nsecsElapsed() const noexcept;
    long long elapsed() const noexcept;
    bool hasExpired(long long timeout) const noexcept;

    long long msecsSinceReference() const noexcept;
    long long msecsTo(const QElapsedTimer &other) const noexcept;
    long long secsTo(const QElapsedTimer &other) const noexcept;

    friend bool operator==(const QElapsedTimer &lhs, const QElapsedTimer &rhs) noexcept
    {
        return lhs.t1 == rhs.t1 && lhs.t2 == rhs.t2;
    }
    friend bool operator!=(const QElapsedTimer &lhs, const QElapsedTimer &rhs) noexcept
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const QElapsedTimer &lhs, const QElapsedTimer &rhs) noexcept;

private:
    long long t1;
    long long t2;
};

}// namespace m2

#endif//M2_ELAPSEDTIMER_H_