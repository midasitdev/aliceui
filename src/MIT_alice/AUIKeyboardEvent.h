#pragma once

#include "AUIAPIDef.h"

#include <cstdint>

#if defined(_WIN32)
#   include <windef.h>
#endif


struct ALICEUI_API AUIKeyboardEvent
{
    enum EventType : unsigned int
    {
        kUndefined_EventType = 0,
        // Basic
        kKeyDown_EventType,
        kKeyUp_EventType,
        kChar_EventType,
        // System
        kSysKeyDown_EventType,
        kSysKeyUp_EventType,
        // IME
        kIMECompStart_EventType,
        kIMEComp_EventType,
        kIMECompEnd_EventType,
        kIMEChar_EventType,
    };

    enum MaskCode : unsigned int
    {
        kNone_MaskCode = 0,
        // Shift
        kShiftOn_MaskCode = 1 << 0,
        kLShiftOn_MaskCode = 1 << 1,
        kRShiftOn_MaskCode = 1 << 2,
        // Alt
        kAltOn_MaskCode = 1 << 3,
        kLAltOn_MaskCode = 1 << 4,
        kRAltOn_MaskCode = 1 << 5,
        // Control
        kCtrlOn_MaskCode = 1 << 6,
        kLCtrlOn_MaskCode = 1 << 7,
        kRCtrlOn_MaskCode = 1 << 8,
        // Lock
        kCapsLockOn_MaskCode = 1 << 9,
        kScrollLockOn_MaskCode = 1 << 10,
        kNumLockOn_MaskCode = 1 << 11,
    };

    enum IMEParam : uint64_t
    {
        kNone_IMEParam = 0,
        kComp_IMEParam = 1 << 0,
        kResult_IMEParam = 1 << 1
    };

    EventType fType = kUndefined_EventType;
    unsigned int fKeycode = 0;
    MaskCode fMaskcode = kNone_MaskCode;
    unsigned int fRepCount = 0;
    unsigned int fCharcode = 0;
    uint64_t fParam = kNone_IMEParam;

    AUIKeyboardEvent() noexcept : fType(kUndefined_EventType), fKeycode(0), fMaskcode(kNone_MaskCode), fRepCount(0), fCharcode(0), fParam(kNone_IMEParam) { }
    explicit AUIKeyboardEvent(EventType type, unsigned int keycode, MaskCode maskcode, unsigned int repcount = 0, unsigned int charcode = 0, uint64_t param = kNone_IMEParam) noexcept : fType(type), fKeycode(keycode), fMaskcode(maskcode), fRepCount(repcount), fCharcode(charcode), fParam(param) { }
#if defined(_WIN32)
    explicit AUIKeyboardEvent(AUIKeyboardEvent::EventType type, UINT nChar, UINT nRepCnt, UINT nFlags) noexcept;
    explicit AUIKeyboardEvent(AUIKeyboardEvent::EventType type, WPARAM wParam, LPARAM lParam) noexcept;
#endif

    AUIKeyboardEvent(const AUIKeyboardEvent&) noexcept = default;
    AUIKeyboardEvent(AUIKeyboardEvent&&) noexcept = default;
    AUIKeyboardEvent& operator=(const AUIKeyboardEvent&) noexcept = default;
    AUIKeyboardEvent& operator=(AUIKeyboardEvent&&) noexcept = default;
};

