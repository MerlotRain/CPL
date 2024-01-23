
#include <datetime.h>

namespace m2 {

TimeSpan::TimeSpan() : TimeSpan(0)
{
}

TimeSpan::TimeSpan(long long microseconds) : TimeSpan(microseconds)
{
}

TimeSpan::TimeSpan(long seconds, long microseconds)
    : TimeSpan(long long(seconds) * TM_SECONDS + microseconds)
{
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int microSeconds)
    : TimeSpan(long long(microSeconds) + long long(seconds) * TM_SECONDS +
               long long(minutes) * TM_MINUTES + long long(hours) * TM_HOURS + long long(days) * TM_DAYS)
{
}

TimeSpan::TimeSpan(const TimeSpan &rhs) : TimeSpan(rhs.TimeSpan)
{
}

TimeSpan::~TimeSpan()
{
}

TimeSpan &TimeSpan::operator=(const TimeSpan &rhs)
{
    TimeSpan = rhs.TimeSpan;
    return *this;
}

TimeSpan &TimeSpan::operator=(long long microseconds)
{
    TimeSpan = microseconds;
    return *this;
}

TimeSpan &TimeSpan::Assign(int days, int hours, int minutes, int seconds, int microSeconds)
{
    TimeSpan = long long(microSeconds) + long long(seconds) * TM_SECONDS +
               long long(minutes) * TM_MINUTES + long long(hours) * TM_HOURS + long long(days) * TM_DAYS;
    return *this;
}

TimeSpan &TimeSpan::Assign(long seconds, long microseconds)
{
    TimeSpan = long long(seconds) * TM_SECONDS + long long(microseconds);
    return *this;
}

void TimeSpan::Swap(TimeSpan &rhs) noexcept
{
    std::swap(TimeSpan, rhs.TimeSpan);
}

bool TimeSpan::operator==(const TimeSpan &rhs) const
{
    return TimeSpan == rhs.TimeSpan;
}

bool TimeSpan::operator!=(const TimeSpan &rhs) const
{
    return TimeSpan != rhs.TimeSpan;
}

bool TimeSpan::operator>(const TimeSpan &rhs) const
{
    return TimeSpan > rhs.TimeSpan;
}

bool TimeSpan::operator>=(const TimeSpan &rhs) const
{
    return TimeSpan >= rhs.TimeSpan;
}

bool TimeSpan::operator<(const TimeSpan &rhs) const
{
    return TimeSpan < rhs.TimeSpan;
}

bool TimeSpan::operator<=(const TimeSpan &rhs) const
{
    return TimeSpan <= rhs.TimeSpan;
}

bool TimeSpan::operator==(long long microSeconds) const
{
    return TimeSpan == microSeconds;
}

bool TimeSpan::operator!=(long long microSeconds) const
{
    return TimeSpan != microSeconds;
}

bool TimeSpan::operator>(long long microSeconds) const
{
    return TimeSpan > microSeconds;
}

bool TimeSpan::operator>=(long long microSeconds) const
{
    return TimeSpan >= microSeconds;
}

bool TimeSpan::operator<(long long microSeconds) const
{
    return TimeSpan < microSeconds;
}

bool TimeSpan::operator<=(long long microSeconds) const
{
    return TimeSpan <= microSeconds;
}

TimeSpan TimeSpan::operator+(const TimeSpan &rhs) const
{
    return TimeSpan(TimeSpan + rhs.TimeSpan);
}

TimeSpan TimeSpan::operator-(const TimeSpan &rhs) const
{
    return TimeSpan(TimeSpan - rhs.TimeSpan);
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &rhs)
{
    TimeSpan += rhs.TimeSpan;
    return *this;
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &rhs)
{
    TimeSpan -= rhs.TimeSpan;
    return *this;
}

TimeSpan TimeSpan::operator+(long long microSeconds) const
{
    return TimeSpan(TimeSpan + microSeconds);
}

TimeSpan TimeSpan::operator-(long long microSeconds) const
{
    return TimeSpan(TimeSpan - microSeconds);
}

TimeSpan &TimeSpan::operator+=(long long microSeconds)
{
    TimeSpan += microSeconds;
    return *this;
}

TimeSpan &TimeSpan::operator-=(long long microSeconds)
{
    TimeSpan -= microSeconds;
    return *this;
}

int TimeSpan::Days() const
{
    return int(TimeSpan / TM_DAYS);
}

int TimeSpan::Hours() const
{
    return int((TimeSpan / TM_HOURS) % 24);
}

int TimeSpan::TotalHours() const
{
    return int(TimeSpan / TM_HOURS);
}

int TimeSpan::Minutes() const
{
    return int((TimeSpan / TM_MINUTES) % 60);
}

int TimeSpan::TotalMinutes() const
{
    return int(TimeSpan / TM_MINUTES);
}

int TimeSpan::Seconds() const
{
    return int((TimeSpan / TM_SECONDS) % 60);
}

int TimeSpan::TotalSeconds() const
{
    return int(TimeSpan / TM_SECONDS);
}

int TimeSpan::Milliseconds() const
{
    return int((TimeSpan / TM_MILLISECONDS) % 1000);
}

long long TimeSpan::TotalMilliseconds() const
{
    return TimeSpan / TM_MILLISECONDS;
}

int TimeSpan::Microseconds() const
{
    return int(TimeSpan % 1000);
}

int TimeSpan::Useconds() const
{
    return int(TimeSpan % 1000000);
}


long long TimeSpan::TotalMicroseconds() const
{
    return TimeSpan;
}

}// namespace m2
