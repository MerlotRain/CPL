#include <filesystem.h>

namespace m2 {


File::File()
{
}

File::File(const char *path)
{
}


File::File(const File &file)
{
}

File::~File()
{
}

File &File::operator=(const File &file)
{
    return *this;
}

File &File::operator=(const String &path)
{
    return *this;
}

File &File::operator=(const char *path)
{
    return *this;
}

const String &File::Path() const
{
    return "";
}

const String &File::Name(bool bHasExtension) const
{
    // TODO: insert return statement here
}

Dir File::Parent() const
{
    return Dir();
}

bool File::Exists() const
{
    return false;
}

String File::Extension() const
{
    return String();
}

String File::ChangeExtension(const char *strExt)
{
    return String();
}

bool File::CanRead() const
{
    return false;
}

bool File::CanWrite() const
{
    return false;
}

bool File::CanExecute() const
{
    return false;
}

bool File::IsLink() const
{
    return false;
}


bool File::IsHidden() const
{
    return false;
}

Timestamp File::Created() const
{
    return Timestamp();
}

Timestamp File::LastModified() const
{
    return Timestamp();
}

File &File::LastModified(const Timestamp &ts)
{
    return *this;
}

unsigned long long File::Size() const
{
    return 0;
}

File &File::Size(unsigned long long size)
{
    return *this;
}

File &File::Writeable(bool flag)
{
    return *this;
}

File &File::ReadOnly(bool flag)
{
    return *this;
}

File &File::Executable(bool flag)
{
    return *this;
}

bool File::CopyTo(const char *path, bool overwrite) const
{
    return false;
}


bool File::MoveTo(const char *path, bool overwrite)
{
    return false;
}

bool File::RenameTo(const char *path, bool overwrite)
{
    return false;
}

void File::LinkTo(const char *path) const
{
}

void File::Remove()
{
}

unsigned long long File::TotalSpace() const
{
    return 0;
}

unsigned long long File::UsableSpace() const
{
    return 0;
}

unsigned long long File::FreeSpace() const
{
    return 0;
}

void File::copyDirectory(const String &path, int options) const
{
}


}// namespace m2
