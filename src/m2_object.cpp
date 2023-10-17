#include <assert.h>
#include <m2_allocator.h>
#include <m2_object.h>

namespace m2 {

/**
 * @brief Construct a new Ref Object:: Ref Object object
 */
RefObject::RefObject() { m_RefCount.store(0); }

/**
 * @brief Destroy the Ref Object:: Ref Object object
 */
RefObject::~RefObject() { Destory(this); }

/**
 * @brief 
 */
void RefObject::addRef()
{
    assert(m_RefCount.load(std::memory_order_relaxed) >= 0);
    m_RefCount.fetch_add(1, std::memory_order_relaxed);
}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool RefObject::tryAddRef()
{
    assert(m_RefCount.load(std::memory_order_relaxed) >= 0);
    auto _old = m_RefCount.load(std::memory_order_relaxed);
    do {
        if (_old == 0) { return false; }
    } while (!m_RefCount.compare_exchange_strong(_old, _old + 1,
                                                 std::memory_order_relaxed));
    return true;
}

/**
 * @brief 
 */
void RefObject::release()
{
    m_RefCount.fetch_sub(1, std::memory_order_relaxed);
    if (m_RefCount.load() <= 0) { this->~RefObject(); }
}

/**
 * @brief 
 * @return int 
 */
int RefObject::refCount() { return m_RefCount.load(std::memory_order_relaxed); }

/**
 * @brief 
 * @return long long 
 */
long long RefObject::hashCode() const { return 0; }

/**
 * @brief 
 * @param  size             
 * @return void* 
 */
void *RefObject::operator new(size_t size)
{
    return ByteAllocator::Allocate(size);
}

/**
 * @brief 
 * @param  size             
 * @return void* 
 */
void *RefObject::operator new[](size_t size)
{
    return ByteAllocator::Allocate(size);
}

/**
 * @brief 
 * @param  data             
 */
void RefObject::operator delete(void *data)
{
    ByteAllocator::Deallocate(data, 0);
}

/**
 * @brief 
 * @param  data             
 */
void RefObject::operator delete[](void *data)
{
    ByteAllocator::Deallocate(data, 0);
}

/*******************************************************************************
 * class WeakRefObject functions
 *******************************************************************************/

/**
 * @brief Construct a new Weak Ref Object:: Weak Ref Object object
 * @param  obj              
 */
WeakRefObject::WeakRefObject(RefObject *obj) : m_RefObject(obj)
{
    if (m_RefObject)
    {
        // 绑定委托
        m_RefObject->Destory.add(this, &WeakRefObject::onDestroy);
        auto strong_count = m_RefObject->refCount();
        m_RefCount.fetch_add(strong_count + 1);
    }
}

/**
 * @brief Destroy the Weak Ref Object:: Weak Ref Object object
 */
WeakRefObject::~WeakRefObject() {}

/**
 * @brief 
 * @return RefObject* 
 */
RefObject *WeakRefObject::lock()
{
    const std::lock_guard<std::mutex> l(_mutex);
    if (!m_RefObject->tryAddRef()) { return nullptr; }
    return m_RefObject;
}

/**
 * @brief 
 * @param  obj              
 */
void WeakRefObject::onDestroy(m2::RefObject *obj)
{
    if (obj == m_RefObject)
    {
        m_RefObject = nullptr;
        m_RefCount.store(0);
    }
}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool WeakRefObject::expired() const noexcept
{
    const std::lock_guard<std::mutex> l(_mutex);
    if (!m_RefObject) { return true; }
    return m_RefObject->refCount() == 0;
}

/**
 * @brief 
 */
void WeakRefObject::unlink() noexcept
{
    const std::lock_guard<std::mutex> l(_mutex);
    m_RefObject = 0;
    this->m_RefCount.store(0);
}

}// namespace m2