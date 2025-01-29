/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifdef _WIN32
#include <Windows.h>
#endif

#include <assert.h>
#include <chrono>
#include <cpl_datetime.h>
#include <cstring>
#include <ctime>
#include <fmt/core.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

namespace CPL {

const Timestamp::TimeVal Timestamp::TIMEVAL_MIN = INT64_MIN;
const Timestamp::TimeVal Timestamp::TIMEVAL_MAX = INT64_MAX;

Timestamp::Timestamp() { Update(); }

Timestamp::Timestamp(TimeVal tv) { _ts = tv; }

Timestamp::Timestamp(const Timestamp &other) { _ts = other._ts; }

Timestamp::~Timestamp() {}

Timestamp &Timestamp::operator=(const Timestamp &other)
{
    _ts = other._ts;
    return *this;
}

Timestamp &Timestamp::operator=(TimeVal tv)
{
    _ts = tv;
    return *this;
}

void Timestamp::Swap(Timestamp &timestamp) noexcept
{
    std::swap(_ts, timestamp._ts);
}

Timestamp Timestamp::FromEpochTime(std::time_t t)
{
    return Timestamp(TimeVal(t) * Resolution());
}

Timestamp Timestamp::FromUtcTime(UtcTimeVal val)
{
    val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
    val /= 10;
    return Timestamp(val);
}

void Timestamp::Update()
{
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart = ft.dwLowDateTime;
    ts.HighPart = ft.dwHighDateTime;
    ts.QuadPart -= epoch.QuadPart;
    _ts = ts.QuadPart / 10;

#else
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        throw std::invalid_argument("cannot get time of day");
    _ts = TimeVal(ts.tv_sec) * Resolution() + ts.tv_nsec / 1000;
#endif
}

Timestamp Timestamp::operator+(const TimeSpan &span) const
{
    return *this + span.TotalMicroseconds();
}

Timestamp Timestamp::operator-(const TimeSpan &span) const
{
    return *this - span.TotalMicroseconds();
}

Timestamp &Timestamp::operator+=(const TimeSpan &span)
{
    return *this += span.TotalMicroseconds();
}

Timestamp &Timestamp::operator-=(const TimeSpan &span)
{
    return *this -= span.TotalMicroseconds();
}

bool Timestamp::operator==(const Timestamp &ts) const { return _ts == ts._ts; }

bool Timestamp::operator!=(const Timestamp &ts) const { return _ts != ts._ts; }

bool Timestamp::operator>(const Timestamp &ts) const { return _ts > ts._ts; }

bool Timestamp::operator>=(const Timestamp &ts) const { return _ts >= ts._ts; }

bool Timestamp::operator<(const Timestamp &ts) const { return _ts < ts._ts; }

bool Timestamp::operator<=(const Timestamp &ts) const { return _ts <= ts._ts; }

Timestamp Timestamp::operator+(Timestamp::TimeDiff d) const
{
    return Timestamp(_ts + d);
}

Timestamp Timestamp::operator-(Timestamp::TimeDiff d) const
{
    return Timestamp(_ts - d);
}

Timestamp::TimeDiff Timestamp::operator-(const Timestamp &ts) const
{
    return _ts - ts._ts;
}

Timestamp &Timestamp::operator+=(Timestamp::TimeDiff d)
{
    _ts += d;
    return *this;
}

Timestamp &Timestamp::operator-=(Timestamp::TimeDiff d)
{
    _ts -= d;
    return *this;
}

std::time_t Timestamp::EpochTime() const
{
    return std::time_t(_ts / Resolution());
}

Timestamp::UtcTimeVal Timestamp::UtcTime() const
{
    return _ts * 10 + (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
}

Timestamp::TimeVal Timestamp::EpochMicroseconds() const { return _ts; }

Timestamp::TimeDiff Timestamp::Elapsed() const
{
    Timestamp now;
    return now - *this;
}

bool Timestamp::IsElapsed(Timestamp::TimeDiff interval) const
{
    Timestamp now;
    Timestamp::TimeDiff diff = now - *this;
    return diff >= interval;
}

constexpr Timestamp::TimeDiff Timestamp::Resolution() { return 1000000; }

void swap(Timestamp &s1, Timestamp &s2) noexcept { s1.Swap(s2); }

Timestamp::TimeVal Timestamp::Raw() const { return _ts; }

#if defined(_WIN32)

Timestamp Timestamp::FromFileTimeNP(std::uint32_t fileTimeLow,
                                    std::uint32_t fileTimeHigh)
{
    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart = fileTimeLow;
    ts.HighPart = fileTimeHigh;
    ts.QuadPart -= epoch.QuadPart;

    return Timestamp(ts.QuadPart / 10);
}

void Timestamp::ToFileTimeNP(std::uint32_t &fileTimeLow,
                             std::uint32_t &fileTimeHigh) const
{
    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.QuadPart = _ts * 10;
    ts.QuadPart += epoch.QuadPart;
    fileTimeLow = ts.LowPart;
    fileTimeHigh = ts.HighPart;
}
#endif


const TimeSpan::TimeDiff TimeSpan::MILLISECONDS = 1000;
const TimeSpan::TimeDiff TimeSpan::SECONDS = 1000 * TimeSpan::MILLISECONDS;
const TimeSpan::TimeDiff TimeSpan::MINUTES = 60 * TimeSpan::SECONDS;
const TimeSpan::TimeDiff TimeSpan::HOURS = 60 * TimeSpan::MINUTES;
const TimeSpan::TimeDiff TimeSpan::DAYS = 24 * TimeSpan::HOURS;

TimeSpan::TimeSpan() : _span(0) {}

TimeSpan::TimeSpan(TimeDiff microSeconds) : _span(microSeconds) {}

TimeSpan::TimeSpan(long seconds, long microSeconds)
    : _span(TimeDiff(seconds) * SECONDS + microSeconds)
{
}

TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds,
                   int microSeconds)
    : _span(TimeDiff(microSeconds) + TimeDiff(seconds) * SECONDS +
            TimeDiff(minutes) * MINUTES + TimeDiff(hours) * HOURS +
            TimeDiff(days) * DAYS)
{
}

TimeSpan::TimeSpan(const TimeSpan &timespan) : _span(timespan._span) {}

TimeSpan::~TimeSpan() {}

TimeSpan &TimeSpan::operator=(const TimeSpan &timespan)
{
    _span = timespan._span;
    return *this;
}

TimeSpan &TimeSpan::operator=(TimeDiff microSeconds)
{
    _span = microSeconds;
    return *this;
}

int TimeSpan::Days() const { return int(_span / DAYS); }

int TimeSpan::Hours() const { return int((_span / HOURS) % 24); }

int TimeSpan::TotalHours() const { return int(_span / HOURS); }

int TimeSpan::Minutes() const { return int((_span / MINUTES) % 60); }

int TimeSpan::TotalMinutes() const { return int(_span / MINUTES); }

int TimeSpan::Seconds() const { return int((_span / SECONDS) % 60); }

int TimeSpan::TotalSeconds() const { return int(_span / SECONDS); }

int TimeSpan::Milliseconds() const
{
    return int((_span / MILLISECONDS) % 1000);
}

TimeSpan::TimeDiff TimeSpan::TotalMilliseconds() const
{
    return _span / MILLISECONDS;
}

int TimeSpan::Microseconds() const { return int(_span % 1000); }

int TimeSpan::Useconds() const { return int(_span % 1000000); }

TimeSpan::TimeDiff TimeSpan::TotalMicroseconds() const { return _span; }

bool TimeSpan::operator==(const TimeSpan &ts) const
{
    return _span == ts._span;
}

bool TimeSpan::operator!=(const TimeSpan &ts) const
{
    return _span != ts._span;
}

bool TimeSpan::operator>(const TimeSpan &ts) const { return _span > ts._span; }

bool TimeSpan::operator>=(const TimeSpan &ts) const
{
    return _span >= ts._span;
}

bool TimeSpan::operator<(const TimeSpan &ts) const { return _span < ts._span; }

bool TimeSpan::operator<=(const TimeSpan &ts) const
{
    return _span <= ts._span;
}

bool TimeSpan::operator==(TimeDiff microSeconds) const
{
    return _span == microSeconds;
}

bool TimeSpan::operator!=(TimeDiff microSeconds) const
{
    return _span != microSeconds;
}

bool TimeSpan::operator>(TimeDiff microSeconds) const
{
    return _span > microSeconds;
}

bool TimeSpan::operator>=(TimeDiff microSeconds) const
{
    return _span >= microSeconds;
}

bool TimeSpan::operator<(TimeDiff microSeconds) const
{
    return _span < microSeconds;
}

bool TimeSpan::operator<=(TimeDiff microSeconds) const
{
    return _span <= microSeconds;
}

void swap(TimeSpan &s1, TimeSpan &s2) noexcept { s1.Swap(s2); }

TimeSpan &TimeSpan::Assign(int days, int hours, int minutes, int seconds,
                           int microSeconds)
{
    _span = TimeDiff(microSeconds) + TimeDiff(seconds) * SECONDS +
            TimeDiff(minutes) * MINUTES + TimeDiff(hours) * HOURS +
            TimeDiff(days) * DAYS;
    return *this;
}

TimeSpan &TimeSpan::Assign(long seconds, long microSeconds)
{
    _span = TimeDiff(seconds) * SECONDS + TimeDiff(microSeconds);
    return *this;
}

void TimeSpan::Swap(TimeSpan &timespan) noexcept
{
    std::swap(_span, timespan._span);
}

TimeSpan TimeSpan::operator+(const TimeSpan &d) const
{
    return TimeSpan(_span + d._span);
}

TimeSpan TimeSpan::operator-(const TimeSpan &d) const
{
    return TimeSpan(_span - d._span);
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &d)
{
    _span += d._span;
    return *this;
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &d)
{
    _span -= d._span;
    return *this;
}

TimeSpan TimeSpan::operator+(TimeDiff microSeconds) const
{
    return TimeSpan(_span + microSeconds);
}

TimeSpan TimeSpan::operator-(TimeDiff microSeconds) const
{
    return TimeSpan(_span - microSeconds);
}

TimeSpan &TimeSpan::operator+=(TimeDiff microSeconds)
{
    _span += microSeconds;
    return *this;
}

TimeSpan &TimeSpan::operator-=(TimeDiff microSeconds)
{
    _span -= microSeconds;
    return *this;
}


DateTime::DateTime()
{
    Timestamp now;
    _utcTime = now.UtcTime();
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
}

DateTime::DateTime(const tm &tmStruct)
    : _year(tmStruct.tm_year + 1900), _month(tmStruct.tm_mon + 1),
      _day(tmStruct.tm_mday), _hour(tmStruct.tm_hour), _minute(tmStruct.tm_min),
      _second(tmStruct.tm_sec), _millisecond(0), _microsecond(0)
{
    CheckValid();
    _utcTime = ToUtcTime(ToJulianDay(_year, _month, _day)) +
               10 * (_hour * TimeSpan::HOURS + _minute * TimeSpan::MINUTES +
                     _second * TimeSpan::SECONDS);
}

DateTime::DateTime(const Timestamp &timestamp) : _utcTime(timestamp.UtcTime())
{
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
}

DateTime::DateTime(int year, int month, int day, int hour, int minute,
                   int second, int millisecond, int microsecond)
    : _year(year), _month(month), _day(day), _hour(hour), _minute(minute),
      _second(second), _millisecond(millisecond), _microsecond(microsecond)
{
    CheckValid();
    _utcTime = ToUtcTime(ToJulianDay(year, month, day)) +
               10 * (hour * TimeSpan::HOURS + minute * TimeSpan::MINUTES +
                     second * TimeSpan::SECONDS +
                     millisecond * TimeSpan::MILLISECONDS + microsecond);
}

DateTime::DateTime(double julianDay) : _utcTime(ToUtcTime(julianDay))
{
    ComputeGregorian(julianDay);
    CheckValid();
}

DateTime::DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff)
    : _utcTime(utcTime + diff * 10)
{
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
}

