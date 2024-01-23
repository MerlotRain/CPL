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


Timestamp::Timestamp()
{
    Update();
}

Timestamp::Timestamp(long long tv) : Timestamp(tv)
{
}

Timestamp::Timestamp(const Timestamp &rhs) : Timestamp(rhs.Timestamp)
{
}

Timestamp::~Timestamp()
{
}

Timestamp &Timestamp::operator=(const Timestamp &rhs)
{
    Timestamp = rhs.Timestamp;
    return *this;
}

Timestamp &Timestamp::operator=(long long tv)
{
    Timestamp = tv;
    return *this;
}

void Timestamp::Swap(Timestamp &ths) noexcept
{
    std::swap(Timestamp, ths.Timestamp);
}

void Timestamp::Update()
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

bool Timestamp::operator==(const Timestamp &rhs) const
{
    return Timestamp == rhs.Timestamp;
}

bool Timestamp::operator!=(const Timestamp &rhs) const
{
    return Timestamp != rhs.Timestamp;
}

bool Timestamp::operator>(const Timestamp &rhs) const
{
    return Timestamp > rhs.Timestamp;
}

bool Timestamp::operator>=(const Timestamp &rhs) const
{
    return Timestamp >= rhs.Timestamp;
}

bool Timestamp::operator<(const Timestamp &rhs) const
{
    return Timestamp < rhs.Timestamp;
}

bool Timestamp::operator<=(const Timestamp &rhs) const
{
    return Timestamp <= rhs.Timestamp;
}

Timestamp Timestamp::operator+(long long duration) const
{
    return Timestamp(Timestamp + duration);
}

Timestamp Timestamp::operator+(const TimeSpan &span) const
{
    return *this + span.TotalMicroseconds();
}

Timestamp Timestamp::operator-(long long duration) const
{
    return Timestamp(Timestamp - duration);
}

Timestamp Timestamp::operator-(const TimeSpan &span) const
{
    return Timestamp();
}

long long Timestamp::operator-(const Timestamp &rhs) const
{
    return Timestamp - rhs.Timestamp;
}

Timestamp &Timestamp::operator+=(long long duration)
{
    Timestamp += duration;
    return *this;
}

Timestamp &Timestamp::operator+=(const TimeSpan &span)
{
    return *this += span.TotalMicroseconds();
}

Timestamp &Timestamp::operator-=(long long duration)
{
    Timestamp -= duration;
    return *this;
}

Timestamp &Timestamp::operator-=(const TimeSpan &span)
{
    return *this -= span.TotalMicroseconds();
}

std::time_t Timestamp::EpochTime() const
{
    return std::time_t(Timestamp / Resolution());
}

long long Timestamp::UTCTime() const
{
    return Timestamp * 10 + (long long(0x01b21dd2) << 32) + 0x13814000;
}

long long Timestamp::EpochMicroseconds() const
{
    return Timestamp;
}

long long Timestamp::Elapsed() const
{
    Timestamp now;
    return now - *this;
}

bool Timestamp::IsElapsed(long long interval) const
{
    Timestamp now;
    long long diff = now - *this;
    return diff >= interval;
}

long long Timestamp::Raw() const
{
    return 1000000;
}

Timestamp Timestamp::FromEpochTime(std::time_t t)
{
    return Timestamp(long long(t) * Resolution());
}

Timestamp Timestamp::FromUTCTime(long long utc)
{
    utc -= (long long(0x01b21dd2) << 32) + 0x13814000;
    utc /= 10;
    return Timestamp(utc);
}

long long Timestamp::Resolution()
{
    return 0;
}

}// namespace m2
