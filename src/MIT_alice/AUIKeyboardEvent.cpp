#include "pch.h"
#include "AUIKeyboardEvent.h"

#if defined(_WIN32)

#include <imm.h>

AUIKeyboardEvent::AUIKeyboardEvent(AUIKeyboardEvent::EventType type, UINT nChar, UINT nRepCnt, UINT nFlags) noexcept
    : fType(type), fKeycode(nChar), fRepCount(nRepCnt), fParam(kNone_IMEParam)
{
    unsigned int maskcode = AUIKeyboardEvent::kNone_MaskCode;
    maskcode |= (AUIKeyboardEvent::kShiftOn_MaskCode | AUIKeyboardEvent::kLShiftOn_MaskCode) * (GetAsyncKeyState(VK_LSHIFT) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kShiftOn_MaskCode | AUIKeyboardEvent::kRShiftOn_MaskCode) * (GetAsyncKeyState(VK_RSHIFT) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kAltOn_MaskCode | AUIKeyboardEvent::kLAltOn_MaskCode) * (GetAsyncKeyState(VK_LMENU) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kAltOn_MaskCode | AUIKeyboardEvent::kRAltOn_MaskCode) * (GetAsyncKeyState(VK_RMENU) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kCtrlOn_MaskCode | AUIKeyboardEvent::kLCtrlOn_MaskCode) * (GetAsyncKeyState(VK_LCONTROL) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kCtrlOn_MaskCode | AUIKeyboardEvent::kRCtrlOn_MaskCode) * (GetAsyncKeyState(VK_RCONTROL) & 0x8000 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kCapsLockOn_MaskCode) * (GetAsyncKeyState(VK_CAPITAL) & 0x0001 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kScrollLockOn_MaskCode) * (GetAsyncKeyState(VK_SCROLL) & 0x0001 ? 1 : 0);
    maskcode |= (AUIKeyboardEvent::kNumLockOn_MaskCode) * (GetAsyncKeyState(VK_NUMLOCK) & 0x0001 ? 1 : 0);
    unsigned int charcode = ::MapVirtualKey(nChar, MAPVK_VK_TO_CHAR);
    fMaskcode = MaskCode(maskcode);
    fCharcode = charcode;
}

AUIKeyboardEvent::AUIKeyboardEvent(AUIKeyboardEvent::EventType type, WPARAM wParam, LPARAM lParam) noexcept
    : fType(kUndefined_EventType), fKeycode(0), fMaskcode(kNone_MaskCode), fRepCount(0), fCharcode(0), fParam(kNone_IMEParam)
{
    switch (type)
    {
    case AUIKeyboardEvent::kIMECompStart_EventType:
        fType = type;
        break;
    case AUIKeyboardEvent::kIMEComp_EventType:
        fType = type;
        fCharcode = unsigned int(wParam);
        if (lParam & GCS_COMPSTR)
            fParam |= AUIKeyboardEvent::kComp_IMEParam;
        else if (lParam & GCS_RESULTSTR)
            fParam |= AUIKeyboardEvent::kResult_IMEParam;
        break;
    case AUIKeyboardEvent::kIMECompEnd_EventType:
        fType = type;
        break;
    case AUIKeyboardEvent::kIMEChar_EventType:
        fType = type;
        fCharcode = unsigned int(wParam);
        if (lParam & GCS_COMPSTR)
            fParam |= AUIKeyboardEvent::kComp_IMEParam;
        else if (lParam & GCS_RESULTSTR)
            fParam |= AUIKeyboardEvent::kResult_IMEParam;
        break;
    default:
        break;
    }
}

#else

#   error TODO: Implement for other OS

#endif
