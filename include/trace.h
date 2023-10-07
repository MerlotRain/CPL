/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file trace.h
 * @brief
 * @details
 * @date 2023-08-16
 * @author
 *
 ******************************************************************************/


#pragma once

#include "flags.h"
#include "stringhelp.h"
#ifdef _WIN32
#include <Windows.h>
#endif

namespace Lite {
namespace Utility {


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

}// namespace Utility
}// namespace Lite
