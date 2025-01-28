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

#pragma once

#include <chrono>
#include <cpl_exports.h>
#include <ctime>

namespace CPL {

class TimeSpan;

/// \class Timestamp
/// \brief Represents a monotonic UTC-based timestamp with microsecond resolution.
///
/// A `Timestamp` stores a monotonic time value with theoretical microseconds resolution.
/// Timestamps are UTC-based and independent of the system's timezone.
/// They support arithmetic operations and comparisons. The base time for `Timestamp`
/// is the Unix epoch: midnight, January 1, 1970.
///
/// Note: Timestamps are only monotonic as long as the system clock is monotonic and not
/// adjusted (e.g., due to time synchronization).
///
/// Additional UTC time values are represented with a different base time:
/// midnight, October 15, 1582, with 100-nanosecond resolution.
class CPL_API Timestamp
{
public:
    /// \brief Represents monotonic UTC time in microsecond resolution.
    /// Base time: midnight, January 1, 1970.
    using TimeVal = std::int64_t;

    /// \brief Represents monotonic UTC time in 100-nanosecond resolution.
    /// Base time: midnight, October 15, 1582.
    using UtcTimeVal = std::int64_t;

    /// \brief Represents the difference between two `TimeVal` values in microseconds.
    using TimeDiff = std::int64_t;

    static const TimeVal TIMEVAL_MIN;///< Minimum timestamp value.
    static const TimeVal TIMEVAL_MAX;///< Maximum timestamp value.

    /// \brief Creates a timestamp initialized with the current time.
    Timestamp();

    /// \brief Creates a timestamp from the given time value.
    /// \param tv Time value in microseconds since midnight, January 1, 1970.
    Timestamp(TimeVal tv);

    /// \brief Copy constructor.
    Timestamp(const Timestamp &other);

    /// \brief Destroys the timestamp.
    ~Timestamp();

    /// \brief Assigns another timestamp to this timestamp.
    Timestamp &operator=(const Timestamp &other);

    /// \brief Assigns a time value to this timestamp.
    /// \param tv Time value in microseconds since midnight, January 1, 1970.
    Timestamp &operator=(TimeVal tv);

    /// \brief Swaps the contents of this timestamp with another timestamp.
    void Swap(Timestamp &timestamp) noexcept;

    /// \brief Updates the timestamp with the current time.
    void Update();

    /// \brief Checks if two timestamps are equal.
    bool operator==(const Timestamp &ts) const;

    /// \brief Checks if two timestamps are not equal.
    bool operator!=(const Timestamp &ts) const;

    /// \brief Checks if this timestamp is greater than another timestamp.
    bool operator>(const Timestamp &ts) const;

    /// \brief Checks if this timestamp is greater than or equal to another timestamp.
    bool operator>=(const Timestamp &ts) const;

    /// \brief Checks if this timestamp is less than another timestamp.
    bool operator<(const Timestamp &ts) const;

    /// \brief Checks if this timestamp is less than or equal to another timestamp.
    bool operator<=(const Timestamp &ts) const;

    /// \brief Returns a new timestamp offset by a given time difference.
    /// \param d Time difference in microseconds.
    Timestamp operator+(TimeDiff d) const;

    /// \brief Returns a new timestamp offset by a given timespan.
    Timestamp operator+(const TimeSpan &span) const;

    /// \brief Returns a new timestamp offset by a negative time difference.
    Timestamp operator-(TimeDiff d) const;

    /// \brief Returns a new timestamp offset by a negative timespan.
    Timestamp operator-(const TimeSpan &span) const;

    /// \brief Calculates the difference between two timestamps in microseconds.
    TimeDiff operator-(const Timestamp &ts) const;

    /// \brief Adds a time difference to this timestamp.
    Timestamp &operator+=(TimeDiff d);

    /// \brief Adds a timespan to this timestamp.
    Timestamp &operator+=(const TimeSpan &span);

    /// \brief Subtracts a time difference from this timestamp.
    Timestamp &operator-=(TimeDiff d);

    /// \brief Subtracts a timespan from this timestamp.
    Timestamp &operator-=(const TimeSpan &span);

