#include <cpl_object.h>

namespace CPL {

bool RefObject::OnFinalRelease() { return true; }

RefObject::RefObject() { m_RefCount = 0; }

int RefObject::AddRef() noexcept
{
    m_RefCount.Increment();
    return m_RefCount.Read();
}

int RefObject::Release() noexcept
{
    m_RefCount.Decrement();
    int count = m_RefCount.Read();
    if (count == 0)
    {
        OnFinalRelease();
        OnDestructor(this);
        delete this;
    }
    return count;
}

int RefObject::RefCount() noexcept { return m_RefCount.Read(); }

void WeakReference::OnDestructor(RefObject *obj)
{
    if (obj == m_RefObject) m_RefObject = nullptr;
}

WeakReference::WeakReference(RefObject *object) : m_RefObject(object)
{
    m_RefObject->OnDestructor.Add(this, &WeakReference::OnDestructor);
}
WeakReference::~WeakReference() { m_RefObject = nullptr; }

RefObject *WeakReference::LockReferenceObject()
{
    if (m_RefObject) { m_RefObject->AddRef(); }
    return m_RefObject;
}

bool WeakReference::Expired()
{
    return (!m_RefObject || m_RefObject->RefCount() == 0);
}

}// namespace CPL