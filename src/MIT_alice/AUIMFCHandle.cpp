#include "pch.h"
#include "AUIMFCHandle.h"
#include "AUIHandle.h"
#include "AUIWnd.h"
#include "AUIApplication.h"
#include "AUIWidget.h"

static_assert(std::is_same<LPCTSTR, const wchar_t*>::value, "Works on Unicode Project");

namespace {
    constexpr int NextPopupOffset = 25;
    bool isPrevPopupPosValid = false;
    int prevPopupPosX = 0;
    int prevPopupPosY = 0;
}

AUIMFCHandle::AUIMFCHandle(CWnd* const pWnd) noexcept
    : m_pWnd( pWnd )
    , m_bUseDefaultPos( true )
{
    AUIAssert( GetWnd() );
}

void AUIMFCHandle::Activate( AUIHandle* const pParent )
{
    this->ActivateWnd(pParent);
    AUIHandle::Activate(pParent);
}

void AUIMFCHandle::ActivateWnd(AUIHandle* const pParent)
{
    if (IsActivated())
    {
        AUIAssert(!"Already activated");
        return;
    }

    DWORD BasicStyle = WS_CLIPCHILDREN;
    DWORD BasicExStyle = WS_EX_LAYERED;

    if (m_bVisible)
    {
        BasicStyle |= WS_VISIBLE;
    }

    if (AUIHandleMode::kPopup == m_Mode)
    {
        BasicStyle |= WS_POPUP;
    }
    else if (AUIHandleMode::kChild == m_Mode)
    {
        BasicStyle |= WS_CHILD;
    }

    if (IsTopMost())
    {
        BasicExStyle |= WS_EX_TOPMOST;
    }

    if (IsNonActivate())
    {
        BasicExStyle |= WS_EX_TOOLWINDOW;
        BasicExStyle |= WS_EX_NOACTIVATE;
    }

    if (IsResizeable())
    {
        BasicStyle |= WS_THICKFRAME;
    }

    if (m_bUseDefaultPos)
    {
        int appx;
        int appy;
        int appwidth;
        int appheight;

        AUIApplication::Instance().GetApplicationPositionAndSize(appx, appy, appwidth, appheight);

        if (m_Mode == AUIHandleMode::kChild)
            appx = appy = 0;

        if (isPrevPopupPosValid == false)
        {
            prevPopupPosX = int(appx + (appwidth - m_iWidth) * 0.5);
            prevPopupPosY = int(appy + (appheight - m_iHeight) * 0.5);
            isPrevPopupPosValid = true;
        }

        auto popupPosX = prevPopupPosX + NextPopupOffset;
        auto popupPosY = prevPopupPosY + NextPopupOffset;
        if (popupPosX + m_iWidth >= appx + appwidth - NextPopupOffset || popupPosY + m_iHeight >= appy + appheight - NextPopupOffset)
        {
            popupPosX = appx + NextPopupOffset;
            popupPosY = appy + NextPopupOffset;
        }

        m_iX = prevPopupPosX = popupPosX;
        m_iY = prevPopupPosY = popupPosY;

        m_bUseDefaultPos = false;
    }

    CWnd* pParentWnd = nullptr;
    if (pParent == nullptr)
    {
        pParentWnd = AUIApplication::Instance().GetApplicationHandle()->Cast< AUIMFCHandle >()->GetWnd();
    }
    else
    {
        pParentWnd = pParent->Cast< AUIMFCHandle >()->GetWnd();
    }

    auto targetClassName = m_strWndClassName;
    if (targetClassName.empty())
        targetClassName = ::AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, NULL, reinterpret_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH)), NULL);
    if (!GetWnd()->CreateEx(BasicExStyle, targetClassName.c_str(), m_strTitle.c_str(), BasicStyle, CRect(m_iX, m_iY, m_iX + m_iWidth, m_iY + m_iHeight), pParentWnd, 0))
    {
        AUIAssert(!"Activation failed");
        return;
    }

    if (m_Opacity != kAUIAlpha100)
    {
        MakeTransparent();
    }

    if (false == IsNonActivate())
    {
        GetWnd()->SetFocus();
    }
}

void AUIMFCHandle::ActivateModal(AUIHandle* const pParent)
{
    ActivateWnd(pParent);
    m_bActivatedAsModal = true;
    this->BeginModal();
}

