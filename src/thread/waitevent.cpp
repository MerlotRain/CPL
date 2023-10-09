#include "waitevent.h"
#include "logger.h"

namespace m2 {

#if GS_OS_WIN

WaitEvent::WaitEvent(EventType type)
    : WaitEvent(type == AutoReset)
{
}

WaitEvent::WaitEvent(bool autoReset)
{
    _event = CreateEvent(NULL, autoReset ? FALSE : TRUE, FALSE, NULL);
    if (!_event)
        GS_E << "cannot create event";
}

WaitEvent::~WaitEvent()
{
    CloseHandle(_event);
}

void WaitEvent::Set()
{
    if (!SetEvent(_event))
        GS_E << "cannot signal event";
}

void WaitEvent::Wait(int milliseconds)
{
    switch (WaitForSingleObject(_event, INFINITE))
    {
        case WAIT_OBJECT_0:
            return;
        default:
            GS_E << "wait for event failed";
    }
}

bool WaitEvent::TryWait(int milliseconds)
{
    assert(milliseconds != INFINITE);
    switch (WaitForSingleObject(_event, milliseconds ? milliseconds : 1))
    {
        case WAIT_TIMEOUT:
            return false;
        case WAIT_OBJECT_0:
            return true;
        default:
            GS_E << "wait for event failed";
    }
}

void WaitEvent::Reset()
{
    if (!ResetEvent(_event))
        GS_E << "cannot reset event";
}

#else

WaitEvent::WaitEvent(EventType type)
{
}

WaitEvent::WaitEvent(bool autoReset)
{
}

WaitEvent::~WaitEvent()
{
}

void WaitEvent::Set()
{
}

void WaitEvent::Wait(int milliseconds)
{
}

bool WaitEvent::TryWait(int milliseconds)
{
    return false;
}

void WaitEvent::Reset()
{
}


#endif

}// namespace m2