DateTime::DateTime(const DateTime &dateTime)
    : _utcTime(dateTime._utcTime), _year(dateTime._year),
      _month(dateTime._month), _day(dateTime._day), _hour(dateTime._hour),
      _minute(dateTime._minute), _second(dateTime._second),
      _millisecond(dateTime._millisecond), _microsecond(dateTime._microsecond)
{
}

DateTime::~DateTime() {}

DateTime &DateTime::operator=(const DateTime &dateTime)
{
    if (&dateTime != this)
    {
        _utcTime = dateTime._utcTime;
        _year = dateTime._year;
        _month = dateTime._month;
        _day = dateTime._day;
        _hour = dateTime._hour;
        _minute = dateTime._minute;
        _second = dateTime._second;
        _millisecond = dateTime._millisecond;
        _microsecond = dateTime._microsecond;
    }
    return *this;
}

DateTime &DateTime::operator=(const Timestamp &timestamp)
{
    _utcTime = timestamp.UtcTime();
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
    return *this;
}

DateTime &DateTime::operator=(double julianDay)
{
    _utcTime = ToUtcTime(julianDay);
    ComputeGregorian(julianDay);
    CheckValid();
    return *this;
}

DateTime &DateTime::Assign(int year, int month, int day, int hour, int minute,
                           int second, int millisecond, int microsecond)
{
    _utcTime = ToUtcTime(ToJulianDay(year, month, day)) +
               10 * (hour * TimeSpan::HOURS + minute * TimeSpan::MINUTES +
                     second * TimeSpan::SECONDS +
                     millisecond * TimeSpan::MILLISECONDS + microsecond);
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _second = second;
    _millisecond = millisecond;
    _microsecond = microsecond;
    CheckValid();

    return *this;
}

