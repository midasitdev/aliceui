#pragma once

#include "AUIAPIDef.h"

class ALICEUI_API AUICursorIcon final
{
public:
    AUICursorIcon();

    enum CursorIcon
    {
        kArrow_CursorIcon,
        kCross_CursorIcon,
        kIBeam_CursorIcon,
        kNo_CursorIcon,
        kWait_CursorIcon,
        kAppStarting_CursorIcon,
        kHand_CursorIcon,
        kHelp_CursorIcon,
        kSizeAll_CursorIcon,
        kSizeNESW_CursorIcon,
        kSizeNS_CursorIcon,
        kSizeNWSE_CursorIcon,
        kSizeWE_CursorIcon,
        kUpArrow_CursorIcon,
        kMagnify_CursorIcon,
        kHorzSplitBar_CursorIcon,
        kVertSplitBar_CursorIcon
    };

    void ResetCursorIcon() { SetCursorIcon(kArrow_CursorIcon); }
    void SetCursorIcon(CursorIcon ct) { m_eCursorIcon = ct; }
    CursorIcon GetCursorIcon() const { return m_eCursorIcon; }
    void ApplyCursorIcon();
private:
    AUICursorIcon(const AUICursorIcon&) = delete;
    CursorIcon m_eCursorIcon = kArrow_CursorIcon;
};
