#include "pch.h"
#include "AUIMFCApplication.h"
#include "AUIMFCHandle.h"

namespace {
    auto funcGetMainWnd() {
        return ::AfxGetApp()->GetMainWnd();
    }
}

AUIApplication::Impl::Impl()
{
    const auto hModule = GetModuleHandle(nullptr);
    wchar_t path[_MAX_PATH] = { L'\0', };
    AUIAssert( hModule );
    ::GetModuleFileNameW(hModule, path, _MAX_PATH);
    AUIAssert(wcslen(path) > 0);
    const auto exepath = std::wstring(path);
    const auto dirpos = exepath.rfind( L'\\' );
    m_strExeDir = exepath.substr( 0, dirpos );
    AUIAssert( m_strExeDir.empty() == false );
}

AUIHandle* AUIApplication::Impl::GetApplicationHandle() const
{
    static auto sApplicationHandle = std::make_shared<AUIMFCHandle>(funcGetMainWnd());
    return sApplicationHandle.get();
}

void AUIApplication::Impl::GetApplicationSize( int& width, int& height ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    width = rect.Width();
    height = rect.Height();
}

void AUIApplication::Impl::GetApplicationPosition( int& x, int& y ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    x = rect.left;
    y = rect.top;
}

std::wstring AUIApplication::Impl::GetApplicationDirectory() const
{
    return m_strExeDir;
}

void AUIApplication::Impl::GetApplicationPositionAndSize( int& x, int& y, int& width, int& height ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    x = rect.left;
    y = rect.top;
    width = rect.Width();
    height = rect.Height();
}

AUIHandle* const AUIApplication::Impl::GetDesktopHandle() const
{
    static auto sDesktopHandle = std::make_shared<AUIMFCHandle>(CWnd::GetDesktopWindow());
    return sDesktopHandle.get();
}

void AUIApplication::Impl::GetDesktopSize( int& width, int& height ) const
{
    width = ::GetSystemMetrics( SM_CXSCREEN );
    height = ::GetSystemMetrics( SM_CYSCREEN );
}

void AUIApplication::Impl::GetMonitorCount( int& count ) const
{
    count = ::GetSystemMetrics( SM_CMONITORS );
}

void AUIApplication::Impl::GetVirtualScreenSize( int& width, int& height ) const
{
    width = ::GetSystemMetrics( SM_CXVIRTUALSCREEN );
    height = ::GetSystemMetrics( SM_CYVIRTUALSCREEN );
}

void AUIApplication::Impl::GetMousePosition( int& x, int& y ) const
{
    CPoint point;
    ::GetCursorPos( &point );
    x = int( point.x );
    y = int( point.y );
}

void AUIApplication::Impl::GetMouseDragOffset( int& x, int& y ) const
{
    x = ::GetSystemMetrics( SM_CXDRAG );
    y = ::GetSystemMetrics( SM_CYDRAG );
}

bool AUIApplication::Impl::IsMouseRightHanded() const
{
    return ( !::GetSystemMetrics( SM_SWAPBUTTON ) );
}

void AUIApplication::Impl::ConvertToDesktopPos( int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle )
{
    if ( nullptr == pHandle )
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Invalid handle");
        return;
    }
    AUIAssert( dynamic_cast< AUIMFCHandle* >( pHandle ) );
    auto pMFCHandle = static_cast< AUIMFCHandle* >( pHandle );
    auto pWnd = pMFCHandle->GetWnd();
    if ( nullptr == pWnd )
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Can't find CWnd class");
        return;
    }

    CPoint pt( x, y );
    ::ClientToScreen( pWnd->GetSafeHwnd(), &pt );
    desktopX = pt.x;
    desktopY = pt.y;
}

void AUIApplication::Impl::GetMonitorRectFromPoint( SkRect& monitorRect, const int& desktopX, const int& desktopY )
{
    const auto hMonitor = ::MonitorFromPoint( CPoint( desktopX, desktopY ), MONITOR_DEFAULTTONEAREST );
    MONITORINFOEX miex = { 0, };
    miex.cbSize = sizeof( miex );
    ::GetMonitorInfo( hMonitor, &miex );

    const auto l = static_cast<SkScalar>( miex.rcMonitor.left );
    const auto t = static_cast<SkScalar>( miex.rcMonitor.top );
    const auto r = static_cast<SkScalar>( miex.rcMonitor.right );
    const auto b = static_cast<SkScalar>( miex.rcMonitor.bottom );

    monitorRect = SkRect::MakeLTRB( l, t, r, b );
}
