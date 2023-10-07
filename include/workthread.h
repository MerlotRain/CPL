/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file workthread.h
 * @brief
 * @details
 * @date 2023-07-05
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"

namespace Lite {
namespace Utility {

/// @brief 对平台线程的封装
/// @details 封装一种可以继承的线程，使其使用风格类似QThread
class UTILITY_EXPORT GsWorkThread
{
public:
    /// @brief 线程优先权
    /// @details https://man7.org/linux/man-pages/man3/pthread_setschedprio.3.html
    /// @details https://learn.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities
    enum GsThreadPriority
    {
        eTHREAD_PRIORITY_HIGHEST,
        eTHREAD_PRIORITY_HIGH,
        eTHREAD_PRIORITY_NOMINAL,
        eTHREAD_PRIORITY_LOW,
        eTHREAD_PRIORITY_LOWEST,
        eTHREAD_PRIORITY_DEFAULT
    };

    /// @brief 线程调度策略
    /// @details https://www.man7.org/linux/man-pages/man7/sched.7.html
    enum GsThreadPolicy
    {
        eTHREAD_SCHEDULE_FIFO,
        eTHREAD_SCHEDULE_ROUND_ROBIN,
        eTHREAD_SCHEDULE_TIME_SHARE,
        eTHREAD_SCHEDULE_DEFAULT
    };

    /// @brief 获取处理器的数量
    /// @return
    static int NumberOfProcessors();
    /// @brief 设置当前线程的处理器相关
    /// @param cpunum
    /// @return
    static int ProcessorAffinityOfCurrentThread(unsigned int cpunum);

    /// @brief 线程休眠时间
    /// @param microsec
    /// @return
    static void Sleep(unsigned int);
    static void MicroSleep(unsigned int);
    static void MilliSleep(unsigned int);
    /// @brief 获取逻辑CPU的数量，最大线程数
    /// @return
    static int LogicCPUCount();
    /// @brief 获取当前线程
    /// @return
    static GsWorkThread *CurrentThread();

    /// @brief 挂起当前线程
    /// @return
    static int YieldCurrentThread();

    /// @brief 获取主线程策略
    /// @return
    static GsThreadPriority MasterPriority();

public:
    explicit GsWorkThread();
    virtual ~GsWorkThread();

    /// @brief 获取当前线程Id
    /// @return
    int ThreadId();

    /// @brief 获取当前进程Id
    /// @return
    size_t ProcessId();

    /// @brief 开启线程
    /// @return
    int Start();
    /// @brief 终止线程
    /// @return
    virtual int Cancel();

    /// @brief
    /// @param priority
    /// @return
    int SchedulePriority(GsThreadPriority priority);

    /// @brief
    /// @return
    int SchedulePriority();

    /// @brief
    /// @param policy
    /// @return
    int SchedulePolicy(GsThreadPolicy policy);

    /// @brief
    /// @return
    int SchedulePolicy();

    /// @brief
    /// @param size
    /// @return
    int StackSize(size_t size);

    /// @brief
    /// @return
    size_t StackSize();

    /// @brief
    /// @return
    int CancelModeDisable();

    /// @brief
    /// @return
    int CancelModeAsynchronous();

    /// @brief
    /// @return
    int CancelModeDeferred();

    /// @brief
    /// @return
    bool IsRunning();

    /// @brief
    virtual void CancelCleanup();

    /// @brief
    /// @return
    void *Implementation();

    /// @brief
    /// @param cpunum
    /// @return
    int ProcessorAffinity(unsigned int cpunum);

    /// @brief
    /// @param microsec
    /// @return
    int InterruptibleWait(unsigned int microsec);

protected:
    /// @brief 线程执行的函数
    virtual void Run() = 0;

private:
    GsWorkThread(const GsWorkThread &) = delete;
    GsWorkThread &operator=(const GsWorkThread &) = delete;

    void *m_Handle;
};


}// namespace Utility
}// namespace Lite
