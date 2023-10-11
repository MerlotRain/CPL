#include <thread>
#include <timer.h>

namespace m2 {

static constexpr int INV_TIMER = -1;

StopWatch::StopWatch() : m_Id(INV_TIMER), m_Inter(0), m_Del(0), m_Single(0), m_Nulltimer(0)
{
}

StopWatch::~StopWatch()
{
    if (m_Id != INV_TIMER)
    {
        Stop();
    }
}

inline bool StopWatch::Active() const
{
    return false;
}

int StopWatch::TimerId() const
{
    return 0;
}

void StopWatch::Interval(int msec)
{
}

int StopWatch::Interval() const
{
    return 0;
}

int StopWatch::RemainingTime() const
{
    return 0;
}

void StopWatch::Start(int msec)
{
}


void StopWatch::Start()
{
}

void StopWatch::Stop()
{
}

void StopWatch::SingleShot(int msec, const void *receiver, const char *member)
{
}

}// namespace m2
