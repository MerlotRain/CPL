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

#include "stringhelp.h"

namespace m2 {

/// @brief 1毫秒换算微秒
static constexpr long long TM_MILLISECONDS = 1000;
/// @brief 1秒换算微秒
static constexpr long long TM_SECONDS = 1000 * TM_MILLISECONDS;
/// @brief 1分钟换算微秒
static constexpr long long TM_MINUTES = 60 * TM_SECONDS;
/// @brief 1小时换算微秒
static constexpr long long TM_HOURS = 60 * TM_MINUTES;
/// @brief 1天换算微秒
static constexpr long long TM_DAYS = 24 * TM_HOURS;

/// @brief 高精度的微秒级别的时间间隔
struct M2_API GsTimeSpan
{
    /// @brief 时间跨度，单位（微秒）
    long long TimeSpan;

    GsTimeSpan();

    /// @brief 构造
    /// @param microseconds 间隔总的微秒数
    explicit GsTimeSpan(long long microseconds);

    /// @brief 构造
    /// @param seconds 间隔的总秒数
    /// @param microseconds 间隔额外的毫秒数
    GsTimeSpan(long seconds, long microseconds);

    /// @brief 构造
    /// @param days 间隔的天数
    /// @param hours 额外的小时数
    /// @param minutes 额外的分钟数
    /// @param seconds 额外的秒数
    /// @param microSeconds 额外的毫秒数
    GsTimeSpan(int days, int hours, int minutes, int seconds, int microSeconds);

    /// @brief 拷贝构造
    /// @param timespan
    GsTimeSpan(const GsTimeSpan &rhs);

    /// @brief 由C++11 chrono 库函数构造
    /// @tparam T
    /// @tparam Period
    /// @param time
    template<class T, class Period>
    explicit GsTimeSpan(const std::chrono::duration<T, Period> &time)
        : TimeSpan(std::chrono::duration_cast<std::chrono::microseconds(time).count()>)
    {
    }

    /// @brief 默认析构
    ~GsTimeSpan();

    /// @brief 赋值复制构造
    /// @param timespan
    /// @return
    GsTimeSpan &operator=(const GsTimeSpan &rhs);

    /// @brief 赋值复制构造
    /// @param microseconds
    /// @return
    GsTimeSpan &operator=(long long microseconds);

    /// @brief
    /// @param days
    /// @param hours
    /// @param minutes
    /// @param seconds
    /// @param microSeconds
    /// @return
    GsTimeSpan &Assign(int days, int hours, int minutes, int seconds, int microSeconds);
    /// @brief
    /// @param seconds
    /// @param microseconds
    /// @return
    GsTimeSpan &Assign(long seconds, long microseconds);
    /// @brief
    /// @tparam T
    /// @tparam Period
    /// @param timr
    /// @return
    template<class T, class Period>
    GsTimeSpan &Assign(const std::chrono::duration<T, Period> &time)
    {
        TimeSpan = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
        return *this;
    }

    /// @brief 交换
    /// @param timespan
    void Swap(GsTimeSpan &timespan) noexcept;

    /// @brief 重载==运算符
    /// @param timespan
    /// @return
    bool operator==(const GsTimeSpan &rhs) const;
    /// @brief 重载!=运算符
    /// @param timespan
    /// @return
    bool operator!=(const GsTimeSpan &rhs) const;
    /// @brief 重载>运算符
    /// @param timespan
    /// @return
    bool operator>(const GsTimeSpan &rhs) const;
    /// @brief 重载>=运算符
    /// @param timespan
    /// @return
    bool operator>=(const GsTimeSpan &rhs) const;
    /// @brief 重载<运算符
    /// @param timespan
    /// @return
    bool operator<(const GsTimeSpan &rhs) const;
    /// @brief 重载<=运算符
    /// @param timespan
    /// @return
    bool operator<=(const GsTimeSpan &rhs) const;

