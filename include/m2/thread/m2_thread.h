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
#define M2_THREAD_H_

#include <preconfig.h>

class M2_API WorkThread
{
public:
    enum ThreadPriority
    {
        eTHREAD_PRIORITY_HIGHEST,
        eTHREAD_PRIORITY_HIGH,
        eTHREAD_PRIORITY_NOMINAL,
        eTHREAD_PRIORITY_LOW,
        eTHREAD_PRIORITY_LOWEST,
        eTHREAD_PRIORITY_DEFAULT
    };

    enum ThreadPolicy
    {
        eTHREAD_SCHEDULE_FIFO,
        eTHREAD_SCHEDULE_ROUND_ROBIN,
        eTHREAD_SCHEDULE_TIME_SHARE,
        eTHREAD_SCHEDULE_DEFAULT
    };

    static int NumberOfProcessors();
    static int ProcessorAffinityOfCurrentThread(unsigned int cpunum);
    static void Sleep(unsigned int);
    static void MicroSleep(unsigned int);
    static void MilliSleep(unsigned int);
    static int LogicCPUCount();

    static WorkThread *CurrentThread();
    static int YieldCurrentThread();
    static ThreadPriority MasterPriority();

public:
    explicit WorkThread();
    virtual ~WorkThread();
    int ThreadId();
    size_t ProcessId();
    int Start();
    virtual int Cancel();
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