    /// \brief Returns the timestamp as a `time_t` value.
    /// \details The `time_t` value represents seconds since midnight, January 1, 1970.
    std::time_t EpochTime() const;

    /// \brief Returns the timestamp as a UTC-based time value.
    /// \details The UTC time value is in 100-nanosecond intervals since midnight,
    /// October 15, 1582.
    UtcTimeVal UtcTime() const;

    /// \brief Returns the timestamp in microseconds since midnight, January 1, 1970.
    TimeVal EpochMicroseconds() const;

    /// \brief Returns the time elapsed since the timestamp.
    /// \details Equivalent to `Timestamp() - *this`.
    TimeDiff Elapsed() const;

    /// \brief Checks if a given time interval has passed since the timestamp.
    bool IsElapsed(TimeDiff interval) const;

    /// \brief Returns the raw time value in microseconds.
    /// \details Equivalent to `epochMicroseconds()`.
    TimeVal Raw() const;

    /// \brief Creates a timestamp from a `std::time_t` value.
    static Timestamp FromEpochTime(std::time_t t);

    /// \brief Creates a timestamp from a UTC-based time value.
    /// \param val Time value in 100-nanosecond intervals since midnight, October 15, 1582.
    static Timestamp FromUtcTime(UtcTimeVal val);

    /// \brief Returns the resolution in units per second.
    /// \details Since timestamps have microsecond resolution, the value is always 1,000,000.
    static constexpr TimeDiff Resolution();

#if defined(_WIN32)
    /// \brief Creates a timestamp from a Windows FILETIME structure.
    static Timestamp FromFileTimeNP(std::uint32_t fileTimeLow,
                                    std::uint32_t fileTimeHigh);

    /// \brief Converts the timestamp to a Windows FILETIME structure.
    void ToFileTimeNP(std::uint32_t &fileTimeLow,
                      std::uint32_t &fileTimeHigh) const;
#endif

private:
    TimeVal _ts;///< Stores the timestamp value in microseconds.
};

/// A class that represents time spans up to microsecond resolution.
class CPL_API TimeSpan
{
public:
    using TimeDiff = Timestamp::TimeDiff;

    /// Creates a zero TimeSpan.
    TimeSpan();

    /// Creates a TimeSpan from a specified number of microseconds.
    TimeSpan(TimeDiff microseconds);

    /// Creates a TimeSpan from seconds and microseconds.
    /// Useful for creating a TimeSpan from a struct timeval.
    TimeSpan(long seconds, long microseconds);

    /// Creates a TimeSpan from days, hours, minutes, seconds, and microseconds.
    TimeSpan(int days, int hours, int minutes, int seconds, int microSeconds);

    /// Creates a copy of another TimeSpan.
    TimeSpan(const TimeSpan &timespan);

    /// Creates a TimeSpan from a std::chrono::duration.
    /// This constructor allows creating a TimeSpan from any chrono duration.
    template<class T, class Period>
    TimeSpan(const std::chrono::duration<T, Period> &dtime)
        : _span(std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count())
    {
    }

    /// Destroys the TimeSpan object.
    ~TimeSpan();

    /// Assignment operator. Copies the value from another TimeSpan.
    TimeSpan &operator=(const TimeSpan &timespan);

    /// Assignment operator. Assigns from a number of microseconds.
    TimeSpan &operator=(TimeDiff microseconds);

    /// Assigns a new time span using days, hours, minutes, seconds, and microseconds.
    TimeSpan &Assign(int days, int hours, int minutes, int seconds,
                     int microSeconds);

    /// Assigns a new time span using seconds and microseconds.
    /// Useful for assigning from a struct timeval.
    TimeSpan &Assign(long seconds, long microseconds);

    /// Assigns a new time span from a std::chrono::duration.
    template<class T, class Period>
    TimeSpan &Assign(const std::chrono::duration<T, Period> &dtime)
    {
        _span = std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count();
        return *this;
    }

    /// Swaps the current TimeSpan with another one.
    void Swap(TimeSpan &timespan) noexcept;

    /// Equality operator. Compares two TimeSpan objects for equality.
    bool operator==(const TimeSpan &ts) const;