    /// @brief 重载==运算符
    /// @param microSeconds
    /// @return
    bool operator==(long long microSeconds) const;
    /// @brief 重载!=运算符
    /// @param microSeconds
    /// @return
    bool operator!=(long long microSeconds) const;
    /// @brief 重载>运算符
    /// @param microSeconds
    /// @return
    bool operator>(long long microSeconds) const;
    /// @brief 重载>=运算符
    /// @param microSeconds
    /// @return
    bool operator>=(long long microSeconds) const;
    /// @brief 重载<运算符
    /// @param microSeconds
    /// @return
    bool operator<(long long microSeconds) const;
    /// @brief 重载<=运算符
    /// @param microSeconds
    /// @return
    bool operator<=(long long microSeconds) const;

    /// @brief 重载+运算符
    /// @param timespan
    /// @return
    GsTimeSpan operator+(const GsTimeSpan &rhs) const;
    /// @brief 重载-运算符
    /// @param timespan
    /// @return
    GsTimeSpan operator-(const GsTimeSpan &rhs) const;
    /// @brief 重载+=运算符
    /// @param timespan
    /// @return
    GsTimeSpan &operator+=(const GsTimeSpan &rhs);
    /// @brief 重载-=运算符
    /// @param timespan
    /// @return
    GsTimeSpan &operator-=(const GsTimeSpan &rhs);

    /// @brief 重载+运算符
    /// @param microSeconds
    /// @return
    GsTimeSpan operator+(long long microSeconds) const;
    /// @brief 重载-运算符
    /// @param microSeconds
    /// @return
    GsTimeSpan operator-(long long microSeconds) const;
    /// @brief 重载+=运算符
    /// @param microSeconds
    /// @return
    GsTimeSpan &operator+=(long long microSeconds);
    /// @brief 重载-=运算符
    /// @param microSeconds
    /// @return
    GsTimeSpan &operator-=(long long microSeconds);

    /// @brief 返回天数
    /// @return
    int Days() const;
    /// @brief 返回小时数 [0,23]
    /// @return
    int Hours() const;
    /// @brief 返回总的小时数
    /// @return
    int TotalHours() const;
    /// @brief 返回分钟数 [0,59]
    /// @return
    int Minutes() const;
    /// @brief 返回总的分钟数
    /// @return
    int TotalMinutes() const;
    /// @brief 返回秒数 [0,59]
    /// @return
    int Seconds() const;
    /// @brief 返回总的秒数
    /// @return
    int TotalSeconds() const;
    /// @brief 返回毫秒数 [0,999]
    /// @return
    int Milliseconds() const;
    /// @brief 返回总的毫秒数
    /// @return
    long long TotalMilliseconds() const;
    /// @brief 返回毫秒的小数 [0,999]
    /// @return
    int Microseconds() const;
    /// @brief 以微秒 [0,999999]（为单位返回秒的分数
    /// @return
    int Useconds() const;
    /// @brief 返回总的微秒数
    /// @return
    long long TotalMicroseconds() const;
};


/**
 * @brief 时间戳对象
 * @details https://www.unixtimestamp.com/
 * The unix time stamp is a way to track time as a running total of seconds.
 * This count starts at the Unix Epoch on January 1st, 1970 at UTC.
 * Therefore, the unix time stamp is merely the number of seconds between a particular
 * date and the Unix Epoch. It should also be pointed out (thanks to the comments from visitors to this site)
 * that this point in time technically does not change no matter where you are located on the globe.
 * This is very useful to computer systems for tracking and sorting dated information in dynamic
 * and distributed applications both online and client side.
*/
struct M2_API GsTimestamp
{
    /// @brief 时间戳
    long long Timestamp;

    /// @brief 时间戳最小值
    constexpr static long long TimestampMinimumValue = LLONG_MIN;
    /// @brief 时间戳最大值
    constexpr static long long TimestampMaximumValue = LLONG_MAX;

