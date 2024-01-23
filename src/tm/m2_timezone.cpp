#include "../exception_p.h"
#include <ctime>
#include <datetime.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace m2 {


int TimeZone::UTCOffset()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return -tzInfo.Bias * 60;
#else
#endif
}

int TimeZone::DST()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias * 60 : 0;
#else
#endif
}

int TimeZone::DST(const Timestamp &timestamp)
{
#ifdef _WIN32
    if (IsDST(timestamp))
    {
        TIME_ZONE_INFORMATION tzInfo;
        GetTimeZoneInformation(&tzInfo);
        return -tzInfo.DaylightBias * 60;
    }
    return 0;
#else
#endif
}

bool TimeZone::IsDST(const Timestamp &timestamp)
{
#ifdef _WIN32
    std::time_t time = timestamp.EpochTime();
    struct std::tm local;
    if (localtime_s(&local, &time))
        throw UtilityException("cannot get local time DST flag");
    return local.tm_isdst > 0;
#else
#endif
}

int TimeZone::TimeZoneDifferential()
{
    return UTCOffset() + DST();
}

String TimeZone::Name()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
    CW2A cw2a(ptr);
    return cw2a.m_Str;
#else

#endif
    return String();
}

String TimeZone::StandardName()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = tzInfo.StandardName;
    CW2A cw2a(ptr);
    return cw2a.m_Str;
#else

#endif
}

String TimeZone::DSTName()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = tzInfo.DaylightName;
    CW2A cw2a(ptr);
    return cw2a.m_Str;
#else

#endif
}

}// namespace m2
