#include "stdafx.h"
#include "MAUIExpandableWidgetPacker.h"
#include "MAUIExpandableWidget.h"
#include "MAUILinearLayoutWidget.h"

using namespace mit::alice;

MRUNTIME_IMPL_KINDOF( MAUIExpandableWidgetPacker, MAUIWidgetPacker );

MAUIExpandableWidgetPacker::MAUIExpandableWidgetPacker()
    : MAUIWidgetPacker( std::make_shared< MAUIExpandableWidget >() )
{
    assert( GetBase() );
}

MAUIExpandableWidgetPacker::MAUIExpandableWidgetPacker( const std::shared_ptr< MAUIExpandableWidget >& pBase )
    : MAUIWidgetPacker( pBase )
{
    assert( GetBase() );
}

MAUIExpandableWidgetPacker::~MAUIExpandableWidgetPacker()
{

}

bool MAUIExpandableWidgetPacker::OnStart()
{
    m_pContent = OnNewContent();

    GetBaseCast< MAUIExpandableWidget >()->SetContentWidget( m_pContent );

    return true;
}

bool MAUIExpandableWidgetPacker::OnEnd()
{

    return true;
}

bool MAUIExpandableWidgetPacker::OnInsert( const std::shared_ptr< MAUIWidget >& pWidget )
{
    assert( m_pContent );
    m_pContent->AddSubWidget( pWidget );

    return true;
}

bool MAUIExpandableWidgetPacker::OnSetProperty( const MAUIProperty& prop )
{
    GetBase()->SetProperty( prop );

    return true;
}

std::shared_ptr< MAUILayoutWidget > MAUIExpandableWidgetPacker::OnNewContent()
{
    return std::make_shared< MAUILinearLayoutWidget >();
}

void MAUIExpandableWidgetPacker::SetTitle( const std::wstring& title )
{
    GetBaseCast< MAUIExpandableWidget >()->SetTitleCaption( title );
}
