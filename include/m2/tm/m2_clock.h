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

#ifndef M2_CLOCK_H_
#define M2_CLOCK_H_

#include <preconfig.h>

namespace m2 {

class LIBM2_EXPORT Clock
{
public:
    Clock();
    explicit Clock(long long c);
    Clock(const Clock &other);
    Clock &operator=(const Clock &other);
    Clock(Clock &&other);
    Clock &operator=(Clock &&other);
    Clock &operator=(long long tv);

    ~Clock();

    void swap(Clock &clock) noexcept;
    void update();

    bool operator==(const Clock &rhs) const;
    bool operator!=(const Clock &rhs) const;
    bool operator>(const Clock &rhs) const;
    bool operator>=(const Clock &rhs) const;
    bool operator<(const Clock &rhs) const;
    bool operator<=(const Clock &rhs) const;
    Clock operator+(long long d) const;
    Clock operator-(long long d) const;
    long long operator-(const Clock &rhs) const;
    Clock &operator+=(long long d);
    Clock &operator-=(long long d);

    long long microseconds() const;
    long long raw() const;
    long long elapsed() const;
    bool isElapsed(long long interval) const;

    static long long Resolution();
    static long long accuracy();
    static bool monotonic();

private:
    long long m_nClock;
};

}// namespace m2

#endif//M2_CLOCK_H_