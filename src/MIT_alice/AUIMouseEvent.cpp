#include "pch.h"
#include "AUIMouseEvent.h"

#if defined(_WIN32)
MAUIMouseEvent::MAUIMouseEvent(EventType type, UINT nFlags, POINT point, short delta) noexcept
    : fType(type), fFlag(EventFlag(nFlags)), fX(point.x), fY(point.y), fParam(delta)
{

}
#else

#error TODO: Implement for other OS

#endif