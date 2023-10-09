#include <filesystem.h>

namespace m2 {
long long FileSystem::MaxStdio()
{
    return 0;
}

long long FileSystem::MaxStdio(long long maxIOCount)
{
    return 0;
}

String FileSystem::AppDataFolder()
{
    return String();
}

String FileSystem::PathFolder()
{
    return String();
}

void FileSystem::AddSearchPath(const char *path)
{
}

String FileSystem::Combine(const char *path1, const char *path2)
{
    return String();
}

int FileSystem::ComparePath(const char *path1, const char *path2)
{
    return 0;
}

BOMType FileSystem::TestBOM(const char *str, int nLen)
{
    return BOMType();
}

int FileSystem::BOMLength(BOMType eType)
{
    return 0;
}

bool FileSystem::IsUtf8Path()
{
    return false;
}

bool FileSystem::IsPathCaseSensitivity()
{
    return false;
}

char FileSystem::PathSeparator()
{
    return 0;
}

bool FileSystem::Exists(const char *strPath)
{
    return false;
}

String FileSystem::TemporaryFolder()
{
    return String();
}

String FileSystem::CurrentFolder()
{
    return String();
}

String FileSystem::HomeFolder()
{
    return String();
}

String FileSystem::ConfigHomeFolder()
{
    return String();
}

String FileSystem::DataHomeFolder()
{
    return String();
}

String FileSystem::TempHomeFolder()
{
    return String();
}

String FileSystem::CacheHomeFolder()
{
    return String();
}

String FileSystem::TempFolder()
{
    return String();
}

String FileSystem::ConfigFolder()
{
    return String();
}


}// namespace m2
