#include "sharedmemory.h"
#include "sharedmemoryhandle.h"

namespace m2 {


SharedMemory::SharedMemory() : m_Handle(0)
{
}

SharedMemory::SharedMemory(const char *name, std::size_t size, AccessMode mode, const void *addrHint,
                               bool server)
    : m_Handle(new SharedMemeoryHandle(name, size, mode, addrHint, server))
{
    (static_cast<SharedMemeoryHandle *>(m_Handle))->AddRef();
}

SharedMemory::SharedMemory(const File &file, AccessMode mode, const void *addrHint)
    : m_Handle(new SharedMemeoryHandle(file, mode, addrHint))
{
    (static_cast<SharedMemeoryHandle *>(m_Handle))->AddRef();
}

SharedMemory::SharedMemory(const SharedMemory &rhs) : m_Handle(rhs.m_Handle)
{
    if (m_Handle)
        (static_cast<SharedMemeoryHandle *>(m_Handle))->AddRef();
}

SharedMemory::~SharedMemory()
{
    if (m_Handle)
        (static_cast<SharedMemeoryHandle *>(m_Handle))->Release();
}

SharedMemory &SharedMemory::operator=(const SharedMemory &rhs)
{
    SharedMemory tmp(rhs);
    Swap(tmp);
    return *this;
}

void SharedMemory::Swap(SharedMemory &rhs) noexcept
{
    std::swap(m_Handle, rhs.m_Handle);
}

char *SharedMemory::Begin() const
{
    if (m_Handle)
        return (static_cast<SharedMemeoryHandle *>(m_Handle))->Begin();
    return nullptr;
}

char *SharedMemory::End() const
{
    if (m_Handle)
        return (static_cast<SharedMemeoryHandle *>(m_Handle))->End();
    return nullptr;
}

unsigned long long SharedMemory::Size() const
{
    if (m_Handle)
        return (static_cast<SharedMemeoryHandle *>(m_Handle))->Size();
    return 0;
}


}// namespace m2
