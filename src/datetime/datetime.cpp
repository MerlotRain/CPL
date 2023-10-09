﻿#include "../exception_p.h"
#include <datetime.h>
#ifdef _WIN32
#include <Windows.h>
#include <sysinfoapi.h>
#else
#endif

namespace m2 {

DateTime::DateTime()
{
    Timestamp now;
    m_nUTCTime = now.UTCTime();
    ComputeGregorian(JulianDay());
    ComputeDaytime();
}

DateTime::DateTime(const tm &_tm)
    : m_nYear(_tm.tm_year + 1900), m_nMonth(_tm.tm_mon + 1), m_nDay(_tm.tm_mday), m_nHour(_tm.tm_hour),
      m_nMinute(_tm.tm_min), m_nSecond(_tm.tm_sec), m_nMillisecond(0), m_nMicrosecond(0)
{
    assert(m_nYear >= 0 && m_nYear <= 9999);
    assert(m_nMonth >= 1 && m_nMonth <= 12);
    assert(m_nDay >= 1 && m_nDay <= DaysOfMonth(m_nYear, m_nMonth));
    assert(m_nHour >= 0 && m_nHour <= 23);
    assert(m_nMinute >= 0 && m_nMinute <= 59);
    assert(m_nSecond >= 0 && m_nSecond <= 60);

    m_nUTCTime = ToUTCTime(ToJulianDay(m_nYear, m_nMonth, m_nDay)) +
                 10 * (m_nHour * TM_HOURS + m_nMinute * TM_MINUTES + m_nSecond * TM_SECONDS);
}

DateTime::DateTime(const Timestamp &timestamp) : m_nUTCTime(timestamp.UTCTime())
{
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond,
                       int microsecond)
    : m_nYear(year), m_nMonth(month), m_nDay(day), m_nHour(hour), m_nMinute(minute), m_nSecond(second),
      m_nMillisecond(millisecond), m_nMicrosecond(microsecond)
{
    assert(year >= 0 && year <= 9999);
    assert(month >= 1 && month <= 12);
    assert(day >= 1 && day <= DaysOfMonth(year, month));
    assert(hour >= 0 && hour <= 23);
    assert(minute >= 0 && minute <= 59);
    assert(second >= 0 && second <= 60);// allow leap seconds
    assert(millisecond >= 0 && millisecond <= 999);
    assert(microsecond >= 0 && microsecond <= 999);

    m_nUTCTime = ToUTCTime(ToJulianDay(year, month, day)) +
                 10 * (hour * TM_HOURS + minute * TM_MINUTES + second * TM_SECONDS +
                       millisecond * TM_MILLISECONDS + microsecond);
}

DateTime::DateTime(long long utcTime, long long diff) : m_nUTCTime(utcTime + diff * 10)
{
    ComputeGregorian(JulianDay());
    ComputeDaytime();
}

DateTime::DateTime(const DateTime &dateTime)
    : m_nUTCTime(dateTime.m_nUTCTime), m_nYear(dateTime.m_nYear), m_nMonth(dateTime.m_nMonth),
      m_nDay(dateTime.m_nDay), m_nHour(dateTime.m_nHour), m_nMinute(dateTime.m_nMinute),
      m_nSecond(dateTime.m_nSecond), m_nMillisecond(dateTime.m_nMillisecond),
      m_nMicrosecond(dateTime.m_nMicrosecond)
{
}

DateTime::~DateTime()
{
}

DateTime &DateTime::operator=(const DateTime &dateTime)
{
    if (&dateTime != this)
    {
        m_nUTCTime = dateTime.m_nUTCTime;
        m_nYear = dateTime.m_nYear;
        m_nMonth = dateTime.m_nMonth;
        m_nDay = dateTime.m_nDay;
        m_nHour = dateTime.m_nHour;
        m_nMinute = dateTime.m_nMinute;
        m_nSecond = dateTime.m_nSecond;
        m_nMillisecond = dateTime.m_nMillisecond;
        m_nMicrosecond = dateTime.m_nMicrosecond;
    }
    return *this;
}

DateTime &DateTime::operator=(const Timestamp &timestamp)
{
    m_nUTCTime = timestamp.UTCTime();
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    return *this;
}

DateTime &DateTime::Assign(int year, int month, int day, int hour, int minute, int second,
                               int millisecond, int microseconds)
{
    assert(year >= 0 && year <= 9999);
    assert(month >= 1 && month <= 12);
    assert(day >= 1 && day <= DaysOfMonth(year, month));
    assert(hour >= 0 && hour <= 23);
    assert(minute >= 0 && minute <= 59);
    assert(second >= 0 && second <= 60);// allow leap seconds
    assert(millisecond >= 0 && millisecond <= 999);
    assert(microseconds >= 0 && microseconds <= 999);

    m_nUTCTime = ToUTCTime(ToJulianDay(year, month, day)) +
                 10 * (hour * TM_HOURS + minute * TM_MINUTES + second * TM_SECONDS +
                       millisecond * TM_MILLISECONDS + microseconds);
    m_nYear = year;
    m_nMonth = month;
    m_nDay = day;
    m_nHour = hour;
    m_nMinute = minute;
    m_nSecond = second;
    m_nMillisecond = millisecond;
    m_nMicrosecond = microseconds;

    return *this;
}

void DateTime::Swap(DateTime &dateTime) noexcept
{
    std::swap(m_nUTCTime, dateTime.m_nUTCTime);
    std::swap(m_nYear, dateTime.m_nYear);
    std::swap(m_nMonth, dateTime.m_nMonth);
    std::swap(m_nDay, dateTime.m_nDay);
    std::swap(m_nHour, dateTime.m_nHour);
    std::swap(m_nMinute, dateTime.m_nMinute);
    std::swap(m_nSecond, dateTime.m_nSecond);
    std::swap(m_nMillisecond, dateTime.m_nMillisecond);
    std::swap(m_nMicrosecond, dateTime.m_nMicrosecond);
}

int DateTime::Year() const
{
    return m_nYear;
}

int DateTime::Month() const
{
    return m_nMonth;
}

int DateTime::Week(int firstDayOfWeek) const
{
    assert(firstDayOfWeek >= 0 && firstDayOfWeek <= 6);

    /// find the first firstDayOfWeek.
    int baseDay = 1;
    while (DateTime(m_nYear, 1, baseDay).DayOfWeek() != firstDayOfWeek) ++baseDay;

    int doy = DayOfYear();
    int offs = baseDay <= 4 ? 0 : 1;
    if (doy < baseDay)
        return offs;
    else
        return (doy - baseDay) / 7 + 1 + offs;
}

int DateTime::Day() const
{
    return m_nDay;
}

int DateTime::DayOfWeek() const
{
    return int((std::floor(JulianDay() + 1.5))) % 7;
}

int DateTime::DayOfYear() const
{
    int doy = 0;
    for (int month = 1; month < m_nMonth; ++month) doy += DaysOfMonth(m_nYear, month);
    doy += m_nDay;
    return doy;
}

int DateTime::Hour() const
{
    return m_nHour;
}

int DateTime::HourAMPM() const
{
    if (m_nHour < 1)
        return 12;
    else if (m_nHour > 12)
        return m_nHour - 12;
    else
        return m_nHour;
}

bool DateTime::AM() const
{
    return m_nHour < 12;
}

bool DateTime::PM() const
{
    return m_nHour >= 12;
}

int DateTime::Minute() const
{
    return m_nMinute;
}

int DateTime::Second() const
{
    return m_nSecond;
}

int DateTime::Millisecond() const
{
    return m_nMillisecond;
}

int DateTime::Microsecond() const
{
    return m_nMicrosecond;
}

double DateTime::JulianDay() const
{
    return ToJulianDay(m_nUTCTime);
}

Timestamp DateTime::Timestamp() const
{
    return Timestamp::FromUTCTime(m_nUTCTime);
}

long long DateTime::UTCTime() const
{
    return 0;
}

DateTime DateTime::ToLocal() const
{
    return DateTime();
}

bool DateTime::operator==(const DateTime &dateTime) const
{
    return m_nUTCTime == dateTime.m_nUTCTime;
}

bool DateTime::operator!=(const DateTime &dateTime) const
{
    return m_nUTCTime != dateTime.m_nUTCTime;
}

bool DateTime::operator<(const DateTime &dateTime) const
{
    return m_nUTCTime < dateTime.m_nUTCTime;
}

bool DateTime::operator<=(const DateTime &dateTime) const
{
    return m_nUTCTime <= dateTime.m_nUTCTime;
}

bool DateTime::operator>(const DateTime &dateTime) const
{
    return m_nUTCTime > dateTime.m_nUTCTime;
}

bool DateTime::operator>=(const DateTime &dateTime) const
{
    return m_nUTCTime >= dateTime.m_nUTCTime;
}

DateTime DateTime::operator+(const TimeSpan &span) const
{
    return DateTime(m_nUTCTime, span.TotalMicroseconds());
}

DateTime DateTime::operator-(const TimeSpan &span) const
{
    return DateTime(m_nUTCTime, -span.TotalMicroseconds());
}

TimeSpan DateTime::operator-(const DateTime &dateTime) const
{
    return TimeSpan((m_nUTCTime - dateTime.m_nUTCTime) / 10);
}

DateTime &DateTime::operator+=(const TimeSpan &span)
{
    m_nUTCTime += span.TotalMicroseconds() * 10;
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    return *this;
}

DateTime &DateTime::operator-=(const TimeSpan &span)
{
    m_nUTCTime -= span.TotalMicroseconds() * 10;
    ComputeGregorian(JulianDay());
    ComputeDaytime();
    return *this;
}

void DateTime::MakeUTC(int tzd)
{
    operator-=(TimeSpan(((long long) tzd) * TM_SECONDS));
}

void DateTime::MakeLocal(int tzd)
{
    operator+=(TimeSpan(((long long) tzd) * TM_SECONDS));
}

bool DateTime::IsLeapYear(int year)
{
    return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
}

int DateTime::DaysOfMonth(int year, int month)
{
    assert(month >= 1 && month <= 12);

    static int daysOfMonthTable[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && IsLeapYear(year))
        return 29;
    else
        return daysOfMonthTable[month];
}

bool DateTime::IsValid(int year, int month, int day, int hour, int minute, int second, int millisecond,
                         int microsecond)
{
    return (year >= 0 && year <= 9999) && (month >= 1 && month <= 12) &&
           (day >= 1 && day <= DaysOfMonth(year, month)) && (hour >= 0 && hour <= 23) &&
           (minute >= 0 && minute <= 59) && (second >= 0 && second <= 60) &&
           (millisecond >= 0 && millisecond <= 999) && (microsecond >= 0 && microsecond <= 999);
}

double DateTime::ToJulianDay(long long utcTime)
{
    double utcDays = double(utcTime) / 864000000000.0;
    return utcDays + 2299160.5;// first day of Gregorian reform (Oct 15 1582)
}

double DateTime::ToJulianDay(int year, int month, int day, int hour, int minute, int second,
                               int millisecond, int microsecond)
{
    static int lookup[] = {-91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337};

    // day to double
    double dday =
            double(day) +
            ((double((hour * 60 + minute) * 60 + second) * 1000 + millisecond) * 1000 + microsecond) /
                    86400000000.0;
    if (month < 3)
    {
        month += 12;
        --year;
    }
    double dyear = double(year);
    return dday + lookup[month] + 365 * year + std::floor(dyear / 4) - std::floor(dyear / 100) +
           std::floor(dyear / 400) + 1721118.5;
}

long long DateTime::ToUTCTime(double julianDay)
{
    return long long((julianDay - 2299160.5) * 864000000000.0);
}

void DateTime::ComputeGregorian(double julianDay)
{
    double z = std::floor(julianDay - 1721118.5);
    double r = julianDay - 1721118.5 - z;
    double g = z - 0.25;
    double a = std::floor(g / 36524.25);
    double b = a - std::floor(a / 4);
    m_nYear = short(std::floor((b + g) / 365.25));
    double c = b + z - std::floor(365.25 * m_nYear);
    m_nMonth = short(std::floor((5 * c + 456) / 153));
    double dday = c - std::floor((153.0 * m_nMonth - 457) / 5) + r;
    m_nDay = short(dday);
    if (m_nMonth > 12)
    {
        ++m_nYear;
        m_nMonth -= 12;
    }
    r *= 24;
    m_nHour = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    m_nMinute = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    m_nSecond = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    m_nMillisecond = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    m_nMicrosecond = short(r + 0.5);

    Normalize();

    assert(m_nMonth >= 1 && m_nMonth <= 12);
    assert(m_nDay >= 1 && m_nDay <= DaysOfMonth(m_nYear, m_nMonth));
    assert(m_nHour >= 0 && m_nHour <= 23);
    assert(m_nMinute >= 0 && m_nMinute <= 59);
    assert(m_nSecond >= 0 && m_nSecond <= 59);
    assert(m_nMillisecond >= 0 && m_nMillisecond <= 999);
    assert(m_nMicrosecond >= 0 && m_nMicrosecond <= 999);
}

void DateTime::ComputeDaytime()
{
    TimeSpan span(m_nUTCTime / 10);
    int hour = span.Hours();
    if (hour == 23 && m_nHour == 0)
    {
        m_nDay--;
        if (m_nDay == 0)
        {
            m_nMonth--;
            if (m_nMonth == 0)
            {
                m_nMonth = 12;
                m_nYear--;
            }
            m_nDay = DaysOfMonth(m_nYear, m_nMonth);
        }
    }
    else if (hour == 0 && m_nHour == 23)
    {
        m_nDay++;
        if (m_nDay > DaysOfMonth(m_nYear, m_nMonth))
        {
            m_nMonth++;
            if (m_nMonth > 12)
            {
                m_nMonth = 1;
                m_nYear++;
            }
            m_nDay = 1;
        }
    }
    m_nHour = hour;
    m_nMinute = span.Minutes();
    m_nSecond = span.Seconds();
    m_nMillisecond = span.Milliseconds();
    m_nMicrosecond = span.Microseconds();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<String> WEEKDAY_NAMES = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                             "Thursday", "Friday", "Saturday"};

const std::vector<String> MONTH_NAMES = {"January", "February", "March", "April",
                                           "May", "June", "July", "August",
                                           "September", "October", "November", "December"};


#define SKIP_JUNK() \
    while (it != end && !Ascii::IsDigit(*it)) ++it


#define SKIP_DIGITS() \
    while (it != end && Ascii::IsDigit(*it)) ++it


#define PARSE_NUMBER(var) \
    while (it != end && Ascii::IsDigit(*it)) var = var * 10 + ((*it++) - '0')


#define PARSE_NUMBER_N(var, n)                                                                  \
    {                                                                                           \
        int i = 0;                                                                              \
        while (i++ < n && it != end && Ascii::IsDigit(*it)) var = var * 10 + ((*it++) - '0'); \
    }


#define PARSE_FRACTIONAL_N(var, n)                          \
    {                                                       \
        int i = 0;                                          \
        while (i < n && it != end && Ascii::IsDigit(*it)) \
        {                                                   \
            var = var * 10 + ((*it++) - '0');               \
            i++;                                            \
        }                                                   \
        while (i++ < n) var *= 10;                          \
    }


static String WellKnownDateTimeFormat(DateTimeFormat format)
{
    static constexpr auto WellKnownFormatList = {
            "%Y-%m-%dT%H:%M:%S%z", "%Y-%m-%dT%H:%M:%s%z", "%w, %e %b %y %H:%M:%S %Z",
            "%w, %e %b %Y %H:%M:%S %Z", "%w, %d %b %Y %H:%M:%S %Z", "%W, %e-%b-%y %H:%M:%S %Z",
            "%W, %e %b %y %H:%M:%S %Z", "%w %b %f %H:%M:%S %Y", "%Y-%m-%d %H:%M:%S"};

    if (format > WellKnownFormatList.size())
        return String();

    return *(WellKnownFormatList.begin() + format);
}

/// @brief 尝试将给定的范围解释为月份名称，范围必须至少有三个字符长
/// @param it
/// @param end
/// @return 如果月份名称有效，则返回月份编号（1..12）
static int ParseMonth(String::const_iterator &it, const String::const_iterator &end)
{
    String month;
    while (it != end && (Ascii::IsSpace(*it) || Ascii::IsPunctuation(*it))) ++it;
    bool isFirst = true;
    while (it != end && Ascii::IsAlpha(*it))
    {
        char ch = (*it++);
        if (isFirst)
        {
            month += Ascii::ToUpper(ch);
            isFirst = false;
        }
        else
            month += Ascii::ToLower(ch);
    }
    if (month.length() < 3)
        throw UtilityException(String::Format(
                "Month name '%s' must be at least three characters long", month.c_str()));
    for (int i = 0; i < 12; ++i)
    {
        if (MONTH_NAMES[i].find(month) == 0)
            return i + 1;
    }
    throw UtilityException(String::Format("%s is not a valid month name", month.c_str()));
}

/// @brief 尝试将给定的范围解释为工作日名称，范围必须至少有三个字符长
/// @param it
/// @param end
/// @return 如果工作日名称有效，则返回工作日编号 0..6，其中0=周日，1=周一
static int ParseDayOfWeek(String::const_iterator &it, const String::const_iterator &end)
{
    String dow;
    while (it != end && (Ascii::IsSpace(*it) || Ascii::IsPunctuation(*it))) ++it;
    bool isFirst = true;
    while (it != end && Ascii::IsAlpha(*it))
    {
        char ch = (*it++);
        if (isFirst)
        {
            dow += Ascii::ToUpper(ch);
            isFirst = false;
        }
        else
            dow += Ascii::ToLower(ch);
    }
    if (dow.length() < 3)
        throw UtilityException(String::Format(
                "Weekday name '%s' must be at least three characters long", dow.c_str()));

    for (int i = 0; i < 7; ++i)
    {
        if (WEEKDAY_NAMES[i].find(dow) == 0)
            return i;
    }

    throw UtilityException(String::Format("%s is not a valid weekday name", dow.c_str()));
}

static int ParseTimeZoneDifferential(String::const_iterator &it, const String::const_iterator &end)
{
    struct Zone
    {
        const char *designator;
        int timeZoneDifferential;
    };

    static Zone zones[] = {
            {   "Z",                0},
            {  "UT",                0},
            { "GMT",                0},
            { "BST",         1 * 3600},
            { "IST",         1 * 3600},
            { "WET",                0},
            {"WEST",         1 * 3600},
            { "CET",         1 * 3600},
            {"CEST",         2 * 3600},
            { "EET",         2 * 3600},
            {"EEST",         3 * 3600},
            { "MSK",         3 * 3600},
            { "MSD",         4 * 3600},
            { "NST", -3 * 3600 - 1800},
            { "NDT", -2 * 3600 - 1800},
            { "AST",        -4 * 3600},
            { "ADT",        -3 * 3600},
            { "EST",        -5 * 3600},
            { "EDT",        -4 * 3600},
            { "CST",        -6 * 3600},
            { "CDT",        -5 * 3600},
            { "MST",        -7 * 3600},
            { "MDT",        -6 * 3600},
            { "PST",        -8 * 3600},
            { "PDT",        -7 * 3600},
            {"AKST",        -9 * 3600},
            {"AKDT",        -8 * 3600},
            { "HST",       -10 * 3600},
            {"AEST",        10 * 3600},
            {"AEDT",        11 * 3600},
            {"ACST",  9 * 3600 + 1800},
            {"ACDT", 10 * 3600 + 1800},
            {"AWST",         8 * 3600},
            {"AWDT",         9 * 3600}
    };

    int tzd = 0;
    while (it != end && Ascii::IsSpace(*it)) ++it;
    if (it != end)
    {
        if (Ascii::IsAlpha(*it))
        {
            String designator;
            designator += *it++;
            if (it != end && Ascii::IsAlpha(*it))
                designator += *it++;
            if (it != end && Ascii::IsAlpha(*it))
                designator += *it++;
            if (it != end && Ascii::IsAlpha(*it))
                designator += *it++;
            for (unsigned i = 0; i < sizeof(zones) / sizeof(Zone); ++i)
            {
                if (designator == zones[i].designator)
                {
                    tzd = zones[i].timeZoneDifferential;
                    break;
                }
            }
        }
        if (it != end && (*it == '+' || *it == '-'))
        {
            int sign = *it == '+' ? 1 : -1;
            ++it;
            int hours = 0;
            PARSE_NUMBER_N(hours, 2);
            if (it != end && *it == ':')
                ++it;
            int minutes = 0;
            PARSE_NUMBER_N(minutes, 2);
            tzd += sign * (hours * 3600 + minutes * 60);
        }
    }
    return tzd;
}

static int ParseAMPM(String::const_iterator &it, const String::const_iterator &end, int hour)
{
    String ampm;
    while (it != end && (Ascii::IsSpace(*it) || Ascii::IsPunctuation(*it))) ++it;
    while (it != end && Ascii::IsAlpha(*it))
    {
        char ch = (*it++);
        ampm += Ascii::ToUpper(ch);
    }
    if (ampm == "AM")
    {
        if (hour == 12)
            return 0;
        else
            return hour;
    }
    else if (ampm == "PM")
    {
        if (hour < 12)
            return hour + 12;
        else
            return hour;
    }
    else
        throw UtilityException(String::Format("%s is not a valid AM/PM designator", ampm.c_str()));
}

void TimeZoneDifferentialISO(String &str, int timeZoneDifferential)
{
    if (timeZoneDifferential != DateTime::UTC)
    {
        if (timeZoneDifferential >= 0)
        {
            str += '+';
            str.Arg(timeZoneDifferential / 3600, 2);
            str += ':';
            str.Arg((timeZoneDifferential % 3600) / 60, 2);
        }
        else
        {
            str += '-';
            str.Arg(-timeZoneDifferential / 3600, 2);
            str += ':';
            str.Arg((-timeZoneDifferential % 3600) / 60, 2);
        }
    }
    else
        str += 'Z';
}

void TimeZoneDifferentialRFC(String &str, int timeZoneDifferential)
{
    if (timeZoneDifferential != DateTime::UTC)
    {
        if (timeZoneDifferential >= 0)
        {
            str += '+';
            str.Arg(timeZoneDifferential / 3600, 2);
            str.Arg((timeZoneDifferential % 3600) / 60, 2);
        }
        else
        {
            str += '-';
            str.Arg(-timeZoneDifferential / 3600, 2);
            str.Arg((-timeZoneDifferential % 3600) / 60, 2);
        }
    }
    else
        str += "GMT";
}

DateTime DateTime::Parse(const String &fmt, const String &str, int &timeZoneDifferential)
{
    DateTime dateTime;
    if (fmt.empty() || str.empty())
        return dateTime;

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millis = 0;
    int micros = 0;
    int tzd = 0;

    String::const_iterator it = str.begin();
    String::const_iterator end = str.end();
    String::const_iterator itf = fmt.begin();
    String::const_iterator endf = fmt.end();

    while (itf != endf && it != end)
    {
        if (*itf == '%')
        {
            if (++itf != endf)
            {
                switch (*itf)
                {
                    case 'w':
                    case 'W':
                        while (it != end && Ascii::IsSpace(*it)) ++it;
                        while (it != end && Ascii::IsAlpha(*it)) ++it;
                        break;
                    case 'b':
                    case 'B':
                        month = ParseMonth(it, end);
                        break;
                    case 'd':
                    case 'e':
                    case 'f':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(day, 2);
                        break;
                    case 'm':
                    case 'n':
                    case 'o':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(month, 2);
                        break;
                    case 'y':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(year, 2);
                        if (year >= 69)
                            year += 1900;
                        else
                            year += 2000;
                        break;
                    case 'Y':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(year, 4);
                        break;
                    case 'r':
                        SKIP_JUNK();
                        PARSE_NUMBER(year);
                        if (year < 1000)
                        {
                            if (year >= 69)
                                year += 1900;
                            else
                                year += 2000;
                        }
                        break;
                    case 'H':
                    case 'h':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(hour, 2);
                        break;
                    case 'a':
                    case 'A':
                        hour = ParseAMPM(it, end, hour);
                        break;
                    case 'M':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(minute, 2);
                        break;
                    case 'S':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(second, 2);
                        break;
                    case 's':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(second, 2);
                        if (it != end && (*it == '.' || *it == ','))
                        {
                            ++it;
                            PARSE_FRACTIONAL_N(millis, 3);
                            PARSE_FRACTIONAL_N(micros, 3);
                            SKIP_DIGITS();
                        }
                        break;
                    case 'i':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(millis, 3);
                        break;
                    case 'c':
                        SKIP_JUNK();
                        PARSE_NUMBER_N(millis, 1);
                        millis *= 100;
                        break;
                    case 'F':
                        SKIP_JUNK();
                        PARSE_FRACTIONAL_N(millis, 3);
                        PARSE_FRACTIONAL_N(micros, 3);
                        SKIP_DIGITS();
                        break;
                    case 'z':
                    case 'Z':
                        tzd = ParseTimeZoneDifferential(it, end);
                        break;
                }
                ++itf;
            }
        }
        else
            ++itf;
    }
    if (month == 0)
        month = 1;
    if (day == 0)
        day = 1;
    if (DateTime::IsValid(year, month, day, hour, minute, second, millis, micros))
        dateTime.Assign(year, month, day, hour, minute, second, millis, micros);
    else
        throw UtilityException("date/time component out of range");
    timeZoneDifferential = tzd;
    return DateTime();
}

DateTime DateTime::Parse(DateTimeFormat fmt, const String &str, int &timeZoneDifferential)
{
    String format = WellKnownDateTimeFormat(fmt);
    return Parse(format, str, timeZoneDifferential);
}

bool DateTime::TryParse(const String &fmt, const String &str, DateTime &dateTime,
                          int &timeZoneDifferential)
{
    try
    {
        dateTime = Parse(fmt, str, timeZoneDifferential);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool DateTime::TryParse(DateTimeFormat fmt, const String &str, DateTime &dateTime,
                          int &timeZoneDifferential)
{
    String format = WellKnownDateTimeFormat(fmt);
    try
    {
        dateTime = Parse(format, str, timeZoneDifferential);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

DateTime DateTime::Parse(const String &str, int &timeZoneDifferential)
{
    DateTime result;
    if (TryParse(str, result, timeZoneDifferential))
        return result;
    else
        throw UtilityException("Unsupported or invalid date/time format");
}

bool DateTime::TryParse(const String &str, DateTime &dateTime, int &timeZoneDifferential)
{
    if (str.length() < 4)
        return false;

    if (str[3] == ',')
        return TryParse("%w, %e %b %r %H:%M:%S %Z", str, dateTime, timeZoneDifferential);
    else if (str[3] == ' ')
        return TryParse(WellKnownDateTimeFormat(eASCTIME_FORMAT), str, dateTime, timeZoneDifferential);
    else if (str.find(',') < 10)
        return TryParse("%W, %e %b %r %H:%M:%S %Z", str, dateTime, timeZoneDifferential);
    else if (Ascii::IsDigit(str[0]))
    {
        if (str.find(' ') != String::npos || str.length() == 10)
            return TryParse(WellKnownDateTimeFormat(eSORTABLE_FORMAT), str, dateTime,
                            timeZoneDifferential);
        else if (str.find('.') != String::npos || str.find(',') != String::npos)
            return TryParse(WellKnownDateTimeFormat(eISO8601_FRAC_FORMAT), str, dateTime,
                            timeZoneDifferential);
        else
            return TryParse(WellKnownDateTimeFormat(eISO8601_FORMAT), str, dateTime,
                            timeZoneDifferential);
    }
    else
        return false;
}

String DateTime::ToString(const DateTime &dateTime, const String &fmt, int timeZoneDifferential)
{
    String result;
    result.reserve(64);
    String::const_iterator it = fmt.begin();
    String::const_iterator end = fmt.end();
    while (it != end)
    {
        if (*it == '%')
        {
            if (++it != end)
            {
                switch (*it)
                {
                    case 'w':
                        result.append(WEEKDAY_NAMES[dateTime.DayOfWeek()].c_str(), 0, 3);
                        break;
                    case 'W':
                        result.append(WEEKDAY_NAMES[dateTime.DayOfWeek()]);
                        break;
                    case 'b':
                        result.append(MONTH_NAMES[dateTime.Month() - 1], 0, 3);
                        break;
                    case 'B':
                        result.append(MONTH_NAMES[dateTime.Month() - 1]);
                        break;
                    case 'd':
                        result.Arg(dateTime.Day(), 2);
                        break;
                    case 'e':
                        result.Arg(dateTime.Day());
                        break;
                    case 'f':
                        result.Arg(dateTime.Day(), 2);
                        break;
                    case 'm':
                        result.Arg(dateTime.Month(), 2);
                        break;
                    case 'n':
                        result.Arg(dateTime.Month());
                        break;
                    case 'o':
                        result.Arg(dateTime.Month(), 2);
                        break;
                    case 'y':
                        result.Arg(dateTime.Year() % 100, 2);
                        break;
                    case 'Y':
                        result.Arg(dateTime.Year(), 4);
                        break;
                    case 'H':
                        result.Arg(dateTime.Hour(), 2);
                        break;
                    case 'h':
                        result.Arg(dateTime.HourAMPM(), 2);
                        break;
                    case 'a':
                        result.append(dateTime.AM() ? "am" : "pm");
                        break;
                    case 'A':
                        result.append(dateTime.AM() ? "AM" : "PM");
                        break;
                    case 'M':
                        result.Arg(dateTime.Minute(), 2);
                        break;
                    case 'S':
                        result.Arg(dateTime.Second(), 2);
                        break;
                    case 's':
                        result.Arg(dateTime.Second(), 2);
                        result += '.';
                        result.Arg(dateTime.Microsecond() * 1000 + dateTime.Microsecond(), 6);
                        break;
                    case 'i':
                        result.Arg(dateTime.Millisecond(), 3);
                        break;
                    case 'c':
                        result.Arg(dateTime.Millisecond() / 100);
                        break;
                    case 'F':
                        result.Arg(dateTime.Millisecond() * 1000 + dateTime.Microsecond(), 6);
                        break;
                    case 'z':
                        TimeZoneDifferentialISO(result, timeZoneDifferential);
                        break;
                    case 'Z':
                        TimeZoneDifferentialRFC(result, timeZoneDifferential);
                        break;
                    default:
                        result += *it;
                }
                ++it;
            }
        }
        else
            result += *it++;
    }
    return result;
}

String DateTime::ToString(const Timestamp &timestamp, const String &fmt,
                              int timeZoneDifferential)
{
    DateTime dateTime(timestamp);
    return ToString(dateTime, fmt, timeZoneDifferential);
}

String DateTime::ToString(const TimeSpan &timespan, const String &fmt)
{
    String result;
    result.reserve(32);
    String::const_iterator it = fmt.begin();
    String::const_iterator end = fmt.end();
    while (it != end)
    {
        if (*it == '%')
        {
            if (++it != end)
            {
                switch (*it)
                {
                    case 'd':
                        result.Arg(timespan.Days());
                        break;
                    case 'H':
                        result.Arg(timespan.Hours(), 2);
                        break;
                    case 'h':
                        result.Arg(timespan.TotalHours());
                        break;
                    case 'M':
                        result.Arg(timespan.Minutes(), 2);
                        break;
                    case 'm':
                        result.Arg(timespan.TotalMinutes());
                        break;
                    case 'S':
                        result.Arg(timespan.Seconds(), 2);
                        break;
                    case 's':
                        result.Arg(timespan.TotalSeconds());
                        break;
                    case 'i':
                        result.Arg(timespan.Milliseconds(), 3);
                        break;
                    case 'c':
                        result.Arg(timespan.Milliseconds() / 100);
                        break;
                    case 'F':
                        result.Arg(timespan.Milliseconds() * 1000 + timespan.Microseconds(), 6);
                        break;
                    default:
                        result += *it;
                }
                ++it;
            }
        }
        else
            result += *it++;
    }
    return result;
}

unsigned long long DateTime::TickCount()
{
#ifdef _WIN32
    return GetTickCount();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
#endif
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
    CheckLimit(m_nMicrosecond, m_nMillisecond, 1000);
    CheckLimit(m_nMillisecond, m_nSecond, 1000);
    CheckLimit(m_nSecond, m_nMinute, 60);
    CheckLimit(m_nMinute, m_nHour, 60);
    CheckLimit(m_nHour, m_nDay, 24);

    if (m_nDay > DaysOfMonth(m_nYear, m_nMonth))
    {
        m_nDay -= DaysOfMonth(m_nYear, m_nMonth);
        if (++m_nMonth > 12)
        {
            ++m_nYear;
            m_nMonth -= 12;
        }
    }
}


}// namespace m2
