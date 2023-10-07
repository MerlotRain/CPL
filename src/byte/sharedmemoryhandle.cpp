#include "sharedmemoryhandle.h"
#include "../exception_p.h"
#include "error.h"

namespace Lite {
namespace Utility {

#ifdef _WIN32

GsSharedMemeoryHandle::GsSharedMemeoryHandle()
{
}

GsSharedMemeoryHandle::GsSharedMemeoryHandle(const char *name, std::size_t size,
                                             GsSharedMemory::AccessMode mode, const void *addrHint,
                                             bool server)
    : m_strName(name), m_Size(static_cast<DWORD>(size)), _memHandle(INVALID_HANDLE_VALUE),
      _fileHandle(INVALID_HANDLE_VALUE), _mode(PAGE_READONLY), m_pAddress(0)
{
    if (mode == GsSharedMemory::AM_WRITE)
        _mode = PAGE_READWRITE;

    GsCA2W ca2w(m_strName);
    GsWString wstrname = ca2w.m_WStr;
    _memHandle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, _mode, 0, m_Size, wstrname.c_str());

    if (!_memHandle)
    {
        DWORD dwRetVal = GetLastError();
#if defined(_WIN32_WCE)
        throw GsUtilityException(GsString::Format("cannot create shared memory object %s [Error %d: %s]",
                                                  name, static_cast<int>(dwRetVal),
                                                  GsError::Message(dwRetVal).c_str()));
#else
        if (_mode == PAGE_READONLY || dwRetVal != 5)
        {
            throw GsUtilityException(
                    GsString::Format("cannot create shared memory object %s [Error %d: %s]", name,
                                     static_cast<int>(dwRetVal), GsError::Message(dwRetVal).c_str()));
        }
        _memHandle = OpenFileMappingW(PAGE_READONLY, FALSE, wstrname.c_str());
        if (!_memHandle)
        {
            dwRetVal = GetLastError();
            throw GsUtilityException(
                    GsString::Format("cannot open shared memory object %s [Error %d: %s]", name,
                                     static_cast<int>(dwRetVal), GsError::Message(dwRetVal).c_str()));
        }
#endif
    }
    Map();
}

GsSharedMemeoryHandle::GsSharedMemeoryHandle(const GsFile &file, GsSharedMemory::AccessMode mode,
                                             const void *addrHint)
{
}

GsSharedMemeoryHandle::~GsSharedMemeoryHandle()
{
    Unmap();
    Close();
}

char *GsSharedMemeoryHandle::Begin() const
{
    return m_pAddress;
}

char *GsSharedMemeoryHandle::End() const
{
    return m_pAddress + m_Size;
}

unsigned long long GsSharedMemeoryHandle::Size() const
{
    return m_Size;
}

void GsSharedMemeoryHandle::Map()
{
    DWORD access = FILE_MAP_READ;
    if (_mode == PAGE_READWRITE)
        access = FILE_MAP_WRITE;

    LPVOID addr = MapViewOfFile(_memHandle, access, 0, 0, m_Size);
    if (!addr)
    {
        DWORD dwRetVal = GetLastError();
        throw GsUtilityException(GsString::Format("cannot map shared memeory object  %s [Error %d: %s]",
                                                  m_strName.c_str(), static_cast<int>(dwRetVal),
                                                  GsError::Message(dwRetVal).c_str()));
    }
    m_pAddress = static_cast<char *>(addr);
}

void GsSharedMemeoryHandle::Unmap()
{
    if (m_pAddress)
    {
        UnmapViewOfFile(m_pAddress);
        m_pAddress = 0;
        return;
    }
}

void GsSharedMemeoryHandle::Close()
{
    if (_memHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(_memHandle);
        _memHandle = INVALID_HANDLE_VALUE;
    }

    if (_fileHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(_fileHandle);
        _memHandle = INVALID_HANDLE_VALUE;
    }
}


#elif defined(__linux__)

GsSharedMemeoryHandle::GsSharedMemeoryHandle()
{
}

GsSharedMemeoryHandle::GsSharedMemeoryHandle(const char *name, std::size_t size,
                                             GsSharedMemory::AccessMode mode, const void *addrHint,
                                             bool server)
{
}

GsSharedMemeoryHandle::GsSharedMemeoryHandle(const GsFile &file, GsSharedMemory::AccessMode mode,
                                             const void *addrHint)
{
}

GsSharedMemeoryHandle::~GsSharedMemeoryHandle()
{
}

char *GsSharedMemeoryHandle::Begin() const
{
    return nullptr;
}

char *GsSharedMemeoryHandle::End() const
{
    return nullptr;
}

unsigned long long GsSharedMemeoryHandle::Size() const
{
    return 0;
}

void GsSharedMemeoryHandle::Map()
{
}

void GsSharedMemeoryHandle::Unmap()
{
}

void GsSharedMemeoryHandle::Close()
{
}


#endif

}// namespace Utility
}// namespace Lite
