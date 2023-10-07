#include <filesystem.h>

namespace Lite {
namespace Utility {

GsOperatorSystemType GsOperatorSystemEnvironment::CurrentOperatorSystemType()
{
#if defined(_WIN32) || defined(_WIN64)
    return GsOperatorSystemType::eWindows;
#elif defined(__APPLE__)
    return GsOperatorSystemType::eMacOSX;
#elif defined(ANDROID) || defined(_ANDROID_)
    return GsOperatorSystemType::eAndroid;
#elif defined(__linux__)
    return GsOperatorSystemType::eLinux;
#else
    return GsOperatorSystemType::eUnknown;
#endif
}

char GsOperatorSystemEnvironment::EnvironmentVariableSeparator()
{
    return 0;
}

GsString GsOperatorSystemEnvironment::EnvironmentVariable(const char *name)
{
    return GsString();
}

void GsOperatorSystemEnvironment::ChangeEnvironmentVariable(const char *name, const char *value)
{
}

void GsOperatorSystemEnvironment::RemoveEnvironmentVariable(const char *name)
{
}

GsString GsOperatorSystemEnvironment::RemoveEnvironmentVariable(const char *name, const char *content)
{
    return GsString();
}

GsString GsOperatorSystemEnvironment::AppendEnvironmentVariable(const char *name, const char *content,
                                                                bool bAddToTail)
{
    return GsString();
}

bool GsOperatorSystemEnvironment::AppendDLLDirectory(const char *dir)
{
    return false;
}

bool GsOperatorSystemEnvironment::RemoveDLLDirectory(const char *dir)
{
    return false;
}

}// namespace Utility
}// namespace Lite
