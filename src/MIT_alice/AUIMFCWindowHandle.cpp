#include "pch.h"
#include "AUIMFCWindowHandle.h"
#include "AUIWidget.h"
#include "AUIRasterWidgetManager.h"

AUIMFCWindowHandle::AUIMFCWindowHandle()
    : SuperClass( &m_wnd )
{
    SetWndClassName(m_wnd.kWndClassName);
}

void AUIMFCWindowHandle::Activate( AUIHandle* const pParent )
{
    m_wnd.GetWidgetManager()->SetHandle(shared_from_this());
    m_wnd.SetRootWidget(m_pWidget);
    SuperClass::Activate( pParent );


    AUIAssert( IsActivated() );
}

void AUIMFCWindowHandle::ActivateModal(AUIHandle* const pParent)
{
    m_wnd.GetWidgetManager()->SetHandle(shared_from_this());
    m_wnd.SetRootWidget(m_pWidget);
    SuperClass::ActivateModal(pParent);
}

void AUIMFCWindowHandle::Deactivate()
{
    m_wnd.SetRootWidget( nullptr );
    m_wnd.GetWidgetManager()->SetHandle( nullptr );

    SuperClass::Deactivate();
}

void AUIMFCWindowHandle::SetRootWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    SuperClass::SetRootWidget( pWidget );

    if ( IsActivated() )
    {
        m_wnd.SetRootWidget( m_pWidget );
    }
}

void AUIMFCWindowHandle::SetSubWindowType(const SUB_WINDOW_TYPE& type)
{
    m_wnd.SetSubWindowType(type);
}

SUB_WINDOW_TYPE AUIMFCWindowHandle::GetSubWindowType() const
{
    return m_wnd.GetSubWindowType();
}

void AUIMFCWindowHandle::SetTransparent(bool val)
{
    m_wnd.SetLayeredWindow(val);
}

bool AUIMFCWindowHandle::IsTransparent() const
{
    return m_wnd.IsLayeredWindow();
}

void AUIMFCWindowHandle::SetMinSize(int width, int height)
{
    SuperClass::SetMinSize(width, height);
    m_wnd.SetMinSize(width, height);
}

void AUIMFCWindowHandle::SetMaxSize(int width, int height)
{
    SuperClass::SetMaxSize(width, height);
    m_wnd.SetMaxSize(width, height);
}
