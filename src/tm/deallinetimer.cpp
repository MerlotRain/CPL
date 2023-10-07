#include "../math/math_traits.h"
#include <mathhelp.h>
#include <timer.h>

namespace Lite {
namespace Utility {

enum
{
#if defined(__unix__) && !defined(__APPLE__)
    // t1 contains seconds and t2 contains nanoseconds
    DeadlineTimerNanosecondsInT2 = 1
#else
    // t1 contains nanoseconds, t2 is always zero
    DeadlineTimerNanosecondsInT2 = 0
#endif
};

namespace {
class TimeReference
{
    enum : unsigned
    {
        umega = 1000 * 1000,
        ugiga = umega * 1000
    };

    enum : int64_t
    {
        kilo = 1000,
        mega = kilo * 1000,
        giga = mega * 1000
    };

public:
    enum RoundingStrategy
    {
        RoundDown,
        RoundUp,
        RoundDefault = RoundDown
    };

    static constexpr int64_t Min = std::numeric_limits<int64_t>::min();
    static constexpr int64_t Max = std::numeric_limits<int64_t>::max();

    inline TimeReference(int64_t = 0, unsigned = 0);
    inline void updateTimer(int64_t &, unsigned &);

    inline bool addNanoseconds(int64_t);
    inline bool addMilliseconds(int64_t);
    bool addSecsAndNSecs(int64_t, int64_t);

    inline bool subtract(const int64_t, const unsigned);

    inline bool toMilliseconds(int64_t *, RoundingStrategy = RoundDefault) const;
    inline bool toNanoseconds(int64_t *) const;

