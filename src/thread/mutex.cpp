#include "../exception_p.h"
#include <datetime.h>
#include <locker.h>
#include <logger.h>

#include <preconfig.h>
#if GS_OS_WIN
#include <Windows.h>
#else
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class MutexImpl
{
public:
    MutexImpl(bool bRecursive = false);
    ~MutexImpl();
    void Lock();
    bool TryLock();
    bool TryLock(int milliseconds);
    void Unlock();

private:
#if GS_OS_WIN
    CRITICAL_SECTION _cs;
#else
    pthread_mutex_t _mutex;
#endif
};


/************************* MutexImpl *************************/

#if GS_OS_WIN

MutexImpl::MutexImpl(bool bRecursive)
{
    InitializeCriticalSectionAndSpinCount(&_cs, 4000);
}

MutexImpl::~MutexImpl()
{
    DeleteCriticalSection(&_cs);
}

void MutexImpl::Lock()
{
    try
    {
        EnterCriticalSection(&_cs);
    }
    catch (const std::exception &e)
    {
        GS_E << e.what();
    }
}

bool MutexImpl::TryLock()
{
    try
    {
        return TryEnterCriticalSection(&_cs) != 0;
    }
    catch (const std::exception &e)
    {
        GS_E << e.what();
    }

    return false;
}

bool MutexImpl::TryLock(int milliseconds)
{
    static constexpr auto sleepMillis = 5;
    Timestamp now;
    long long diff = milliseconds * 1000;
    do
    {
        try
        {
            if (TryEnterCriticalSection(&_cs) == TRUE)
                return true;
        }
        catch (const std::exception &e)
        {
            GS_E << e.what();
        }
        Sleep(sleepMillis);
    } while (!now.IsElapsed(diff));
    return false;
}

void MutexImpl::Unlock()
{
    LeaveCriticalSection(&_cs);
}

#else

MutexImpl::MutexImpl()
{
}

MutexImpl::~MutexImpl()
{
}

void MutexImpl::Lock()
{
}

bool MutexImpl::TryLock()
{
}

bool MutexImpl::TryLock(int milliseconds)
{
}

void MutexImpl::Unlock()
{
}

#endif


/************************* Mutex *************************/

Mutex::Mutex()
    : m_Handle(new MutexImpl())
{
}

Mutex::~Mutex()
{
    delete m_Handle;
    m_Handle = nullptr;
}

void Mutex::Lock()
{
    if (m_Handle)
        (static_cast<MutexImpl *>(m_Handle))->Lock();
}

void Mutex::Lock(long milliseconds)
{
    if (m_Handle)
        (static_cast<MutexImpl *>(m_Handle))->TryLock(milliseconds);
}

void Mutex::Unlock()
{
    if (m_Handle)
        (static_cast<MutexImpl *>(m_Handle))->Unlock();
}

bool Mutex::Trylock()
{
    if (m_Handle)
        return (static_cast<MutexImpl *>(m_Handle))->TryLock();
    return false;
}

bool Mutex::Trylock(long milliseconds)
{
    if (m_Handle)
        return (static_cast<MutexImpl *>(m_Handle))->TryLock(milliseconds);
    return false;
}

}// namespace m2
