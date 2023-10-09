#include "trace.h"

namespace m2 {

CrashReport::CrashReport()
{
}

void CrashReport::StackTrace(StackTrace *value)
{
}

StackTrace *CrashReport::StackTrace() const
{
    return nullptr;
}

void CrashReport::Flags(CrashReport::CrashFlags flags)
{
}

CrashReport::CrashFlags CrashReport::Flags() const
{
    return CrashFlags();
}

const String CrashReport::ToHtml() const
{
    return String();
}

const String CrashReport::CrashID() const
{
    return String();
}

void CrashReport::ExportToCrashFolder()
{
}

String CrashReport::CrashReportFolder()
{
    return String();
}

void CrashReport::VersionInfo(const StringList &versionInfo)
{
}

}// namespace m2
