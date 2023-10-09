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

namespace m2 {

std::mutex Library::m_mutex;

#ifdef _WIN32
Library::Library()
{
    m_Handle = 0;
}

Library::Library(const char *path) : m_strPath(path) { Load(path); }

Library::Library(const char *path, int flags) : m_strPath(path)
{
    Load(path, 0);
}

Library::~Library() {}

void Library::Load(const char *path) { Load(path, 0); }

void Library::Load(const char *path, int flag)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_Handle)
        throw UtilityException(m_strPath);
    DWORD flags(0);
#if !defined(_WIN32_WCE)
    Path p(path);
    if (p.IsAbsolute())
        flags |= LOAD_WITH_ALTERED_SEARCH_PATH;
#endif
    CA2W ca2w(path);
    m_Handle = LoadLibraryExW(ca2w.m_WStr.c_str(), 0, flags);
    if (!m_Handle)
    {
        DWORD errn = Error::LastError();
        String errMsg = Error::Message(errn).Trimmed();
        String err = String::Format("Error %ul while loading [%s]: [%s]", errn,
                                        path, errMsg);
        throw UtilityException(err);
    }
    m_strPath = path;
}

void Library::Unload()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_Handle)
    {
        FreeLibrary((HMODULE) m_Handle);
        m_Handle = 0;
    }
    m_strPath.clear();
}

bool Library::IsLoaded() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_Handle != 0;
}

bool Library::HasSymbol(const char *name) { return Symbol(name) != 0; }

void *Library::Symbol(const char *name)
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

const String &Library::Path() const { return m_strPath; }

String Library::Suffix() { return ".dll"; }

bool Library::SearchPath(const String &path)
{
#if _WIN32_WINNT >= 0x0502
    std::wstring wpath;
    CA2W ca2w(path);
    return SetDllDirectoryW(ca2w.m_WStr.c_str()) != 0;
#else
    return false;
#endif
}

#else

Library::Library(const char *path) : Library(path, 0)
{
}

Library::Library(const char *path, int flags) : m_strPath(path)
{
    Load(path, flags);
}

Library::~Library() = default;

void Library::Load(const char *path) { Load(path, 0); }

void Library::Load(const char *path, int flags)
{
    if (path == NULL)
        throw IllegalArgumentException("path is null");
    std::unique_lock<std::mutex> l(m_mutex);
    if (m_Handle)
        throw UtilityException(path);
    int readFlags = RTLD_LAZY;
    if (flags & SHLIB_LOCAL)
        readFlags |= RTLD_LOCAL;
    else
        readFlags |= RTLD_GLOBAL;
    m_Handle = dlopen(path, readFlags);
    if (!m_Handle)
    {
        const char *err = dlerror();
        throw UtilityException(err ? String(err) : path);
    }
}

void Library::Unload()
{
    std::unique_lock<std::mutex> l(m_mutex);
    if (m_Handle)
    {
        dlclose(m_Handle);
        m_Handle = 0;
    }
}

bool Library::IsLoaded() const
{
    std::unique_lock<std::mutex> l(m_mutex);
    return m_Handle != 0;
}

bool Library::HasSymbol(const char *name) { return Symbol(name) != 0; }

void *Library::Symbol(const char *name)
{
    std::unique_lock<std::mutex> l(m_mutex);
    void *result = 0;
    if (m_Handle)
    {
        result = dlsym(m_Handle, name);
    }
    return result;
}

const String &Library::Path() const { return m_strPath; }

String Library::Suffix()
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

bool Library::SearchPath(const String &path) { return false; }

#endif

}// namespace m2