    /// @brief 默认构造
    GsTimestamp();
    /// @brief
    /// @param tv
    explicit GsTimestamp(long long tv);
    /// @brief 拷贝构造
    /// @param rhs
    GsTimestamp(const GsTimestamp &rhs);
    ~GsTimestamp();
    /// @brief 赋值复制构造
    /// @param rhs
    /// @return
    GsTimestamp &operator=(const GsTimestamp &rhs);
    /// @brief 赋值复制构造
    /// @param timestamp
    /// @return
    GsTimestamp &operator=(long long timestamp);
    /// @brief 交换时间戳
    /// @param timestamp
    void Swap(GsTimestamp &timestamp) noexcept;

    /// @brief 使用当前时间更新时间戳
    void Update();

    /// @brief 重载==运算符
    /// @param timestamp
    /// @return
    bool operator==(const GsTimestamp &timestamp) const;
    /// @brief 重载!=运算符
    /// @param timestamp
    /// @return
    bool operator!=(const GsTimestamp &timestamp) const;
    /// @brief 重载>运算符
    /// @param timestamp
    /// @return
    bool operator>(const GsTimestamp &timestamp) const;
    /// @brief 重载>=运算符
    /// @param timestamp
    /// @return
    bool operator>=(const GsTimestamp &timestamp) const;
    /// @brief 重载<运算符
    /// @param timestamp
    /// @return
    bool operator<(const GsTimestamp &timestamp) const;
    /// @brief 重载<=运算符
    /// @param timestamp
    /// @return
    bool operator<=(const GsTimestamp &timestamp) const;

    /// @brief 重载+运算符
    /// @param duration
    /// @return
    GsTimestamp operator+(long long duration) const;
    GsTimestamp operator+(const GsTimeSpan &rhs) const;
    /// @brief 重载-运算符
    /// @param duration
    /// @return
    GsTimestamp operator-(long long duration) const;
    GsTimestamp operator-(const GsTimeSpan &rhs) const;
    long long operator-(const GsTimestamp &timestamp) const;
    /// @brief 重载+=运算符
    /// @param duration
    /// @return
    GsTimestamp &operator+=(long long duration);
    GsTimestamp &operator+=(const GsTimeSpan &rhs);
    /// @brief 重载-=运算符
    /// @param duration
    /// @return
    GsTimestamp &operator-=(long long duration);
    GsTimestamp &operator-=(const GsTimeSpan &rhs);

    /// @brief 返回以time_t表示的时间戳
    /// @details time_t基准时间是从1970.1.1，单位是秒
    std::time_t EpochTime() const;

    /// @brief 返回以UTC时间表示的时间戳
    /// @details UTC基准时间是1582年10月15日午夜。分辨率为100纳秒
    long long UTCTime() const;

    /// @brief 返回自1970年1月1日午夜Unix纪元以来的时间戳（以微秒为单位）
    /// @return
    long long EpochMicroseconds() const;

    /// @brief 返回自时间戳表示的时间以来经过的时间
    long long Elapsed() const;
    /// @brief 如果从时间戳表示的时间起经过了给定的时间间隔，则返回true
    bool IsElapsed(long long interval) const;
    /// @brief 返回自1970年1月1日午夜Unix纪元以来的时间戳（以微秒为单位）
    long long Raw() const;

    /// @brief 从time_t构造
    /// @param t
    /// @return
    static GsTimestamp FromEpochTime(std::time_t t);
    /// @brief 从UTC时间构造
    /// @param utc
    /// @return
    static GsTimestamp FromUTCTime(long long utc);

