#include "pch.h"
#include "AUICursorIcon.h"

static void ChangeCursorIcon(AUICursorIcon::CursorIcon ct)
{
#if defined(WIN32)
    switch (ct)
    {
    case AUICursorIcon::kArrow_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_ARROW));
        break;
    case AUICursorIcon::kCross_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_CROSS));
        break;
    case AUICursorIcon::kIBeam_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_IBEAM));
        break;
    case AUICursorIcon::kNo_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_NO));
        break;
    case AUICursorIcon::kWait_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_WAIT));
        break;
    case AUICursorIcon::kAppStarting_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_APPSTARTING));
        break;
    case AUICursorIcon::kHand_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_HAND));
        break;
    case AUICursorIcon::kHelp_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_HAND));
        break;
    case AUICursorIcon::kSizeAll_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_SIZEALL));
        break;
    case AUICursorIcon::kSizeNESW_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_SIZENESW));
        break;
    case AUICursorIcon::kSizeNS_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_SIZENS));
        break;
    case AUICursorIcon::kSizeNWSE_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_SIZENWSE));
        break;
    case AUICursorIcon::kSizeWE_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_SIZEWE));
        break;
    case AUICursorIcon::kUpArrow_CursorIcon:
        ::SetCursor(::LoadCursor(nullptr, IDC_UPARROW));
        break;
#   if defined(_MSC_VER)
    case AUICursorIcon::kMagnify_CursorIcon:
        ::SetCursor(::AfxGetApp()->LoadCursor(AFX_IDC_MAGNIFY));
        break;
    case AUICursorIcon::kHorzSplitBar_CursorIcon:
        ::SetCursor(::AfxGetApp()->LoadCursor(AFX_IDC_HSPLITBAR));
        break;
    case AUICursorIcon::kVertSplitBar_CursorIcon:
        ::SetCursor(::AfxGetApp()->LoadCursor(AFX_IDC_VSPLITBAR));
        break;
#   endif
    default:
        AUIAssertFail();
        break;
    }
#else
#   error Implement this function
#endif
}

AUICursorIcon::AUICursorIcon()
    : m_eCursorIcon(kArrow_CursorIcon)
{

}

void AUICursorIcon::ApplyCursorIcon()
{
    ::ChangeCursorIcon(m_eCursorIcon);
}
