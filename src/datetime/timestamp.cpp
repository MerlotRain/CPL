#include <Windows.h>
#include <algorithm>
#include <datetime.h>

namespace m2 {


#ifdef _WIN32
class TickOffset
{
public:
    TickOffset()
    {
        SYSTEMTIME st1, st2;
        std::memset(&st1, 0, sizeof(SYSTEMTIME));
        std::memset(&st2, 0, sizeof(SYSTEMTIME));
        GetSystemTime(&st1);
        while (true)
        {
            GetSystemTime(&st2);
            if (st1.wSecond != st2.wSecond)
            {
                _offset = GetTickCount() % 1000;
                break;
            }
        }
    }

    void calibrate(int seconds)
    {
        SYSTEMTIME st1, st2;
        systemTime(&st1);

        WORD s = st1.wSecond;
        int sum = 0;
        int remaining = seconds;
        while (remaining > 0)
        {
            systemTime(&st2);
            WORD s2 = st2.wSecond;

            if (s != s2)
            {
                remaining--;
                sum += (st2.wMilliseconds > 500) ? (st2.wMilliseconds - 1000) : st2.wMilliseconds;
                s = st2.wSecond;
            }
        }
        if (sum < 0)
            _offset += (int) std::floor(sum / (float) seconds);
        else
            _offset += (int) std::ceil(sum / (float) seconds);
    }

    void systemTime(SYSTEMTIME *pST)
    {
        std::memset(pST, 0, sizeof(SYSTEMTIME));

        WORD tick = GetTickCount() % 1000;
        GetSystemTime(pST);
        WORD ms = (tick >= _offset) ? (tick - _offset) : (1000 - (_offset - tick));
        pST->wMilliseconds = ms;
    }

    void systemTimeAsFileTime(FILETIME *pFT)
    {
        SYSTEMTIME st;
        systemTime(&st);
        SystemTimeToFileTime(&st, pFT);
    }

private:
    WORD _offset;
};

static TickOffset offset;
void GetSystemTimeAsFileTimeWithMillisecondResolution(FILETIME *pFT)
{
    offset.systemTimeAsFileTime(pFT);
}
#endif


GsTimestamp::GsTimestamp()
{
    Update();
}

GsTimestamp::GsTimestamp(long long tv) : Timestamp(tv)
{
}

GsTimestamp::GsTimestamp(const GsTimestamp &rhs) : Timestamp(rhs.Timestamp)
{
}

GsTimestamp::~GsTimestamp()
{
}

GsTimestamp &GsTimestamp::operator=(const GsTimestamp &rhs)
{
    Timestamp = rhs.Timestamp;
    return *this;
}

GsTimestamp &GsTimestamp::operator=(long long tv)
{
    Timestamp = tv;
    return *this;
}

void GsTimestamp::Swap(GsTimestamp &ths) noexcept
{
    std::swap(Timestamp, ths.Timestamp);
}

void GsTimestamp::Update()
{
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTimeWithMillisecondResolution(&ft);
    ULARGE_INTEGER epoch;
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER rhs;
    rhs.LowPart = ft.dwLowDateTime;
    rhs.HighPart = ft.dwHighDateTime;
    rhs.QuadPart -= epoch.QuadPart;
    Timestamp = rhs.QuadPart / 10;
#else
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        throw SystemException("cannot get time of day");
    Timestamp = TimeVal(tv.tv_sec) * resolution() + tv.tv_usec;

#endif
}

bool GsTimestamp::operator==(const GsTimestamp &rhs) const
{
    return Timestamp == rhs.Timestamp;
}

bool GsTimestamp::operator!=(const GsTimestamp &rhs) const
{
    return Timestamp != rhs.Timestamp;
}

bool GsTimestamp::operator>(const GsTimestamp &rhs) const
{
    return Timestamp > rhs.Timestamp;
}

bool GsTimestamp::operator>=(const GsTimestamp &rhs) const
{
    return Timestamp >= rhs.Timestamp;
}

bool GsTimestamp::operator<(const GsTimestamp &rhs) const
{
    return Timestamp < rhs.Timestamp;
}

bool GsTimestamp::operator<=(const GsTimestamp &rhs) const
{
    return Timestamp <= rhs.Timestamp;
}

GsTimestamp GsTimestamp::operator+(long long duration) const
{
    return GsTimestamp(Timestamp + duration);
}

GsTimestamp GsTimestamp::operator+(const GsTimeSpan &span) const
{
    return *this + span.TotalMicroseconds();
}

GsTimestamp GsTimestamp::operator-(long long duration) const
{
    return GsTimestamp(Timestamp - duration);
}

GsTimestamp GsTimestamp::operator-(const GsTimeSpan &span) const
{
    return GsTimestamp();
}

long long GsTimestamp::operator-(const GsTimestamp &rhs) const
{
    return Timestamp - rhs.Timestamp;
}

GsTimestamp &GsTimestamp::operator+=(long long duration)
{
    Timestamp += duration;
    return *this;
}

GsTimestamp &GsTimestamp::operator+=(const GsTimeSpan &span)
{
    return *this += span.TotalMicroseconds();
}

GsTimestamp &GsTimestamp::operator-=(long long duration)
{
    Timestamp -= duration;
    return *this;
}

GsTimestamp &GsTimestamp::operator-=(const GsTimeSpan &span)
{
    return *this -= span.TotalMicroseconds();
}

std::time_t GsTimestamp::EpochTime() const
{
    return std::time_t(Timestamp / Resolution());
}

long long GsTimestamp::UTCTime() const
{
    return Timestamp * 10 + (long long(0x01b21dd2) << 32) + 0x13814000;
}

long long GsTimestamp::EpochMicroseconds() const
{
    return Timestamp;
}

long long GsTimestamp::Elapsed() const
{
    GsTimestamp now;
    return now - *this;
}

bool GsTimestamp::IsElapsed(long long interval) const
{
    GsTimestamp now;
    long long diff = now - *this;
    return diff >= interval;
}

long long GsTimestamp::Raw() const
{
    return 1000000;
}

GsTimestamp GsTimestamp::FromEpochTime(std::time_t t)
{
    return GsTimestamp(long long(t) * Resolution());
}

GsTimestamp GsTimestamp::FromUTCTime(long long utc)
{
    utc -= (long long(0x01b21dd2) << 32) + 0x13814000;
    utc /= 10;
    return GsTimestamp(utc);
}

long long GsTimestamp::Resolution()
{
    return 0;
}

}// namespace m2
