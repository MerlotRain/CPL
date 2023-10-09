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


/// @brief 计时器
class Timer
{
public:
    Timer();

    // 其他接口和QT一致，在内部调用WorkThread的start接口
    //
};

/// @brief 高精度计时器
class StopWatch
{
public:
    /// @brief 默认构造
    explicit StopWatch();
    /// @brief 默认析构
    ~StopWatch();

    /// @brief 计时器是否激活
    /// @return
    inline bool Active() const;
    /// @brief 计时器ID
    /// @return
    int TimerId() const;

    /// @brief 设置计时器间隔（单位：毫秒）
    /// @param msec
    void Interval(int msec);
    /// @brief 获取计时器间隔（单位：毫秒）
    /// @return
    int Interval() const;

    /// @brief 计时器剩余时间
    /// @return
    int RemainingTime() const;

    /// @brief 单次定时器
    /// @param singleShot
    inline void SingleShot(bool singleShot) { m_Single = singleShot; }

    /// @brief 判断计时器是否是单次计时器
    /// @return
    inline bool IsSingleShot() const { return m_Single; }

    /// @brief 开始计时
    /// @param msec 计时时间
    void Start(int msec);

    /// @brief 开始
    void Start();

    /// @brief 停止
    void Stop();

    /// @brief 计时结束的委托
    Delegate<void()> OnTimeOut;

    /// @brief 单词计时器
    /// @param msec
    /// @param receiver
    /// @param member
    static void SingleShot(int msec, const void *receiver, const char *member);

private:
    /// @brief 开始计时
    /// @param
    /// @return
    inline int
    StartTimer(int)
    {
        return -1;
    }

    /// @brief 结束计时器
    /// @param
    inline void KillTimer(int) {}

    int m_Id, m_Inter, m_Del;
    unsigned int m_Single : 2;
    unsigned int m_Nulltimer : 2;
};


class ElapsedTimer
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

    ElapsedTimer();
    static ClockType ClockType() noexcept;
    static bool IsMonotonic() noexcept;

    void Start() noexcept;
    int64_t Restart() noexcept;
    void Invalidate() noexcept;
    bool IsValid() const noexcept;

    int64_t NsecsElapsed() const noexcept;
    int64_t Elapsed() const noexcept;
    bool HasExpired(int64_t timeout) const noexcept;

    int64_t MsecsSinceReference() const noexcept;
    int64_t MsecsTo(const ElapsedTimer &other) const noexcept;
    int64_t SecsTo(const ElapsedTimer &other) const noexcept;

    bool operator==(const ElapsedTimer &other) const noexcept
    {
        return t1 == other.t1 && t2 == other.t2;
    }
    bool operator!=(const ElapsedTimer &other) const noexcept
    {
        return !(*this == other);
    }

    friend bool operator<(const ElapsedTimer &v1, const ElapsedTimer &v2) noexcept;

private:
    int64_t t1;
    int64_t t2;
};


/// @brief 通常用于计算未来的截止日期并验证截止日期是否已过期
class DeadlineTimer
{
public:
    enum ForeverConstant
    {
        /// @brief 指示截止日期不应过期
        Forever
    };

    /// @brief 默认构造
    /// @param forever 是否永不过期
    /// @details \a forver true时，时间节点为long long最大值
    DeadlineTimer(bool forever = false) noexcept;
    /// @brief 构造
    /// @param msecs
    explicit DeadlineTimer(int64_t msecs) noexcept;
    /// @brief 交换
    /// @param other
    void Swap(DeadlineTimer &other) noexcept;
    /// @brief 截止时间是否为永久
    /// @return
    constexpr bool IsForever() const noexcept;
    /// @brief 是否过期
    /// @return
    bool Expired() const noexcept;

    /// @brief
    /// @return
    int64_t RemainingTime() const noexcept;
    /// @brief
    /// @return
    int64_t RemainingTimeNSecs() const noexcept;
    /// @brief
    /// @param msecs
    void RemainingTime(int64_t msecs) noexcept;
    /// @brief
    /// @param secs
    /// @param nsecs
    void PreciseRemainingTime(int64_t secs, int64_t nsecs = 0) noexcept;

