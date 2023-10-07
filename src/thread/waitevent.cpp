#include "waitevent.h"
#include "logger.h"

namespace Lite {
namespace Utility {

#if GS_OS_WIN

GsWaitEvent::GsWaitEvent(EventType type)
    : GsWaitEvent(type == AutoReset)
{
}

GsWaitEvent::GsWaitEvent(bool autoReset)
{
    _event = CreateEvent(NULL, autoReset ? FALSE : TRUE, FALSE, NULL);
    if (!_event)
        GS_E << "cannot create event";
}

GsWaitEvent::~GsWaitEvent()
{
    CloseHandle(_event);
}

void GsWaitEvent::Set()
{
    if (!SetEvent(_event))
        GS_E << "cannot signal event";
}

void GsWaitEvent::Wait(int milliseconds)
{
    switch (WaitForSingleObject(_event, INFINITE))
    {
        case WAIT_OBJECT_0:
            return;
        default:
            GS_E << "wait for event failed";
    }
}

bool GsWaitEvent::TryWait(int milliseconds)
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

void GsWaitEvent::Reset()
{
    if (!ResetEvent(_event))
        GS_E << "cannot reset event";
}

#else

GsWaitEvent::GsWaitEvent(EventType type)
{
}

GsWaitEvent::GsWaitEvent(bool autoReset)
{
}

GsWaitEvent::~GsWaitEvent()
{
}

void GsWaitEvent::Set()
{
}

void GsWaitEvent::Wait(int milliseconds)
{
}

bool GsWaitEvent::TryWait(int milliseconds)
{
    return false;
}

void GsWaitEvent::Reset()
{
}


#endif

}// namespace Utility
}// namespace Lite
