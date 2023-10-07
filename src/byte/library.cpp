#include "../exception_p.h"
#include "error.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include "stringhelp.h"
#include <filesystem.h>
#include <library.h>

namespace Lite {
namespace Utility {

std::mutex GsLibrary::m_mutex;

#ifdef _WIN32
GsLibrary::GsLibrary()
{
    m_Handle = 0;
}

GsLibrary::GsLibrary(const char *path) : m_strPath(path) { Load(path); }

GsLibrary::GsLibrary(const char *path, int flags) : m_strPath(path)
{
    Load(path, 0);
}

GsLibrary::~GsLibrary() {}

void GsLibrary::Load(const char *path) { Load(path, 0); }

void GsLibrary::Load(const char *path, int flag)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_Handle)
        throw GsUtilityException(m_strPath);
    DWORD flags(0);
#if !defined(_WIN32_WCE)
    GsPath p(path);
    if (p.IsAbsolute())
        flags |= LOAD_WITH_ALTERED_SEARCH_PATH;
#endif
    GsCA2W ca2w(path);
    m_Handle = LoadLibraryExW(ca2w.m_WStr.c_str(), 0, flags);
    if (!m_Handle)
    {
        DWORD errn = GsError::LastError();
        GsString errMsg = GsError::Message(errn).Trimmed();
        GsString err = GsString::Format("Error %ul while loading [%s]: [%s]", errn,
                                        path, errMsg);
        throw GsUtilityException(err);
    }
    m_strPath = path;
}

void GsLibrary::Unload()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_Handle)
    {
        FreeLibrary((HMODULE) m_Handle);
        m_Handle = 0;
    }
    m_strPath.clear();
}

bool GsLibrary::IsLoaded() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_Handle != 0;
}

bool GsLibrary::HasSymbol(const char *name) { return Symbol(name) != 0; }

void *GsLibrary::Symbol(const char *name)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_Handle)
    {
#if defined(_WIN32_WCE)
        std::wstring uname;
        UnicodeConverter::toUTF16(name, uname);
        return (void *) GetProcAddressW((HMODULE) m_Handle, uname.c_str());
#else
        return (void *) GetProcAddress((HMODULE) m_Handle, name);
#endif
    }
    else
        return 0;
}

const GsString &GsLibrary::Path() const { return m_strPath; }

GsString GsLibrary::Suffix() { return ".dll"; }

bool GsLibrary::SearchPath(const GsString &path)
{
#if _WIN32_WINNT >= 0x0502
    std::wstring wpath;
    GsCA2W ca2w(path);
    return SetDllDirectoryW(ca2w.m_WStr.c_str()) != 0;
#else
    return false;
#endif
}

#else

GsLibrary::GsLibrary(const char *path) : GsLibrary(path, 0)
{
}

GsLibrary::GsLibrary(const char *path, int flags) : m_strPath(path)
{
    Load(path, flags);
}

GsLibrary::~GsLibrary() = default;

void GsLibrary::Load(const char *path) { Load(path, 0); }

void GsLibrary::Load(const char *path, int flags)
{
    if (path == NULL)
        throw GsIllegalArgumentException("path is null");
    std::unique_lock<std::mutex> l(m_mutex);
    if (m_Handle)
        throw GsUtilityException(path);
    int readFlags = RTLD_LAZY;
    if (flags & SHLIB_LOCAL)
        readFlags |= RTLD_LOCAL;
    else
        readFlags |= RTLD_GLOBAL;
    m_Handle = dlopen(path, readFlags);
    if (!m_Handle)
    {
        const char *err = dlerror();
        throw GsUtilityException(err ? GsString(err) : path);
    }
}

void GsLibrary::Unload()
{
    std::unique_lock<std::mutex> l(m_mutex);
    if (m_Handle)
    {
        dlclose(m_Handle);
        m_Handle = 0;
    }
}

bool GsLibrary::IsLoaded() const
{
    std::unique_lock<std::mutex> l(m_mutex);
    return m_Handle != 0;
}

bool GsLibrary::HasSymbol(const char *name) { return Symbol(name) != 0; }

void *GsLibrary::Symbol(const char *name)
{
    std::unique_lock<std::mutex> l(m_mutex);
    void *result = 0;
    if (m_Handle)
    {
        result = dlsym(m_Handle, name);
    }
    return result;
}

const GsString &GsLibrary::Path() const { return m_strPath; }

GsString GsLibrary::Suffix()
{
#ifdef __APPLE__
    return ".dylib";
#elif defined(hpux)
    return ".sl";
#elif defined(__CYGWIN__)
    return ".dll";
#else
    return ".so";
#endif
}

bool GsLibrary::SearchPath(const GsString &path) { return false; }

#endif

}// namespace Utility
}// namespace Lite
