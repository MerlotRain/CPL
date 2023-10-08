#include "trace.h"

namespace m2 {

GsCrashReport::GsCrashReport()
{
}

void GsCrashReport::StackTrace(GsStackTrace *value)
{
}

GsStackTrace *GsCrashReport::StackTrace() const
{
    return nullptr;
}

void GsCrashReport::Flags(GsCrashReport::CrashFlags flags)
{
}

GsCrashReport::CrashFlags GsCrashReport::Flags() const
{
    return CrashFlags();
}

const GsString GsCrashReport::ToHtml() const
{
    return GsString();
}

const GsString GsCrashReport::CrashID() const
{
    return GsString();
}

void GsCrashReport::ExportToCrashFolder()
{
}

GsString GsCrashReport::CrashReportFolder()
{
    return GsString();
}

void GsCrashReport::VersionInfo(const GsStringList &versionInfo)
{
}

}// namespace m2
