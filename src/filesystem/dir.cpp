#include <filesystem.h>

namespace m2 {

GsDir::GsDir()
{
}

GsDir::GsDir(const GsDir &pDir)
{
}

GsDir::GsDir(const char *strDirPath)
{
}

GsDir::~GsDir()
{
}

GsString GsDir::Path() const
{
    return GsString();
}

bool GsDir::Create()
{
    return false;
}

GsString GsDir::Name() const
{
    return GsString();
}

GsString GsDir::FullPath() const
{
    return GsString();
}

bool GsDir::Exists() const
{
    return false;
}

bool GsDir::IsRoot() const
{
    return false;
}

GsDir GsDir::Parent() const
{
    return GsDir();
}

void GsDir::ForEachFiles(GsDelegate<bool(const char *, void *)> &onFileCallBack, void *context,
                         const char *searchPattern)
{
}

std::vector<GsFile> GsDir::Files(const char *searchPattern) const
{
    return std::vector<GsFile>();
}

std::vector<GsFile> *GsDir::Files(std::vector<GsFile> &files) const
{
    return nullptr;
}

GsDir GsDir::SubDir(const char *subName) const
{
    return GsDir();
}

GsFile GsDir::File(const char *fileName) const
{
    return GsFile();
}

void GsDir::ForEachDirs(GsDelegate<bool(const char *, void *)> &onFileCallBack, void *context)
{
}

std::vector<GsDir> GsDir::Dirs() const
{
    return std::vector<GsDir>();
}

std::vector<GsDir> *GsDir::Dirs(std::vector<GsDir> &files) const
{
    return nullptr;
}

bool GsDir::operator==(const GsDir &rhs) const
{
    return false;
}

GsDir &GsDir::operator=(const GsDir &rhs)
{
    // TODO: insert return statement here
}

GsDir &GsDir::operator=(const char *strDirPath)
{
    // TODO: insert return statement here
}

GsDir &GsDir::operator=(const GsString &strDirPath)
{
    // TODO: insert return statement here
}

GsDir::operator bool()
{
}

bool GsDir::Rename(const char *name)
{
    return false;
}

bool GsDir::Remove(bool recursive)
{
    return false;
}

bool GsDir::Remove(const char *path, bool recursive)
{
    return false;
}

std::vector<GsString> GsDir::Drives()
{
    return std::vector<GsString>();
}

unsigned long long GsDir::TotalSpace() const
{
    return 0;
}

unsigned long long GsDir::UsableSpace() const
{
    return 0;
}

unsigned long long GsDir::FreeSpace() const
{
    return 0;
}


}// namespace m2
