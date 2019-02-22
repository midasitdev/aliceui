#include "pch.h"
#include "AUIRecyclerLayoutManager.h"
#include "AUIRecyclerWidget.h"

AUIRecyclerLayoutManager::AUIRecyclerLayoutManager()
    : m_pRecyclerWidget( nullptr )
{

}

AUIRecyclerLayoutManager::~AUIRecyclerLayoutManager()
{

}

void AUIRecyclerLayoutManager::MeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    AUIAssert( m_pRecyclerWidget );
    this->OnMeasureSize(width, widthSpec, height, heightSpec);
}

void AUIRecyclerLayoutManager::UpdateChildPosition()
{
    AUIAssert( m_pRecyclerWidget );
    this->OnUpdateChildPosition();
}

void AUIRecyclerLayoutManager::AddWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }
    OnAddWidget( pWidget, kAUIChildPosEnd );
}

void AUIRecyclerLayoutManager::AddWidget( const std::shared_ptr< AUIWidget >& pWidget, const size_t index )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }
    OnAddWidget( pWidget, index );
}

void AUIRecyclerLayoutManager::DelWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }

    OnDelWidget( pWidget );
}

void AUIRecyclerLayoutManager::AttachWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }

    OnAttachWidget( pWidget, kAUIChildPosEnd );
}

void AUIRecyclerLayoutManager::AttachWidget( const std::shared_ptr< AUIWidget >& pWidget, const size_t index )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }
    OnAttachWidget( pWidget, index );
}

void AUIRecyclerLayoutManager::DetachWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIAssert( m_pRecyclerWidget );
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Null widget");
        return;
    }
    OnDetachWidget( pWidget );
}

void AUIRecyclerLayoutManager::ClearWidget()
{
    AUIAssert( m_pRecyclerWidget );
    OnClearWidget();
}

void AUIRecyclerLayoutManager::OnAddWidget( const std::shared_ptr< AUIWidget >& pWidget, const size_t index )
{
    GetRecyclerWidget()->AddSubWidgetAt( pWidget, index );
}

void AUIRecyclerLayoutManager::OnDelWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    GetRecyclerWidget()->DelSubWidget( pWidget );
}

void AUIRecyclerLayoutManager::OnAttachWidget( const std::shared_ptr< AUIWidget >& pWidget, const size_t index )
{

}

void AUIRecyclerLayoutManager::OnDetachWidget( const std::shared_ptr< AUIWidget >& pWidget )
{

}

void AUIRecyclerLayoutManager::OnClearWidget()
{
    GetRecyclerWidget()->ClearSubWidget();
}