void DateTime::Swap(DateTime &dateTime) noexcept
{
    std::swap(_utcTime, dateTime._utcTime);
    std::swap(_year, dateTime._year);
    std::swap(_month, dateTime._month);
    std::swap(_day, dateTime._day);
    std::swap(_hour, dateTime._hour);
    std::swap(_minute, dateTime._minute);
    std::swap(_second, dateTime._second);
    std::swap(_millisecond, dateTime._millisecond);
    std::swap(_microsecond, dateTime._microsecond);
}

int DateTime::DayOfWeek() const
{
    return int((std::floor(JulianDay() + 1.5))) % 7;
}

int DateTime::DayOfYear() const
{
    int doy = 0;
    for (int month = 1; month < _month; ++month)
        doy += DaysOfMonth(_year, month);
    doy += _day;
    return doy;
}

int DateTime::DaysOfMonth(int year, int month)
{
    static int daysOfMonthTable[] = {0,  31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};

    if (month == 2 && IsLeapYear(year)) return 29;
    else if (month < 1 || month > 12)
        return 0;
    return daysOfMonthTable[month];
}

void DateTime::CheckValid()
{
    if (!IsValid(_year, _month, _day, _hour, _minute, _second, _millisecond,
                 _microsecond))
        throw std::invalid_argument(fmt::format(
                "Date time is {0}-{1}-{2}T{3}:{4}:{5}.{6}.{7}\n"
                "Valid values:\n"
                "-4713 <= year <= 9999\n"
                "1 <= month <= 12\n"
                "1 <= day <=  {8}\n"
                "0 <= hour <= 23\n"
                "0 <= minute <= 59\n"
                "0 <= second <= 60\n"
                "0 <= millisecond <= 999\n"
                "0 <= microsecond <= 999",
                _year, _month, _day, _hour, _minute, _second, _millisecond,
                _microsecond, DaysOfMonth(_year, _month)));
}

