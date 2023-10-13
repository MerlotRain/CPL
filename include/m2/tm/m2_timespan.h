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

#ifndef M2_TIMESPAN_H_
#define M2_TIMESPAN_H_

#include <m2_string.h>

namespace m2 {

struct M2_API TimeSpan
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

}// namespace m2

#endif