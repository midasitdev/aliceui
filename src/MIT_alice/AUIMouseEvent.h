#pragma once

#include "AUIAPIDef.h"

struct ALICEUI_API MAUIMouseEvent
{
    enum EventFlag : unsigned int
    {
        kNone_EventFlag = 0x0000,
        kLBtn_EventFlag = 0x0001,
        kRBtn_EventFlag = 0x0002,
        kShift_EventFlag = 0x0004,
        kCtrl_EventFlag = 0x0008,
        kMBtn_EventFlag = 0x0010,
    };
    enum EventType : unsigned int
    {
        kUndefined_EventType = 0,
        // Left button
        kLBtnDblClk_EventType,
        kLBtnDown_EventType,
        kLBtnUp_EventType,
        // Middle Btn
        kMBtnDblClk_EventType,
        kMBtnDown_EventType,
        kMBtnUp_EventType,
        // Right Btn
        kRBtnDblClk_EventType,
        kRBtnDown_EventType,
        kRBtnUp_EventType,
        // Wheel
        kWheel_EventType,
        // Move
        kMove_EventType,
        // Leave
        kLeave_EventType
    };

    EventType fType = kUndefined_EventType;
    EventFlag fFlag = kNone_EventFlag;
    int fX = 0;
    int fY = 0;
    int fParam = 0;

    MAUIMouseEvent() noexcept = default;
    explicit MAUIMouseEvent(EventType type, EventFlag flag, int x, int y, int param = 0) noexcept : fType(type), fFlag(flag), fX(x), fY(y), fParam(param) { }
#if defined(_WIN32)
    explicit MAUIMouseEvent(EventType type, UINT nFlags, POINT point, short delta = 0) noexcept;
#endif

    MAUIMouseEvent(const MAUIMouseEvent&) noexcept = default;
    MAUIMouseEvent(MAUIMouseEvent&&) noexcept = default;
    MAUIMouseEvent& operator=(const MAUIMouseEvent&) noexcept = default;
    MAUIMouseEvent& operator=(MAUIMouseEvent&&) noexcept = default;
};

