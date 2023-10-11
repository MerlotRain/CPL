#include "processhandle.h"
#include "pipehandle.h"
#include <error.h>
#include <filesystem.h>
#include <logger.h>
#include <process.h>

namespace m2 {


/*********************************** ProcessHandleImpl ***********************************/

#ifdef _WIN32

ProcessHandleImpl::ProcessHandleImpl(HANDLE handle, unsigned int pid)
    : _process(handle), _pid(pid)
{
}

ProcessHandleImpl::~ProcessHandleImpl()
{
    closeHandle();
}

HANDLE ProcessHandleImpl::Process() const
{
    return _process;
}

void ProcessHandleImpl::closeHandle()
{
    if (_process)
        CloseHandle(_process);
    _process = nullptr;
}

unsigned int ProcessHandleImpl::PID() const
{
    return _pid;
}

int ProcessHandleImpl::Wait() const
{
    DWORD rc = WaitForSingleObject(_process, INFINITE);
    if (rc != WAIT_OBJECT_0)
        throw std::runtime_error(String::Format("Wait failed for process %d", _pid).c_str());
    DWORD exitCode;
    if (GetExitCodeProcess(_process, &exitCode) == 0)
        throw std::runtime_error(String::Format("Cannot get exit code for process %d", _pid).c_str());

    return exitCode;
}

int ProcessHandleImpl::TryWait() const
{
    DWORD exitCode;
    if (GetExitCodeProcess(_process, &exitCode) == 0)
        throw std::runtime_error(String::Format("Cannot get exit code for process %d", _pid).c_str());
    if (exitCode == STILL_ACTIVE)
        return -1;
    else
        return exitCode;
}


/*********************************** ProcessImpl ***********************************/


std::vector<wchar_t> getUnicodeEnvironmentVariablesBuffer(const _Env &env)
{
    std::vector<wchar_t> envbuf;
    std::size_t pos = 0;

    for (const auto &p: env)
    {
        std::size_t envlen = p.first.length() + p.second.length() + 1;

        WString uname;
        TextConverter::Convert(p.first, uname);
        WString uvalue;
        TextConverter::Convert(p.second, uvalue);

        envbuf.resize(pos + envlen + 1);
        std::copy(uname.begin(), uname.end(), &envbuf[pos]);
        pos += uname.length();
        envbuf[pos] = L'=';
        ++pos;
        std::copy(uvalue.begin(), uvalue.end(), &envbuf[pos]);
        pos += uvalue.length();

        envbuf[pos] = L'\0';
        ++pos;
    }

    envbuf.resize(pos + 1);
    envbuf[pos] = L'\0';

    return envbuf;
}

_PID ProcessImpl::ID()
{
    return GetCurrentProcessId();
}

void ProcessImpl::Times(long &userTime, long &kernelTime)
{
    FILETIME ftCreation;
    FILETIME ftExit;
    FILETIME ftKernel;
    FILETIME ftUser;

    if (GetProcessTimes(GetCurrentProcess(), &ftCreation, &ftExit, &ftKernel, &ftUser) != 0)
    {
        ULARGE_INTEGER time;
        time.LowPart = ftKernel.dwLowDateTime;
        time.HighPart = ftKernel.dwHighDateTime;
        kernelTime = long(time.QuadPart / 10000000L);
        time.LowPart = ftUser.dwLowDateTime;
        time.HighPart = ftUser.dwHighDateTime;
        userTime = long(time.QuadPart / 10000000L);
    }
    else
    {
        userTime = kernelTime = -1;
    }
}

ProcessHandleImpl *ProcessImpl::Launch(const String &command, const _Args &args, const String &initialDirectory,
                                           Pipe *inPipe, Pipe *outPipe, Pipe *errPipe, const _Env &env)
{
    String commandLine = EscapeArg(command);
    for (const auto &a: args)
    {
        commandLine.append(" ");
        commandLine.append(EscapeArg(a));
    }

    WString ucommandLine;
    TextConverter::Convert(commandLine, ucommandLine);

    const wchar_t *applicationName = 0;
    WString uapplicationName;
    if (command.size() > MAX_PATH)
    {
        File file(command);
        if (file.Exists())
        {
            TextConverter::Convert(command, uapplicationName);
            if (file.Extension().empty())
                uapplicationName += L".EXE";
            applicationName = uapplicationName.c_str();
        }
    }

    STARTUPINFOW startupInfo;
    GetStartupInfoW(&startupInfo);// take defaults from current process
    startupInfo.cb = sizeof(STARTUPINFOW);
    startupInfo.lpReserved = NULL;
    startupInfo.lpDesktop = NULL;
    startupInfo.lpTitle = NULL;
    startupInfo.dwFlags = STARTF_FORCEOFFFEEDBACK;
    startupInfo.cbReserved2 = 0;
    startupInfo.lpReserved2 = NULL;

    HANDLE hProc = GetCurrentProcess();
    bool mustInheritHandles = false;
    if (inPipe)
    {
        DuplicateHandle(hProc, PIPE_HANDLE(inPipe->Handle())->readHandle, hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
        inPipe->Close(Pipe::PipeCloseMode::eCloseRead);
    }
    else if (GetStdHandle(STD_INPUT_HANDLE))
    {
        DuplicateHandle(hProc, GetStdHandle(STD_INPUT_HANDLE), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
    }
    else
    {
        startupInfo.hStdInput = 0;
    }
    // outPipe may be the same as errPipe, so we duplicate first and close later.
    if (outPipe)
    {
        DuplicateHandle(hProc, PIPE_HANDLE(inPipe->Handle())->writeHandle, hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
    }
    else if (GetStdHandle(STD_OUTPUT_HANDLE))
    {
        DuplicateHandle(hProc, GetStdHandle(STD_OUTPUT_HANDLE), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
    }
    else
    {
        startupInfo.hStdOutput = 0;
    }
    if (errPipe)
    {
        DuplicateHandle(hProc, PIPE_HANDLE(errPipe->Handle())->writeHandle, hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
    }
    else if (GetStdHandle(STD_ERROR_HANDLE))
    {
        DuplicateHandle(hProc, GetStdHandle(STD_ERROR_HANDLE), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
        mustInheritHandles = true;
    }
    else
    {
        startupInfo.hStdError = 0;
    }
    if (outPipe) outPipe->Close(Pipe::PipeCloseMode::eCloseWrite);
    if (errPipe) errPipe->Close(Pipe::PipeCloseMode::eCloseWrite);

    if (mustInheritHandles)
    {
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
    }

    WString uinitialDirectory;
    TextConverter::Convert(initialDirectory, uinitialDirectory);
    const wchar_t *workingDirectory = uinitialDirectory.empty() ? 0 : uinitialDirectory.c_str();

    const wchar_t *pEnv = 0;
    std::vector<wchar_t> envChars;
    if (!env.empty())
    {
        envChars = getUnicodeEnvironmentVariablesBuffer(env);
        pEnv = &envChars[0];
    }

    PROCESS_INFORMATION processInfo;
    DWORD creationFlags = GetConsoleWindow() ? 0 : CREATE_NO_WINDOW;
    if (pEnv) creationFlags |= CREATE_UNICODE_ENVIRONMENT;
    BOOL rc = CreateProcessW(
            applicationName,
            const_cast<wchar_t *>(ucommandLine.c_str()),
            NULL,// processAttributes
            NULL,// threadAttributes
            mustInheritHandles,
            creationFlags,
            (LPVOID) pEnv,
            workingDirectory,
            &startupInfo,
            &processInfo);
    if (startupInfo.hStdInput) CloseHandle(startupInfo.hStdInput);
    if (startupInfo.hStdOutput) CloseHandle(startupInfo.hStdOutput);
    if (startupInfo.hStdError) CloseHandle(startupInfo.hStdError);
    if (rc)
    {
        CloseHandle(processInfo.hThread);
        return new ProcessHandleImpl(processInfo.hProcess, processInfo.dwProcessId);
    }
    else
        throw std::runtime_error(String::Format("Cannot launch process %s", command.c_str()));
}

void ProcessImpl::Kill(ProcessHandleImpl &handle)
{
    if (handle.Process())
    {
        if (TerminateProcess(handle.Process(), 0) == 0)
        {
            handle.closeHandle();
            throw std::runtime_error("cannot kill process");
        }
        handle.closeHandle();
    }
}

void ProcessImpl::Kill(_PID pid)
{
    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProc)
    {
        if (TerminateProcess(hProc, 0) == 0)
        {
            CloseHandle(hProc);
            throw std::runtime_error("cannot kill process");
        }
        CloseHandle(hProc);
    }
    else
    {
        switch (GetLastError())
        {
            case ERROR_ACCESS_DENIED:
                throw std::runtime_error("cannot kill process");
            case ERROR_NOT_FOUND:
                throw std::runtime_error("cannot kill process");
            case ERROR_INVALID_PARAMETER:
                throw std::runtime_error("cannot kill process");
            default:
                throw std::runtime_error("cannot kill process");
        }
    }
}

bool ProcessImpl::IsRunning(const ProcessHandleImpl &handle)
{
    bool result = true;
    DWORD exitCode;
    BOOL rc = GetExitCodeProcess(handle.Process(), &exitCode);
    if (!rc || exitCode != STILL_ACTIVE) result = false;
    return result;
}

bool ProcessImpl::IsRunning(_PID pid)
{
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    bool result = true;
    if (hProc)
    {
        DWORD exitCode;
        BOOL rc = GetExitCodeProcess(hProc, &exitCode);
        if (!rc || exitCode != STILL_ACTIVE) result = false;
        CloseHandle(hProc);
    }
    else
    {
        result = false;
    }
    return result;
}

void ProcessImpl::RequestTermination(_PID pid)
{
    String str = TerminationEventName(pid);
    WString ustr;
    TextConverter::Convert(str, ustr);
    HANDLE event = CreateEventW(NULL, FALSE, FALSE, ustr.c_str());
    if (!event)
    {
        int code = Error::LastError();
        GS_E << String::Format("cannot create named event %s [Error %d: %s]", str.c_str(), code, Error::Message(code).c_str());
        return;
    }

    if (!SetEvent(event))
    {
        GS_E << String::Format("cannot signal named event %s", str.c_str());
    }
    CloseHandle(event);
}

String ProcessImpl::TerminationEventName(_PID pid)
{
    String evName("POCOTRM");
    evName.Arg(pid, 0x10, 8);
    return evName;
}

bool ProcessImpl::MustEscapeArg(const String &arg)
{
    bool result = false;
    bool inQuotes = false;
    bool escaped = false;
    for (char c: arg)
    {
        if (Ascii::IsSpace(c) && !inQuotes && !escaped)
        {
            result = true;
            break;
        }
        else if (c == '"' && !escaped)
        {
            inQuotes = !inQuotes;
        }
        else if (c == '\\' && !escaped)
        {
            escaped = true;
        }
        else
        {
            escaped = false;
        }
    }
    return result || inQuotes;
}

String ProcessImpl::EscapeArg(const String &arg)
{
    if (MustEscapeArg(arg))
    {
        String quotedArg("\"");
        for (String::const_iterator it = arg.begin();; ++it)
        {
            unsigned backslashCount = 0;
            while (it != arg.end() && '\\' == *it)
            {
                ++it;
                ++backslashCount;
            }

            if (it == arg.end())
            {
                quotedArg.append(2 * backslashCount, '\\');
                break;
            }
            else if ('"' == *it)
            {
                quotedArg.append(2 * backslashCount + 1, '\\');
                quotedArg.push_back('"');
            }
            else
            {
                quotedArg.append(backslashCount, '\\');
                quotedArg.push_back(*it);
            }
        }
        quotedArg.push_back('"');
        return quotedArg;
    }
    else
        return arg;
}


#elif defined(__linux__) || defined(__linux)


/*********************************** ProcessHandleImpl ********************************** */

ProcessHandleImpl::ProcessHandleImpl(pid_t pid)
{
}

ProcessHandleImpl::~ProcessHandleImpl()
{
}

unsigned int ProcessHandleImpl::PID() const
{
    return 0;
}

int ProcessHandleImpl::Wait() const
{
    return 0;
}

int ProcessHandleImpl::TryWait() const
{
    return 0;
}

/*********************************** ProcessImpl ***********************************/

_PID ProcessImpl::ID()
{
}

void ProcessImpl::Times(long &userTime, long &kernelTime)
{
}

ProcessHandleImpl *ProcessImpl::Launch(const String &command, const _Args &args, const String &initialDirectory,
                                           Pipe *inPipe, Pipe *outPipe, Pipe *errPipe, const _Env &env)
{
    return nullptr;
}

void ProcessImpl::Kill(ProcessHandleImpl &handle)
{
}

void ProcessImpl::Kill(_PID pid)
{
}

bool ProcessImpl::IsRunning(const ProcessHandleImpl &handle)
{
    return false;
}

bool ProcessImpl::IsRunning(_PID pid)
{
    return false;
}

void ProcessImpl::RequestTermination(_PID pid)
{
}

ProcessHandleImpl *ProcessImpl::LaunchByForkExec(const String &command, const _Args &args,
                                                     const String &initialDirectory, Pipe *inPipe,
                                                     Pipe *outPipe, Pipe *errPipe, const _Env &env)
{
    return nullptr;
}

#endif

}// namespace m2
