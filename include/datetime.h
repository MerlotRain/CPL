/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <ctime>
#include <dwg/exports.h>
#include <string>
#include <chrono>

class Timespan;

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

class LIBDWG_API Timestamp
{
public:
    using TimeVal = std::int64_t;
    /// \brief Represents monotonic UTC time in microsecond resolution.
    /// Base time: midnight, January 1, 1970.

    using UtcTimeVal = std::int64_t;
    /// \brief Represents monotonic UTC time in 100-nanosecond resolution.
    /// Base time: midnight, October 15, 1582.

    using TimeDiff = std::int64_t;
    /// \brief Represents the difference between two `TimeVal` values in microseconds.

    static const TimeVal TIMEVAL_MIN;///< Minimum timestamp value.
    static const TimeVal TIMEVAL_MAX;///< Maximum timestamp value.

    Timestamp();
    /// \brief Creates a timestamp initialized with the current time.

    Timestamp(TimeVal tv);
    /// \brief Creates a timestamp from the given time value.
    /// \param tv Time value in microseconds since midnight, January 1, 1970.

    Timestamp(const Timestamp &other);
    /// \brief Copy constructor.

    ~Timestamp();
    /// \brief Destroys the timestamp.

    Timestamp &operator=(const Timestamp &other);
    /// \brief Assigns another timestamp to this timestamp.

    Timestamp &operator=(TimeVal tv);
    /// \brief Assigns a time value to this timestamp.
    /// \param tv Time value in microseconds since midnight, January 1, 1970.

    void swap(Timestamp &timestamp) noexcept;
    /// \brief Swaps the contents of this timestamp with another timestamp.

    void update();
    /// \brief Updates the timestamp with the current time.

    bool operator==(const Timestamp &ts) const;
    /// \brief Checks if two timestamps are equal.

    bool operator!=(const Timestamp &ts) const;
    /// \brief Checks if two timestamps are not equal.

    bool operator>(const Timestamp &ts) const;
    /// \brief Checks if this timestamp is greater than another timestamp.

    bool operator>=(const Timestamp &ts) const;
    /// \brief Checks if this timestamp is greater than or equal to another timestamp.

    bool operator<(const Timestamp &ts) const;
    /// \brief Checks if this timestamp is less than another timestamp.

    bool operator<=(const Timestamp &ts) const;
    /// \brief Checks if this timestamp is less than or equal to another timestamp.

    Timestamp operator+(TimeDiff d) const;
    /// \brief Returns a new timestamp offset by a given time difference.
    /// \param d Time difference in microseconds.

    Timestamp operator+(const Timespan &span) const;
    /// \brief Returns a new timestamp offset by a given timespan.

    Timestamp operator-(TimeDiff d) const;
    /// \brief Returns a new timestamp offset by a negative time difference.

    Timestamp operator-(const Timespan &span) const;
    /// \brief Returns a new timestamp offset by a negative timespan.

    TimeDiff operator-(const Timestamp &ts) const;
    /// \brief Calculates the difference between two timestamps in microseconds.

    Timestamp &operator+=(TimeDiff d);
    /// \brief Adds a time difference to this timestamp.

    Timestamp &operator+=(const Timespan &span);
    /// \brief Adds a timespan to this timestamp.

    Timestamp &operator-=(TimeDiff d);
    /// \brief Subtracts a time difference from this timestamp.

    Timestamp &operator-=(const Timespan &span);
    /// \brief Subtracts a timespan from this timestamp.

    std::time_t epochTime() const;
    /// \brief Returns the timestamp as a `time_t` value.
    /// \details The `time_t` value represents seconds since midnight, January 1, 1970.

    UtcTimeVal utcTime() const;
    /// \brief Returns the timestamp as a UTC-based time value.
    /// \details The UTC time value is in 100-nanosecond intervals since midnight,
    /// October 15, 1582.

    TimeVal epochMicroseconds() const;
    /// \brief Returns the timestamp in microseconds since midnight, January 1, 1970.

    TimeDiff elapsed() const;
    /// \brief Returns the time elapsed since the timestamp.
    /// \details Equivalent to `Timestamp() - *this`.

    bool isElapsed(TimeDiff interval) const;
    /// \brief Checks if a given time interval has passed since the timestamp.

    TimeVal raw() const;
    /// \brief Returns the raw time value in microseconds.
    /// \details Equivalent to `epochMicroseconds()`.

    static Timestamp fromEpochTime(std::time_t t);
    /// \brief Creates a timestamp from a `std::time_t` value.

