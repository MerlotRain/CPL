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

namespace m2 {

#ifdef _WIN32

class ProcessHandleImpl : public RefObject
{
public:
    ProcessHandleImpl(HANDLE handle, unsigned int pid);
    virtual ~ProcessHandleImpl();
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
typedef std::vector<String> _Args;
typedef std::map<String, String> _Env;

class ProcessImpl
{
public:
    static _PID ID();
    static void Times(long &userTime, long &kernelTime);
    static ProcessHandleImpl *Launch(const String &command, const _Args &args,
                                       const String &initialDirectory, Pipe *inPipe,
                                       Pipe *outPipe, Pipe *errPipe, const _Env &env);
    static void Kill(ProcessHandleImpl &handle);
    static void Kill(_PID pid);
    static bool IsRunning(const ProcessHandleImpl &handle);
    static bool IsRunning(_PID pid);
    static void RequestTermination(_PID pid);
    static String TerminationEventName(_PID pid);
    static bool MustEscapeArg(const String &arg);
    static String EscapeArg(const String &arg);
};


#elif defined(__linux__) || defined(__linux)

class ProcessHandleImpl : public RefObject
{
public:
    ProcessHandleImpl(pid_t pid);
    virtual ~ProcessHandleImpl();
    virtual unsigned int PID() const;
    virtual int Wait() const;
    virtual int TryWait() const;

protected:
    pid_t _pid;
};

typedef pid_t _PID;
typedef std::vector<String> _Args;
typedef std::map<String, String> _Env;

class ProcessImpl
{
public:
    static _PID ID();
    static void Times(long &userTime, long &kernelTime);
    static ProcessHandleImpl *Launch(const String &command, const _Args &args,
                                       const String &initialDirectory, Pipe *inPipe,
                                       Pipe *outPipe, Pipe *errPipe, const _Env &env);
    static void Kill(ProcessHandleImpl &handle);
    static void Kill(_PID pid);
    static bool IsRunning(const ProcessHandleImpl &handle);
    static bool IsRunning(_PID pid);
    static void RequestTermination(_PID pid);

private:
    static ProcessHandleImpl *LaunchByForkExec(const String &command, const _Args &args,
                                                 const String &initialDirectory, Pipe *inPipe,
                                                 Pipe *outPipe, Pipe *errPipe, const _Env &env);
};

#endif


}// namespace m2


#endif//UTILITY_PROCESSHANDLE_H
