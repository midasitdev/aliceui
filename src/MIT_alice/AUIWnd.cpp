#include "pch.h"
#include "AUIWnd.h"
#include "AUIApplication.h"
#include "AUIWidget.h"
#include "AUIInnerGroupWidget.h"
#include "AUIRasterWidgetManager.h"

const wchar_t AUIWnd::kWndClassName[] = L"AUIWnd";

IMPLEMENT_DYNCREATE( AUIWnd, CWnd );

AUIWnd::AUIWnd()
    : m_bInDrawCall( false )
    , m_bTrackMouse( FALSE )
{
    RegisterWndClass();
}

AUIWnd::~AUIWnd()
{

}

BEGIN_MESSAGE_MAP(AUIWnd, CWnd)

    ON_WM_CREATE()
    ON_WM_DESTROY()

    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()

    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()

    ON_WM_LBUTTONDOWN()
    ON_WM_MBUTTONDOWN()
    ON_WM_RBUTTONDOWN()

    ON_WM_LBUTTONDBLCLK()
    ON_WM_MBUTTONDBLCLK()
    ON_WM_RBUTTONDBLCLK()

    ON_WM_LBUTTONUP()
    ON_WM_MBUTTONUP()
    ON_WM_RBUTTONUP()

    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_MOUSELEAVE()

    ON_WM_SETCURSOR()

    ON_WM_KEYDOWN()
    ON_WM_CHAR()
    ON_WM_KEYUP()

    ON_MESSAGE( WM_IME_STARTCOMPOSITION, OnIMEStart )
    ON_MESSAGE( WM_IME_COMPOSITION, OnIMEComposition )
    ON_MESSAGE( WM_IME_ENDCOMPOSITION, OnIMEEnd )

    ON_WM_GETMINMAXINFO()

    ON_WM_NCPAINT()
    ON_WM_NCCALCSIZE()
    ON_WM_NCHITTEST()
    ON_WM_NCACTIVATE()

END_MESSAGE_MAP();

bool AUIWnd::RegisterWndClass()
{
    WNDCLASSEX windowclass = { 0, };
    auto hInst = ::AfxGetInstanceHandle();
    if ( !( ::GetClassInfoExW( hInst, kWndClassName, &windowclass ) ) )
    {
        WNDCLASSEX nwndclass = { 0, };
        nwndclass.cbSize = sizeof( WNDCLASSEX );
        nwndclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        nwndclass.lpfnWndProc = ::DefWindowProc;
        nwndclass.cbClsExtra = nwndclass.cbWndExtra = 0;
        nwndclass.hInstance = hInst;
        nwndclass.hIcon = NULL;
        nwndclass.hCursor = ::AfxGetApp()->LoadStandardCursor( IDC_ARROW );
        nwndclass.hbrBackground = ::GetSysColorBrush( COLOR_WINDOW );
        nwndclass.lpszMenuName = NULL;
        nwndclass.lpszClassName = kWndClassName;

        if ( !::RegisterClassExW( &nwndclass ) )
        {
            ::AfxThrowResourceException();
            return false;
        }
    }
    return true;
}

int AUIWnd::OnCreate( LPCREATESTRUCT lpcs )
{
    if ( CWnd::OnCreate( lpcs ) < 0 )
        return -1;


    SetLayeredWindow(IsLayeredWindow());

    m_RefreshPool.Connect( AUIApplication::Instance().RefreshMainSignal, [&]() {
        this->SendTickTimeEvent();
        if (this->GetWidgetManager()->IsDirty())
            this->Invalidate();
    } );

    return 0;
}

void AUIWnd::OnDestroy()
{
    m_RefreshPool.DisconnectAll();

    this->GetWidgetManager()->ClearInstance();
    AUIApplication::Instance().RunUpdateInstanceTask();

    CWnd::OnDestroy();
}

