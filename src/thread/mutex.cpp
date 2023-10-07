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

namespace Lite {
namespace Utility {

class GsMutexImpl
{
public:
    GsMutexImpl(bool bRecursive = false);
    ~GsMutexImpl();
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


/************************* GsMutexImpl *************************/

#if GS_OS_WIN

GsMutexImpl::GsMutexImpl(bool bRecursive)
{
    InitializeCriticalSectionAndSpinCount(&_cs, 4000);
}

GsMutexImpl::~GsMutexImpl()
{
    DeleteCriticalSection(&_cs);
}

void GsMutexImpl::Lock()
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

bool GsMutexImpl::TryLock()
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

bool GsMutexImpl::TryLock(int milliseconds)
{
    static constexpr auto sleepMillis = 5;
    GsTimestamp now;
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

void GsMutexImpl::Unlock()
{
    LeaveCriticalSection(&_cs);
}

#else

GsMutexImpl::GsMutexImpl()
{
}

GsMutexImpl::~GsMutexImpl()
{
}

void GsMutexImpl::Lock()
{
}

bool GsMutexImpl::TryLock()
{
}

bool GsMutexImpl::TryLock(int milliseconds)
{
}

void GsMutexImpl::Unlock()
{
}

#endif


/************************* GsMutex *************************/

GsMutex::GsMutex()
    : m_Handle(new GsMutexImpl())
{
}

GsMutex::~GsMutex()
{
    delete m_Handle;
    m_Handle = nullptr;
}

void GsMutex::Lock()
{
    if (m_Handle)
        (static_cast<GsMutexImpl *>(m_Handle))->Lock();
}

void GsMutex::Lock(long milliseconds)
{
    if (m_Handle)
        (static_cast<GsMutexImpl *>(m_Handle))->TryLock(milliseconds);
}

void GsMutex::Unlock()
{
    if (m_Handle)
        (static_cast<GsMutexImpl *>(m_Handle))->Unlock();
}

bool GsMutex::Trylock()
{
    if (m_Handle)
        return (static_cast<GsMutexImpl *>(m_Handle))->TryLock();
    return false;
}

bool GsMutex::Trylock(long milliseconds)
{
    if (m_Handle)
        return (static_cast<GsMutexImpl *>(m_Handle))->TryLock(milliseconds);
    return false;
}

}// namespace Utility
}// namespace Lite
