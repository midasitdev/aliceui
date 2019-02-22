#include "pch.h"
#include "AUIRecyclerItemDecorator.h"
#include "AUIWidget.h"

AUIRecyclerItemDecorator::AUIRecyclerItemDecorator()
{

}

AUIRecyclerItemDecorator::~AUIRecyclerItemDecorator()
{

}

void AUIRecyclerItemDecorator::GetItemOffset( SkRect& outRect, const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{
    AUIAssert( pWidget );
    AUIAssert( pParent );
    this->OnGetItemOffset( outRect, pWidget, pParent );
}

void AUIRecyclerItemDecorator::OnGetItemOffset( SkRect& outRect, const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{
    outRect.fLeft = pWidget->GetPaddingLeft();
    outRect.fTop = pWidget->GetPaddingTop();
    outRect.fRight = pWidget->GetPaddingRight();
    outRect.fBottom = pWidget->GetPaddingBottom();
}

void AUIRecyclerItemDecorator::Draw( SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{
    AUIAssert( canvas );
    AUIAssert( pParent );
    this->OnDraw( canvas, pParent );
}

void AUIRecyclerItemDecorator::DrawOver( SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{
    AUIAssert( canvas );
    AUIAssert( pParent );
    this->OnDrawOver( canvas, pParent );
}

void AUIRecyclerItemDecorator::OnDraw( SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{

}

void AUIRecyclerItemDecorator::OnDrawOver( SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent )
{

}
