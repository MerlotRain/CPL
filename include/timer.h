
/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file timer.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "object.h"

namespace Lite {
namespace Utility {


/// @brief 计时器
class GsTimer
{
public:
    GsTimer();

    // 其他接口和QT一致，在内部调用GsWorkThread的start接口
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
    GsDelegate<void()> OnTimeOut;

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


class GsElapsedTimer
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

    GsElapsedTimer();
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
    int64_t MsecsTo(const GsElapsedTimer &other) const noexcept;
    int64_t SecsTo(const GsElapsedTimer &other) const noexcept;

    bool operator==(const GsElapsedTimer &other) const noexcept
    {
        return t1 == other.t1 && t2 == other.t2;
    }
    bool operator!=(const GsElapsedTimer &other) const noexcept
    {
        return !(*this == other);
    }

    friend bool operator<(const GsElapsedTimer &v1, const GsElapsedTimer &v2) noexcept;

private:
    int64_t t1;
    int64_t t2;
};


/// @brief 通常用于计算未来的截止日期并验证截止日期是否已过期
class GsDeadlineTimer
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
    GsDeadlineTimer(bool forever = false) noexcept;
    /// @brief 构造
    /// @param msecs
    explicit GsDeadlineTimer(int64_t msecs) noexcept;
    /// @brief 交换
    /// @param other
    void Swap(GsDeadlineTimer &other) noexcept;
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
    static GsDeadlineTimer AddNSecs(GsDeadlineTimer dt, int64_t nsecs) noexcept;
    /// @brief
    /// @return
    static GsDeadlineTimer Current() noexcept;

    friend bool operator==(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend bool operator!=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend bool operator<(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend bool operator<=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend bool operator>(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend bool operator>=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept;
    friend GsDeadlineTimer operator+(GsDeadlineTimer dt, int64_t msecs);
    friend GsDeadlineTimer operator+(int64_t msecs, GsDeadlineTimer dt);
    friend GsDeadlineTimer operator-(GsDeadlineTimer dt, int64_t msecs);
    friend int64_t operator-(GsDeadlineTimer dt1, GsDeadlineTimer dt2);

    /// @brief 重载+=操作符
    /// @param msecs
    /// @return
    GsDeadlineTimer &operator+=(int64_t msecs);
    /// @brief 重载-=操作符
    /// @param msecs
    /// @return
    GsDeadlineTimer &operator-=(int64_t msecs);

    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @param deadline_
    template<class Clock, class Duration>
    GsDeadlineTimer(std::chrono::time_point<Clock, Duration> deadline_) : t2(0)
    {
        Deadline(deadline_);
    }
    /// @brief
    /// @tparam Clock
    /// @tparam Duration
    /// @param deadline_
    /// @return
    template<class Clock, class Duration>
    GsDeadlineTimer &operator=(std::chrono::time_point<Clock, Duration> deadline_)
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
        auto val = std::chrono::nanoseconds(rawRemainingTimeNSecs()) + Clock::now();
        return std::chrono::time_point_cast<Duration>(val);
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param remaining
    template<class Rep, class Period>
    GsDeadlineTimer(std::chrono::duration<Rep, Period> remaining)
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
    GsDeadlineTimer &operator=(std::chrono::duration<Rep, Period> remaining)
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
            *this = GsDeadlineTimer(Forever, type_);
        }
        else
        {
            setPreciseRemainingTime(0, std::chrono::nanoseconds(remaining).count());
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
    friend GsDeadlineTimer operator+(GsDeadlineTimer dt, std::chrono::duration<Rep, Period> value)
    {
        return GsDeadlineTimer::addNSecs(dt, std::chrono::duration_cast<std::chrono::nanoseconds>(value).count());
    }
    /// @brief
    /// @tparam Rep
    /// @tparam Period
    /// @param value
    /// @param dt
    /// @return
    template<class Rep, class Period>
    friend GsDeadlineTimer operator+(std::chrono::duration<Rep, Period> value, GsDeadlineTimer dt)
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
    friend GsDeadlineTimer operator+=(GsDeadlineTimer &dt, std::chrono::duration<Rep, Period> value)
    {
        return dt = dt + value;
    }

private:
    int64_t t1;
    unsigned int t2;

    int64_t RawRemainingTimeNSecs() const noexcept;
};


}// namespace Utility
}// namespace Lite
