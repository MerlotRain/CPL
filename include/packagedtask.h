/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file packagedtask.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "locker.h"
#include "workthread.h"

namespace Lite {
namespace Utility {


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

}// namespace Utility
}// namespace Lite