bool DateTime::IsValid(int year, int month, int day, int hour, int minute,
                       int second, int millisecond, int microsecond)
{
    return (year >= -4713 && year <= 9999) && (month >= 1 && month <= 12) &&
           (day >= 1 && day <= DaysOfMonth(year, month)) &&
           (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59) &&
           (second >= 0 && second <= 60) &&
           (millisecond >= 0 && millisecond <= 999) &&
           (microsecond >= 0 && microsecond <= 999);
}

int DateTime::Week(int firstDayOfWeek) const
{
    assert(firstDayOfWeek >= 0 && firstDayOfWeek <= 6);

    /// find the first firstDayOfWeek.
    int baseDay = 1;
    while (DateTime(_year, 1, baseDay).DayOfWeek() != firstDayOfWeek) ++baseDay;

    int doy = DayOfYear();
    int offs = baseDay <= 4 ? 0 : 1;
    if (doy < baseDay) return offs;
    else
        return (doy - baseDay) / 7 + 1 + offs;
}

double DateTime::JulianDay() const { return ToJulianDay(_utcTime); }

DateTime DateTime::operator+(const TimeSpan &span) const
{
    return DateTime(_utcTime, span.TotalMicroseconds());
}

DateTime DateTime::operator-(const TimeSpan &span) const
{
    return DateTime(_utcTime, -span.TotalMicroseconds());
}