    inline void saturate(bool toMax);
    static bool sign(int64_t, int64_t);

private:
    bool adjust(const int64_t, const unsigned, int64_t = 0);

private:
    int64_t secs;
    unsigned nsecs;
};
}// namespace


inline TimeReference::TimeReference(int64_t t1, unsigned t2) : secs(t1), nsecs(t2)
{
}

inline void TimeReference::updateTimer(int64_t &t1, unsigned &t2)
{
    t1 = secs;
    t2 = nsecs;
}

inline void TimeReference::saturate(bool toMax)
{
    secs = toMax ? Max : Min;
}

bool TimeReference::sign(int64_t secs, int64_t nsecs)
{
    if (secs > 0)
    {
        if (nsecs > 0)
            return true;
    }
    else
    {
        if (nsecs < 0)
            return false;
    }

    secs += nsecs / giga;
    if (secs > 0)
        return true;
    else if (secs < 0)
        return false;
    assert(nsecs % giga != 0);
    return nsecs > 0;
}

#if defined(__unix__) && !defined(__APPLE__)
inline bool TimeReference::addNanoseconds(int64_t arg)
{
    return addSecsAndNSecs(arg / giga, arg % giga);
}

inline bool TimeReference::addMilliseconds(int64_t arg)
{
    return addSecsAndNSecs(arg / kilo, (arg % kilo) * mega);
}

bool TimeReference::addSecsAndNSecs(int64_t addSecs, int64_t addNSecs)
{
    if (Math::Abs(addNSecs) >= giga)
    {
        if (add_overflow<int64_t>(addSecs, addNSecs / giga, &addSecs))
            return false;

        addNSecs %= giga;
    }

    if (addNSecs < 0)
        return adjust(addSecs, ugiga - unsigned(-addNSecs), -1);

    return adjust(addSecs, unsigned(addNSecs));
}

bool TimeReference::adjust(const int64_t t1, const unsigned t2, int64_t carrySeconds)
{
    static_assert(QDeadlineTimerNanosecondsInT2);
    nsecs += t2;
    if (nsecs >= ugiga)
    {
        nsecs -= ugiga;
        carrySeconds++;
    }
    return !add_overflow<int64_t>(secs, t1, &secs) && !add_overflow<int64_t>(secs, carrySeconds, &secs);
}

inline bool TimeReference::subtract(const int64_t t1, const unsigned t2)
{
    Q_ASSERT(t2 < ugiga);
    return adjust(-t1, ugiga - t2, -1);
}

inline bool TimeReference::toMilliseconds(int64_t *result, RoundingStrategy rounding) const
{
    static constexpr int64_t maxSeconds = Max / kilo;
    static constexpr int64_t minSeconds = Min / kilo;
    if (secs > maxSeconds || secs < minSeconds)
        return false;

    unsigned ns = rounding == RoundDown ? nsecs : nsecs + umega - 1;

    return !add_overflow<int64_t>(secs * kilo, ns / umega, result);
}

inline bool TimeReference::toNanoseconds(int64_t *result) const
{
    static constexpr int64_t maxSeconds = Max / giga;
    static constexpr int64_t minSeconds = Min / giga;
    if (secs > maxSeconds || secs < minSeconds)
        return false;

    return !add_overflow<int64_t>(secs * giga, nsecs, result);
}
#else
inline bool TimeReference::addNanoseconds(int64_t arg)
{
    return adjust(arg, 0);
}

inline bool TimeReference::addMilliseconds(int64_t arg)
{
    static constexpr int64_t maxMilliseconds = Max / mega;
    if (Math::Abs(arg) > maxMilliseconds)
        return false;

    return addNanoseconds(arg * mega);
}

inline bool TimeReference::addSecsAndNSecs(int64_t addSecs, int64_t addNSecs)
{
    static constexpr int64_t maxSeconds = Max / giga;
    static constexpr int64_t minSeconds = Min / giga;
    if (addSecs > maxSeconds || addSecs < minSeconds ||
        add_overflow<int64_t>(addSecs * giga, addNSecs, &addNSecs))
        return false;

    return addNanoseconds(addNSecs);
}

inline bool TimeReference::adjust(const int64_t t1, const unsigned t2, int64_t carrySeconds)
{
    static_assert(bool(!DeadlineTimerNanosecondsInT2), "!DeadlineTimerNanosecondsInT2");
    return !add_overflow<int64_t>(secs, t1, &secs);
}

inline bool TimeReference::subtract(const int64_t t1, const unsigned t2)
{
    return addNanoseconds(-t1);
}

inline bool TimeReference::toMilliseconds(int64_t *result, RoundingStrategy rounding) const
{
    if (secs == Max || secs == Min)
        return false;

    *result = secs / mega;
    if (rounding == RoundUp && secs > *result * mega)
        (*result)++;

    return true;
}

inline bool TimeReference::toNanoseconds(int64_t *result) const
{
    *result = secs;
    return true;
}
#endif


GsDeadlineTimer::GsDeadlineTimer(bool forever) noexcept : t2(0)
{
    if (forever)
        t1 = std::numeric_limits<int64_t>::max();
    else
        t1 = 0;
}

GsDeadlineTimer::GsDeadlineTimer(int64_t msecs) noexcept : t2(0)
{
    RemainingTime(msecs);
}

void GsDeadlineTimer::Swap(GsDeadlineTimer &other) noexcept
{
    std::swap(t1, other.t1);
    std::swap(t2, other.t2);
}

constexpr bool GsDeadlineTimer::IsForever() const noexcept
{
    return t1 == (std::numeric_limits<int64_t>::max)();
}

bool GsDeadlineTimer::Expired() const noexcept
{
    if (IsForever())
        return false;
    return *this <= Current();
}

int64_t GsDeadlineTimer::RemainingTime() const noexcept
{
    if (IsForever())
        return -1;

    GsDeadlineTimer now = Current();
    TimeReference ref(t1, t2);

    int64_t msecs;
    if (!ref.subtract(now.t1, now.t2))
        return 0;// We can only underflow here

    // If we fail the conversion, t1 < now.t1 means we underflowed,
    // thus the deadline had long expired
    if (!ref.toMilliseconds(&msecs, TimeReference::RoundUp))
        return t1 < now.t1 ? 0 : -1;

    return msecs < 0 ? 0 : msecs;
}

int64_t GsDeadlineTimer::RemainingTimeNSecs() const noexcept
{
    if (IsForever())
        return -1;
    int64_t raw = RawRemainingTimeNSecs();
    return raw < 0 ? 0 : raw;
}

void GsDeadlineTimer::RemainingTime(int64_t msecs) noexcept
{
    if (msecs == -1)
    {
        *this = GsDeadlineTimer();
        return;
    }

    *this = Current();

    TimeReference ref(t1, t2);
    if (!ref.addMilliseconds(msecs))
        ref.saturate(msecs > 0);
    ref.updateTimer(t1, t2);
}

void GsDeadlineTimer::PreciseRemainingTime(int64_t secs, int64_t nsecs) noexcept
{
    if (secs == -1)
    {
        *this = GsDeadlineTimer();
        return;
    }

    *this = Current();
    TimeReference ref(t1, t2);
    if (!ref.addSecsAndNSecs(secs, nsecs))
        ref.saturate(TimeReference::sign(secs, nsecs));
    ref.updateTimer(t1, t2);
}

int64_t GsDeadlineTimer::Deadline() const noexcept
{
    if (IsForever())
        return TimeReference::Max;

    int64_t result;
    if (!TimeReference(t1, t2).toMilliseconds(&result))
        return t1 < 0 ? TimeReference::Min : TimeReference::Max;

    return result;
}

int64_t GsDeadlineTimer::DeadlineNSecs() const noexcept
{
    if (IsForever())
        return TimeReference::Max;

    int64_t result;
    if (!TimeReference(t1, t2).toNanoseconds(&result))
        return t1 < 0 ? TimeReference::Min : TimeReference::Max;

    return result;
}

void GsDeadlineTimer::Deadline(int64_t msecs) noexcept
{
    if (msecs == TimeReference::Max)
    {
        *this = GsDeadlineTimer();
        return;
    }

    TimeReference ref;
    if (!ref.addMilliseconds(msecs))
        ref.saturate(msecs > 0);
    ref.updateTimer(t1, t2);
}

void GsDeadlineTimer::PreciseDeadline(int64_t secs, int64_t nsecs) noexcept
{
    // We don't pass the seconds to the constructor, because we don't know
    // at this point if t1 holds the seconds or nanoseconds; it's platform specific.
    TimeReference ref;
    if (!ref.addSecsAndNSecs(secs, nsecs))
        ref.saturate(TimeReference::sign(secs, nsecs));
    ref.updateTimer(t1, t2);
}

GsDeadlineTimer GsDeadlineTimer::AddNSecs(GsDeadlineTimer dt, int64_t nsecs) noexcept
{
    if (dt.IsForever())
        return dt;

    TimeReference ref(dt.t1, dt.t2);
    if (!ref.addNanoseconds(nsecs))
        ref.saturate(nsecs > 0);
    ref.updateTimer(dt.t1, dt.t2);

    return dt;
}

GsDeadlineTimer GsDeadlineTimer::Current() noexcept
{
    static_assert(bool(!DeadlineTimerNanosecondsInT2), "!DeadlineTimerNanosecondsInT2");
    GsDeadlineTimer result;
    result.t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    return result;
}

GsDeadlineTimer &GsDeadlineTimer::operator+=(int64_t msecs)
{
    *this = *this + msecs;
    return *this;
}

GsDeadlineTimer &GsDeadlineTimer::operator-=(int64_t msecs)
{
    *this = *this + (-msecs);
    return *this;
}

std::chrono::nanoseconds GsDeadlineTimer::RemainingTimeAsDuration() const noexcept
{
    if (IsForever())
        return std::chrono::nanoseconds::max();
    int64_t nsecs = RawRemainingTimeNSecs();
    if (nsecs <= 0)
        return std::chrono::nanoseconds::zero();
    return std::chrono::nanoseconds(nsecs);
}

int64_t GsDeadlineTimer::RawRemainingTimeNSecs() const noexcept
{
    GsDeadlineTimer now = Current();
    TimeReference ref(t1, t2);

    int64_t nsecs;
    if (!ref.subtract(now.t1, now.t2))
        return TimeReference::Min;// We can only underflow here

    // If we fail the conversion, t1 < now.t1 means we underflowed,
    // thus the deadline had long expired
    if (!ref.toNanoseconds(&nsecs))
        return t1 < now.t1 ? TimeReference::Min : TimeReference::Max;
    return nsecs;
}

bool operator==(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return d1.t1 == d2.t1 && d1.t2 == d2.t2;
}
bool operator!=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return !(d1 == d2);
}
bool operator<(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return d1.t1 < d2.t1 || (d1.t1 == d2.t1 && d1.t2 < d2.t2);
}
bool operator<=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return d1 == d2 || d1 < d2;
}
bool operator>(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return d2 < d1;
}
bool operator>=(GsDeadlineTimer d1, GsDeadlineTimer d2) noexcept
{
    return !(d1 < d2);
}
GsDeadlineTimer operator+(GsDeadlineTimer dt, int64_t msecs)
{
    if (dt.Forever())
        return dt;

    TimeReference ref(dt.t1, dt.t2);
    if (!ref.addMilliseconds(msecs))
        ref.saturate(msecs > 0);
    ref.updateTimer(dt.t1, dt.t2);

    return dt;
}
GsDeadlineTimer operator+(int64_t msecs, GsDeadlineTimer dt)
{
    return dt + (-msecs);
}
GsDeadlineTimer operator-(GsDeadlineTimer dt, int64_t msecs)
{
    return dt + (-msecs);
}
int64_t operator-(GsDeadlineTimer dt1, GsDeadlineTimer dt2)
{
    return (dt1.DeadlineNSecs() - dt2.DeadlineNSecs()) / (1000 * 1000);
}

}// namespace Utility
}// namespace Lite