    /// Inequality operator. Compares two TimeSpan objects for inequality.
    bool operator!=(const TimeSpan &ts) const;

    /// Greater-than operator. Checks if one TimeSpan is greater than another.
    bool operator>(const TimeSpan &ts) const;

    /// Greater-than-or-equal-to operator.
    bool operator>=(const TimeSpan &ts) const;

    /// Less-than operator. Checks if one TimeSpan is less than another.
    bool operator<(const TimeSpan &ts) const;

    /// Less-than-or-equal-to operator.
    bool operator<=(const TimeSpan &ts) const;

    /// Equality operator for TimeDiff. Compares a TimeSpan with a number of microseconds.
    bool operator==(TimeDiff microSeconds) const;

    /// Inequality operator for TimeDiff.
    bool operator!=(TimeDiff microSeconds) const;

    /// Greater-than operator for TimeDiff.
    bool operator>(TimeDiff microSeconds) const;

    /// Greater-than-or-equal-to operator for TimeDiff.
    bool operator>=(TimeDiff microSeconds) const;

    /// Less-than operator for TimeDiff.
    bool operator<(TimeDiff microSeconds) const;

    /// Less-than-or-equal-to operator for TimeDiff.
    bool operator<=(TimeDiff microSeconds) const;

    /// Addition operator. Adds two TimeSpan objects.
    TimeSpan operator+(const TimeSpan &d) const;

    /// Subtraction operator. Subtracts one TimeSpan from another.
    TimeSpan operator-(const TimeSpan &d) const;

    /// Addition assignment operator. Adds a TimeSpan to the current one.
    TimeSpan &operator+=(const TimeSpan &d);

    /// Subtraction assignment operator. Subtracts a TimeSpan from the current one.
    TimeSpan &operator-=(const TimeSpan &d);

    /// Addition operator with TimeDiff. Adds a number of microseconds to the current TimeSpan.
    TimeSpan operator+(TimeDiff microSeconds) const;

    /// Subtraction operator with TimeDiff. Subtracts a number of microseconds from the current TimeSpan.
    TimeSpan operator-(TimeDiff microSeconds) const;

    /// Addition assignment operator with TimeDiff.
    TimeSpan &operator+=(TimeDiff microSeconds);

    /// Subtraction assignment operator with TimeDiff.
    TimeSpan &operator-=(TimeDiff microSeconds);

    /// Returns the number of days in the TimeSpan.
    int Days() const;

    /// Returns the number of hours (0 to 23) in the TimeSpan.
    int Hours() const;

    /// Returns the total number of hours in the TimeSpan, including overflowed days.
    int TotalHours() const;

    /// Returns the number of minutes (0 to 59) in the TimeSpan.
    int Minutes() const;

    /// Returns the total number of minutes in the TimeSpan, including overflowed hours.
    int TotalMinutes() const;

    /// Returns the number of seconds (0 to 59) in the TimeSpan.
    int Seconds() const;

    /// Returns the total number of seconds in the TimeSpan, including overflowed minutes.
    int TotalSeconds() const;

    /// Returns the number of milliseconds (0 to 999) in the TimeSpan.
    int Milliseconds() const;

    /// Returns the total number of milliseconds in the TimeSpan.
    TimeDiff TotalMilliseconds() const;

    /// Returns the number of microseconds (0 to 999) in the TimeSpan.
    int Microseconds() const;

    /// Returns the fractions of a second in microseconds (0 to 999999).
    int Useconds() const;

    /// Returns the total number of microseconds in the TimeSpan.
    TimeDiff TotalMicroseconds() const;

    /// The number of microseconds in a millisecond.
    static const TimeDiff MILLISECONDS;

    /// The number of microseconds in a second.
    static const TimeDiff SECONDS;

    /// The number of microseconds in a minute.
    static const TimeDiff MINUTES;

    /// The number of microseconds in an hour.
    static const TimeDiff HOURS;

