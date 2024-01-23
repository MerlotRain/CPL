#include "process.h"
#include "filesystem.h"
#include "processhandle.h"

namespace m2 {

/*********************************** ProcessHandle ***********************************/

ProcessHandle::ProcessHandle()
    : m_Handle(nullptr)
{
}

ProcessHandle::ProcessHandle(void *handle)
    : m_Handle(handle)
{
}

ProcessHandle::ProcessHandle(const ProcessHandle &rhs)
    : m_Handle(rhs.m_Handle)
{
    (static_cast<ProcessHandleImpl *>(m_Handle))->AddRef();
}

ProcessHandle &ProcessHandle::operator=(const ProcessHandle &rhs)
{
    if (m_Handle)
        (static_cast<ProcessHandleImpl *>(m_Handle))->Release();

    if (&rhs != this)
    {
        (static_cast<ProcessHandleImpl *>(m_Handle))->Release();
        m_Handle = rhs.m_Handle;
        (static_cast<ProcessHandleImpl *>(m_Handle))->AddRef();
    }
    return *this;
}

ProcessHandle::~ProcessHandle()
{
    if (m_Handle)
        (static_cast<ProcessHandleImpl *>(m_Handle))->Release();
}

unsigned int ProcessHandle::PID() const
{
    if (m_Handle)
        return (static_cast<ProcessHandleImpl *>(m_Handle))->PID();
    return 0;
}

int ProcessHandle::Wait() const
{
    if (m_Handle)
        return (static_cast<ProcessHandleImpl *>(m_Handle))->Wait();
    return 0;
}

int ProcessHandle::TryWait() const
{
    if (m_Handle)
        return (static_cast<ProcessHandleImpl *>(m_Handle))->TryWait();
    return 0;
}


/*********************************** Process ***********************************/

unsigned int Process::PID()
{
    return ProcessImpl::ID();
}

void Process::Times(long &userTime, long &kernelTime)
{
    ProcessImpl::Times(userTime, kernelTime);
}

ProcessHandle Process::Launch(const char *command, const StringList &args, int option)
{
    String initialDirectory;
    _Env env;
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, 0, 0, 0, env));
}

ProcessHandle Process::Launch(const char *command, const StringList &args,
                                  const char *initialDirectory, int option)
{
    _Env env;
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, 0, 0, 0, env));
}

ProcessHandle Process::Launch(const char *command, const StringList &args, Pipe *in, Pipe *out,
                                  Pipe *error, int option)
{
    assert(in == 0 || (in != out && in != error));
    String initialDirectory;
    _Env env;
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

ProcessHandle Process::Launch(const char *command, const StringList &args,
                                  const char *initialDirectory, Pipe *in, Pipe *out, Pipe *error,
                                  int option)
{
    assert(in == 0 || (in != out && in != error));
    _Env env;
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

ProcessHandle Process::Launch(const char *command, const StringList &args, Pipe *in, Pipe *out,
                                  Pipe *error, const std::map<String, String> &env, int option)
{
    assert(in == 0 || (in != out && in != error));
    String initialDirectory;
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

ProcessHandle Process::Launch(const char *command, const StringList &args,
                                  const char *initialDirectory, Pipe *in, Pipe *out, Pipe *error,
                                  const std::map<String, String> &env, int option)
{
    assert(in == 0 || (in != out && in != error));
    return ProcessHandle(ProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

int Process::Wait(const ProcessHandle &handle)
{
    return handle.Wait();
}

int Process::TryWait(const ProcessHandle &handle)
{
    return handle.TryWait();
}

bool Process::IsRunning(const ProcessHandle &handle)
{
    return ProcessImpl::IsRunning(*(static_cast<ProcessHandleImpl *>(handle.m_Handle)));
}

bool Process::IsRunning(unsigned int pid)
{
    return ProcessImpl::IsRunning(pid);
}

void Process::Kill(ProcessHandle &handle)
{
    ProcessImpl::Kill(*(static_cast<ProcessHandleImpl *>(handle.m_Handle)));
}

void Process::Kill(unsigned int pid)
{
    ProcessImpl::Kill(pid);
}

void Process::RequestTermination(unsigned int pid)
{
    ProcessImpl::RequestTermination(pid);
}

}// namespace m2