void AUIMFCHandle::Deactivate()
{
    if ( IsActivated() == false )
    {
        AUIAssertFailReason("Deactivating non-activated handle");
        return;
    }

    if (IsActivatedAsModal())
    {
        this->EndModal(0);
        m_bActivatedAsModal = false;
    }
    else
    {
        GetWnd()->DestroyWindow();
    }
}

void AUIMFCHandle::SetSize( int width, int height )
{
    if ( IsActivated() )
    {
        int x;
        int y;
        GetPosition( x, y );

        UINT flag = SWP_NOZORDER | SWP_NOSIZE;
        if ( IsNonActivate() )
        {
            flag |= SWP_NOACTIVATE;
        }
        GetWnd()->SetWindowPos( nullptr, x, y, width, height, flag );
    }
    AUIHandle::SetSize( width, height );
}

void AUIMFCHandle::SetPosition( int x, int y )
{
    if ( IsActivated() )
    {
        int width;
        int height;
        GetSize( width, height );

        UINT flag = SWP_NOZORDER | SWP_NOREPOSITION;
        if ( IsNonActivate() )
        {
            flag |= SWP_NOACTIVATE;
        }
        GetWnd()->SetWindowPos( nullptr, x, y, width, height, flag );
    }
    AUIHandle::SetPosition( x, y );
    m_bUseDefaultPos = false;
}

void AUIMFCHandle::SetPositionAndSize( int x, int y, int sx, int sy )
{
    if ( IsActivated() )
    {
        UINT flag = SWP_NOZORDER;
        if ( IsNonActivate() )
        {
            flag |= SWP_NOACTIVATE;
        }
        GetWnd()->SetWindowPos( nullptr, x, y, sx, sy, flag );
    }

    AUIHandle::SetPositionAndSize( x, y, sx, sy );
    m_bUseDefaultPos = false;
}

void AUIMFCHandle::GetSize( int& sx, int& sy )
{
    if ( IsActivated() )
    {
        CRect rect;
        GetWnd()->GetWindowRect( rect );
        m_iWidth = rect.Width();
        m_iHeight = rect.Height(); 
    }
    AUIHandle::GetSize( sx, sy );
}

void AUIMFCHandle::GetPosition( int& x, int& y )
{
    if ( IsActivated() )
    {
        CRect rect;
        GetWnd()->GetWindowRect( rect );
        m_iX = rect.left;
        m_iY = rect.top; 
    }
    AUIHandle::GetPosition( x, y );
}

void AUIMFCHandle::GetPositionAndSize( int& x, int& y, int& sx, int& sy )
{
    if ( IsActivated() )
    {
        CRect rect;
        GetWnd()->GetWindowRect( rect );
        m_iX = rect.left;
        m_iY = rect.top; 
        m_iWidth = rect.Width();
        m_iHeight = rect.Height(); 
    }
    AUIHandle::GetPositionAndSize( x, y, sx, sy );
}

bool AUIMFCHandle::MakeTransparent()
{
    if ( IsActivated() == false )
        return false;

    const auto hWnd = GetWnd()->GetSafeHwnd();
    AUIAssert( hWnd );

    typedef DWORD( WINAPI* funcSLWA )( HWND, DWORD, BYTE, DWORD );
    static funcSLWA pFuncSetLayeredWindowAttributes = nullptr;
    static std::once_flag initload;
    std::call_once( initload, [](){
        if (const auto hUser32 = LoadLibrary( _T( "user32" ) ))
            pFuncSetLayeredWindowAttributes = reinterpret_cast< funcSLWA >( GetProcAddress( hUser32, "SetLayeredWindowAttributes" ) );
    } );

    if ( pFuncSetLayeredWindowAttributes == nullptr )
        return false;

    // Layered window
    SetLastError( NULL );
    SetWindowLongPtr( hWnd, GWL_EXSTYLE, GetWindowLongPtr( hWnd, GWL_EXSTYLE ) | WS_EX_LAYERED );
    if ( GetLastError() )
        return false;

    return ( pFuncSetLayeredWindowAttributes( hWnd, RGB( 0, 0, 1 ), GetOpacity(), LWA_COLORKEY | LWA_ALPHA ) > 0 ) ? true : false;
}

void AUIMFCHandle::SetOpacity( const SkAlpha alpha )
{
    m_Opacity = alpha;

    if ( IsActivated() )
    {
        MakeTransparent();
    }
}