    /// @brief 返回以每秒为单位的分辨率。
    /// @details 由于时间戳具有微秒分辨率，返回的值总是1000000。
    /// @return
    static long long Resolution();
};


/// @brief 月份
enum GsMonth
{
    /// @brief 一月
    eJanuary = 1,
    /// @brief 二月
    eFebruary,
    /// @brief 三月
    eMarch,
    /// @brief 四月
    eApril,
    /// @brief 五月
    eMay,
    /// @brief 六月
    eJune,
    /// @brief 七月
    eJuly,
    /// @brief 八月
    eAugust,
    /// @brief 九月
    eSeptember,
    /// @brief 十月
    eOctober,
    /// @brief 十一月
    eNovember,
    /// @brief 十二月
    eDecember
};


/// @brief 星期
enum GsWeekDay
{
    /// @brief 星期天
    eSunday,
    /// @brief 星期一
    eMonday,
    /// @brief 星期二
    eTuesday,
    /// @brief 星期三
    eWednesday,
    /// @brief 星期四
    eThursday,
    /// @brief 星期五
    eFriday,
    /// @brief 星期六
    eSaturday,
};


/// @brief 默认的标准化的日期格式化样式
enum GsDateTimeFormat
{
    /// @brief ISO8601标准
    /// @details https://www.ionos.com/digitalguide/websites/web-development/iso-8601/
    /// @example 2019-09-07T15:50+00Z Likewise, 3:30 pm on September 7, 2019 in the time zone of universal time with the addition of “Z” in the notation
    eISO8601_FORMAT,
    /// @brief ISO8601标准，以秒为单位
    /// @example 2023-07-21T12:00:00.000000Z
    eISO8601_FRAC_FORMAT,

    /// @brief
    /// @details https://www.w3.org/Protocols/rfc822/
    eRFC822_FORMAT,
    /// @brief
    /// @details https://wiki.freepascal.org/RFC_1123_Time_Format
    eRFC1123_FORMAT,

    /// @brief
    /// @details https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Date
    eHTTP_FORMAT,

    /// @brief
    /// @details https://datatracker.ietf.org/doc/html/rfc850
    eRFC850_FORMAT,
    /// @brief
    /// @details https://www.rfc-editor.org/rfc/rfc1036
    eRFC1036_FORMAT,

    /// @brief
    /// @details https://cplusplus.com/reference/ctime/asctime/
    eASCTIME_FORMAT,

    /// @brief
    /// @details https://learn.microsoft.com/en-us/dotnet/standard/base-types/standard-date-and-time-format-strings
    eSORTABLE_FORMAT,
};


/**
 * @brief 时间
 * @details 此类表示时间上的瞬间，以格里高利日历为单位，以年、月、日、小时、分钟、秒和毫秒表示。
 * 该类主要用于UTC、儒略日和公历日期之间的转换。
 * DateTime中存储的日期和时间始终以UTC（协调世界时）为单位，因此与系统上有效的时区无关。
 * 转换计算基于Peter Baum在http://vsg.cape.com/~pbaum/date/date0.htm
 * 在内部，由于性能原因，此类以两种形式（UTC和细分）存储日期/时间。仅将此类用于日期/时间表示之间的转换。
 * 对其他所有内容都使用Timestamp类。
 *
 * @note
 *   * 零是有效年份（根据ISO 8601和天文年份编号）
 *   * 零（0）年是闰年
 *   * 不支持负年份（公元前1年之前的年份）
 * http://en.wikipedia.org/wiki/Gregorian_Calendar
 * http://en.wikipedia.org/wiki/Julian_day
 * http://en.wikipedia.org/wiki/UTC
 * http://en.wikipedia.org/wiki/ISO_8601
 */
class M2_API GsDateTime
{
public:
    enum
    {
        UTC = 0xFFFF/// Special value for timeZoneDifferential denoting UTC.
    };

public:
    /// @brief 默认构造
    /// @return
    GsDateTime();
    /// @brief 根据tm结构体构造
    /// @param _tm
    explicit GsDateTime(const tm &_tm);
    /// @brief 根据时间戳构造
    /// @param timestamp
    explicit GsDateTime(const GsTimestamp &timestamp);
    /// @brief 根据传入的时间构造
    /// @param year [0,9999]
    /// @param month [1,12]
    /// @param day [1,31]
    /// @param hour [0,23]
    /// @param minute [0,59]
    /// @param second [0,60]
    /// @param millisecond [0,999]
    /// @param microsecond [0,999]
    GsDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

