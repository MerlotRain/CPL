#include "datetime.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined(__linux__)
#include <time.h>
#include <unistd.h>
#endif

namespace Lite {
namespace Utility {

GsClock::GsClock()
{
    Update();
}

GsClock::GsClock(long long c)
{
    m_nClock = c;
}

GsClock::GsClock(const GsClock &other)
{
    m_nClock = other.m_nClock;
}

GsClock::~GsClock()
{
}

GsClock &GsClock::operator=(const GsClock &other)
{
    m_nClock = other.m_nClock;
    return *this;
}

GsClock &GsClock::operator=(long long tv)
{
    m_nClock = tv;
    return *this;
}

void GsClock::Swap(GsClock &clock) noexcept
{
    std::swap(m_nClock, clock.m_nClock);
}

void GsClock::Update()
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

bool GsClock::operator==(const GsClock &rhs) const
{
    return m_nClock == rhs.m_nClock;
}

bool GsClock::operator!=(const GsClock &rhs) const
{
    return m_nClock != rhs.m_nClock;
}

bool GsClock::operator>(const GsClock &rhs) const
{
    return m_nClock > rhs.m_nClock;
}

bool GsClock::operator>=(const GsClock &rhs) const
{
    return m_nClock >= rhs.m_nClock;
}

bool GsClock::operator<(const GsClock &rhs) const
{
    return m_nClock < rhs.m_nClock;
}

bool GsClock::operator<=(const GsClock &rhs) const
{
    return m_nClock <= rhs.m_nClock;
}

GsClock GsClock::operator+(long long d) const
{
    return GsClock(m_nClock + d);
}

GsClock GsClock::operator-(long long d) const
{
    return GsClock(m_nClock - d);
}

long long GsClock::operator-(const GsClock &rhs) const
{
    return m_nClock - rhs.m_nClock;
}

GsClock &GsClock::operator+=(long long d)
{
    m_nClock += d;
    return *this;
}

GsClock &GsClock::operator-=(long long d)
{
    m_nClock -= d;
    return *this;
}

long long GsClock::Microseconds() const
{
    return m_nClock;
}

long long GsClock::Raw() const
{
    return m_nClock;
}

long long GsClock::Elapsed() const
{
    GsClock now;
    return now - *this;
}

bool GsClock::IsElapsed(long long interval) const
{
    GsClock now;
    long long diff = now - *this;
    return diff >= interval;
}

long long GsClock::Resolution()
{
    return 1000000;
}

long long GsClock::Accuracy()
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

bool GsClock::Monotonic()
{
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}

}// namespace Utility
}// namespace Lite