TimeSpan DateTime::operator-(const DateTime &dateTime) const
{
    return TimeSpan((_utcTime - dateTime._utcTime) / 10);
}

DateTime &DateTime::operator+=(const TimeSpan &span)
{
    _utcTime += span.TotalMicroseconds() * 10;
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
    return *this;
}

DateTime &DateTime::operator-=(const TimeSpan &span)
{
    _utcTime -= span.TotalMicroseconds() * 10;
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    CheckValid();
    return *this;
}

tm DateTime::MakeTM() const
{
    tm tmStruct;

    tmStruct.tm_sec = _second;
    tmStruct.tm_min = _minute;
    tmStruct.tm_hour = _hour;
    tmStruct.tm_mday = _day;
    assert(_month > 0);
    tmStruct.tm_mon = _month - 1;
    assert(_year >= 1900);
    tmStruct.tm_year = _year - 1900;
    tmStruct.tm_wday = DayOfWeek();
    int doy = DayOfYear();
    assert(_year > 0);
    tmStruct.tm_yday = doy - 1;
    tmStruct.tm_isdst = -1;

    return tmStruct;
}

void DateTime::MakeUTC(int tzd)
{
    operator-=(TimeSpan(((Timestamp::TimeDiff) tzd) * TimeSpan::SECONDS));
}

void DateTime::MakeLocal(int tzd)
{
    operator+=(TimeSpan(((Timestamp::TimeDiff) tzd) * TimeSpan::SECONDS));
}

double DateTime::ToJulianDay(int year, int month, int day, int hour, int minute,
                             int second, int millisecond, int microsecond)
{
    // lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
    static int lookup[] = {-91, -60, -30, 0,   31,  61,  92, 122,
                           153, 184, 214, 245, 275, 306, 337};

    // day to double
    double dday =
            double(day) +
            ((double((hour * 60 + minute) * 60 + second) * 1000 + millisecond) *
                     1000 +
             microsecond) /
                    86400000000.0;
    if (month < 3)
    {
        month += 12;
        --year;
    }
    double dyear = double(year);
    return dday + lookup[month] + 365 * year + std::floor(dyear / 4) -
           std::floor(dyear / 100) + std::floor(dyear / 400) + 1721118.5;
}

void DateTime::CheckLimit(short &lower, short &higher, short limit)
{
    if (lower >= limit)
    {
        higher += short(lower / limit);
        lower = short(lower % limit);
    }
}

void DateTime::Normalize()
{
    CheckLimit(_microsecond, _millisecond, 1000);
    CheckLimit(_millisecond, _second, 1000);
    CheckLimit(_second, _minute, 60);
    CheckLimit(_minute, _hour, 60);
    CheckLimit(_hour, _day, 24);

    if (_day > DaysOfMonth(_year, _month))
    {
        _day -= DaysOfMonth(_year, _month);
        if (++_month > 12)
        {
            ++_year;
            _month -= 12;
        }
    }
}