bool AUIMFCHandle::IsActivated() const 
{
    if ( ::IsWindow( GetWnd()->GetSafeHwnd() ) )
        return true;
    else
        return false;
}

void AUIMFCHandle::SetTitle( const std::wstring& title )
{
    if ( IsActivated() )
    {
        GetWnd()->SetWindowText( CString( title.c_str() ) );
    }
    AUIHandle::SetTitle( title );
}

void AUIMFCHandle::CaptureMouseEvent()
{
    if ( IsActivated() )
    {
        SetCapture( GetWnd()->GetSafeHwnd() );
        m_bMouseCaptured = true;
    }
    else
    {
        m_bMouseCaptured = false;
    }
}

void AUIMFCHandle::ReleaseMouseEvent()
{
    if ( IsActivated() )
    {
        ReleaseCapture();
    }
    m_bMouseCaptured = false;
}

void AUIMFCHandle::DoShowMinimized()
{
    if ( IsActivated() )
    {
        int flag = SW_MINIMIZE;
        GetWnd()->ShowWindow( flag );
    }
}

void AUIMFCHandle::DoShowMaximized()
{
    if ( IsActivated() )
    {
        int flag = SW_MAXIMIZE;
        GetWnd()->ShowWindow( flag );
    }
}

void AUIMFCHandle::DoShowDefault()
{
    if ( IsActivated() )
    {
        int flag = SW_NORMAL;
        GetWnd()->ShowWindow( flag );
    }
}

void AUIMFCHandle::SetVisible( bool state )
{
    AUIHandle::SetVisible( state );

    if ( IsActivated() )
    {
        int flag = 0;
        if ( IsNonActivate() )
        {
            flag = state ? SW_SHOWNA : SW_HIDE;
        }
        else
        {
            flag = state ? SW_SHOW : SW_HIDE;
        }
        GetWnd()->ShowWindow( flag );
    }
}

void AUIMFCHandle::SetFocus()
{
    AUIHandle::SetFocus();

    if ( IsActivated() && false == IsNonActivate() )
    {
        GetWnd()->SetFocus();
    }
}

void AUIMFCHandle::Invalidate()
{
    AUIHandle::Invalidate();

    if ( IsActivated() )
    {
        GetWnd()->Invalidate();
    }
}

void AUIMFCHandle::BeginModal()
{
    AUIAssert(GetWnd());
    auto pParentWnd = GetWnd()->GetParent();
    if (nullptr == pParentWnd)
    {
        AUIAssert(!"Must have parent");
        return;
    }
    pParentWnd->EnableWindow(FALSE);

    GetWnd()->EnableWindow(TRUE);
    GetWnd()->Invalidate();
    DWORD dwFlags = MLF_SHOWONIDLE;
    if (GetWnd()->GetStyle() & DS_NOIDLEMSG)
        dwFlags |= MLF_NOIDLEMSG;
    GetWnd()->RunModalLoop(dwFlags);

    //Deactivate();
    if (IsActivated())
        Deactivate();
}

void AUIMFCHandle::EndModal(int result)
{
    auto pParentWnd = GetWnd()->GetParent();
    AUIAssert(pParentWnd);
    pParentWnd->EnableWindow(TRUE);

    //GetWnd()->DestroyWindow();
    //// Deactivate
    //Deactivate();


    GetWnd()->EndModalLoop(result);

    //GetWnd()->DestroyWindow();
}

bool AUIMFCHandle::IsZoomed() const
{
    return static_cast<bool>(GetWnd()->IsZoomed());
}

bool AUIMFCHandle::IsIconic() const
{
    return static_cast<bool>(GetWnd()->IsIconic());
}

void AUIMFCHandle::UpdateWindow()
{
    GetWnd()->UpdateWindow();
}

void AUIMFCHandle::SetResizeable(bool val)
{
    SuperClass::SetResizeable(val);
    if (IsActivated())
    {
        if (val)
            GetWnd()->ModifyStyle(NULL, WS_THICKFRAME);
        else
            GetWnd()->ModifyStyle(WS_THICKFRAME, NULL);
    }
}

bool AUIMFCHandle::IsResizeable() const
{
    if (IsActivated())
    {
        if (GetWnd()->GetStyle() & WS_THICKFRAME)
            return true;
        else
            return false;
    }
    return SuperClass::IsResizeable();
}
