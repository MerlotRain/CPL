#ifndef UTILITY_WAITEVENT_H
#define UTILITY_WAITEVENT_H

#include "locker.h"
#include "preconfig.h"

#if GS_OS_WIN
#include <Windows.h>
#else
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class WaitEvent : public NonCopyable
{
public:
    enum EventType
    {
        ManualReset,
        AutoReset
    };

    explicit WaitEvent(EventType t = AutoReset);
    explicit WaitEvent(bool autoReset);
    ~WaitEvent();

    void Set();
    void Wait(int milliseconds);
    bool TryWait(int milliseconds);
    void Reset();

private:
#if GS_OS_WIN
    std::atomic<HANDLE> _event;
#else
    bool m_auto;
    bool m_state;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
#endif
};

}// namespace m2

#endif//UTILITY_WAITEVENT_H