void DateTime::ComputeGregorian(double julianDay)
{
    double z = std::floor(julianDay - 1721118.5);
    double r = julianDay - 1721118.5 - z;
    double g = z - 0.25;
    double a = std::floor(g / 36524.25);
    double b = a - std::floor(a / 4);
    _year = short(std::floor((b + g) / 365.25));
    double c = b + z - std::floor(365.25 * _year);
    _month = short(std::floor((5 * c + 456) / 153));
    double dday = c - std::floor((153.0 * _month - 457) / 5) + r;
    _day = short(dday);
    if (_month > 12)
    {
        ++_year;
        _month -= 12;
    }
    r *= 24;
    _hour = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    _minute = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    _second = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    _millisecond = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    _microsecond = short(r + 0.5);

    Normalize();
}

void DateTime::ComputeDaytime()
{
    Timestamp::UtcTimeVal ut(_utcTime);
    if (ut < 0)
    {
        // GH3723: UtcTimeVal is negative for pre-gregorian dates
        // move it 1600 years to the future
        // keeping hour, minute, second,... for corrections
        ut += std::int64_t(86400) * 1000 * 1000 * 10 * 1600 * 365;
    }
    TimeSpan span(ut / 10);
    int hour = span.Hours();
    // Due to double rounding issues, the previous call to computeGregorian()
    // may have crossed into the next or previous day. We need to correct that.
    if (hour == 23 && _hour == 0)
    {
        _day--;
        if (_day == 0)
        {
            _month--;
            if (_month == 0)
            {
                _month = 12;
                _year--;
            }
            _day = DaysOfMonth(_year, _month);
        }
    }
    else if (hour == 0 && _hour == 23)
    {
        _day++;
        if (_day > DaysOfMonth(_year, _month))
        {
            _month++;
            if (_month > 12)
            {
                _month = 1;
                _year++;
            }
            _day = 1;
        }
    }
    _hour = hour;
    _minute = span.Minutes();
    _second = span.Seconds();
    _millisecond = span.Milliseconds();
    _microsecond = span.Microseconds();
}

double DateTime::ToJulianDay(Timestamp::UtcTimeVal utcTime)
{
    double utcDays = double(utcTime) / 864000000000.0;
    return utcDays + 2299160.5;// first day of Gregorian reform (Oct 15 1582)
}

Timestamp::UtcTimeVal DateTime::ToUtcTime(double julianDay)
{
    return Timestamp::UtcTimeVal((julianDay - 2299160.5) * 864000000000.0);
}

Timestamp::UtcTimeVal DateTime::UtcTime() const { return _utcTime; }

int DateTime::Year() const { return _year; }

int DateTime::Month() const { return _month; }

int DateTime::Day() const { return _day; }

int DateTime::Hour() const { return _hour; }

int DateTime::HourAMPM() const
{
    if (_hour < 1) return 12;
    else if (_hour > 12)
        return _hour - 12;
    else
        return _hour;
}

bool DateTime::IsAM() const { return _hour < 12; }

bool DateTime::IsPM() const { return _hour >= 12; }

int DateTime::Minute() const { return _minute; }

int DateTime::Second() const { return _second; }

int DateTime::Millisecond() const { return _millisecond; }

int DateTime::Microsecond() const { return _microsecond; }

bool DateTime::operator==(const DateTime &dateTime) const
{
    return _utcTime == dateTime._utcTime;
}

bool DateTime::operator!=(const DateTime &dateTime) const
{
    return _utcTime != dateTime._utcTime;
}

bool DateTime::operator<(const DateTime &dateTime) const
{
    return _utcTime < dateTime._utcTime;
}

bool DateTime::operator<=(const DateTime &dateTime) const
{
    return _utcTime <= dateTime._utcTime;
}

bool DateTime::operator>(const DateTime &dateTime) const
{
    return _utcTime > dateTime._utcTime;
}

bool DateTime::operator>=(const DateTime &dateTime) const
{
    return _utcTime >= dateTime._utcTime;
}

bool DateTime::IsLeapYear(int year)
{
    return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
}

}// namespace CPL