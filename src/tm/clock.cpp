#include "datetime.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined(__linux__)
#include <time.h>
#include <unistd.h>
#endif

namespace m2 {

Clock::Clock()
{
    Update();
}

Clock::Clock(long long c)
{
    m_nClock = c;
}

Clock::Clock(const Clock &other)
{
    m_nClock = other.m_nClock;
}

Clock::~Clock()
{
}

Clock &Clock::operator=(const Clock &other)
{
    m_nClock = other.m_nClock;
    return *this;
}

Clock &Clock::operator=(long long tv)
{
    m_nClock = tv;
    return *this;
}

void Clock::Swap(Clock &clock) noexcept
{
    std::swap(m_nClock, clock.m_nClock);
}

void Clock::Update()
{
#ifdef _WIN32

    LARGE_INTEGER perfCounter;
    LARGE_INTEGER perfFreq;
    if (QueryPerformanceCounter(&perfCounter) && QueryPerformanceFrequency(&perfFreq))
    {
        m_nClock = Resolution() * (perfCounter.QuadPart / perfFreq.QuadPart);
        m_nClock += (perfCounter.QuadPart % perfFreq.QuadPart) * Resolution() / perfFreq.QuadPart;
    }
#elif defined(__linux__)
#endif
}

bool Clock::operator==(const Clock &rhs) const
{
    return m_nClock == rhs.m_nClock;
}

bool Clock::operator!=(const Clock &rhs) const
{
    return m_nClock != rhs.m_nClock;
}

bool Clock::operator>(const Clock &rhs) const
{
    return m_nClock > rhs.m_nClock;
}

bool Clock::operator>=(const Clock &rhs) const
{
    return m_nClock >= rhs.m_nClock;
}

bool Clock::operator<(const Clock &rhs) const
{
    return m_nClock < rhs.m_nClock;
}

bool Clock::operator<=(const Clock &rhs) const
{
    return m_nClock <= rhs.m_nClock;
}

Clock Clock::operator+(long long d) const
{
    return Clock(m_nClock + d);
}

Clock Clock::operator-(long long d) const
{
    return Clock(m_nClock - d);
}

long long Clock::operator-(const Clock &rhs) const
{
    return m_nClock - rhs.m_nClock;
}

Clock &Clock::operator+=(long long d)
{
    m_nClock += d;
    return *this;
}

Clock &Clock::operator-=(long long d)
{
    m_nClock -= d;
    return *this;
}

long long Clock::Microseconds() const
{
    return m_nClock;
}

long long Clock::Raw() const
{
    return m_nClock;
}

long long Clock::Elapsed() const
{
    Clock now;
    return now - *this;
}

bool Clock::IsElapsed(long long interval) const
{
    Clock now;
    long long diff = now - *this;
    return diff >= interval;
}

long long Clock::Resolution()
{
    return 1000000;
}

long long Clock::Accuracy()
{
#ifdef _WIN32
    LARGE_INTEGER perfFreq;
    if (QueryPerformanceFrequency(&perfFreq) && perfFreq.QuadPart > 0)
    {
        long long acc = Resolution() / perfFreq.QuadPart;
        return acc > 0 ? acc : 1;
    }
#elif defined(__linux__)
#endif
    return 0;
}

bool Clock::Monotonic()
{
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}

}// namespace m2
