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

#ifndef M2_DATETIME_H_
#define M2_DATETIME_H_

#include <m2_string.h>

namespace m2 {

static constexpr long long TM_MILLISECONDS = 1000;
static constexpr long long TM_SECONDS = 1000 * TM_MILLISECONDS;
static constexpr long long TM_MINUTES = 60 * TM_SECONDS;
static constexpr long long TM_HOURS = 60 * TM_MINUTES;
static constexpr long long TM_DAYS = 24 * TM_HOURS;

class Timestamp;
class TimeSpan;
class LIBM2_EXPORT DateTime
{
public:
    enum
    {
        UTC = 0xFFFF
    };

    enum Month
    {
        eJanuary = 1,
        eFebruary,
        eMarch,
        eApril,
        eMay,
        eJune,
        eJuly,
        eAugust,
        eSeptember,
        eOctober,
        eNovember,
        eDecember
    };

    enum WeekDay
    {
        eSunday,
        eMonday,
        eTuesday,
        eWednesday,
        eThursday,
        eFriday,
        eSaturday,
    };

    enum DateTimeFormat
    {
        eISO8601Format,
        eISO8601_FRACFormat,
        eRFC822Format,
        eRFC1123Format,
        eHTTPFormat,
        eRFC850Format,
        eRFC1036Format,
        eASCTIMEFormat,
        eSORTABLEFormat,
    };

public:
    DateTime();
    explicit DateTime(const tm &_tm);
    explicit DateTime(const Timestamp &timestamp);
    DateTime(int year, int month, int day, int hour = 0, int minute = 0,
             int second = 0, int millisecond = 0, int microsecond = 0);
    DateTime(long long utcTime, long long diff);
    DateTime(const DateTime &dateTime);
    ~DateTime();

    DateTime &operator=(const DateTime &dateTime);
    DateTime &operator=(const Timestamp &timestamp);
    DateTime &Assign(int year, int month, int day, int hour = 0, int minute = 0,
                     int second = 0, int millisecond = 0, int microseconds = 0);
    void swap(DateTime &dateTime) noexcept;

    int year() const;
    int month() const;
    int week(int firstDayOfWeek = eMonday) const;
    int day() const;
    int dayOfWeek() const;
    int dayOfYear() const;
    int hour() const;
    int HourAMPM() const;
    bool isAM() const;
    bool isPM() const;
    int minute() const;
    int second() const;
    int millisecond() const;
    int microsecond() const;

    double julianDay() const;
    Timestamp timestamp() const;

    long long UTCTime() const;
    DateTime toLocal() const;

    bool operator==(const DateTime &dateTime) const;
    bool operator!=(const DateTime &dateTime) const;
    bool operator<(const DateTime &dateTime) const;
    bool operator<=(const DateTime &dateTime) const;
    bool operator>(const DateTime &dateTime) const;
    bool operator>=(const DateTime &dateTime) const;

    DateTime operator+(const TimeSpan &span) const;
    DateTime operator-(const TimeSpan &span) const;
    TimeSpan operator-(const DateTime &dateTime) const;
    DateTime &operator+=(const TimeSpan &span);
    DateTime &operator-=(const TimeSpan &span);

    void makeUTC(int tzd);
    void makeLocal(int tzd);

    static bool isLeapYear(int year);
    static int daysOfMonth(int year, int month);
    static bool isValid(int year, int month, int day, int hour = 0,
                        int minute = 0, int second = 0, int millisecond = 0,
                        int microsecond = 0);
    static double toJulianDay(long long utcTime);
    static double toJulianDay(int year, int month, int day, int hour = 0,
                              int minute = 0, int second = 0,
                              int millisecond = 0, int microsecond = 0);

    static long long toUTCTime(double julianDay);
    void computeGregorian(double julianDay);
    void computeDaytime();

    static DateTime parse(const String &fmt, const String &str,
                          int &timeZoneDifferential);
    static DateTime parse(DateTimeFormat fmt, const String &str,
                          int &timeZoneDifferential);

    static bool tryParse(const String &fmt, const String &str,
                         DateTime &dateTime, int &timeZoneDifferential);
    static bool tryParse(DateTimeFormat fmt, const String &str,
                         DateTime &dateTime, int &timeZoneDifferential);

    static DateTime parse(const String &str, int &timeZoneDifferential);
    static bool tryParse(const String &str, DateTime &dateTime,
                         int &timeZoneDifferential);
    static String toString(const DateTime &dateTime, const String &fmt,
                           int timeZoneDifferential = UTC);
    static String toString(const Timestamp &tsp, const String &fmt,
                           int timeZoneDifferential = UTC);
    static String toString(const TimeSpan &rhs,
                           const String &fmt = "%dd %H:%M:%S.%i");
    static unsigned long long tickCount();

private:
    void checkLimit(short &lower, short &higher, short limit);
    void normalize();

    long long m_nUTCTime;
    short m_nYear;
    short m_nMonth;
    short m_nDay;
    short m_nHour;
    short m_nMinute;
    short m_nSecond;
    short m_nMillisecond;
    short m_nMicrosecond;
};

}// namespace m2

#endif//M2_DATETIME_H_