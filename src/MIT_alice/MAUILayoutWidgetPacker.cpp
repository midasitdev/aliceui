#include "stdafx.h"
#include "MAUILayoutWidgetPacker.h"
#include "MAUILayoutWidget.h"
#include "MAUILinearLayoutWidget.h"
#include "MAUIRelativeLayoutWidget.h"

using namespace mit::alice;

MRUNTIME_IMPL_KINDOF( MAUILayoutWidgetPacker, MAUIWidgetPacker );

MAUILayoutWidgetPacker::MAUILayoutWidgetPacker()
    : MAUIWidgetPacker( std::make_shared< MAUILinearLayoutWidget >() )
{
    assert( GetBase() );
}

MAUILayoutWidgetPacker::MAUILayoutWidgetPacker( const std::shared_ptr< MAUILayoutWidget >& pBase )
    : MAUIWidgetPacker( pBase )
{
    assert( GetBase() );
}

MAUILayoutWidgetPacker::~MAUILayoutWidgetPacker()
{

}

std::shared_ptr< MAUILayoutWidgetPacker > MAUILayoutWidgetPacker::CreateLinear( bool horizontal )
{
    return std::make_shared< MAUILayoutWidgetPacker >( std::make_shared< MAUILinearLayoutWidget >( horizontal ) );
}

std::shared_ptr< MAUILayoutWidgetPacker > MAUILayoutWidgetPacker::CreateRelative()
{
    return std::make_shared< MAUILayoutWidgetPacker >( std::make_shared< MAUIRelativeLayoutWidget >() );
}

bool MAUILayoutWidgetPacker::OnStart()
{
    GetBaseCast< MAUILayoutWidget >()->ClearSubWidget();

    return true;
}

bool MAUILayoutWidgetPacker::OnEnd()
{
    return true;
}

bool MAUILayoutWidgetPacker::OnInsert( const std::shared_ptr< MAUIWidget >& pWidget )
{
    assert( pWidget );

    GetBaseCast< MAUILayoutWidget >()->AddSubWidget( pWidget );

    return true;
}

bool MAUILayoutWidgetPacker::OnSetProperty( const MAUIProperty& prop )
{
    GetBase()->SetProperty( prop );

    return true;
}
