
#include <datetime.h>

namespace m2 {

GsTimeSpan::GsTimeSpan() : TimeSpan(0)
{
}

GsTimeSpan::GsTimeSpan(long long microseconds) : TimeSpan(microseconds)
{
}

GsTimeSpan::GsTimeSpan(long seconds, long microseconds)
    : TimeSpan(long long(seconds) * TM_SECONDS + microseconds)
{
}

GsTimeSpan::GsTimeSpan(int days, int hours, int minutes, int seconds, int microSeconds)
    : TimeSpan(long long(microSeconds) + long long(seconds) * TM_SECONDS +
               long long(minutes) * TM_MINUTES + long long(hours) * TM_HOURS + long long(days) * TM_DAYS)
{
}

GsTimeSpan::GsTimeSpan(const GsTimeSpan &rhs) : TimeSpan(rhs.TimeSpan)
{
}

GsTimeSpan::~GsTimeSpan()
{
}

GsTimeSpan &GsTimeSpan::operator=(const GsTimeSpan &rhs)
{
    TimeSpan = rhs.TimeSpan;
    return *this;
}

GsTimeSpan &GsTimeSpan::operator=(long long microseconds)
{
    TimeSpan = microseconds;
    return *this;
}

GsTimeSpan &GsTimeSpan::Assign(int days, int hours, int minutes, int seconds, int microSeconds)
{
    TimeSpan = long long(microSeconds) + long long(seconds) * TM_SECONDS +
               long long(minutes) * TM_MINUTES + long long(hours) * TM_HOURS + long long(days) * TM_DAYS;
    return *this;
}

GsTimeSpan &GsTimeSpan::Assign(long seconds, long microseconds)
{
    TimeSpan = long long(seconds) * TM_SECONDS + long long(microseconds);
    return *this;
}

void GsTimeSpan::Swap(GsTimeSpan &rhs) noexcept
{
    std::swap(TimeSpan, rhs.TimeSpan);
}

bool GsTimeSpan::operator==(const GsTimeSpan &rhs) const
{
    return TimeSpan == rhs.TimeSpan;
}

bool GsTimeSpan::operator!=(const GsTimeSpan &rhs) const
{
    return TimeSpan != rhs.TimeSpan;
}

bool GsTimeSpan::operator>(const GsTimeSpan &rhs) const
{
    return TimeSpan > rhs.TimeSpan;
}

bool GsTimeSpan::operator>=(const GsTimeSpan &rhs) const
{
    return TimeSpan >= rhs.TimeSpan;
}

bool GsTimeSpan::operator<(const GsTimeSpan &rhs) const
{
    return TimeSpan < rhs.TimeSpan;
}

bool GsTimeSpan::operator<=(const GsTimeSpan &rhs) const
{
    return TimeSpan <= rhs.TimeSpan;
}

bool GsTimeSpan::operator==(long long microSeconds) const
{
    return TimeSpan == microSeconds;
}

bool GsTimeSpan::operator!=(long long microSeconds) const
{
    return TimeSpan != microSeconds;
}

bool GsTimeSpan::operator>(long long microSeconds) const
{
    return TimeSpan > microSeconds;
}

bool GsTimeSpan::operator>=(long long microSeconds) const
{
    return TimeSpan >= microSeconds;
}

bool GsTimeSpan::operator<(long long microSeconds) const
{
    return TimeSpan < microSeconds;
}

bool GsTimeSpan::operator<=(long long microSeconds) const
{
    return TimeSpan <= microSeconds;
}

GsTimeSpan GsTimeSpan::operator+(const GsTimeSpan &rhs) const
{
    return GsTimeSpan(TimeSpan + rhs.TimeSpan);
}

GsTimeSpan GsTimeSpan::operator-(const GsTimeSpan &rhs) const
{
    return GsTimeSpan(TimeSpan - rhs.TimeSpan);
}

GsTimeSpan &GsTimeSpan::operator+=(const GsTimeSpan &rhs)
{
    TimeSpan += rhs.TimeSpan;
    return *this;
}

GsTimeSpan &GsTimeSpan::operator-=(const GsTimeSpan &rhs)
{
    TimeSpan -= rhs.TimeSpan;
    return *this;
}

GsTimeSpan GsTimeSpan::operator+(long long microSeconds) const
{
    return GsTimeSpan(TimeSpan + microSeconds);
}

GsTimeSpan GsTimeSpan::operator-(long long microSeconds) const
{
    return GsTimeSpan(TimeSpan - microSeconds);
}

GsTimeSpan &GsTimeSpan::operator+=(long long microSeconds)
{
    TimeSpan += microSeconds;
    return *this;
}

GsTimeSpan &GsTimeSpan::operator-=(long long microSeconds)
{
    TimeSpan -= microSeconds;
    return *this;
}

int GsTimeSpan::Days() const
{
    return int(TimeSpan / TM_DAYS);
}

int GsTimeSpan::Hours() const
{
    return int((TimeSpan / TM_HOURS) % 24);
}

int GsTimeSpan::TotalHours() const
{
    return int(TimeSpan / TM_HOURS);
}

int GsTimeSpan::Minutes() const
{
    return int((TimeSpan / TM_MINUTES) % 60);
}

int GsTimeSpan::TotalMinutes() const
{
    return int(TimeSpan / TM_MINUTES);
}

int GsTimeSpan::Seconds() const
{
    return int((TimeSpan / TM_SECONDS) % 60);
}

int GsTimeSpan::TotalSeconds() const
{
    return int(TimeSpan / TM_SECONDS);
}

int GsTimeSpan::Milliseconds() const
{
    return int((TimeSpan / TM_MILLISECONDS) % 1000);
}

long long GsTimeSpan::TotalMilliseconds() const
{
    return TimeSpan / TM_MILLISECONDS;
}

int GsTimeSpan::Microseconds() const
{
    return int(TimeSpan % 1000);
}

int GsTimeSpan::Useconds() const
{
    return int(TimeSpan % 1000000);
}


long long GsTimeSpan::TotalMicroseconds() const
{
    return TimeSpan;
}

}// namespace m2
