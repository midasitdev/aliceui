#include "pch.h"
#include "AUIHandle.h"
#include "AUIWidget.h"

AUIHandle::AUIHandle() noexcept
    : m_bActivated( false )
    , m_bActivatedAsModal(false)
    , m_bTopMost( false )
    , m_bNonActivate( false )
    , m_bVisible( true )
    , m_bMouseCaptured( false )
    , m_iX( 0 )
    , m_iY( 0 )
    , m_iWidth( 0 )
    , m_iHeight( 0 )
    , m_Opacity(kAUIAlpha100 )
{

}

void AUIHandle::SetRootWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    m_pWidget = pWidget;
}

std::shared_ptr< AUIWidget > AUIHandle::GetWidget() const
{
    return m_pWidget;
}

void AUIHandle::SetTitle( const std::wstring& title )
{
    m_strTitle = title;
}

std::wstring AUIHandle::GetTitle() const
{
    return m_strTitle;
}

void AUIHandle::Activate( AUIHandle* const pParent )
{
    m_bActivated = true;
    m_bActivatedAsModal = false;
}

void AUIHandle::Deactivate()
{
    m_bActivated = false;
}

bool AUIHandle::IsActivated() const
{
    return m_bActivated;
}

void AUIHandle::SetOpacity( const SkAlpha opacity )
{
    m_Opacity = opacity;
}

SkAlpha AUIHandle::GetOpacity() const
{
    return m_Opacity;
}

void AUIHandle::SetSize( int width, int height )
{
    m_iWidth = width;
    m_iHeight = height;

    if ( m_pWidget )
        m_pWidget->SetDefaultSize( float( width ), float( height ) );
}

void AUIHandle::SetPosition( int x, int y )
{
    m_iX = x;
    m_iY = y;
}

void AUIHandle::SetPositionAndSize( int x, int y, int width, int height )
{
    m_iX = x;
    m_iY = y;
    m_iWidth = width;
    m_iHeight = height;


    if ( m_pWidget )
        m_pWidget->SetDefaultSize( float( width ), float( height ) );
}

void AUIHandle::GetSize( int& width, int& height )
{
    width = m_iWidth;
    height = m_iHeight;
}

void AUIHandle::GetPosition( int& x, int& y )
{
    x = m_iX;
    y = m_iY;
}

void AUIHandle::GetPositionAndSize( int& x, int& y, int& width, int& height )
{
    x = m_iX;
    y = m_iY;
    width = m_iWidth;
    height = m_iHeight;
}

void AUIHandle::CaptureMouseEvent()
{
    m_bMouseCaptured = true;
}

void AUIHandle::ReleaseMouseEvent()
{
    m_bMouseCaptured = false;
}

void AUIHandle::DoShowMinimized()
{

}

void AUIHandle::DoShowMaximized()
{

}

void AUIHandle::DoShowDefault()
{

}

void AUIHandle::SetMode( AUIHandleMode mode )
{
    m_Mode = mode;
}

AUIHandleMode AUIHandle::GetMode() const
{
    return m_Mode;
}

void AUIHandle::SetVisible( bool state )
{
    if ( auto pWidget = GetWidget() )
        pWidget->SetVisible( state );

    m_bVisible = state;
}

void AUIHandle::SetFocus()
{

}

void AUIHandle::Invalidate()
{

}

void AUIHandle::BeginModal()
{

}

void AUIHandle::EndModal(int result)
{

}

void AUIHandle::ActivateModal(AUIHandle* const pHandle)
{
    m_bActivated = true;
    m_bActivatedAsModal = true;
}

void AUIHandle::UpdateWindow()
{

}

void AUIHandle::SetResizeable(bool val)
{
    m_Resizeable = val;
}

bool AUIHandle::IsResizeable() const
{
    return m_Resizeable;
}

void AUIHandle::SetMinSize(int width, int height)
{
    m_MinWidth = width;
    m_MinHeight = height;
}

void AUIHandle::SetMaxSize(int width, int height)
{
    m_MaxWidth = width;
    m_MaxHeight = height;
}

void AUIHandle::GetMinSize(int& width, int& height)
{
    width = m_MinWidth;
    height = m_MinHeight;
}

void AUIHandle::GetMaxSize(int& width, int& height)
{
    width = m_MaxWidth;
    height = m_MaxHeight;
}

