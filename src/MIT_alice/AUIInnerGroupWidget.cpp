#include "pch.h"
#include "AUIInnerGroupWidget.h"
#include "AUIWidgetManager.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIApplication.h"

void AUIInnerGroupWidget::AddChild( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    AUIAssert( widget );
    AUIAssert( this != widget.get() );

    AUIApplication::Instance().GetWidgetTree().AddChildAt( this, pos, widget.get() );

}

bool AUIInnerGroupWidget::HasChild(const std::shared_ptr< AUIWidget >& widget) const
{
    return AUIApplication::Instance().GetWidgetTree().IsChild(const_cast<AUIInnerGroupWidget*>(this), widget.get());
}

void AUIInnerGroupWidget::DelChild( const std::shared_ptr< AUIWidget >& widget )
{
    AUIAssert( widget );
    AUIAssert( this != widget.get() );

    AUIApplication::Instance().GetWidgetTree().DelChild( this, widget.get() );
}

void AUIInnerGroupWidget::PopChild()
{
    AUIAssert( false );
}

void AUIInnerGroupWidget::ClearChild()
{
    AUIApplication::Instance().GetWidgetTree().ClearChild( this );
}

void AUIInnerGroupWidget::ClearChildRecursive()
{
    AUIApplication::Instance().GetWidgetTree().ClearChildRecursive( this );
}

const std::shared_ptr< AUIWidget > AUIInnerGroupWidget::GetNextChildFocusable() const
{
    auto pCurFocused = GetWidgetManager()->GetFocusedTarget().lock();

    const auto arrChildren = GetChildren();

    bool retNext = false ;
    for ( auto child = arrChildren.begin() ; child != arrChildren.end() ; child++ )
    {
        auto pChildWidget = (*child);
        if ( retNext )
        {
            if ( pChildWidget->IsFocusable() )
                return pChildWidget;
        }
        if ( pChildWidget == pCurFocused )
            retNext = true;
    }

    // If not found, from beginning
    for ( auto child = arrChildren.begin() ; child != arrChildren.end() ; child++ )
    {
        auto pChildWidget = (*child);
        if ( pChildWidget == pCurFocused )
            break;
        if ( pChildWidget->IsFocusable() )
            return pChildWidget;
    }
    return {};
}

const std::shared_ptr< AUIWidget > AUIInnerGroupWidget::GetPrevChildFocusable() const
{
    auto pCurFocused = GetWidgetManager()->GetFocusedTarget().lock();

    const auto arrChildren = GetChildren();

    bool retNext = false;
    for ( auto child = arrChildren.rbegin() ; child != arrChildren.rend() ; child++ )
    {
        auto pChildWidget = (*child);
        if ( retNext )
        {
            if ( pChildWidget->IsFocusable() )
                return pChildWidget;
        }
        if ( pChildWidget== pCurFocused )
            retNext = true;
    }

    // If not found, from beginning
    for ( auto child = arrChildren.rbegin() ; child != arrChildren.rend() ; child++ )
    {
        auto pChildWidget = (*child);
        if ( pChildWidget == pCurFocused )
            break;
        if ( pChildWidget->IsFocusable() )
            return pChildWidget;
    }
    return {};
}

const std::shared_ptr< AUIWidget > AUIInnerGroupWidget::GetNextFocusable()
{
    if ( auto pChildWidget = GetNextChildFocusable() )
        return pChildWidget;
    return SuperWidget::GetNextFocusable();
}

const std::shared_ptr< AUIWidget > AUIInnerGroupWidget::GetPrevFocusable()
{
    if ( auto pChildWidget = GetPrevChildFocusable() )
        return pChildWidget;
    return SuperWidget::GetPrevFocusable();
}
