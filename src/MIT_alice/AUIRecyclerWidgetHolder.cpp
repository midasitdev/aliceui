#include "pch.h"
#include "AUIRecyclerWidgetHolder.h"

AUIRecyclerWidgetHolder::AUIRecyclerWidgetHolder( const std::shared_ptr< AUIWidget >& pItemWidget )
    : m_pItemWidget( pItemWidget )
    , m_bRecyclable( false )
    , m_AdapterPosition( AdapterNoPosition )
    , m_ItemId( AdapterNoId )
    , m_ItemWidgetType( 0 )
    , m_LayoutPosition( AdapterNoPosition )
    , m_OldPosition( AdapterNoPosition )
{

}

AUIRecyclerWidgetHolder::~AUIRecyclerWidgetHolder()
{

}
