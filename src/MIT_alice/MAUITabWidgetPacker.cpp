#include "stdafx.h"
#include "MAUITabWidgetPacker.h"
#include "MAUITabWidget.h"
#include "MAUITab.h"
#include "MAUIImageDrawable.h"

using namespace mit::alice;

MRUNTIME_IMPL_KINDOF( MAUITabWidgetPacker, MAUIWidgetPacker );

MAUITabWidgetPacker::MAUITabWidgetPacker()
    : MAUIWidgetPacker( std::make_shared< MAUITabWidget >() )
    , m_TabName( L"N/A" )
{
    assert( GetBase() );
}

MAUITabWidgetPacker::MAUITabWidgetPacker( const std::shared_ptr< MAUITabWidget >& pBase )
    : MAUIWidgetPacker( pBase )
{
    assert( GetBase() );
}

MAUITabWidgetPacker::~MAUITabWidgetPacker()
{

}

bool MAUITabWidgetPacker::OnStart()
{
    GetBaseCast< MAUITabWidget >()->ClearTab();
    m_TabData.clear();
    return true;
}

bool MAUITabWidgetPacker::OnEnd()
{
    for ( auto pTab : m_TabData )
    {
        GetBaseCast< MAUITabWidget >()->AddTab( pTab );
    }
    m_TabData.clear();


    return true;
}

bool MAUITabWidgetPacker::OnInsert( const std::shared_ptr< MAUIWidget >& pWidget )
{
    m_TabData.emplace_back( this->OnNewTab( pWidget ) );

    SetTabName( L"N/A" );
    SetTabIcon( nullptr );

    return true;
}

bool MAUITabWidgetPacker::OnSetProperty( const MAUIProperty& prop )
{
    GetBase()->SetProperty( prop );

    return true;
}

std::shared_ptr< MAUITab > MAUITabWidgetPacker::OnNewTab( const std::shared_ptr< MAUIWidget >& pContent )
{
    auto pIconDrawable = std::make_shared< MAUIImageDrawable >();
    pIconDrawable->SetImage( m_pIcon );
    pIconDrawable->SetImageStretch( ImageStretch::Original );
    return MAUITab::CreateTab( m_TabName, pIconDrawable, pContent );
}
