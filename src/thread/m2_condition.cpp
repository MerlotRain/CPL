#include "locker.h"
#include "waitevent.h"

namespace m2 {

void WaitCondition::Notify()
{
    ScopedLock<RecursiveMutex> l(m_mutex);
    if (!m_waitDeque.empty())
    {
        m_waitDeque.front()->Set();
        Dequeue();
    }
}

void WaitCondition::NotifyAll()
{
    ScopedLock<RecursiveMutex> l(m_mutex);
    for (auto &p: m_waitDeque)
    {
        p->Set();
    }
    m_waitDeque.clear();
}

void WaitCondition::Enqueue(WaitEvent &event)
{
    m_waitDeque.push_back(&event);
}

void WaitCondition::Dequeue()
{
    m_waitDeque.pop_front();
}

void WaitCondition::Dequeue(WaitEvent &event)
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
