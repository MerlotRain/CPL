#include <locker.h>
#if GS_OS_WIN
#include <Windows.h>
#else
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class GsRWLockImpl
{
public:
    GsRWLockImpl();
    ~GsRWLockImpl();
    void ReadLock();
    bool TryReadLock();
    void WriteLock();
    bool TryWriteLock();
    void Unlock();

private:
#if GS_OS_WIN
    void AddWriter();
    void RemoveWriter();
    DWORD TryReadLockOnce();
    HANDLE m_mutex;
    HANDLE m_readEvent;
    HANDLE m_writeEvent;
    unsigned m_readers;
    unsigned m_writersWaiting;
    unsigned m_writers;
#else
    pthread_rwlock_t m_rwl;
#endif
};


#if GS_OS_WIN

GsRWLockImpl::GsRWLockImpl()
    : m_readers(0), m_writers(0), m_writersWaiting(0)
{
    m_mutex = CreateMutexW(NULL, FALSE, NULL);
    if (!m_mutex)
        throw std::runtime_error("cannot create readwrite mutex");

    m_readEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
    if (!m_readEvent)
        throw std::runtime_error("cannot create readwrite mutex");

    m_writeEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
    if (!m_writeEvent)
        throw std::runtime_error("cannot create readwrite mutex");
}

GsRWLockImpl::~GsRWLockImpl()
{
    CloseHandle(m_mutex);
    CloseHandle(m_readEvent);
    CloseHandle(m_writeEvent);
}

void GsRWLockImpl::ReadLock()
{
    HANDLE hdl[2];
    hdl[0] = m_mutex;
    hdl[1] = m_readEvent;
    switch (WaitForMultipleObjects(2, hdl, TRUE, INFINITE))
    {
        case WAIT_OBJECT_0:
        case WAIT_OBJECT_0 + 1:
            ++m_readers;
            ResetEvent(m_writeEvent);
            ReleaseMutex(m_mutex);
            break;
        default:
            throw std::runtime_error("cannot lock readwrite mutex");
    }
}

bool GsRWLockImpl::TryReadLock()
{
    for (;;)
    {
        if (m_writers != 0 || m_writersWaiting != 0)
            return false;

        DWORD result = TryReadLockOnce();
        switch (result)
        {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                return true;
                break;
            case WAIT_TIMEOUT:
                continue;
            default:
                throw std::runtime_error("cannot lock readwrite mutex");
        }
    }
}

void GsRWLockImpl::WriteLock()
{
    AddWriter();
    HANDLE hdl[2];
    hdl[0] = m_mutex;
    hdl[1] = m_writeEvent;
    switch (WaitForMultipleObjects(2, hdl, TRUE, INFINITE))
    {
        case WAIT_OBJECT_0:
        case WAIT_OBJECT_0 + 1:
            --m_writersWaiting;
            ++m_readers;
            ++m_writers;
            ResetEvent(m_readEvent);
            ResetEvent(m_writeEvent);
            ReleaseMutex(m_mutex);
            break;
        default:
            RemoveWriter();
            throw std::runtime_error("cannot lock readwrite mutex");
    }
}

bool GsRWLockImpl::TryWriteLock()
{
    AddWriter();
    HANDLE hdl[2];
    hdl[0] = m_mutex;
    hdl[1] = m_writeEvent;
    switch (WaitForMultipleObjects(2, hdl, TRUE, 1))
    {
        case WAIT_OBJECT_0:
        case WAIT_OBJECT_0 + 1:
            --m_writersWaiting;
            ++m_readers;
            ++m_writers;
            ResetEvent(m_readEvent);
            ResetEvent(m_writeEvent);
            ReleaseMutex(m_mutex);
            return true;
        case WAIT_TIMEOUT:
            RemoveWriter();
            return false;
        default:
            RemoveWriter();
            throw std::runtime_error("cannot lock readwrite mutex");
    }
}

void GsRWLockImpl::Unlock()
{
    switch (WaitForSingleObject(m_mutex, INFINITE))
    {
        case WAIT_OBJECT_0:
            m_writers = 0;
            if (m_writersWaiting == 0)
                SetEvent(m_readEvent);
            if (--m_readers == 0)
                SetEvent(m_writeEvent);
            ReleaseMutex(m_mutex);
            break;
        default:
            throw std::runtime_error("cannot unlock readwrite mutex");
    }
}

void GsRWLockImpl::AddWriter()
{
    switch (WaitForSingleObject(m_mutex, INFINITE))
    {
        case WAIT_OBJECT_0:
            if (++m_writersWaiting == 1) ResetEvent(m_readEvent);
            ReleaseMutex(m_mutex);
            break;
        default:
            throw std::runtime_error("cannot unlock readwrite mutex");
    }
}

void GsRWLockImpl::RemoveWriter()
{
    switch (WaitForSingleObject(m_mutex, INFINITE))
    {
        case WAIT_OBJECT_0:
            if (--m_writersWaiting == 0 && m_writers == 0) SetEvent(m_readEvent);
            ReleaseMutex(m_mutex);
            break;
        default:
            throw std::runtime_error("cannot unlock readwrite mutex");
    }
}

DWORD GsRWLockImpl::TryReadLockOnce()
{
    HANDLE hdl[2];
    hdl[0] = m_mutex;
    hdl[1] = m_readEvent;
    DWORD result = WaitForMultipleObjects(2, hdl, TRUE, 1);
    switch (result)
    {
        case WAIT_OBJECT_0:
        case WAIT_OBJECT_0 + 1:
            ++m_readers;
            ResetEvent(m_writeEvent);
            ReleaseMutex(m_mutex);
            return result;
        case WAIT_TIMEOUT:
            return result;
        default:
            throw std::runtime_error("cannot unlock readwrite mutex");
    }
}

#else

GsRWLockImpl::GsRWLockImpl()
{
}

GsRWLockImpl::~GsRWLockImpl()
{
}

void GsRWLockImpl::ReadLock()
{
}

bool GsRWLockImpl::TryReadLock()
{
}

void GsRWLockImpl::WriteLock()
{
}

bool GsRWLockImpl::TryWriteLock()
{
}

void GsRWLockImpl::Unlock()
{
}

#endif


GsRWLock::GsRWLock()
    : m_Handle(new GsRWLockImpl())
{
}

GsRWLock::~GsRWLock()
{
    if (m_Handle)
        delete m_Handle;
    m_Handle = nullptr;
}

void GsRWLock::ReadLock()
{
    if (m_Handle)
        (static_cast<GsRWLockImpl *>(m_Handle))->ReadLock();
}

bool GsRWLock::TryReadLock()
{
    if (m_Handle)
        return (static_cast<GsRWLockImpl *>(m_Handle))->TryReadLock();
    return false;
}

void GsRWLock::WriteLock()
{
    if (m_Handle)
        (static_cast<GsRWLockImpl *>(m_Handle))->WriteLock();
}

bool GsRWLock::TryWriteLock()
{
    if (m_Handle)
        return (static_cast<GsRWLockImpl *>(m_Handle))->TryWriteLock();
    return false;
}

void GsRWLock::Unlock()
{
    if (m_Handle)
        (static_cast<GsRWLockImpl *>(m_Handle))->Unlock();
}

}// namespace m2
