#include "pch.h"
#include "AUIPopup.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"

AUIPopup::AUIPopup()
    : m_pWidgetManager( nullptr )
{

}

AUIPopup::~AUIPopup()
{

}

bool AUIPopup::IsInvoked() const
{
    if ( m_pWidgetManager )
    {
        if ( m_pWidgetManager->IsInvoked( m_pPopupWidget ) )
            return true;
    }
    return false;
}

bool AUIPopup::Invoke( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pParent, const AUIPopupPos& opt )
{
    if ( pWidgetManager == nullptr )
        return false;

    if ( pWidgetManager )
    {
        if ( pWidgetManager->IsInvoked( m_pPopupWidget ) )
            pWidgetManager->Dismiss( m_pPopupWidget );
    }

    m_pWidgetManager = pWidgetManager;
    m_wpParent = pParent;

    AUIAssert( m_pWidgetManager );
    m_pWidgetManager->Invoke( m_pPopupWidget , pParent, GetPopupPosition(), opt );

    InvokeSignal.Send();

    return true;
}

void AUIPopup::Dismiss()
{
    if ( m_pWidgetManager )
    {
        if ( m_pWidgetManager->IsInvoked( m_pPopupWidget ) )
            m_pWidgetManager->Dismiss( m_pPopupWidget );
    }
    m_pWidgetManager = nullptr;
    DismissSignal.Send();
}

void AUIPopup::SetPopupWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    Dismiss();
    m_pPopupWidget = pWidget;
    Invoke( m_pWidgetManager, m_wpParent.lock() );
}
