#include "sharedmemory.h"
#include "sharedmemoryhandle.h"

namespace Lite {
namespace Utility {


GsSharedMemory::GsSharedMemory() : m_Handle(0)
{
}

GsSharedMemory::GsSharedMemory(const char *name, std::size_t size, AccessMode mode, const void *addrHint,
                               bool server)
    : m_Handle(new GsSharedMemeoryHandle(name, size, mode, addrHint, server))
{
    (static_cast<GsSharedMemeoryHandle *>(m_Handle))->AddRef();
}

GsSharedMemory::GsSharedMemory(const GsFile &file, AccessMode mode, const void *addrHint)
    : m_Handle(new GsSharedMemeoryHandle(file, mode, addrHint))
{
    (static_cast<GsSharedMemeoryHandle *>(m_Handle))->AddRef();
}

GsSharedMemory::GsSharedMemory(const GsSharedMemory &rhs) : m_Handle(rhs.m_Handle)
{
    if (m_Handle)
        (static_cast<GsSharedMemeoryHandle *>(m_Handle))->AddRef();
}

GsSharedMemory::~GsSharedMemory()
{
    if (m_Handle)
        (static_cast<GsSharedMemeoryHandle *>(m_Handle))->Release();
}

GsSharedMemory &GsSharedMemory::operator=(const GsSharedMemory &rhs)
{
    GsSharedMemory tmp(rhs);
    Swap(tmp);
    return *this;
}

void GsSharedMemory::Swap(GsSharedMemory &rhs) noexcept
{
    std::swap(m_Handle, rhs.m_Handle);
}

char *GsSharedMemory::Begin() const
{
    if (m_Handle)
        return (static_cast<GsSharedMemeoryHandle *>(m_Handle))->Begin();
    return nullptr;
}

char *GsSharedMemory::End() const
{
    if (m_Handle)
        return (static_cast<GsSharedMemeoryHandle *>(m_Handle))->End();
    return nullptr;
}

unsigned long long GsSharedMemory::Size() const
{
    if (m_Handle)
        return (static_cast<GsSharedMemeoryHandle *>(m_Handle))->Size();
    return 0;
}


}// namespace Utility
}// namespace Lite