    static Timestamp fromUtcTime(UtcTimeVal val);
    /// \brief Creates a timestamp from a UTC-based time value.
    /// \param val Time value in 100-nanosecond intervals since midnight, October 15, 1582.

    static constexpr TimeDiff resolution();
    /// \brief Returns the resolution in units per second.
    /// \details Since timestamps have microsecond resolution, the value is always 1,000,000.

#if defined(_WIN32)
    static Timestamp fromFileTimeNP(std::uint32_t fileTimeLow,
                                    std::uint32_t fileTimeHigh);
    /// \brief Creates a timestamp from a Windows FILETIME structure.

    void toFileTimeNP(std::uint32_t &fileTimeLow,
                      std::uint32_t &fileTimeHigh) const;
    /// \brief Converts the timestamp to a Windows FILETIME structure.
#endif

private:
    TimeVal _ts;///< Stores the timestamp value in microseconds.
};


class LIBDWG_API Timespan
/// A class that represents time spans up to microsecond resolution.
{
public:
    using TimeDiff = Timestamp::TimeDiff;

    Timespan();
    /// Creates a zero Timespan.

    Timespan(TimeDiff microseconds);
    /// Creates a Timespan.

    Timespan(long seconds, long microseconds);
    /// Creates a Timespan. Useful for creating
    /// a Timespan from a struct timeval.

    Timespan(int days, int hours, int minutes, int seconds, int microSeconds);
    /// Creates a Timespan.

    Timespan(const Timespan &timespan);
    /// Creates a Timespan from another one.

    template<class T, class Period>
    Timespan(const std::chrono::duration<T, Period> &dtime)
        : _span(std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count())
    {
    }
    /// Creates a Timespan from std::chrono::duration.

    ~Timespan();
    /// Destroys the Timespan.

    Timespan &operator=(const Timespan &timespan);
    /// Assignment operator.

    Timespan &operator=(TimeDiff microseconds);
    /// Assignment operator.

    Timespan &assign(int days, int hours, int minutes, int seconds,
                     int microSeconds);
    /// Assigns a new span.

    Timespan &assign(long seconds, long microseconds);
    /// Assigns a new span. Useful for assigning
    /// from a struct timeval.

    template<class T, class Period>
    Timespan &assign(const std::chrono::duration<T, Period> &dtime)
    /// Assigns a new span from std::chrono::duration.
    {
        _span = std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count();
        return *this;
    }

    void swap(Timespan &timespan) noexcept;
    /// Swaps the Timespan with another one.

    bool operator==(const Timespan &ts) const;
    /// Equality operator.

    bool operator!=(const Timespan &ts) const;
    /// Inequality operator.

    bool operator>(const Timespan &ts) const;
    /// Greater-than operator.

    bool operator>=(const Timespan &ts) const;
    /// Greater-than-or-equal-to operator.

    bool operator<(const Timespan &ts) const;
    /// Less-than operator.

    bool operator<=(const Timespan &ts) const;
    /// Less-than-or-equal-to operator.

    bool operator==(TimeDiff microSeconds) const;
    /// Equality operator for TimeDiff.

    bool operator!=(TimeDiff microSeconds) const;
    /// Inequality operator for TimeDiff.

    bool operator>(TimeDiff microSeconds) const;
    /// Greater-than operator for TimeDiff.

    bool operator>=(TimeDiff microSeconds) const;
    /// Greater-than-or-equal-to operator for TimeDiff.

    bool operator<(TimeDiff microSeconds) const;
    /// Less-than operator for TimeDiff.

    bool operator<=(TimeDiff microSeconds) const;
    /// Less-than-or-equal-to operator for TimeDiff.

    Timespan operator+(const Timespan &d) const;
    /// Addition operator.

    Timespan operator-(const Timespan &d) const;
    /// Subtraction operator.

    Timespan &operator+=(const Timespan &d);
    /// Addition assignment operator.

    Timespan &operator-=(const Timespan &d);
    /// Subtraction assignment operator.

    Timespan operator+(TimeDiff microSeconds) const;
    /// Addition operator with TimeDiff.

    Timespan operator-(TimeDiff microSeconds) const;
    /// Subtraction operator with TimeDiff.

    Timespan &operator+=(TimeDiff microSeconds);
    /// Addition assignment operator with TimeDiff.

    Timespan &operator-=(TimeDiff microSeconds);
    /// Subtraction assignment operator with TimeDiff.

    int days() const;
    /// Returns the number of days.

    int hours() const;
    /// Returns the number of hours (0 to 23).

    int totalHours() const;
    /// Returns the total number of hours.

    int minutes() const;
    /// Returns the number of minutes (0 to 59).

    int totalMinutes() const;
    /// Returns the total number of minutes.

    int seconds() const;
    /// Returns the number of seconds (0 to 59).

    int totalSeconds() const;
    /// Returns the total number of seconds.

    int milliseconds() const;
    /// Returns the number of milliseconds (0 to 999).

    TimeDiff totalMilliseconds() const;
    /// Returns the total number of milliseconds.

    int microseconds() const;
    /// Returns the fractions of a millisecond
    /// in microseconds (0 to 999).

    int useconds() const;
    /// Returns the fractions of a second
    /// in microseconds (0 to 999999).

    TimeDiff totalMicroseconds() const;
    /// Returns the total number of microseconds.

    static const TimeDiff
            MILLISECONDS;/// The number of microseconds in a millisecond.
    static const TimeDiff SECONDS;/// The number of microseconds in a second.
    static const TimeDiff MINUTES;/// The number of microseconds in a minute.
    static const TimeDiff HOURS;  /// The number of microseconds in an hour.
    static const TimeDiff DAYS;   /// The number of microseconds in a day.

private:
    TimeDiff _span;
};


