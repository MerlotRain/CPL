#include "pipehandle.h"
#include "process.h"
#include <object.h>
#ifdef _WIN32
#include <Windows.h>
#endif


namespace m2 {

/******************************************* PipeImpl *******************************************/

#ifdef _WIN32

PipeImpl::PipeImpl()
{
    SECURITY_ATTRIBUTES attr;
    attr.nLength = sizeof(attr);
    attr.lpSecurityDescriptor = NULL;
    attr.bInheritHandle = FALSE;

    if (!CreatePipe(&readHandle, &writeHandle, &attr, 0)) { throw std::runtime_error("anonymous pipe"); }
}

PipeImpl::~PipeImpl()
{
    CloseRead();
    CloseWrite();
}

int PipeImpl::Write(const unsigned char *buf, int len)
{
    assert(writeHandle);

    DWORD byteWritten = 0;
    if (!WriteFile(writeHandle, buf, len, &byteWritten, NULL))
    {
        throw std::runtime_error("anonymous pipe");
    }
    return byteWritten;
}

int PipeImpl::Read(unsigned char *buf, int len)
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

void PipeImpl::CloseWrite()
{
    if (writeHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(writeHandle);
        writeHandle = INVALID_HANDLE_VALUE;
    }
}

void PipeImpl::CloseRead()
{
    if (readHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(readHandle);
        readHandle = INVALID_HANDLE_VALUE;
    }
}

#else

PipeImpl::PipeImpl()
{
}

PipeImpl::~PipeImpl() {}

int PipeImpl::Write(const unsigned char *buf, int len) { return 0; }

int PipeImpl::Read(unsigned char *buf, int len) { return 0; }

void PipeImpl::CloseWrite() {}

void PipeImpl::CloseRead() {}

#endif


/******************************************* Pipe *******************************************/

Pipe::Pipe()
{
    PipeImpl *p = new PipeImpl();
    p->AddRef();
    m_Handle = p;
}

Pipe::Pipe(const Pipe &pipe) : m_Handle(pipe.m_Handle)
{
    (static_cast<PipeImpl *>(m_Handle))->AddRef();
}

Pipe::~Pipe() { (static_cast<PipeImpl *>(m_Handle))->Release(); }

Pipe &Pipe::operator=(const Pipe &pipe)
{
    if (this != &pipe)
    {
        (static_cast<PipeImpl *>(m_Handle))->Release();
        m_Handle = pipe.m_Handle;
        (static_cast<PipeImpl *>(m_Handle))->AddRef();
    }
    return *this;
}

int Pipe::Write(const unsigned char *pBuffer, int nLen)
{
    return (static_cast<PipeImpl *>(m_Handle))->Write(pBuffer, nLen);
}

int Pipe::Read(unsigned char *pBuffer, int nLen)
{
    return (static_cast<PipeImpl *>(m_Handle))->Read(pBuffer, nLen);
}

void Pipe::Close(PipeCloseMode mode)
{
    switch (mode)
    {
        case PipeCloseMode::eCloseRead:
            (static_cast<PipeImpl *>(m_Handle))->CloseRead();
            break;
        case PipeCloseMode::eCloseWrite:
            (static_cast<PipeImpl *>(m_Handle))->CloseWrite();
            break;
        case PipeCloseMode::eCloseAll:
            (static_cast<PipeImpl *>(m_Handle))->CloseRead();
            (static_cast<PipeImpl *>(m_Handle))->CloseWrite();
            break;
        default:
            break;
    }
}

void *Pipe::Handle()
{
    return m_Handle;
}

}// namespace m2