void AUIWnd::OnPaint()
{
    if (m_bInDrawCall)
        return;

    CPaintDC dc( this );
    if ( IsIconic() || !::IsWindow( GetSafeHwnd() ) )
    {
        return;
    }

    struct BooleanGuard
    {
        BooleanGuard( bool& val ) : fVal( val ) {
            fVal = true;
        }
        ~BooleanGuard() {
            fVal = false;
        }
        bool& fVal;
    };
    BooleanGuard guard( m_bInDrawCall );

    if (nullptr == m_pSurface)
        return;

    this->AsyncUpdate();
    this->Render(m_pSurface);

    auto pImage = m_pSurface->makeImageSnapshot();
    if (nullptr == pImage)
        return;
    SkPixmap pixmap;
    if (false == pImage->peekPixels(&pixmap))
        return;

    const auto rowBytes = pixmap.rowBytes();
    const auto imgWidth = pixmap.width();
    const auto imgHeight = pixmap.height();

    CRect rect;
    GetClientRect( rect );

    if ( imgWidth != rect.Width() || imgHeight != rect.Height() )
        return;

    BITMAPINFO bmpInfo = { 0, };
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = imgWidth;
    bmpInfo.bmiHeader.biHeight = -imgHeight;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    bmpInfo.bmiHeader.biSizeImage = 0;
    bmpInfo.bmiHeader.biXPelsPerMeter = 1;
    bmpInfo.bmiHeader.biYPelsPerMeter = 1;
    bmpInfo.bmiHeader.biClrUsed = 0;
    bmpInfo.bmiHeader.biClrImportant = 0;

    AUIAssert(pixmap.addr());
    AUIAssert(imgWidth == rect.Width());
    AUIAssert(imgHeight == rect.Height());
    AUIAssert(rowBytes == imgWidth * sizeof(uint8_t) * 4);
    ::SetDIBitsToDevice( dc, 0, 0, imgWidth, imgHeight, 0, 0, 0, imgHeight, pixmap.addr(), &bmpInfo, DIB_RGB_COLORS );
}

BOOL AUIWnd::OnEraseBkgnd( CDC* pDC )
{
    return TRUE;
}

void AUIWnd::OnSize( UINT nType, int cx, int cy )
{
    CWnd::OnSize( nType, cx, cy );

    if ( cx <= 0 || cy <= 0 )
        return;

    m_pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(cx, cy, SkAlphaType::kOpaque_SkAlphaType));
    AUIAssert(m_pSurface);
    this->MakeNeedRedraw();
    this->SetViewport(cx, cy);

    if ( auto pWidget = GetRootWidget() )
    {
        pWidget->SetDefaultSize(SkIntToScalar(cx), SkIntToScalar(cy));
        pWidget->UpdateChildPosition();
        pWidget->UpdateSize();
    }

    Invalidate();
    UpdateWindow();
}

void AUIWnd::OnSetFocus( CWnd* pOldWnd )
{
    CWnd::OnSetFocus( pOldWnd );

    if ( auto pRootWidget = GetRootWidget() )
    {
        if ( GetWidgetManager()->GetFocusedTarget().expired() )
        {
            GetWidgetManager()->SetFocusTarget( pRootWidget->shared_from_this() );
        }
    }

    if (IsWindow(GetSafeHwnd()))
        Invalidate();
}

void AUIWnd::OnKillFocus( CWnd* pNewWnd )
{
    CWnd::OnKillFocus( pNewWnd );

    CPoint mousePos;
    GetCursorPos( &mousePos );
    GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kLeave_EventType, NULL, mousePos ) );
    // Clear focus
    GetWidgetManager()->SetFocusTarget();

    if (IsWindow(GetSafeHwnd()))
        Invalidate();
}

void AUIWnd::OnLButtonDown( UINT nFlags, CPoint point )
{
    SetFocus();
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kLBtnDown_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnLButtonDown( nFlags, point );
}

void AUIWnd::OnMButtonDown( UINT nFlags, CPoint point )
{
    SetFocus();
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kMBtnDown_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnMButtonDown( nFlags, point );

}

void AUIWnd::OnRButtonDown( UINT nFlags, CPoint point )
{
    SetFocus();
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kRBtnDown_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnRButtonDown( nFlags, point );

}

void AUIWnd::OnLButtonUp( UINT nFlags, CPoint point )
{

    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kLBtnUp_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnMButtonUp( nFlags, point );
}

void AUIWnd::OnMButtonUp( UINT nFlags, CPoint point )
{
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kMBtnUp_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnMButtonUp( nFlags, point );

}

void AUIWnd::OnRButtonUp( UINT nFlags, CPoint point )
{

    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kRBtnUp_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnRButtonUp( nFlags, point );
}

void AUIWnd::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kLBtnDblClk_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnLButtonDblClk( nFlags, point );

}

void AUIWnd::OnMButtonDblClk( UINT nFlags, CPoint point )
{
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kMBtnDblClk_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnMButtonDblClk( nFlags, point );

}

void AUIWnd::OnRButtonDblClk( UINT nFlags, CPoint point )
{

    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kRBtnDblClk_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnRButtonDblClk( nFlags, point );
}

