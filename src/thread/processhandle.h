#ifndef UTILITY_PROCESSHANDLE_H
#define UTILITY_PROCESSHANDLE_H

#include "object.h"
#include "process.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace Lite {
namespace Utility {

#ifdef _WIN32

class GsProcessHandleImpl : public GsRefObject
{
public:
    GsProcessHandleImpl(HANDLE handle, unsigned int pid);
    virtual ~GsProcessHandleImpl();
    HANDLE Process() const;
    void closeHandle();

    virtual unsigned int PID() const;
    virtual int Wait() const;
    virtual int TryWait() const;

protected:
    HANDLE _process;
    unsigned int _pid;
};


typedef unsigned int _PID;
typedef std::vector<GsString> _Args;
typedef std::map<GsString, GsString> _Env;

class GsProcessImpl
{
public:
    static _PID ID();
    static void Times(long &userTime, long &kernelTime);
    static GsProcessHandleImpl *Launch(const GsString &command, const _Args &args,
                                       const GsString &initialDirectory, GsPipe *inPipe,
                                       GsPipe *outPipe, GsPipe *errPipe, const _Env &env);
    static void Kill(GsProcessHandleImpl &handle);
    static void Kill(_PID pid);
    static bool IsRunning(const GsProcessHandleImpl &handle);
    static bool IsRunning(_PID pid);
    static void RequestTermination(_PID pid);
    static GsString TerminationEventName(_PID pid);
    static bool MustEscapeArg(const GsString &arg);
    static GsString EscapeArg(const GsString &arg);
};


#elif defined(__linux__) || defined(__linux)

class GsProcessHandleImpl : public GsRefObject
{
public:
    GsProcessHandleImpl(pid_t pid);
    virtual ~GsProcessHandleImpl();
    virtual unsigned int PID() const;
    virtual int Wait() const;
    virtual int TryWait() const;

protected:
    pid_t _pid;
};

typedef pid_t _PID;
typedef std::vector<GsString> _Args;
typedef std::map<GsString, GsString> _Env;

class GsProcessImpl
{
public:
    static _PID ID();
    static void Times(long &userTime, long &kernelTime);
    static GsProcessHandleImpl *Launch(const GsString &command, const _Args &args,
                                       const GsString &initialDirectory, GsPipe *inPipe,
                                       GsPipe *outPipe, GsPipe *errPipe, const _Env &env);
    static void Kill(GsProcessHandleImpl &handle);
    static void Kill(_PID pid);
    static bool IsRunning(const GsProcessHandleImpl &handle);
    static bool IsRunning(_PID pid);
    static void RequestTermination(_PID pid);

private:
    static GsProcessHandleImpl *LaunchByForkExec(const GsString &command, const _Args &args,
                                                 const GsString &initialDirectory, GsPipe *inPipe,
                                                 GsPipe *outPipe, GsPipe *errPipe, const _Env &env);
};

#endif


}// namespace Utility
}// namespace Lite


#endif//UTILITY_PROCESSHANDLE_H
