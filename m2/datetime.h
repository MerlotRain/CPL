#ifndef M2_DATETIME_H_
#define M2_DATETIME_H_

#include <m2_string.h>

namespace m2 {

static constexpr long long TM_MILLISECONDS = 1000;
static constexpr long long TM_SECONDS = 1000 * TM_MILLISECONDS;
static constexpr long long TM_MINUTES = 60 * TM_SECONDS;
static constexpr long long TM_HOURS = 60 * TM_MINUTES;
static constexpr long long TM_DAYS = 24 * TM_HOURS;


struct LIBM2_EXPORT TimeSpan
{
public:
    TimeSpan();
    explicit TimeSpan(long long microseconds);
    TimeSpan(long seconds, long microseconds);
    TimeSpan(int days, int hours, int minutes, int seconds, int microSeconds);
    TimeSpan(const TimeSpan &rhs);

    template<class T, class Period>
    explicit TimeSpan(const std::chrono::duration<T, Period> &time)
        : TimeSpan(std::chrono::duration_cast<
                   std::chrono::microseconds(time).count()>)
    {
    }

    ~TimeSpan();

    TimeSpan &operator=(const TimeSpan &rhs);
    TimeSpan &operator=(long long microseconds);

    TimeSpan &assign(int days, int hours, int minutes, int seconds,
                     int microSeconds);
    TimeSpan &assign(long seconds, long microseconds);

    template<class T, class Period>
    TimeSpan &assign(const std::chrono::duration<T, Period> &time)
    {
        TimeSpan = std::chrono::duration_cast<std::chrono::microseconds>(time)
                           .count();
        return *this;
    }

    void swap(TimeSpan &timespan) noexcept;

    bool operator==(const TimeSpan &rhs) const;
    bool operator!=(const TimeSpan &rhs) const;
    bool operator>(const TimeSpan &rhs) const;
    bool operator>=(const TimeSpan &rhs) const;
    bool operator<(const TimeSpan &rhs) const;
    bool operator<=(const TimeSpan &rhs) const;
    bool operator==(long long microSeconds) const;
    bool operator!=(long long microSeconds) const;
    bool operator>(long long microSeconds) const;
    bool operator>=(long long microSeconds) const;
    bool operator<(long long microSeconds) const;
    bool operator<=(long long microSeconds) const;

    TimeSpan operator+(const TimeSpan &rhs) const;
    TimeSpan operator-(const TimeSpan &rhs) const;
    TimeSpan &operator+=(const TimeSpan &rhs);
    TimeSpan &operator-=(const TimeSpan &rhs);
    TimeSpan operator+(long long microSeconds) const;
    TimeSpan operator-(long long microSeconds) const;
    TimeSpan &operator+=(long long microSeconds);
    TimeSpan &operator-=(long long microSeconds);

    int days() const;
    int hours() const;
    int totalHours() const;
    int minutes() const;
    int totalMinutes() const;
    int seconds() const;
    int totalSeconds() const;
    int milliseconds() const;
    long long totalMilliseconds() const;
    int microseconds() const;
    int useconds() const;
    long long totalMicroseconds() const;

private:
    long long tspan;
};


struct LIBM2_EXPORT Timestamp
{
public:
    Timestamp();
    /// @brief
    /// @param tv
    explicit Timestamp(long long tv);
    /// @brief 拷贝构造
    /// @param rhs
    Timestamp(const Timestamp &rhs);
    ~Timestamp();
    /// @brief 赋值复制构造
    /// @param rhs
    /// @return
    Timestamp &operator=(const Timestamp &rhs);
    /// @brief 赋值复制构造
    /// @param timestamp
    /// @return
    Timestamp &operator=(long long timestamp);
    /// @brief 交换时间戳
    /// @param timestamp
    void Swap(Timestamp &timestamp) noexcept;

    /// @brief 使用当前时间更新时间戳
    void Update();

    bool operator==(const Timestamp &timestamp) const;
    bool operator!=(const Timestamp &timestamp) const;
    bool operator>(const Timestamp &timestamp) const;
    bool operator>=(const Timestamp &timestamp) const;
    bool operator<(const Timestamp &timestamp) const;
    bool operator<=(const Timestamp &timestamp) const;

    Timestamp operator+(long long duration) const;
    Timestamp operator+(const TimeSpan &rhs) const;
    Timestamp operator-(long long duration) const;
    Timestamp operator-(const TimeSpan &rhs) const;
    long long operator-(const Timestamp &timestamp) const;
    Timestamp &operator+=(long long duration);
    Timestamp &operator+=(const TimeSpan &rhs);
    Timestamp &operator-=(long long duration);
    Timestamp &operator-=(const TimeSpan &rhs);

    std::time_t EpochTime() const;
    long long UTCTime() const;
    long long EpochMicroseconds() const;
    long long Elapsed() const;
    bool IsElapsed(long long interval) const;
    long long Raw() const;

    static Timestamp FromEpochTime(std::time_t t);
    static Timestamp FromUTCTime(long long utc);
    static long long Resolution();

private:
    long long tstamp;
    constexpr static long long TimestampMinimumValue = LLONG_MIN;
    constexpr static long long TimestampMaximumValue = LLONG_MAX;
};


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


class LIBM2_EXPORT TimeZone
{
public:
    static int UTCOffset();

    static int DST();
    static int DST(const Timestamp &timestamp);

    static bool IsDST(const Timestamp &timestamp);

    static int TimeZoneDifferential();
    static String Name();
    static String StandardName();
    static String DSTName();
};

}// namespace m2

#endif//M2_DATETIME_H_