    /// @brief 根据一个UTC时间和相对这个时间的偏移量构造
    /// @param utcTime
    /// @param diff
    GsDateTime(long long utcTime, long long diff);
    /// @brief 移动构造
    /// @param dateTime
    GsDateTime(const GsDateTime &dateTime);
    ~GsDateTime();

    GsDateTime &operator=(const GsDateTime &dateTime);
    GsDateTime &operator=(const GsTimestamp &timestamp);
    GsDateTime &Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);
    void Swap(GsDateTime &dateTime) noexcept;

    /// @brief 返回年
    /// @return
    int Year() const;
    /// @brief 返回月
    /// @return
    int Month() const;
    /// @brief 返回一年中的周数
    /// @param firstDayOfWeek 只能是星期一或者星期天，一周的起始方式不同，得到的结果不同
    /// @return
    int Week(int firstDayOfWeek = eMonday) const;
    /// @brief 返回天
    /// @return
    int Day() const;
    /// @brief 返回星期
    /// @return
    int DayOfWeek() const;
    /// @brief 返回一年的第几天
    /// @return
    int DayOfYear() const;
    /// @brief 返回小时 [0,23]
    /// @return
    int Hour() const;
    /// @brief 返回小时 [0,12]
    /// @return
    int HourAMPM() const;
    /// @brief 是否是上午
    /// @return
    bool AM() const;
    /// @brief 是否是下午
    /// @return
    bool PM() const;
    /// @brief 返回分钟数
    /// @return
    int Minute() const;
    /// @brief 返回秒数
    /// @return
    int Second() const;
    /// @brief 返回毫秒数
    /// @return
    int Millisecond() const;
    /// @brief 返回微秒数
    /// @return
    int Microsecond() const;
    /// @brief 儒略日
    /// @return
    double JulianDay() const;
    /// @brief 获取当前时间的时间戳
    /// @return
    GsTimestamp Timestamp() const;
    /// @brief 获取UTC时间
    /// @return
    long long UTCTime() const;
    /// @brief 根据时区，将UTC时间转换为本地时间
    /// @return
    GsDateTime ToLocal() const;

    bool operator==(const GsDateTime &dateTime) const;
    bool operator!=(const GsDateTime &dateTime) const;
    bool operator<(const GsDateTime &dateTime) const;
    bool operator<=(const GsDateTime &dateTime) const;
    bool operator>(const GsDateTime &dateTime) const;
    bool operator>=(const GsDateTime &dateTime) const;

    GsDateTime operator+(const GsTimeSpan &span) const;
    GsDateTime operator-(const GsTimeSpan &span) const;
    GsTimeSpan operator-(const GsDateTime &dateTime) const;
    GsDateTime &operator+=(const GsTimeSpan &span);
    GsDateTime &operator-=(const GsTimeSpan &span);

    /// @brief 通过应用给定的时区差，将本地时间转换为UTC
    /// @param tzd
    void MakeUTC(int tzd);
    /// @brief 通过应用给定的时区差，将UTC时间转换为本地时间
    /// @param tzd
    void MakeLocal(int tzd);
    /// @brief 判断是否是闰年
    /// @param year
    /// @return
    static bool IsLeapYear(int year);
    /// @brief 返回给定月份和年份中的天数
    /// @param year
    /// @param month
    /// @return
    static int DaysOfMonth(int year, int month);
    /// @brief 判断日期是否合法
    /// @param year
    /// @param month
    /// @param day
    /// @param hour
    /// @param minute
    /// @param second
    /// @param millisecond
    /// @param microsecond
    /// @return
    static bool IsValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
    /// @brief UTC时间转儒略日
    /// @param utcTime
    /// @return
    static double ToJulianDay(long long utcTime);
    /// @brief 计算公历日期和时间的儒略日
    /// @param year
    /// @param month
    /// @param day
    /// @param hour
    /// @param minute
    /// @param second
    /// @param millisecond
    /// @param microsecond
    /// @return
    static double ToJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
    /// @brief 儒略日转UTC时间
    /// @param julianDay
    /// @return
    static long long ToUTCTime(double julianDay);
    /// @brief 计算给定儒略日的公历日期
    /// @param julianDay
    void ComputeGregorian(double julianDay);
    /// @brief 从UTC时间中提取信息
    void ComputeDaytime();


