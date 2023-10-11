#include <filesystem.h>

namespace m2 {

OperatorSystemType OperatorSystemEnvironment::CurrentOperatorSystemType()
{
#if defined(_WIN32) || defined(_WIN64)
    return OperatorSystemType::eWindows;
#elif defined(__APPLE__)
    return OperatorSystemType::eMacOSX;
#elif defined(ANDROID) || defined(_ANDROID_)
    return OperatorSystemType::eAndroid;
#elif defined(__linux__)
    return OperatorSystemType::eLinux;
#else
    return OperatorSystemType::eUnknown;
#endif
}

char OperatorSystemEnvironment::EnvironmentVariableSeparator()
{
    return 0;
}

String OperatorSystemEnvironment::EnvironmentVariable(const char *name)
{
    return String();
}

void OperatorSystemEnvironment::ChangeEnvironmentVariable(const char *name, const char *value)
{
}

void OperatorSystemEnvironment::RemoveEnvironmentVariable(const char *name)
{
}

String OperatorSystemEnvironment::RemoveEnvironmentVariable(const char *name, const char *content)
{
    return String();
}

String OperatorSystemEnvironment::AppendEnvironmentVariable(const char *name, const char *content,
                                                                bool bAddToTail)
{
    return String();
}

bool OperatorSystemEnvironment::AppendDLLDirectory(const char *dir)
{
    return false;
}

bool OperatorSystemEnvironment::RemoveDLLDirectory(const char *dir)
{
    return false;
}

}// namespace m2
