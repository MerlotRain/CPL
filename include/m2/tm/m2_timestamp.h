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

#ifndef M2_TIMESTAMP_H_
#define M2_TIMESTAMP_H_

#include <m2_timespan.h>

namespace m2 {

struct M2_API Timestamp
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

}// namespace m2

#endif//