#include "pch.h"
#include "AUIRecyclerAdapter.h"
#include "AUIRecyclerWidgetHolder.h"

AUIRecyclerAdapter::AUIRecyclerAdapter()
{

}

AUIRecyclerAdapter::~AUIRecyclerAdapter()
{

}

size_t AUIRecyclerAdapter::GetItemWidgetType( const size_t pos ) const
{
    return 0;
}

size_t AUIRecyclerAdapter::GetItemCount() const
{
    return OnGetItemCount();
}

void AUIRecyclerAdapter::BindWidgetHolder( const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder, const size_t pos )
{
    OnBindWidgetHolder( pHolder, pos );
}

std::shared_ptr< AUIRecyclerWidgetHolder > AUIRecyclerAdapter::CreateWidgetHolder( AUIWidget* pParent, const size_t widgetType )
{
    if ( nullptr == pParent )
    {
        AUIAssert( pParent );
        return nullptr;
    }
    return OnCreateWidgetHolder( pParent, widgetType );
}

void AUIRecyclerAdapter::AttachedToRecycler( const std::shared_ptr< AUIRecyclerWidget >& pRecycler, const size_t pos )
{

}

void AUIRecyclerAdapter::DetachedFromRecycler( const std::shared_ptr< AUIRecyclerWidget >& pRecycler )
{

}

void AUIRecyclerAdapter::FailedToRecycler( const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder )
{

}

void AUIRecyclerAdapter::WidgetRecycled( const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder )
{

}
