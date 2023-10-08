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

#include "locker.h"
#include "workthread.h"

namespace m2 {


class UTILITY_EXPORT ThreadPool;
class UTILITY_EXPORT WorkerThread;

class UTILITY_EXPORT GsBackgroundTask : public GsRefObject
{
public:
    virtual ~GsBackgroundTask() {}

    virtual void ExecuteTask() = 0;

    virtual void Cancel();

    static GsSharedPointer<GsBackgroundTask> Create(std::function<void()> funcationTask);

protected:
    GsBackgroundTask();
    volatile bool m_bCancel;
};
GS_SMARTER_PTR(GsBackgroundTask)


enum GsDispatchOption
{
    eDummy,
    eRoundRobin,
};

class GsDispatchOp;
class UTILITY_EXPORT GsPackagedTack : public GsRefObject
{
    std::queue<GsBackgroundTaskPtr> m_Tasks;
    std::unique_ptr<GsDispatchOp> m_Option;

public:
    GsPackagedTack(GsDispatchOption option = eDummy);

    ~GsPackagedTack();

    void AddTask(GsBackgroundTask *pTask);

    void Shutdown();
};
GS_SMARTER_PTR(GsPackagedTack)

}// namespace m2
