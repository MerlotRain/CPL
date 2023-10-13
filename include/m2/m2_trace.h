/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_TRACE_H_
#define M2_TRACE_H_

#include <m2_flags.h>
#include <m2_string.h>
#include <m2_stringlist.h>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace m2 {

class StackTrace
{
public:
    struct StackLine
    {
        String Module;
        String Symbol;
        String File;
        String Line;
    };

    bool bSymbolLoaded;
    String strFullStack;
    std::vector<StackTrace::StackLine> vctLines;

#ifdef _WIN32
    HANDLE process;
    HANDLE thread;
    std::vector<HANDLE> threads;
    static StackTrace *Trace(DWORD processID, DWORD threadID,
                             struct _EXCEPTION_POINTERS *ExceptionInfo,
                             String symbolPath);
#else
    static std::vector<StackTrace::StackLine>
    Trace(unsigned int maxFrames = 63);
#endif
};

class CrashReport
{
public:
    CrashReport();

public:
    enum CrashFlag
    {
        Stack = 1 << 0,
        Plugins = 1 << 1,
        ProjectDetails = 1 << 2,
        SystemInfo = 1 << 3,
        All = Stack | Plugins | ProjectDetails | SystemInfo
    };
    M2_DECLARE_FLAGS(CrashFlags, CrashFlag)

    enum class LikelyPythonFaultCause
    {
        NotPython,
        Unknown,
        ProcessingScript,
        Plugin,
        ConsoleCommand
    };

    void setStackTrace(StackTrace *value);
    StackTrace *stackTrace() const;
    void setFlags(CrashReport::CrashFlags flags);
    CrashFlags flags() const;
    const String toHtml() const;
    const String crashID() const;
    void exportToCrashFolder();
    String crashReportFolder();
    void versionInfo(const StringList &versionInfo);

private:
    CrashFlags m_Flags;
    StackTrace *m_StackTrace = nullptr;
    StringList m_VersionInfo;
};

}// namespace m2

#endif//M2_TRACE_H_