    /// The number of microseconds in a day.
    static const TimeDiff DAYS;

private:
    TimeDiff _span;
};

/// This class represents an instant in time, expressed
/// in years, months, days, hours, minutes, seconds,
/// and milliseconds based on the Gregorian calendar.
///
/// The class is mainly useful for conversions between
/// UTC, Julian day, and Gregorian calendar dates.
///
/// The date and time stored in a DateTime instance are
/// always in UTC (Coordinated Universal Time), ensuring
/// independence from the system's timezone settings.
///
/// Conversion calculations are based on algorithms
/// described by Peter Baum. Refer to:
/// http://vsg.cape.com/~pbaum/date/date0.htm for details.
///
/// Internally, the class optimizes performance by storing
/// the date and time in two forms (UTC and broken down).
/// It is recommended to use this class only for date/time
/// representation conversions. Use the `Timestamp` class
/// for general time-related functionalities.
///
/// Key Notes:
/// * Year zero (0) is valid and follows ISO 8601 and
///   astronomical year numbering conventions.
/// * Year zero is a leap year.
/// * Minimum representable date/time: 12:00:00 UTC Monday,
///   1 January 4713 BC (Julian Day 0, Gregorian -4713-11-24).
///
/// Further reading:
///   * Gregorian Calendar: http://en.wikipedia.org/wiki/Gregorian_Calendar
///   * Julian Day: http://en.wikipedia.org/wiki/Julian_day
///   * UTC: http://en.wikipedia.org/wiki/UTC
///   * ISO 8601: http://en.wikipedia.org/wiki/ISO_8601
class CPL_API DateTime
{
public:
    enum Months
    /// Enumeration for symbolic names of months (1 to 12).
    {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    enum DaysOfWeek
    /// Enumeration for symbolic names of weekdays (0 to 6).
    {
        SUNDAY = 0,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    };

    DateTime();
    /// Default constructor: Creates a DateTime instance for the current date and time.

    DateTime(const tm &tmStruct);
    /// Creates a DateTime instance from a standard `tm` struct.

    DateTime(const Timestamp &timestamp);
    /// Initializes a DateTime instance based on a given Timestamp.

    DateTime(int year, int month, int day, int hour = 0, int minute = 0,
             int second = 0, int millisecond = 0, int microsecond = 0);
    /// Creates a DateTime instance using the specified Gregorian date and time components.
    ///
    /// Parameters:
    /// * `year`: Valid range [0, 9999].
    /// * `month`: Valid range [1, 12].
    /// * `day`: Valid range [1, 31].
    /// * `hour`: Valid range [0, 23].
    /// * `minute`: Valid range [0, 59].
    /// * `second`: Valid range [0, 60] (to account for leap seconds).
    /// * `millisecond`: Valid range [0, 999].
    /// * `microsecond`: Valid range [0, 999].
    ///
    /// Throws an InvalidArgumentException if the arguments are out of valid ranges.

    DateTime(double julianDay);
    /// Constructs a DateTime instance based on a Julian day.

    DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff);
    /// Creates a DateTime instance using a UTC-based time value and a time difference.
    /// Used internally by DateTime and related classes.

    DateTime(const DateTime &dateTime);
    /// Copy constructor: Initializes a DateTime instance from another DateTime.

    ~DateTime();
    /// Destructor: Cleans up resources associated with the DateTime instance.

    DateTime &operator=(const DateTime &dateTime);
    /// Overloads the assignment operator for DateTime.

    DateTime &operator=(const Timestamp &timestamp);
    /// Assigns a Timestamp to the DateTime instance.

    DateTime &operator=(double julianDay);
    /// Assigns a Julian day to the DateTime instance.

    DateTime &Assign(int year, int month, int day, int hour = 0, int minute = 0,
                     int second = 0, int millisecond = 0, int microsecond = 0);
    /// Assigns a Gregorian date and time to the instance. Similar to the parameterized constructor.

    void Swap(DateTime &dateTime) noexcept;
    /// Efficiently swaps the contents of two DateTime instances.

    // Accessor methods for year, month, day, and time components
    int Year() const;
    /// Gets the year component.

    int Month() const;
    /// Gets the month (1~12).

    int Week(int firstDayOfWeek = MONDAY) const;
    /// Gets the ISO 8601 week number.

    int Day() const;
    /// Gets the day of the month (1~31).