void AUIWnd::OnMouseMove( UINT nFlags, CPoint point )
{
    if ( !m_bTrackMouse )
    {
        TRACKMOUSEEVENT tme = { 0, };
        tme.cbSize = sizeof( TRACKMOUSEEVENT );
        tme.hwndTrack = GetSafeHwnd();
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = 1;
        m_bTrackMouse = _TrackMouseEvent( &tme );
    }

    auto uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kMove_EventType, nFlags, point ) );
    if ( false == uiret )
        CWnd::OnMouseMove( nFlags, point );

    if (uiret && GetWidgetManager()->IsDirty())
    {
        Invalidate();
        UpdateWindow();
    }
    //if ( IsRefreshTickValidated() )
    //{
    //    UpdateWindow();
    //}
}

BOOL AUIWnd::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
    CRect rect;
    GetWindowRect( rect );
    CPoint relPoint = CPoint( pt.x - rect.left, pt.y - rect.top );
    const auto uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kWheel_EventType, nFlags, relPoint, zDelta ) );
    if (uiret)
    {
        const float DefaultWheelDelta = 120.0f;
        AUIApplication::Instance().MouseWheelSignal.Send(GetWidgetManager(), pt.x, pt.y, static_cast<float>(zDelta) / DefaultWheelDelta);

        return TRUE;
    }

    return CWnd::OnMouseWheel( nFlags, zDelta, pt );
}

void AUIWnd::OnMouseLeave()
{
    bool uiret = GetWidgetManager()->SendMouseEvent( MAUIMouseEvent( MAUIMouseEvent::kLeave_EventType, NULL, CPoint() ) );

    CWnd::OnMouseLeave();

    m_bTrackMouse = FALSE;
}

BOOL AUIWnd::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
    bool uiret = this->SendSetCursorEvent();
    if ( uiret )
        return TRUE;

    return CWnd::OnSetCursor( pWnd, nHitTest, message );

}

void AUIWnd::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{

    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kKeyUp_EventType, nChar, nRepCnt, nFlags ) );
    if ( false == uiret )
        CWnd::OnKeyUp( nChar, nRepCnt, nFlags );
}

void AUIWnd::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{

    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kChar_EventType, nChar, nRepCnt, nFlags ) );
    if ( false == uiret )
        CWnd::OnChar( nChar, nRepCnt, nFlags );
}

void AUIWnd::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kKeyDown_EventType, nChar, nRepCnt, nFlags ) );
    if ( false == uiret )
        CWnd::OnKeyDown( nChar, nRepCnt, nFlags );
}

LRESULT AUIWnd::OnIMEStart( WPARAM wParam, LPARAM lParam )
{
    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kIMECompStart_EventType, wParam, lParam ) );

    return NULL;

}

LRESULT AUIWnd::OnIMEComposition( WPARAM wParam, LPARAM lParam )
{
    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kIMEComp_EventType, wParam, lParam ) );

    return NULL;

}

LRESULT AUIWnd::OnIMEEnd( WPARAM wParam, LPARAM lParam )
{

    bool uiret = GetWidgetManager()->SendKeyboardEvent( AUIKeyboardEvent( AUIKeyboardEvent::kIMECompEnd_EventType, wParam, lParam ) );

    return NULL;
}

BOOL AUIWnd::PreTranslateMessage( MSG* pMsg )
{
    auto ret = CWnd::PreTranslateMessage( pMsg );
    if ( GetSafeHwnd() == pMsg->hwnd )
    {
        switch ( pMsg->message )
        {
        case WM_LBUTTONDOWN:
            SetCapture();
            break;
        case WM_LBUTTONUP:
            if ( GetCapture() != this )
                return TRUE;
            ReleaseCapture();
            break;
        case WM_MBUTTONDOWN:
            SetCapture();
            break;
        case WM_MBUTTONUP:
            if ( GetCapture() != this )
                return TRUE;
            ReleaseCapture();
            break;
        case WM_RBUTTONDOWN:
            SetCapture();
            break;
        case WM_RBUTTONUP:
            if ( GetCapture() != this )
                return TRUE;
            ReleaseCapture();
            break;
        case WM_SYSCOMMAND:
            if (SC_CLOSE == pMsg->wParam)
            {
                // TODO : Move this code somehow to MAUIMFCHandle
                // Exit if modal
                if (m_nFlags & WF_MODALLOOP)
                {
                    if (auto pParentWnd = GetParent())
                        pParentWnd->EnableWindow(TRUE);
                    this->EndModalLoop(0);
                    this->DestroyWindow();
                    return TRUE;
                }
            }
            break;
        default:
            break;
        }
    }
    return ret;
}

