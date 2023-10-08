#include <locker.h>
#if GS_OS_WIN
#include <Windows.h>
#else
#include <atomic>
#include <errno.h>
#include <pthread.h>
#endif

namespace m2 {

class GsSemaphoreImpl
{
public:
    GsSemaphoreImpl(int n, int max);
    ~GsSemaphoreImpl();
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

GsSemaphoreImpl::GsSemaphoreImpl(int n, int max)
{
    assert(n >= 0 && max > 0 && n <= max);
    m_sema = CreateSemaphoreW(NULL, n, max, NULL);
    if (!m_sema)
        throw std::runtime_error("cannot create semaphore");
}

GsSemaphoreImpl::~GsSemaphoreImpl()
{
    CloseHandle(m_sema);
}

void GsSemaphoreImpl::Set()
{
    if (!ReleaseSemaphore(m_sema, 1, NULL))
        throw std::runtime_error("cannot signal semaphore");
}

void GsSemaphoreImpl::Wait()
{
    switch (WaitForSingleObject(m_sema, INFINITE))
    {
        case WAIT_OBJECT_0:
            return;
        default:
            throw std::runtime_error("wait for semaphore failed");
    }
}

bool GsSemaphoreImpl::Wait(int milliseconds)
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

GsSemaphoreImpl::GsSemaphoreImpl(int n, int max)
{
}

GsSemaphoreImpl::~GsSemaphoreImpl()
{
}

void GsSemaphoreImpl::Set()
{
}

void GsSemaphoreImpl::Wait()
{
}

bool GsSemaphoreImpl::Wait(int milliseconds)
{
}

#endif

GsSemaphore::GsSemaphore(int n)
    : GsSemaphore(n, n)
{
}

GsSemaphore::GsSemaphore(int n, int max)
    : m_Handle(new GsSemaphoreImpl(n, max))
{
}

GsSemaphore::~GsSemaphore()
{
    delete m_Handle;
    m_Handle = NULL;
}

void GsSemaphore::Acquire()
{
    if (m_Handle)
        (static_cast<GsSemaphoreImpl *>(m_Handle))->Set();
}

void GsSemaphore::Wait()
{
    if (m_Handle)
        (static_cast<GsSemaphoreImpl *>(m_Handle))->Wait();
}

void GsSemaphore::Wait(int milliseconds)
{
    if (!TryWait(milliseconds))
        throw std::runtime_error("cannot wait semaphore");
}

bool GsSemaphore::TryWait(int milliseconds)
{
    if (m_Handle)
        return (static_cast<GsSemaphoreImpl *>(m_Handle))->Wait(milliseconds);
    return false;
}

}// namespace m2
