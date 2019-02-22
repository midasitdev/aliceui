#include "pch.h"
#include "AUIWindow.h"
#include "AUIApplication.h"
#include "AUIWindowWidget.h"
#include "AUIWindowTitleBarWidget.h"

namespace {
    const int DefaultWidth = 640;
    const int DefaultHeight = 480;
}

AUIWindow::AUIWindow()
    : m_pWindow(std::make_shared<AUIWindowWidget>())
    , m_iPrevMouseX( 0 )
    , m_iPrevMouseY( 0 )
{
    m_pWindow->SetIgnoreSysButton(true, true, false);

    m_Form.SetSize( DefaultWidth, DefaultHeight );
    m_Form.SetRootWidget( m_pWindow );

    m_spoolWindow.Connect( m_pWindow->GetDragStartSignal(), this, &AUIWindow::OnDragStart );
    m_spoolWindow.Connect( m_pWindow->GetDragEndSignal(), this, &AUIWindow::OnDragEnd );
    m_spoolWindow.Connect( m_pWindow->GetDraggingSignal(), this, &AUIWindow::OnDragging );
    m_spoolWindow.Connect( m_pWindow->GetMinimizeSignal(), this, &AUIWindow::OnClickMinimize );
    m_spoolWindow.Connect( m_pWindow->GetCloseSignal(), this, &AUIWindow::OnClickClose );

}

AUIWindow::AUIWindow(const std::shared_ptr<AUIWindowWidget>& pWindowWidget)
    : m_pWindow(pWindowWidget)
    , m_iPrevMouseX(0)
    , m_iPrevMouseY(0)
{

    m_pWindow->SetIgnoreSysButton(true, true, false);

    m_Form.SetSize(DefaultWidth, DefaultHeight);
    m_Form.SetRootWidget(m_pWindow);

    m_spoolWindow.Connect(m_pWindow->GetDragStartSignal(), this, &AUIWindow::OnDragStart);
    m_spoolWindow.Connect(m_pWindow->GetDragEndSignal(), this, &AUIWindow::OnDragEnd);
    m_spoolWindow.Connect(m_pWindow->GetDraggingSignal(), this, &AUIWindow::OnDragging);
    m_spoolWindow.Connect(m_pWindow->GetMinimizeSignal(), this, &AUIWindow::OnClickMinimize);
    m_spoolWindow.Connect(m_pWindow->GetCloseSignal(), this, &AUIWindow::OnClickClose);
}

AUIWindow::~AUIWindow()
{
    if ( m_Form.IsActivated() )
        m_Form.Deactivate();
}

void AUIWindow::SetContent( const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( m_pContent == pWidget )
        return;
    m_pWindow->DelSubWidget( m_pContent );
    m_pContent = pWidget;
    m_pWindow->AddSubWidget( m_pContent );
}

void AUIWindow::SetTitle( const std::wstring& title )
{
    m_pWindow->SetTitle( title );
    m_Form.SetTitle( title );
}

std::wstring AUIWindow::GetTitle() const
{
    return m_Form.GetTitle();
}

void AUIWindow::Activate()
{
    Activate( nullptr );
}

void AUIWindow::Activate( const std::shared_ptr< AUIWindow >& pParent )
{
    AUIApplication::Instance().RegisterWindow( shared_from_this(), pParent );

    if ( pParent == nullptr )
        m_Form.Activate();
    else
        m_Form.Activate( &pParent->m_Form );
}

void AUIWindow::ActivateWithHandle( AUIHandle* const pHandle )
{
    AUIApplication::Instance().RegisterWindow( shared_from_this(), nullptr );

    m_Form.Activate( pHandle );
}

void AUIWindow::ActivateModal()
{
    ActivateModal( nullptr );
}

void AUIWindow::ActivateModal( const std::shared_ptr< AUIWindow >& pParent )
{
    AUIApplication::Instance().RegisterWindow( shared_from_this(), pParent );

	m_Form.SetTopMost(true);

    if (pParent == nullptr)
        m_Form.ActivateModal();
    else
        m_Form.ActivateModal(&pParent->m_Form);
}

void AUIWindow::Deactivate()
{
    AUIApplication::Instance().UnregisterWindow( shared_from_this() );

    m_Form.Deactivate();
}

void AUIWindow::OnDragStart( AUIWidget* )
{
    AUIApplication::Instance().GetMousePosition( m_iPrevMouseX, m_iPrevMouseY );
    //m_Form.CaptureMouseEvent();
}

void AUIWindow::OnDragEnd( AUIWidget* const )
{
    //m_Form.ReleaseMouseEvent();
}

void AUIWindow::OnDragging( AUIWidget*, float dx, float dy )
{
    int curMouseX;
    int curMouseY;
    AUIApplication::Instance().GetMousePosition( curMouseX, curMouseY );

    const auto diffX = ( curMouseX - m_iPrevMouseX );
    const auto diffY = ( curMouseY - m_iPrevMouseY );

    if ( m_Form.IsActivated() )
    {
        int prevPosX;
        int prevPosY;
        m_Form.GetPosition( prevPosX, prevPosY );
        m_Form.SetPosition( prevPosX + diffX, prevPosY + diffY );
    }

    m_iPrevMouseX = curMouseX;
    m_iPrevMouseY = curMouseY;
}

void AUIWindow::OnClickMinimize( AUIWidget* )
{
    ClickMinimizeSignal.Send( this );
    m_Form.DoShowMinimized();
}

void AUIWindow::OnClickClose( AUIWidget* )
{
    ClickCloseSignal.Send( this );
    Deactivate();
}

void AUIWindow::SetIgnoreSysButton( bool ignore)
{
    m_pWindow->SetIgnoreSysButton(ignore);
}

void AUIWindow::SetSize( int width, int height )
{
    m_Form.SetSize( width, height );
}

void AUIWindow::SetPosition( int x, int y )
{
    m_Form.SetPosition( x, y );
}

void AUIWindow::SetPositionAndSize( int x, int y, int width, int height )
{
    m_Form.SetPositionAndSize( x, y, width, height );
}

void AUIWindow::GetSize( int& width, int& height )
{
    m_Form.GetSize( width, height );
}

void AUIWindow::GetPosition( int& x, int& y )
{
    m_Form.GetPosition( x, y );
}

void AUIWindow::SetBackgroundDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    m_pWindow->SetBackgroundDrawable( pDrawable );
}

void AUIWindow::SetTitleBarDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    m_pWindow->GetTitleBarWidget()->ClearLayer();
    m_pWindow->GetTitleBarWidget()->InsertLayer( pDrawable );
}

bool AUIWindow::IsActivated() const
{
    return m_Form.IsActivated();
}

void AUIWindow::SetIgnoreTitleBar(bool ignore)
{
    m_pWindow->SetIgnoreTitleBar(ignore);
}

void AUIWindow::SetTransparent(bool val)
{
    m_Form.SetTransparent(val);
}

bool AUIWindow::IsTransparent() const
{
    return m_Form.IsTransparent();
}

void AUIWindow::SetMinSize(int width, int height)
{
    m_Form.SetMinSize(width, height);
}

void AUIWindow::SetMaxSize(int width, int height)
{
    m_Form.SetMaxSize(width, height);
}

void AUIWindow::SetResizeable(bool val)
{
    m_Form.SetResizeable(val);
}

bool AUIWindow::IsResizeable() const
{
    return m_Form.IsResizeable();
}
