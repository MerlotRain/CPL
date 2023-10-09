#ifndef UTILITY_SHAREDMEMORYHANDLE_H
#define UTILITY_SHAREDMEMORYHANDLE_H

#include "sharedmemory.h"
#include "stringhelp.h"
#ifdef _WIN32
#include <Windows.h>
#else
#endif
#include "object.h"


namespace m2 {

class SharedMemeoryHandle : public RefObject
{
public:
    SharedMemeoryHandle();
    SharedMemeoryHandle(const char *name, std::size_t size, SharedMemory::AccessMode mode,
                          const void *addrHint, bool server);
    SharedMemeoryHandle(const File &file, SharedMemory::AccessMode mode, const void *addrHint);
    ~SharedMemeoryHandle();
    char *Begin() const;
    char *End() const;
    unsigned long long Size() const;

protected:
    void Map();
    void Unmap();
    void Close();


    String m_strName;
    unsigned long long m_Size;
    char *m_pAddress;
#ifdef _WIN32
    HANDLE _memHandle;
    HANDLE _fileHandle;
    DWORD _mode;
#else
    int _fd;
    SharedMemory::AccessMode _access;
    bool _fileMapped;
    bool _server;
#endif
};


}// namespace m2


#endif//UTILITY_SHAREDMEMORYHANDLE_H
