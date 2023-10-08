#include <assert.h>
#include <object.h>
#include <stlhelp.h>

namespace m2 {

GsRefObject::GsRefObject()
{
    m_RefCount.store(0);
}

GsRefObject::~GsRefObject()
{
    Destory(this);
}

void GsRefObject::AddRef()
{
    assert(m_RefCount.load(std::memory_order_relaxed) >= 0);
    m_RefCount.fetch_add(1, std::memory_order_relaxed);
}

bool GsRefObject::TryAddRef()
{
    assert(m_RefCount.load(std::memory_order_relaxed) >= 0);
    auto _old = m_RefCount.load(std::memory_order_relaxed);
    do
    {
        if (_old == 0)
        {
            return false;
        }
    } while (!m_RefCount.compare_exchange_strong(_old, _old + 1, std::memory_order_relaxed));
    return true;
}

void GsRefObject::Release()
{
    m_RefCount.fetch_sub(1, std::memory_order_relaxed);
    if (m_RefCount.load() <= 0)
    {
        this->~GsRefObject();
    }
}

int GsRefObject::RefCount()
{
    return m_RefCount.load(std::memory_order_relaxed);
}

long long GsRefObject::HashCode() const
{
    return 0;
}

void *GsRefObject::operator new(size_t size) { return GsByteAllocator::Allocate(size); }

void *GsRefObject::operator new[](size_t size) { return GsByteAllocator::Allocate(size); }

void GsRefObject::operator delete(void *data) { GsByteAllocator::Deallocate(data, 0); }

void GsRefObject::operator delete[](void *data) { GsByteAllocator::Deallocate(data, 0); }


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

GsWeakReference::GsWeakReference(GsRefObject *obj) : m_RefObject(obj)
{
    // 强指针转弱指针，弱指针引用计数=强引用计数 + 1，强指针引用计数不变
    if (m_RefObject)
    {
        // 绑定委托
        m_RefObject->Destory.Add(this, &GsWeakReference::OnDestroy);
        auto strong_count = m_RefObject->RefCount();
        m_RefCount.fetch_add(strong_count + 1);
    }
}

GsWeakReference::~GsWeakReference()
{
}

GsRefObject *GsWeakReference::Lock()
{
    const std::lock_guard<std::mutex> l(_mutex);
    if (!m_RefObject->TryAddRef())
    {
        return nullptr;
    }
    return m_RefObject;
}

void GsWeakReference::OnDestroy(Lite::Utility::GsRefObject *obj)
{
    if (obj == m_RefObject)
    {
        m_RefObject = nullptr;
        m_RefCount.store(0);
    }
}

bool GsWeakReference::Expired() const noexcept
{
    const std::lock_guard<std::mutex> l(_mutex);
    if (!m_RefObject)
    {
        return true;
    }
    return m_RefObject->RefCount() == 0;
}

void GsWeakReference::Unlink() noexcept
{
    const std::lock_guard<std::mutex> l(_mutex);
    m_RefObject = 0;
    this->m_RefCount.store(0);
}


}// namespace m2
