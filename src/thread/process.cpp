#include "process.h"
#include "filesystem.h"
#include "processhandle.h"

namespace Lite {
namespace Utility {

/*********************************** GsProcessHandle ***********************************/

GsProcessHandle::GsProcessHandle()
    : m_Handle(nullptr)
{
}

GsProcessHandle::GsProcessHandle(void *handle)
    : m_Handle(handle)
{
}

GsProcessHandle::GsProcessHandle(const GsProcessHandle &rhs)
    : m_Handle(rhs.m_Handle)
{
    (static_cast<GsProcessHandleImpl *>(m_Handle))->AddRef();
}

GsProcessHandle &GsProcessHandle::operator=(const GsProcessHandle &rhs)
{
    if (m_Handle)
        (static_cast<GsProcessHandleImpl *>(m_Handle))->Release();

    if (&rhs != this)
    {
        (static_cast<GsProcessHandleImpl *>(m_Handle))->Release();
        m_Handle = rhs.m_Handle;
        (static_cast<GsProcessHandleImpl *>(m_Handle))->AddRef();
    }
    return *this;
}

GsProcessHandle::~GsProcessHandle()
{
    if (m_Handle)
        (static_cast<GsProcessHandleImpl *>(m_Handle))->Release();
}

unsigned int GsProcessHandle::PID() const
{
    if (m_Handle)
        return (static_cast<GsProcessHandleImpl *>(m_Handle))->PID();
    return 0;
}

int GsProcessHandle::Wait() const
{
    if (m_Handle)
        return (static_cast<GsProcessHandleImpl *>(m_Handle))->Wait();
    return 0;
}

int GsProcessHandle::TryWait() const
{
    if (m_Handle)
        return (static_cast<GsProcessHandleImpl *>(m_Handle))->TryWait();
    return 0;
}


/*********************************** GsProcess ***********************************/

unsigned int GsProcess::PID()
{
    return GsProcessImpl::ID();
}

void GsProcess::Times(long &userTime, long &kernelTime)
{
    GsProcessImpl::Times(userTime, kernelTime);
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args, int option)
{
    GsString initialDirectory;
    _Env env;
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, 0, 0, 0, env));
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, int option)
{
    _Env env;
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, 0, 0, 0, env));
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args, GsPipe *in, GsPipe *out,
                                  GsPipe *error, int option)
{
    assert(in == 0 || (in != out && in != error));
    GsString initialDirectory;
    _Env env;
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, GsPipe *in, GsPipe *out, GsPipe *error,
                                  int option)
{
    assert(in == 0 || (in != out && in != error));
    _Env env;
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args, GsPipe *in, GsPipe *out,
                                  GsPipe *error, const std::map<GsString, GsString> &env, int option)
{
    assert(in == 0 || (in != out && in != error));
    GsString initialDirectory;
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

GsProcessHandle GsProcess::Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, GsPipe *in, GsPipe *out, GsPipe *error,
                                  const std::map<GsString, GsString> &env, int option)
{
    assert(in == 0 || (in != out && in != error));
    return GsProcessHandle(GsProcessImpl::Launch(command, args, initialDirectory, in, out, error, env));
}

int GsProcess::Wait(const GsProcessHandle &handle)
{
    return handle.Wait();
}

int GsProcess::TryWait(const GsProcessHandle &handle)
{
    return handle.TryWait();
}

bool GsProcess::IsRunning(const GsProcessHandle &handle)
{
    return GsProcessImpl::IsRunning(*(static_cast<GsProcessHandleImpl *>(handle.m_Handle)));
}

bool GsProcess::IsRunning(unsigned int pid)
{
    return GsProcessImpl::IsRunning(pid);
}

void GsProcess::Kill(GsProcessHandle &handle)
{
    GsProcessImpl::Kill(*(static_cast<GsProcessHandleImpl *>(handle.m_Handle)));
}

void GsProcess::Kill(unsigned int pid)
{
    GsProcessImpl::Kill(pid);
}

void GsProcess::RequestTermination(unsigned int pid)
{
    GsProcessImpl::RequestTermination(pid);
}

}// namespace Utility
}// namespace Lite