class LIBDWG_API DateTime
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

    DateTime &assign(int year, int month, int day, int hour = 0, int minute = 0,
                     int second = 0, int millisecond = 0, int microsecond = 0);
    /// Assigns a Gregorian date and time to the instance. Similar to the parameterized constructor.

    void swap(DateTime &dateTime) noexcept;
    /// Efficiently swaps the contents of two DateTime instances.

    // Accessor methods for year, month, day, and time components
    int year() const;          // Gets the year component.
    int month() const;         // Gets the month (1�C12).
    int week(int firstDayOfWeek = MONDAY) const; // Gets the ISO 8601 week number.
    int day() const;           // Gets the day of the month (1�C31).
    int dayOfWeek() const;     // Gets the weekday (0 = Sunday, ..., 6 = Saturday).
    int dayOfYear() const;     // Gets the day of the year (1�C365/366).
    int hour() const;          // Gets the hour (0�C23).
    int hourAMPM() const;      // Gets the hour in 12-hour format.
    bool isAM() const;         // Returns true if the time is before noon.
    bool isPM() const;         // Returns true if the time is afternoon or later.
    int minute() const;        // Gets the minute (0�C59).
    int second() const;        // Gets the second (0�C60, accounts for leap seconds).
    int millisecond() const;   // Gets the millisecond (0�C999).
    int microsecond() const;   // Gets the microsecond (0�C999).

    double julianDay() const;  // Converts to a Julian day.

    Timestamp timestamp() const; // Converts the DateTime to a Timestamp.
    Timestamp::UtcTimeVal utcTime() const; // Converts the DateTime to UTC-based time.

    // Comparison operators
    bool operator==(const DateTime &dateTime) const;
    bool operator!=(const DateTime &dateTime) const;
    bool operator<(const DateTime &dateTime) const;
    bool operator<=(const DateTime &dateTime) const;
    bool operator>(const DateTime &dateTime) const;
    bool operator>=(const DateTime &dateTime) const;

    // Arithmetic operators for date/time manipulation
    DateTime operator+(const Timespan &span) const;
    DateTime operator-(const Timespan &span) const;
    Timespan operator-(const DateTime &dateTime) const;
    DateTime &operator+=(const Timespan &span);
    DateTime &operator-=(const Timespan &span);

    tm makeTM() const;  // Converts DateTime to a `tm` struct.

    void makeUTC(int tzd); // Converts local time to UTC using a timezone offset.
    void makeLocal(int tzd); // Converts UTC time to local time using a timezone offset.

    // Static utility methods
    static bool isLeapYear(int year); // Checks if the year is a leap year.
    static int daysOfMonth(int year, int month); // Gets the number of days in a month/year.
    static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0,
                        int millisecond = 0, int microsecond = 0); // Validates a date/time.

protected:
    void checkValid(); // Validates internal date/time components.
    static double toJulianDay(Timestamp::UtcTimeVal utcTime); // Converts UTC to Julian day.
    static double toJulianDay(int year, int month, int day, int hour = 0, int minute = 0,
                              int second = 0, int millisecond = 0, int microsecond = 0); // Gregorian to Julian.
    static Timestamp::UtcTimeVal toUtcTime(double julianDay); // Converts Julian to UTC.
    void computeGregorian(double julianDay); // Converts Julian day to Gregorian date.
    void computeDaytime(); // Extracts hours, minutes, and seconds from UTC.

private:
    // Utility methods for internal calculations
    void checkLimit(short &lower, short &higher, short limit);
    void normalize();

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
