#include <locker.h>
#if GS_OS_WIN
#include <Windows.h>
#else
#include <atomic>
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class SemaphoreImpl
{
public:
    SemaphoreImpl(int n, int max);
    ~SemaphoreImpl();
    void Set();
    void Wait();
    bool Wait(int milliseconds);

private:
#if GS_OS_WIN
    HANDLE m_sema;
#else
    std::atomic<int> m_n;
    int m_max;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
#endif
};

#if GS_OS_WIN

SemaphoreImpl::SemaphoreImpl(int n, int max)
{
    assert(n >= 0 && max > 0 && n <= max);
    m_sema = CreateSemaphoreW(NULL, n, max, NULL);
    if (!m_sema)
        throw std::runtime_error("cannot create semaphore");
}

SemaphoreImpl::~SemaphoreImpl()
{
    CloseHandle(m_sema);
}

void SemaphoreImpl::Set()
{
    if (!ReleaseSemaphore(m_sema, 1, NULL))
        throw std::runtime_error("cannot signal semaphore");
}

void SemaphoreImpl::Wait()
{
    switch (WaitForSingleObject(m_sema, INFINITE))
    {
        case WAIT_OBJECT_0:
            return;
        default:
            throw std::runtime_error("wait for semaphore failed");
    }
}

bool SemaphoreImpl::Wait(int milliseconds)
{
    switch (WaitForSingleObject(m_sema, milliseconds + 1))
    {
        case WAIT_TIMEOUT:
            return false;
        case WAIT_OBJECT_0:
            return true;
        default:
            throw std::runtime_error("wait for semaphore failed");
    }
}

#else

SemaphoreImpl::SemaphoreImpl(int n, int max)
{
}

SemaphoreImpl::~SemaphoreImpl()
{
}

void SemaphoreImpl::Set()
{
}

void SemaphoreImpl::Wait()
{
}

bool SemaphoreImpl::Wait(int milliseconds)
{
}

#endif

Semaphore::Semaphore(int n)
    : Semaphore(n, n)
{
}

Semaphore::Semaphore(int n, int max)
    : m_Handle(new SemaphoreImpl(n, max))
{
}

Semaphore::~Semaphore()
{
    delete m_Handle;
    m_Handle = NULL;
}

void Semaphore::Acquire()
{
    if (m_Handle)
        (static_cast<SemaphoreImpl *>(m_Handle))->Set();
}

void Semaphore::Wait()
{
    if (m_Handle)
        (static_cast<SemaphoreImpl *>(m_Handle))->Wait();
}

void Semaphore::Wait(int milliseconds)
{
    if (!TryWait(milliseconds))
        throw std::runtime_error("cannot wait semaphore");
}

bool Semaphore::TryWait(int milliseconds)
{
    if (m_Handle)
        return (static_cast<SemaphoreImpl *>(m_Handle))->Wait(milliseconds);
    return false;
}

}// namespace m2
