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

#ifndef M2_DEADLINETIMER_H_
#define M2_DEADLINETIMER_H_

#include <preconfig.h>

namespace m2 {

class DeadlineTimer
{
public:
    enum ForeverConstant
    {
        Forever
    };

    DeadlineTimer() noexcept;
    DeadlineTimer(ForeverConstant) noexcept;
    explicit DeadlineTimer(long long msecs) noexcept;

    void swap(DeadlineTimer &other) noexcept;

    bool isForever() const noexcept;
    bool hasExpired() const noexcept;

    long long remainingTime() const noexcept;
    long long remainingTimeNSecs() const noexcept;
    void setRemainingTime(long long msecs) noexcept;
    void setPreciseRemainingTime(long long secs, long long nsecs = 0) noexcept;

    long long deadline() const noexcept;
    long long deadlineNSecs() const noexcept;
    void setDeadline(long long msecs) noexcept;
    void setPreciseDeadline(long long secs, long long nsecs = 0) noexcept;

    static DeadlineTimer addNSecs(DeadlineTimer dt, long long nsecs) noexcept;
    static DeadlineTimer current() noexcept;

    friend bool operator==(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return d1.t1 == d2.t1 && d1.t2 == d2.t2;
    }
    friend bool operator!=(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return !(d1 == d2);
    }
    friend bool operator<(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return d1.t1 < d2.t1 || (d1.t1 == d2.t1 && d1.t2 < d2.t2);
    }
    friend bool operator<=(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return d1 == d2 || d1 < d2;
    }
    friend bool operator>(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return d2 < d1;
    }
    friend bool operator>=(DeadlineTimer d1, DeadlineTimer d2) noexcept
    {
        return !(d1 < d2);
    }

    friend DeadlineTimer operator+(DeadlineTimer dt, long long msecs);
    friend DeadlineTimer operator+(long long msecs, DeadlineTimer dt)
    {
        return dt + msecs;
    }
    friend DeadlineTimer operator-(DeadlineTimer dt, long long msecs)
    {
        return dt + (-msecs);
    }
    friend long long operator-(DeadlineTimer dt1, DeadlineTimer dt2)
    {
        return (dt1.deadlineNSecs() - dt2.deadlineNSecs()) / (1000 * 1000);
    }
    DeadlineTimer &operator+=(long long msecs)
    {
        *this = *this + msecs;
        return *this;
    }
    DeadlineTimer &operator-=(long long msecs)
    {
        *this = *this + (-msecs);
        return *this;
    }

    template<class Clock, class Duration>
    DeadlineTimer(std::chrono::time_point<Clock, Duration> deadline_) : t2(0)
    {
        setDeadline(deadline_);
    }
    template<class Clock, class Duration>
    DeadlineTimer &operator=(std::chrono::time_point<Clock, Duration> deadline_)
    {
        setDeadline(deadline_);
        return *this;
    }

    template<class Clock, class Duration>
    void setDeadline(std::chrono::time_point<Clock, Duration> deadline_)
    {
        setRemainingTime(deadline_ == deadline_.max()
                                 ? Duration::max()
                                 : deadline_ - Clock::now());
    }

    template<class Clock, class Duration = typename Clock::duration>
    std::chrono::time_point<Clock, Duration> deadline() const
    {
        auto val = std::chrono::nanoseconds(rawRemainingTimeNSecs()) +
                   Clock::now();
        return std::chrono::time_point_cast<Duration>(val);
    }

    template<class Rep, class Period>
    DeadlineTimer(std::chrono::duration<Rep, Period> remaining) : t2(0)
    {
        setRemainingTime(remaining, type_);
    }

    template<class Rep, class Period>
    DeadlineTimer &operator=(std::chrono::duration<Rep, Period> remaining)
    {
        setRemainingTime(remaining);
        return *this;
    }

    template<class Rep, class Period>
    void setRemainingTime(std::chrono::duration<Rep, Period> remaining)
    {
        if (remaining == remaining.max()) *this = DeadlineTimer(Forever, type_);
        else
            setPreciseRemainingTime(
                    0, std::chrono::nanoseconds(remaining).count(), type_);
    }

    std::chrono::nanoseconds remainingTimeAsDuration() const noexcept
    {
        if (isForever()) return std::chrono::nanoseconds::max();
        long long nsecs = rawRemainingTimeNSecs();
        if (nsecs <= 0) return std::chrono::nanoseconds::zero();
        return std::chrono::nanoseconds(nsecs);
    }

    template<class Rep, class Period>
    friend DeadlineTimer operator+(DeadlineTimer dt,
                                   std::chrono::duration<Rep, Period> value)
    {
        return DeadlineTimer::addNSecs(
                dt, std::chrono::duration_cast<std::chrono::nanoseconds>(value)
                            .count());
    }
    template<class Rep, class Period>
    friend DeadlineTimer operator+(std::chrono::duration<Rep, Period> value,
                                   DeadlineTimer dt)
    {
        return dt + value;
    }
    template<class Rep, class Period>
    friend DeadlineTimer operator+=(DeadlineTimer &dt,
                                    std::chrono::duration<Rep, Period> value)
    {
        return dt = dt + value;
    }

private:
    long long t1;
    unsigned t2;

    long long rawRemainingTimeNSecs() const noexcept;
};

}// namespace m2

#endif//