    /// @brief
    /// @return
    int64_t Deadline() const noexcept;
    /// @brief
    /// @return
    int64_t DeadlineNSecs() const noexcept;
    /// @brief
    /// @param msecs
    void Deadline(int64_t msecs) noexcept;
    /// @brief
    /// @param secs
    /// @param nsecs
    void PreciseDeadline(int64_t secs, int64_t nsecs = 0) noexcept;

    /// @brief
    /// @param dt
    /// @param nsecs
    /// @return
    static DeadlineTimer AddNSecs(DeadlineTimer dt, int64_t nsecs) noexcept;
    /// @brief
    /// @return
    static DeadlineTimer Current() noexcept;

    friend bool operator==(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend bool operator!=(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend bool operator<(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend bool operator<=(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend bool operator>(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend bool operator>=(DeadlineTimer d1, DeadlineTimer d2) noexcept;
    friend DeadlineTimer operator+(DeadlineTimer dt, int64_t msecs);
    friend DeadlineTimer operator+(int64_t msecs, DeadlineTimer dt);
    friend DeadlineTimer operator-(DeadlineTimer dt, int64_t msecs);
    friend int64_t operator-(DeadlineTimer dt1, DeadlineTimer dt2);

    /// @brief 重载+=操作符
    /// @param msecs
    /// @return
    DeadlineTimer &operator+=(int64_t msecs);
    /// @brief 重载-=操作符
    /// @param msecs
    /// @return
    DeadlineTimer &operator-=(int64_t msecs);

    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @param deadline_
    template<class Clock, class Duration>
    DeadlineTimer(std::chrono::time_point<Clock, Duration> deadline_) : t2(0)
    {
        Deadline(deadline_);
    }
    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @param deadline_
    /// @return
    template<class Clock, class Duration>
    DeadlineTimer &operator=(std::chrono::time_point<Clock, Duration> deadline_)
    {
        Deadline(deadline_);
        return *this;
    }
    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @param deadline_
    template<class Clock, class Duration>
    void Deadline(std::chrono::time_point<Clock, Duration> deadline_)
    {
        RemainingTime(deadline_ == deadline_.max() ? Duration::max() : deadline_ - Clock::now());
    }
    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @return
    template<class Clock, class Duration = typename Clock::duration>
    std::chrono::time_point<Clock, Duration> deadline() const
    {
        auto val = std::chrono::nanoseconds(RawRemainingTimeNSecs()) + Clock::now();
        return std::chrono::time_point_cast<Duration>(val);
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param remaining
    template<class Rep, class Period>
    DeadlineTimer(std::chrono::duration<Rep, Period> remaining)
        : t2(0)
    {
        RemainingTime(remaining);
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param remaining
    /// @return
    template<class Rep, class Period>
    DeadlineTimer &operator=(std::chrono::duration<Rep, Period> remaining)
    {
        RemainingTime(remaining);
        return *this;
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param remaining
    template<class Rep, class Period>
    void RemainingTime(std::chrono::duration<Rep, Period> remaining)
    {
        if (remaining == remaining.max())
        {
            *this = DeadlineTimer(Forever, 1);
        }
        else
        {
            PreciseRemainingTime(0, std::chrono::nanoseconds(remaining).count());
        }
    }

    /// @brief
    /// @return
    std::chrono::nanoseconds RemainingTimeAsDuration() const noexcept;

    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param dt
    /// @param value
    /// @return
    template<class Rep, class Period>
    friend DeadlineTimer operator+(DeadlineTimer dt, std::chrono::duration<Rep, Period> value)
    {
        return DeadlineTimer::AddNSecs(dt, std::chrono::duration_cast<std::chrono::nanoseconds>(value).count());
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param value
    /// @param dt
    /// @return
    template<class Rep, class Period>
    friend DeadlineTimer operator+(std::chrono::duration<Rep, Period> value, DeadlineTimer dt)
    {
        return dt + value;
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param dt
    /// @param value
    /// @return
    template<class Rep, class Period>
    friend DeadlineTimer operator+=(DeadlineTimer &dt, std::chrono::duration<Rep, Period> value)
    {
        return dt = dt + value;
    }

private:
    int64_t t1;
    unsigned int t2;

    int64_t RawRemainingTimeNSecs() const noexcept;
};


}// namespace m2