    /// @brief 从给定字符串中以给定格式分析日期和时间
    /// @param fmt
    /// @param str
    /// @param timeZoneDifferential
    static GsDateTime Parse(const GsString &fmt, const GsString &str, int &timeZoneDifferential);
    static GsDateTime Parse(GsDateTimeFormat fmt, const GsString &str, int &timeZoneDifferential);

    /// @brief 尝试从给定字符串中以给定格式分析日期和时间
    /// @param fmt
    /// @param str
    /// @param timeZoneDifferential
    /// @return
    static bool TryParse(const GsString &fmt, const GsString &str, GsDateTime &dateTime, int &timeZoneDifferential);
    static bool TryParse(GsDateTimeFormat fmt, const GsString &str, GsDateTime &dateTime, int &timeZoneDifferential);

    /// @brief 从给定的字符串中分析日期和时间
    /// @param str
    /// @param dateTime
    /// @param timeZoneDifferential
    static GsDateTime Parse(const GsString &str, int &timeZoneDifferential);

    /// @brief 尝试从给定字符串中分析日期和时间
    /// @param str
    /// @param timeZoneDifferential
    /// @return
    static bool TryParse(const GsString &str, GsDateTime &dateTime, int &timeZoneDifferential);

    /// @brief
    /// @details 参考strftime
    /// http://www.cplusplus.com/reference/ctime/strftime/
    //%a 星期几的简写
    //%A 星期几的全称
    //%b 月份的简写
    //%B 月份的全称
    //%c 标准的日期的时间串
    //%C 年份的前两位数字
    //%d 十进制表示的每月的第几天
    //%D 月/天/年
    //%e 在两字符域中，十进制表示的每月的第几天
    //%F 年-月-日
    //%g 年份的后两位数字，使用基于周的年
    //%G 年份，使用基于周的年
    //%h 简写的月份名
    //%H 24小时制的小时
    //%I 12小时制的小时
    //%j 十进制表示的每年的第几天
    //%m 十进制表示的月份
    //%M 十时制表示的分钟数
    //%n 新行符
    //%p 本地的AM或PM的等价显示
    //%r 12小时的时间
    //%R 显示小时和分钟：hh:mm
    //%S 十进制的秒数
    //%t 水平制表符
    //%T 显示时分秒：hh:mm:ss
    //%u 每周的第几天，星期一为第一天 （值从1到7，星期一为1）
    //%U 第年的第几周，把星期日作为第一天（值从0到53）
    //%V 每年的第几周，使用基于周的年
    //%w 十进制表示的星期几（值从0到6，星期天为0）
    //%W 每年的第几周，把星期一做为第一天（值从0到53）
    //%x 标准的日期串
    //%X 标准的时间串
    //%y 不带世纪的十进制年份（值从0到99）
    //%Y 带世纪部分的十制年份
    //%z，%Z 时区名称，如果不能得到时区名称则返回空字符。
    //%% 百分号
    /// @param dateTime
    /// @param fmt
    /// @param timeZoneDifferential
    /// @return
    static GsString ToString(const GsDateTime &dateTime, const GsString &fmt, int timeZoneDifferential = UTC);

