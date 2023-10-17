#include <m2_trace.h>

namespace m2 {

CrashReport::CrashReport() {}

void CrashReport::setStackTrace(StackTrace *value) {}

StackTrace *CrashReport::stackTrace() const { return nullptr; }

void CrashReport::setFlags(CrashReport::CrashFlags flags) {}

CrashReport::CrashFlags CrashReport::flags() const { return CrashFlags(); }

const String CrashReport::toHtml() const { return String(); }

const String CrashReport::crashID() const { return String(); }

void CrashReport::exportToCrashFolder() {}

String CrashReport::crashReportFolder() { return String(); }

void CrashReport::versionInfo(const StringList &versionInfo) {}

}// namespace m2
