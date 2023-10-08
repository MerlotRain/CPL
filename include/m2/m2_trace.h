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


#pragma once

#include "flags.h"
#include "stringhelp.h"
#ifdef _WIN32
#include <Windows.h>
#endif

namespace m2 {


/// @brief 错误信息
/// @details 用于捕获平台抛出的错误代码和错误信息
/// @details 仅Utility模块使用，其余模块应脱离系统函数，或将需要的系统函数封装到Utility模块中
/// @details 所有错误信息都会被写入到日志中
class M2_API GsError
{
public:
    /// @brief 获取系统最近的错误编码
    /// @return
    static int LastError();

    /// @brief 获取错误编码对应的错误信息
    /// @param code
    /// @return
    static GsString Message(int code);
};


/// @brief 异常
class M2_API GsException : public std::runtime_error
{
public:
    GsException() : std::runtime_error("Unknown error") {}

    explicit GsException(GsString const &msg) : std::runtime_error(msg) {}

    GsException(GsString const &name, GsString const &msg)
        : std::runtime_error(name + ": " + msg)
    {
    }
};

/// @brief 参数错误的异常
class M2_API GsIllegalArgumentException : public GsException
{
public:
    GsIllegalArgumentException()
        : GsException("IllegalArgumentException", "")
    {
    }

    explicit GsIllegalArgumentException(const std::string &msg)
        : GsException("IllegalArgumentException", msg)
    {
    }

    ~GsIllegalArgumentException() noexcept override = default;
};

/// @brief 栈追踪
class GsStackTrace
{
public:
    /// @brief 堆栈信息
    struct GsStackLine
    {
        GsString Module;
        GsString Symbol;
        GsString File;
        GsString Line;
    };

    bool bSymbolLoaded;
    GsString strFullStack;
    std::vector<GsStackTrace::GsStackLine> vctLines;

#ifdef _WIN32
    HANDLE process;
    HANDLE thread;
    std::vector<HANDLE> threads;
    /// @brief 返回调用方函数的解映射堆栈回溯
    /// @param processID
    /// @param threadID
    /// @param ExceptionInfo
    /// @param symbolPath
    /// @return
    static GsStackTrace *Trace(DWORD processID, DWORD threadID, struct _EXCEPTION_POINTERS *ExceptionInfo, GsString symbolPath);
#else
    static std::vector<GsStackTrace::GsStackLine> Trace(unsigned int maxFrames = 63);
#endif
};

/// @brief 崩溃日志
class GsCrashReport
{
public:
    GsCrashReport();

public:
    enum CrashFlag
    {
        Stack = 1 << 0,
        Plugins = 1 << 1,
        ProjectDetails = 1 << 2,
        SystemInfo = 1 << 3,
        All = Stack | Plugins | ProjectDetails | SystemInfo
    };
    GS_DECLARE_FLAGS(CrashFlags, CrashFlag)

    enum class LikelyPythonFaultCause
    {
        NotPython,
        Unknown,
        ProcessingScript,
        Plugin,
        ConsoleCommand
    };

    /// @brief 设置崩溃报告的堆栈跟踪
    /// @param value
    void StackTrace(GsStackTrace *value);

    /// @brief 崩溃报告的堆栈跟踪
    /// @return
    GsStackTrace *StackTrace() const;

    /// @brief 设置标志以标记此故障报告中包含的功能
    /// @param flags
    void Flags(GsCrashReport::CrashFlags flags);

    /// @brief 标记此故障报告中包含的功能
    /// @return
    CrashFlags Flags() const;

    /// @brief 崩溃日志转为Html格式
    /// @return
    const GsString ToHtml() const;

    /// @brief 为崩溃报告生成崩溃ID
    /// @return
    const GsString CrashID() const;

    /// @brief 导出崩溃报告到指定文件夹
    void ExportToCrashFolder();
    /// @brief 崩溃日志路径
    /// @return
    GsString CrashReportFolder();
    /// @brief 设置版本信息
    /// @param versionInfo
    void VersionInfo(const GsStringList &versionInfo);

private:
    CrashFlags m_Flags;
    GsStackTrace *m_StackTrace = nullptr;
    GsStringList m_VersionInfo;
};

}// namespace m2