    /// @brief 根据给定的格式格式化给定的时间戳
    /// @param timestamp
    /// @param fmt
    /// @param timeZoneDifferential
    /// @return
    static GsString ToString(const GsTimestamp &timestamp, const GsString &fmt, int timeZoneDifferential = UTC);

    /// @brief
    /// @param rhs
    /// @param fmt
    /// @return
    static GsString ToString(const GsTimeSpan &rhs, const GsString &fmt = "%dd %H:%M:%S.%i");

    /// @brief 当前cpu时钟周期
    static unsigned long long TickCount();

private:
    void CheckLimit(short &lower, short &higher, short limit);
    void Normalize();
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


/// @brief 时区
class M2_API GsTimeZone
{
public:
    /// @brief 返回本地时间到UTC的偏移量（以秒为单位）
    /// @return
    static int UTCOffset();

    /// @brief 如果正在使用夏令时，则返回夏令时偏移量（以秒为单位）
    /// @return
    static int DST();

    /// @brief 如果给定时间正在使用夏令时，则返回夏令时偏移量（以秒为单位）
    /// @param timestamp
    /// @return
    static int DST(const GsTimestamp &timestamp);

    /// @brief 如果夏令时在给定时间内有效，则返回true
    /// @details 根据操作系统平台的不同，这可能只适用于某些日期范围，因为使用了C库的localtime（）函数
    /// @param timestamp
    /// @return
    static bool IsDST(const GsTimestamp &timestamp);

    /// @brief 返回当前时区的时区差异
    /// @return
    static int TimeZoneDifferential();

    /// @brief 返回当前有效的时区名称
    /// @return
    static GsString Name();

    /// @brief 如果夏令时未生效，则返回时区名称
    /// @return
    static GsString StandardName();

    /// @brief 如果夏令时生效，则返回时区名称
    /// @return
    static GsString DSTName();
};


/// @brief 时钟
class M2_API GsClock
{
public:
    /// @brief 默认构造
    GsClock();
    /// @brief 根据毫秒构造
    /// @param c
    explicit GsClock(long long c);
    /// @brief 拷贝构造
    /// @param other
    GsClock(const GsClock &other);
    /// @brief 析构
    ~GsClock();

    /// @brief 赋值复制构造
    /// @param other
    /// @return
    GsClock &operator=(const GsClock &other);
    /// @brief 根据毫秒赋值构造
    /// @param tv
    /// @return
    GsClock &operator=(long long tv);
    /// @brief 交换两个时钟
    /// @param clock
    void Swap(GsClock &clock) noexcept;
    /// @brief 更新时钟到当前系统时钟
    void Update();

    bool operator==(const GsClock &rhs) const;
    bool operator!=(const GsClock &rhs) const;
    bool operator>(const GsClock &rhs) const;
    bool operator>=(const GsClock &rhs) const;
    bool operator<(const GsClock &rhs) const;
    bool operator<=(const GsClock &rhs) const;
    GsClock operator+(long long d) const;
    GsClock operator-(long long d) const;
    long long operator-(const GsClock &rhs) const;
    GsClock &operator+=(long long d);
    GsClock &operator-=(long long d);

    /// @brief 返回自系统特定epoch时间
    /// @return
    long long Microseconds() const;
    /// @brief 与 Microseconds 相同
    /// @return
    long long Raw() const;

    /// @brief 返回时钟经历的毫秒数
    /// @return
    long long Elapsed() const;

    /// @brief 判断时钟是否已经经过了输入的时间间隔
    /// @param interval
    /// @return
    bool IsElapsed(long long interval) const;

    /// @brief 时钟分辨率
    /// @return
    static long long Resolution();

    /// @brief 微秒为单位返回系统的时钟精度
    /// @return
    static long long Accuracy();

    /// @brief 判断时钟是否单调
    /// @return
    static bool Monotonic();

private:
    long long m_nClock;
};


}// namespace m2