    int DayOfWeek() const;
    /// Gets the weekday (0 = Sunday, ..., 6 = Saturday).

    int DayOfYear() const;
    /// Gets the day of the year (1~365/366).

    int Hour() const;
    /// Gets the hour (0~23).

    int HourAMPM() const;
    /// Gets the hour in 12-hour format.

    bool IsAM() const;
    /// Returns true if the time is before noon.

    bool IsPM() const;
    /// Returns true if the time is afternoon or later.

    int Minute() const;
    /// Gets the minute (0~59).

    int Second() const;
    /// Gets the second (0~60, accounts for leap seconds).

    int Millisecond() const;
    /// Gets the millisecond (0~999).

    int Microsecond() const;
    /// Gets the microsecond (0~999).

    double JulianDay() const;
    /// Converts to a Julian day.

    Timestamp Timestamp() const;
    /// Converts the DateTime to a Timestamp.

    Timestamp::UtcTimeVal UtcTime() const;
    /// Converts the DateTime to UTC-based time.

    // Comparison operators
    bool operator==(const DateTime &dateTime) const;
    /// Checks if two DateTime instances are equal.

    bool operator!=(const DateTime &dateTime) const;
    /// Checks if two DateTime instances are not equal.

    bool operator<(const DateTime &dateTime) const;
    /// Checks if this DateTime instance is earlier than another.

    bool operator<=(const DateTime &dateTime) const;
    /// Checks if this DateTime instance is earlier or equal to another.

    bool operator>(const DateTime &dateTime) const;
    /// Checks if this DateTime instance is later than another.

    bool operator>=(const DateTime &dateTime) const;
    /// Checks if this DateTime instance is later or equal to another.

    // Arithmetic operators for date/time manipulation
    DateTime operator+(const TimeSpan &span) const;
    /// Adds a TimeSpan to the DateTime instance.

    DateTime operator-(const TimeSpan &span) const;
    /// Subtracts a TimeSpan from the DateTime instance.

    TimeSpan operator-(const DateTime &dateTime) const;
    /// Subtracts another DateTime from the current DateTime and returns the TimeSpan.

    DateTime &operator+=(const TimeSpan &span);
    /// Adds a TimeSpan to the current DateTime instance.

    DateTime &operator-=(const TimeSpan &span);
    /// Subtracts a TimeSpan from the current DateTime instance.

    tm MakeTM() const;
    /// Converts DateTime to a `tm` struct.

    void MakeUTC(int tzd);
    /// Converts local time to UTC using a timezone offset.

    void MakeLocal(int tzd);
    /// Converts UTC time to local time using a timezone offset.

    // Static utility methods
    static bool IsLeapYear(int year);
    /// Checks if the year is a leap year.

    static int DaysOfMonth(int year, int month);
    /// Gets the number of days in a month/year.

    static bool IsValid(int year, int month, int day, int hour = 0,
                        int minute = 0, int second = 0, int millisecond = 0,
                        int microsecond = 0);
    /// Validates a date/time.

protected:
    void CheckValid();
    /// Validates internal date/time components.

    static double ToJulianDay(Timestamp::UtcTimeVal utcTime);
    /// Converts UTC to Julian day.

    static double ToJulianDay(int year, int month, int day, int hour = 0,
                              int minute = 0, int second = 0,
                              int millisecond = 0, int microsecond = 0);
    /// Converts Gregorian to Julian.

    static Timestamp::UtcTimeVal ToUtcTime(double julianDay);
    /// Converts Julian to UTC.

    void ComputeGregorian(double julianDay);
    /// Converts Julian day to Gregorian date.

    void ComputeDaytime();
    /// Extracts hours, minutes, and seconds from UTC.

private:
    // Utility methods for internal calculations
    void CheckLimit(short &lower, short &higher, short limit);
    /// Checks if a date/time component is within valid limits.

    void Normalize();
    /// Normalizes the date/time components to ensure they are within valid ranges.

    // Internal member variables
    Timestamp::UtcTimeVal _utcTime;
    short _year;
    short _month;
    short _day;
    short _hour;
    short _minute;
    short _second;
    short _millisecond;
    short _microsecond;
};

}// namespace CPL