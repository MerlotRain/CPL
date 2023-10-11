#include "sharedmemoryhandle.h"
#include "../exception_p.h"
#include "error.h"

namespace m2 {

#ifdef _WIN32

SharedMemeoryHandle::SharedMemeoryHandle()
{
}

SharedMemeoryHandle::SharedMemeoryHandle(const char *name, std::size_t size,
                                             SharedMemory::AccessMode mode, const void *addrHint,
                                             bool server)
    : m_strName(name), m_Size(static_cast<DWORD>(size)), _memHandle(INVALID_HANDLE_VALUE),
      _fileHandle(INVALID_HANDLE_VALUE), _mode(PAGE_READONLY), m_pAddress(0)
{
    if (mode == SharedMemory::AM_WRITE)
        _mode = PAGE_READWRITE;

    CA2W ca2w(m_strName);
    WString wstrname = ca2w.m_WStr;
    _memHandle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, _mode, 0, m_Size, wstrname.c_str());

    if (!_memHandle)
    {
        DWORD dwRetVal = GetLastError();
#if defined(_WIN32_WCE)
        throw UtilityException(String::Format("cannot create shared memory object %s [Error %d: %s]",
                                                  name, static_cast<int>(dwRetVal),
                                                  Error::Message(dwRetVal).c_str()));
#else
        if (_mode == PAGE_READONLY || dwRetVal != 5)
        {
            throw UtilityException(
                    String::Format("cannot create shared memory object %s [Error %d: %s]", name,
                                     static_cast<int>(dwRetVal), Error::Message(dwRetVal).c_str()));
        }
        _memHandle = OpenFileMappingW(PAGE_READONLY, FALSE, wstrname.c_str());
        if (!_memHandle)
        {
            dwRetVal = GetLastError();
            throw UtilityException(
                    String::Format("cannot open shared memory object %s [Error %d: %s]", name,
                                     static_cast<int>(dwRetVal), Error::Message(dwRetVal).c_str()));
        }
#endif
    }
    Map();
}

SharedMemeoryHandle::SharedMemeoryHandle(const File &file, SharedMemory::AccessMode mode,
                                             const void *addrHint)
{
}

SharedMemeoryHandle::~SharedMemeoryHandle()
{
    Unmap();
    Close();
}

char *SharedMemeoryHandle::Begin() const
{
    return m_pAddress;
}

char *SharedMemeoryHandle::End() const
{
    return m_pAddress + m_Size;
}

unsigned long long SharedMemeoryHandle::Size() const
{
    return m_Size;
}

void SharedMemeoryHandle::Map()
{
    DWORD access = FILE_MAP_READ;
    if (_mode == PAGE_READWRITE)
        access = FILE_MAP_WRITE;

    LPVOID addr = MapViewOfFile(_memHandle, access, 0, 0, m_Size);
    if (!addr)
    {
        DWORD dwRetVal = GetLastError();
        throw UtilityException(String::Format("cannot map shared memeory object  %s [Error %d: %s]",
                                                  m_strName.c_str(), static_cast<int>(dwRetVal),
                                                  Error::Message(dwRetVal).c_str()));
    }
    m_pAddress = static_cast<char *>(addr);
}

void SharedMemeoryHandle::Unmap()
{
    if (m_pAddress)
    {
        UnmapViewOfFile(m_pAddress);
        m_pAddress = 0;
        return;
    }
}

void SharedMemeoryHandle::Close()
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

SharedMemeoryHandle::SharedMemeoryHandle()
{
}

SharedMemeoryHandle::SharedMemeoryHandle(const char *name, std::size_t size,
                                             SharedMemory::AccessMode mode, const void *addrHint,
                                             bool server)
{
}

SharedMemeoryHandle::SharedMemeoryHandle(const File &file, SharedMemory::AccessMode mode,
                                             const void *addrHint)
{
}

SharedMemeoryHandle::~SharedMemeoryHandle()
{
}

char *SharedMemeoryHandle::Begin() const
{
    return nullptr;
}

char *SharedMemeoryHandle::End() const
{
    return nullptr;
}

unsigned long long SharedMemeoryHandle::Size() const
{
    return 0;
}

void SharedMemeoryHandle::Map()
{
}

void SharedMemeoryHandle::Unmap()
{
}

void SharedMemeoryHandle::Close()
{
}


#endif

}// namespace m2