BOOL AUIWnd::PreCreateWindow( CREATESTRUCT& cs )
{
    return CWnd::PreCreateWindow( cs );
}

void AUIWnd::SetLayeredWindow(bool val)
{
    m_bLayeredWindow = val;
    if (::IsWindow(GetSafeHwnd()))
    {
        SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
        if (m_bLayeredWindow)
        {
            SetLayeredWindowAttributes(RGB(0, 0, 0), 0, LWA_COLORKEY);
            this->SetBackgroundColor(SkColorSetARGB(0, 0, 0, 0));
        }
        else
        {
            SetLayeredWindowAttributes(RGB(0, 0, 0), 255, LWA_ALPHA);
            this->SetBackgroundColor(SkColorSetARGB(255, 255, 255, 255));
        }
        Invalidate();
    }
}

bool AUIWnd::IsLayeredWindow() const
{
    return m_bLayeredWindow;
}

void AUIWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    if (m_MinWidth > kNoMinMaxSizeValue)
        lpMMI->ptMinTrackSize.x = m_MinWidth;
    if (m_MinHeight > kNoMinMaxSizeValue)
        lpMMI->ptMinTrackSize.y = m_MinHeight;

    if (m_MaxWidth > kNoMinMaxSizeValue)
        lpMMI->ptMaxTrackSize.x = m_MaxWidth;
    if (m_MaxHeight > kNoMinMaxSizeValue)
        lpMMI->ptMaxTrackSize.y = m_MaxHeight;

    return CWnd::OnGetMinMaxInfo(lpMMI);

}

void AUIWnd::SetMinSize(int width, int height)
{
    m_MinWidth = width;
    m_MinHeight = height;
}

void AUIWnd::SetMaxSize(int width, int height)
{
    m_MaxWidth = width;
    m_MaxHeight = height;
}

void AUIWnd::OnNcPaint()
{
    const auto isResizeable = !!(GetStyle() & WS_THICKFRAME);
    if (isResizeable)
    {
        CWindowDC dc(this);
    }
    else
    {
        SuperClass::OnNcPaint();
    }
}

void AUIWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
    const auto isResizeable = !!(GetStyle() & WS_THICKFRAME);
    if (isResizeable)
    {
        lpncsp->rgrc[2] = lpncsp->rgrc[0];
    }
    else
    {
        SuperClass::OnNcCalcSize(bCalcValidRects, lpncsp);
    }
}

LRESULT AUIWnd::OnNcHitTest(CPoint point)
{
    AUIAssert(::IsWindow(GetSafeHwnd()));

    CRect rect;
    GetWindowRect(rect);

    constexpr LONG kResizeOffset = 2;
    const auto ptX = point.x;
    const auto ptY = point.y;

    const auto isResizeable = !!(GetStyle() & WS_THICKFRAME);
    if (false == isResizeable)
    {
        if (rect.left < ptX && rect.right > ptX && rect.top < ptY && rect.bottom > ptY)
            return HTCLIENT;
        else
            return HTNOWHERE;
    }


    if (rect.left <= ptX && rect.left + kResizeOffset >= ptX)
    {
        if (rect.top <= ptY && rect.top + kResizeOffset >= ptY)
            return HTTOPLEFT;
        if (rect.bottom >= ptY && rect.bottom - kResizeOffset - 1 <= ptY)
            return HTBOTTOMLEFT;
        return HTLEFT;
    }
    if (rect.right >= ptX && rect.right - kResizeOffset - 1 <= ptX)
    {
        if (rect.top <= ptY && rect.top + kResizeOffset >= ptY)
            return HTTOPRIGHT;
        if (rect.bottom >= ptY && rect.bottom - kResizeOffset - 1 <= ptY)
            return HTBOTTOMRIGHT;
        return HTRIGHT;
    }
    if (rect.top <= ptY && rect.top + kResizeOffset >= ptY)
        return HTTOP;
    if (rect.bottom >= ptY && rect.bottom - kResizeOffset - 1 <= ptY)
        return HTBOTTOM;

    if (rect.left < ptX && rect.right > ptX && rect.top < ptY && rect.bottom > ptY)
        return HTCLIENT;

    return HTNOWHERE;
}

BOOL AUIWnd::OnNcActivate(BOOL bActive)
{
    if (bActive)
        RedrawWindow();
    return TRUE;
}
