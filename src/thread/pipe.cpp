#include "pipehandle.h"
#include "process.h"
#include <object.h>
#ifdef _WIN32
#include <Windows.h>
#endif


namespace Lite {
namespace Utility {

/******************************************* GsPipeImpl *******************************************/

#ifdef _WIN32

GsPipeImpl::GsPipeImpl()
{
    SECURITY_ATTRIBUTES attr;
    attr.nLength = sizeof(attr);
    attr.lpSecurityDescriptor = NULL;
    attr.bInheritHandle = FALSE;

    if (!CreatePipe(&readHandle, &writeHandle, &attr, 0)) { throw std::runtime_error("anonymous pipe"); }
}

GsPipeImpl::~GsPipeImpl()
{
    CloseRead();
    CloseWrite();
}

int GsPipeImpl::Write(const unsigned char *buf, int len)
{
    assert(writeHandle);

    DWORD byteWritten = 0;
    if (!WriteFile(writeHandle, buf, len, &byteWritten, NULL))
    {
        throw std::runtime_error("anonymous pipe");
    }
    return byteWritten;
}

int GsPipeImpl::Read(unsigned char *buf, int len)
{
    assert(readHandle);

    DWORD byteRead = 0;
    BOOL ok = ReadFile(readHandle, buf, len, &byteRead, NULL);
    if (ok || GetLastError() == ERROR_BROKEN_PIPE)
    {
        return byteRead;
    }
    else
    {
        throw std::runtime_error("anonymous pipe");
    }
}

void GsPipeImpl::CloseWrite()
{
    if (writeHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(writeHandle);
        writeHandle = INVALID_HANDLE_VALUE;
    }
}

void GsPipeImpl::CloseRead()
{
    if (readHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(readHandle);
        readHandle = INVALID_HANDLE_VALUE;
    }
}

#else

GsPipeImpl::GsPipeImpl()
{
}

GsPipeImpl::~GsPipeImpl() {}

int GsPipeImpl::Write(const unsigned char *buf, int len) { return 0; }

int GsPipeImpl::Read(unsigned char *buf, int len) { return 0; }

void GsPipeImpl::CloseWrite() {}

void GsPipeImpl::CloseRead() {}

#endif


/******************************************* GsPipe *******************************************/

GsPipe::GsPipe()
{
    GsPipeImpl *p = new GsPipeImpl();
    p->AddRef();
    m_Handle = p;
}

GsPipe::GsPipe(const GsPipe &pipe) : m_Handle(pipe.m_Handle)
{
    (static_cast<GsPipeImpl *>(m_Handle))->AddRef();
}

GsPipe::~GsPipe() { (static_cast<GsPipeImpl *>(m_Handle))->Release(); }

GsPipe &GsPipe::operator=(const GsPipe &pipe)
{
    if (this != &pipe)
    {
        (static_cast<GsPipeImpl *>(m_Handle))->Release();
        m_Handle = pipe.m_Handle;
        (static_cast<GsPipeImpl *>(m_Handle))->AddRef();
    }
    return *this;
}

int GsPipe::Write(const unsigned char *pBuffer, int nLen)
{
    return (static_cast<GsPipeImpl *>(m_Handle))->Write(pBuffer, nLen);
}

int GsPipe::Read(unsigned char *pBuffer, int nLen)
{
    return (static_cast<GsPipeImpl *>(m_Handle))->Read(pBuffer, nLen);
}

void GsPipe::Close(GsPipeCloseMode mode)
{
    switch (mode)
    {
        case GsPipeCloseMode::eCloseRead:
            (static_cast<GsPipeImpl *>(m_Handle))->CloseRead();
            break;
        case GsPipeCloseMode::eCloseWrite:
            (static_cast<GsPipeImpl *>(m_Handle))->CloseWrite();
            break;
        case GsPipeCloseMode::eCloseAll:
            (static_cast<GsPipeImpl *>(m_Handle))->CloseRead();
            (static_cast<GsPipeImpl *>(m_Handle))->CloseWrite();
            break;
        default:
            break;
    }
}

void *GsPipe::Handle()
{
    return m_Handle;
}

}// namespace Utility
}// namespace Lite
