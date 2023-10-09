#include <filesystem.h>

namespace m2 {

Dir::Dir()
{
}

Dir::Dir(const Dir &pDir)
{
}

Dir::Dir(const char *strDirPath)
{
}

Dir::~Dir()
{
}

String Dir::Path() const
{
    return String();
}

bool Dir::Create()
{
    return false;
}

String Dir::Name() const
{
    return String();
}

String Dir::FullPath() const
{
    return String();
}

bool Dir::Exists() const
{
    return false;
}

bool Dir::IsRoot() const
{
    return false;
}

Dir Dir::Parent() const
{
    return Dir();
}

void Dir::ForEachFiles(Delegate<bool(const char *, void *)> &onFileCallBack, void *context,
                         const char *searchPattern)
{
}

std::vector<File> Dir::Files(const char *searchPattern) const
{
    return std::vector<File>();
}

std::vector<File> *Dir::Files(std::vector<File> &files) const
{
    return nullptr;
}

Dir Dir::SubDir(const char *subName) const
{
    return Dir();
}

File Dir::File(const char *fileName) const
{
    return File();
}

void Dir::ForEachDirs(Delegate<bool(const char *, void *)> &onFileCallBack, void *context)
{
}

std::vector<Dir> Dir::Dirs() const
{
    return std::vector<Dir>();
}

std::vector<Dir> *Dir::Dirs(std::vector<Dir> &files) const
{
    return nullptr;
}

bool Dir::operator==(const Dir &rhs) const
{
    return false;
}

Dir &Dir::operator=(const Dir &rhs)
{
    // TODO: insert return statement here
}

Dir &Dir::operator=(const char *strDirPath)
{
    // TODO: insert return statement here
}

Dir &Dir::operator=(const String &strDirPath)
{
    // TODO: insert return statement here
}

Dir::operator bool()
{
}

bool Dir::Rename(const char *name)
{
    return false;
}

bool Dir::Remove(bool recursive)
{
    return false;
}

bool Dir::Remove(const char *path, bool recursive)
{
    return false;
}

std::vector<String> Dir::Drives()
{
    return std::vector<String>();
}

unsigned long long Dir::TotalSpace() const
{
    return 0;
}

unsigned long long Dir::UsableSpace() const
{
    return 0;
}

unsigned long long Dir::FreeSpace() const
{
    return 0;
}


}// namespace m2
