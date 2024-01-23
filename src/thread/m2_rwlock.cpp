#include <locker.h>
#if GS_OS_WIN
#include <Windows.h>
#else
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class RWLockImpl
{
public:
    RWLockImpl();
    ~RWLockImpl();
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

RWLockImpl::RWLockImpl()
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

RWLockImpl::~RWLockImpl()
{
    CloseHandle(m_mutex);
    CloseHandle(m_readEvent);
    CloseHandle(m_writeEvent);
}

void RWLockImpl::ReadLock()
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

bool RWLockImpl::TryReadLock()
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

void RWLockImpl::WriteLock()
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

bool RWLockImpl::TryWriteLock()
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

void RWLockImpl::Unlock()
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

void RWLockImpl::AddWriter()
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

void RWLockImpl::RemoveWriter()
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

DWORD RWLockImpl::TryReadLockOnce()
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

RWLockImpl::RWLockImpl()
{
}

RWLockImpl::~RWLockImpl()
{
}

void RWLockImpl::ReadLock()
{
}

bool RWLockImpl::TryReadLock()
{
}

void RWLockImpl::WriteLock()
{
}

bool RWLockImpl::TryWriteLock()
{
}

void RWLockImpl::Unlock()
{
}

#endif


RWLock::RWLock()
    : m_Handle(new RWLockImpl())
{
}

RWLock::~RWLock()
{
    if (m_Handle)
        delete m_Handle;
    m_Handle = nullptr;
}

void RWLock::ReadLock()
{
    if (m_Handle)
        (static_cast<RWLockImpl *>(m_Handle))->ReadLock();
}

bool RWLock::TryReadLock()
{
    if (m_Handle)
        return (static_cast<RWLockImpl *>(m_Handle))->TryReadLock();
    return false;
}

void RWLock::WriteLock()
{
    if (m_Handle)
        (static_cast<RWLockImpl *>(m_Handle))->WriteLock();
}

bool RWLock::TryWriteLock()
{
    if (m_Handle)
        return (static_cast<RWLockImpl *>(m_Handle))->TryWriteLock();
    return false;
}

void RWLock::Unlock()
{
    if (m_Handle)
        (static_cast<RWLockImpl *>(m_Handle))->Unlock();
}

}// namespace m2
