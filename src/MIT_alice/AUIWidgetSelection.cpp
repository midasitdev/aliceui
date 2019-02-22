#include "pch.h"
#include "AUIWidgetSelection.h"

void AUIWidgetSelection::Insert( const_iterator pos, const widget_ref_type pWidget )
{
    AUIAssert( Exist( pWidget ) );
    m_listSelWidgets.insert( pos, pWidget );
}

void AUIWidgetSelection::Remove( const widget_ref_type pWidget )
{
     if ( pWidget.expired() )
         return;

     m_listSelWidgets.remove_if( [pWidget]( const widget_ref_type& pListWidget )->bool {
         return ( pListWidget.lock() == pWidget.lock() );
     } );
}

bool AUIWidgetSelection::Exist( const widget_ref_type pWidget )
{
    for ( auto pListWidget : m_listSelWidgets )
    {
        if ( pListWidget.lock() == pWidget.lock() )
            return true;
    }
    return false;
}

void AUIWidgetSelection::GetCopy(list_type& lst) const
{
    lst.assign( m_listSelWidgets.begin(), m_listSelWidgets.end() );
}
