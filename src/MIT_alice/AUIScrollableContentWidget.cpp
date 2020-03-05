#include "pch.h"
#include "AUIScrollableContentWidget.h"

namespace {
    constexpr SkScalar kMaxFullContentHeight = 600000.0f;
    constexpr SkScalar kOverfittingSize = 600000.0f;
}


AUIScrollableContentWidget::AUIScrollableContentWidget()
{
    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);
}

AUIScrollableContentWidget::~AUIScrollableContentWidget()
{

}

void AUIScrollableContentWidget::OnScrolling(float delta)
{
    ScrollSignal.Send( this, delta );
}

bool AUIScrollableContentWidget::OnMouseWheel( MAUIMouseEvent::EventFlag flag, float delta )
{
    if ( IsMouseHover() )
    {
        if ( !!( flag & MAUIMouseEvent::kShift_EventFlag ) )
        {
            OnScrolling( 10.0f * delta );
        }
        else
        {
            OnScrolling( delta );
        }
    }

    return true;
}

void AUIScrollableContentWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    const auto beforeHeight = height;
    if ( AUISizePolicy::kContent == GetSizePolicyHeight() && AUIMeasureSpec::kAtMost == heightSpec )
    {
        height = kOverfittingSize;
    }
    SuperWidget::OnMeasureSize(width, widthSpec, height, widthSpec);

    if (kOverfittingSize <= GetMeasureHeight())
        SetMeasureSize(GetMeasureWidth(), kMaxFullContentHeight);
}
