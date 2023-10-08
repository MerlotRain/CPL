#include <filesystem.h>

namespace m2 {


GsFile::GsFile()
{
}

GsFile::GsFile(const char *path)
{
}


GsFile::GsFile(const GsFile &file)
{
}

GsFile::~GsFile()
{
}

GsFile &GsFile::operator=(const GsFile &file)
{
    return *this;
}

GsFile &GsFile::operator=(const GsString &path)
{
    return *this;
}

GsFile &GsFile::operator=(const char *path)
{
    return *this;
}

const GsString &GsFile::Path() const
{
    return "";
}

const GsString &GsFile::Name(bool bHasExtension) const
{
    // TODO: insert return statement here
}

GsDir GsFile::Parent() const
{
    return GsDir();
}

bool GsFile::Exists() const
{
    return false;
}

GsString GsFile::Extension() const
{
    return GsString();
}

GsString GsFile::ChangeExtension(const char *strExt)
{
    return GsString();
}

bool GsFile::CanRead() const
{
    return false;
}

bool GsFile::CanWrite() const
{
    return false;
}

bool GsFile::CanExecute() const
{
    return false;
}

bool GsFile::IsLink() const
{
    return false;
}


bool GsFile::IsHidden() const
{
    return false;
}

GsTimestamp GsFile::Created() const
{
    return GsTimestamp();
}

GsTimestamp GsFile::LastModified() const
{
    return GsTimestamp();
}

GsFile &GsFile::LastModified(const GsTimestamp &ts)
{
    return *this;
}

unsigned long long GsFile::Size() const
{
    return 0;
}

GsFile &GsFile::Size(unsigned long long size)
{
    return *this;
}

GsFile &GsFile::Writeable(bool flag)
{
    return *this;
}

GsFile &GsFile::ReadOnly(bool flag)
{
    return *this;
}

GsFile &GsFile::Executable(bool flag)
{
    return *this;
}

bool GsFile::CopyTo(const char *path, bool overwrite) const
{
    return false;
}


bool GsFile::MoveTo(const char *path, bool overwrite)
{
    return false;
}

bool GsFile::RenameTo(const char *path, bool overwrite)
{
    return false;
}

void GsFile::LinkTo(const char *path) const
{
}

void GsFile::Remove()
{
}

unsigned long long GsFile::TotalSpace() const
{
    return 0;
}

unsigned long long GsFile::UsableSpace() const
{
    return 0;
}

unsigned long long GsFile::FreeSpace() const
{
    return 0;
}

void GsFile::copyDirectory(const GsString &path, int options) const
{
}


}// namespace m2
