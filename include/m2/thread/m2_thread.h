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

#ifndef M2_THREAD_H_

/// @brief 对平台线程的封装
/// @details 封装一种可以继承的线程，使其使用风格类似QThread
class M2_API WorkThread
{
public:
    /// @brief 线程优先权
    /// @details https://man7.org/linux/man-pages/man3/pthread_setschedprio.3.html
    /// @details https://learn.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities
    enum ThreadPriority
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
    enum ThreadPolicy
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
    static WorkThread *CurrentThread();

    /// @brief 挂起当前线程
    /// @return
    static int YieldCurrentThread();

    /// @brief 获取主线程策略
    /// @return
    static ThreadPriority MasterPriority();

public:
    explicit WorkThread();
    virtual ~WorkThread();

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
    int SchedulePriority(ThreadPriority priority);

    /// @brief
    /// @return
    int SchedulePriority();

    /// @brief
    /// @param policy
    /// @return
    int SchedulePolicy(ThreadPolicy policy);

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
    WorkThread(const WorkThread &) = delete;
    WorkThread &operator=(const WorkThread &) = delete;

    void *m_Handle;
};

#endif//