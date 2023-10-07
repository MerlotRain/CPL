#include <filesystem.h>

namespace Lite {
namespace Utility {
long long GsFileSystem::MaxStdio()
{
    return 0;
}

long long GsFileSystem::MaxStdio(long long maxIOCount)
{
    return 0;
}

GsString GsFileSystem::AppDataFolder()
{
    return GsString();
}

GsString GsFileSystem::PathFolder()
{
    return GsString();
}

void GsFileSystem::AddSearchPath(const char *path)
{
}

GsString GsFileSystem::Combine(const char *path1, const char *path2)
{
    return GsString();
}

int GsFileSystem::ComparePath(const char *path1, const char *path2)
{
    return 0;
}

GsBOMType GsFileSystem::TestBOM(const char *str, int nLen)
{
    return GsBOMType();
}

int GsFileSystem::BOMLength(GsBOMType eType)
{
    return 0;
}

bool GsFileSystem::IsUtf8Path()
{
    return false;
}

bool GsFileSystem::IsPathCaseSensitivity()
{
    return false;
}

char GsFileSystem::PathSeparator()
{
    return 0;
}

bool GsFileSystem::Exists(const char *strPath)
{
    return false;
}

GsString GsFileSystem::TemporaryFolder()
{
    return GsString();
}

GsString GsFileSystem::CurrentFolder()
{
    return GsString();
}

GsString GsFileSystem::HomeFolder()
{
    return GsString();
}

GsString GsFileSystem::ConfigHomeFolder()
{
    return GsString();
}

GsString GsFileSystem::DataHomeFolder()
{
    return GsString();
}

GsString GsFileSystem::TempHomeFolder()
{
    return GsString();
}

GsString GsFileSystem::CacheHomeFolder()
{
    return GsString();
}

GsString GsFileSystem::TempFolder()
{
    return GsString();
}

GsString GsFileSystem::ConfigFolder()
{
    return GsString();
}


}// namespace Utility
}// namespace Lite
