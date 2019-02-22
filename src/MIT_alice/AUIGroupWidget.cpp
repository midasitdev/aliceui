#include "pch.h"
#include "AUIGroupWidget.h"

void AUIGroupWidget::AddSubWidget( const std::shared_ptr< AUIWidget >& widget )
{
    this->AddSubWidgetAt( widget, kAUIChildPosEnd );
}

void AUIGroupWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    if ( nullptr == widget )
        return;

    AddChild( widget, pos );
}

bool AUIGroupWidget::HasSubWidget(const std::shared_ptr<AUIWidget>& widget) const
{
    if (nullptr == widget)
        return false;

    return HasChild(widget);
}

void AUIGroupWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget)
{
    if ( widget == nullptr )
        return;

    DelChild( widget );
}

void AUIGroupWidget::PopSubWidget()
{
    PopChild();
}

void AUIGroupWidget::ClearSubWidget()
{
    ClearChild();
}

std::shared_ptr< AUIWidget > AUIGroupWidget::FindSubWidget( const size_t pos )
{
    return FindChild( pos );
}

size_t AUIGroupWidget::SubWidgetCount() const
{
    return ChildCount();
}

void AUIGroupWidget::ClearSubWidgetRecursive()
{
    ClearChildRecursive();
}
