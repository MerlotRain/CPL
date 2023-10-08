#include "locker.h"
#include "waitevent.h"

namespace m2 {

void GsWaitCondition::Notify()
{
    GsScopedLock<GsRecursiveMutex> l(m_mutex);
    if (!m_waitDeque.empty())
    {
        m_waitDeque.front()->Set();
        Dequeue();
    }
}

void GsWaitCondition::NotifyAll()
{
    GsScopedLock<GsRecursiveMutex> l(m_mutex);
    for (auto &p: m_waitDeque)
    {
        p->Set();
    }
    m_waitDeque.clear();
}

void GsWaitCondition::Enqueue(GsWaitEvent &event)
{
    m_waitDeque.push_back(&event);
}

void GsWaitCondition::Dequeue()
{
    m_waitDeque.pop_front();
}

void GsWaitCondition::Dequeue(GsWaitEvent &event)
{
    for (auto it = m_waitDeque.begin(); it != m_waitDeque.end(); ++it)
    {
        if (*it == &event)
        {
            m_waitDeque.erase(it);
            break;
        }
    }
}

}// namespace m2
