#include "pch.h"
#include "AUIRelativeLayout.h"
#include "AUIWidget.h"

void AUIRelativeLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }


    const auto spWidth = pTarget->GetSizePolicyWidth();
    const auto spHeight = pTarget->GetSizePolicyHeight();

    const auto defaultSize = pTarget->GetDefaultSize();

    auto targetWidth = defaultSize.fX;
    auto targetHeight = defaultSize.fY;

    auto childWidthSpec = AUIMeasureSpec::kUnspecified;
    auto childHeightSpec = AUIMeasureSpec::kUnspecified;

    auto needWidthFitting = false;
    auto needHeightFitting = false;

    if (widthSpec == AUIMeasureSpec::kExactly)
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = width;
    }
    else if (widthSpec == AUIMeasureSpec::kAtMost)
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        if (AUISizePolicy::kFixed == spWidth)
        {
            targetWidth = (std::min)(width, defaultSize.fX);
        }
        else
        {
            targetWidth = width;
        }

        if (AUISizePolicy::kContent == spWidth)
        {
            needWidthFitting = true;
        }
    }
    else if (widthSpec == AUIMeasureSpec::kUnspecified)
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = defaultSize.fX;
        needWidthFitting = true;
    }
    else
    {
        AUIAssertFail();
    }


    if (heightSpec == AUIMeasureSpec::kExactly)
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = height;
    }
    else if (heightSpec == AUIMeasureSpec::kAtMost)
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        if (AUISizePolicy::kFixed == spHeight)
        {
            targetHeight = (std::min)(height, defaultSize.fY);
        }
        else
        {
            targetHeight = height;
        }

        if (AUISizePolicy::kContent == spHeight)
        {
            needHeightFitting = true;
        }
    }
    else if (heightSpec == AUIMeasureSpec::kUnspecified)
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = defaultSize.fY;
        needHeightFitting = true;
    }
    else
    {
        AUIAssertFail();
    }



    auto availableWidth = targetWidth - (pTarget->GetPaddingLeft() + pTarget->GetPaddingRight());
    auto availableHeight = targetHeight - (pTarget->GetPaddingTop() + pTarget->GetPaddingBottom());


    auto requiredWidth = 0.0f;
    auto requiredHeight = 0.0f;

    const auto& children = pTarget->GetChildren();
    for (auto itr = children.begin(); itr != children.end(); ++itr)
    {
        auto pChildWidget = (*itr).get();
        if (pChildWidget->IsIgnored())
            continue;

        const auto targetChildWidth = availableWidth - (pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
        const auto targetChildHeight = availableHeight - (pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());


        AUIWidget::OnCallMeasureAndUpdateSize(pChildWidget, targetChildWidth, childWidthSpec, targetChildHeight, childHeightSpec);

        const auto childPos = pChildWidget->GetPosition();
        const auto childSize = pChildWidget->GetMeasureSize();

        requiredWidth = (std::max)(requiredWidth, childPos.fX + childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
        requiredHeight = (std::max)(requiredHeight, childPos.fY + childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());
    }

    if (widthSpec == AUIMeasureSpec::kAtMost)
        requiredWidth = (std::min)(requiredWidth, width);
    if (heightSpec == AUIMeasureSpec::kAtMost)
        requiredHeight = (std::min)(requiredHeight, height);

    if (needWidthFitting)
        targetWidth = requiredWidth;
    if (needHeightFitting)
        targetHeight = requiredHeight;

    pTarget->SetMeasureSize(targetWidth, targetHeight);
}

void AUIRelativeLayout::OnUpdateChildPosition()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }
    const auto width = pTarget->GetWidth();
    const auto height = pTarget->GetHeight();

    const auto& children = pTarget->GetChildren();

    // Update All first
    for (auto& child : children)
    {
        child->OnUpdateChildPosition();
        child->Invalidate();
    }

    // Parent option
    for (auto& child : children)
    {
        if (child->IsIgnored())
            continue;

        auto childpos = child->GetPosition();

        if (child->GetPropParentLeft())
        {
            childpos.fX = pTarget->GetPaddingLeft() + child->GetMarginLeft();
        }
        else if (child->GetPropParentRight())
        {
            childpos.fX = pTarget->GetWidth() - child->GetWidth() - pTarget->GetPaddingRight() - child->GetMarginRight();
        }
        else
        {
            childpos.fX = (std::min)(childpos.fX, width - child->GetWidth() - pTarget->GetPaddingRight() - child->GetMarginRight());
            childpos.fX = (std::max)(childpos.fX, pTarget->GetPaddingLeft() + child->GetMarginLeft());
        }

        if (child->GetPropParentTop())
        {
            childpos.fY = pTarget->GetPaddingTop() + child->GetMarginTop();
        }
        else if (child->GetPropParentBottom())
        {
            childpos.fY = height - child->GetHeight() - pTarget->GetPaddingBottom() - child->GetMarginBottom();
        }
        else
        {
            childpos.fY = (std::min)(childpos.fY, height - child->GetHeight() - pTarget->GetPaddingBottom() - child->GetMarginBottom());
            childpos.fY = (std::max)(childpos.fY, pTarget->GetPaddingTop() + child->GetMarginTop());
        }

        if (child->GetPropParentCenterHorizontal())
        {
            childpos.fX = std::floor(width * 0.5f - child->GetWidth() * 0.5f);
        }
        if (child->GetPropParentCenterVertical())
        {
            childpos.fY = std::floor(height * 0.5f - child->GetHeight() * 0.5f);
        }
        if (child->GetPropParentCenter())
        {
            childpos.fX = std::floor(width * 0.5f - child->GetWidth() * 0.5f);
            childpos.fY = std::floor(height * 0.5f - child->GetHeight() * 0.5f);
        }

        child->SetPosition(childpos + pTarget->GetScrollVal());
    }

    // Target option
    for (auto& child : children)
    {
        if (child->IsIgnored())
            continue;

        auto childpos = child->GetPosition();

        const auto aboveID = child->GetPropAbove();
        const auto pAboveTarget = AUIWidget::FindByRuntimeID(aboveID);
        if (pAboveTarget)
        {
            childpos.fY = pAboveTarget->GetPosition().fY - pAboveTarget->GetMarginTop() - child->GetHeight() - child->GetMarginBottom();
        }

        const auto belowID = child->GetPropBelow();
        const auto pBelowTarget = AUIWidget::FindByRuntimeID(belowID);
        if (pBelowTarget)
        {
            childpos.fY = pBelowTarget->GetPosition().fY + pBelowTarget->GetHeight() + pBelowTarget->GetMarginBottom() + child->GetMarginTop();
        }

        const auto toLeftID = child->GetPropToLeftOf();
        const auto pToLeftTarget = AUIWidget::FindByRuntimeID(toLeftID);
        if (pToLeftTarget)
        {
            childpos.fX = pToLeftTarget->GetPosition().fX - pToLeftTarget->GetMarginLeft() - child->GetWidth() - child->GetMarginRight();
        }

        const auto toRightID = child->GetPropToRightOf();
        const auto pToRightTarget = AUIWidget::FindByRuntimeID(toRightID);
        if (pToRightTarget)
        {
            childpos.fX = pToRightTarget->GetPosition().fX + pToRightTarget->GetWidth() + pToRightTarget->GetMarginRight() + child->GetMarginLeft();
        }

        const auto alignLeftID = child->GetPropAlignLeft();
        const auto pAlignLeftTarget = AUIWidget::FindByRuntimeID(alignLeftID);
        if (pAlignLeftTarget)
        {
            childpos.fX = pAlignLeftTarget->GetPosition().fX + child->GetMarginLeft();
        }

        const auto alignTopID = child->GetPropAlignTop();
        const auto pAlignTopTarget = AUIWidget::FindByRuntimeID(alignTopID);
        if (pAlignTopTarget)
        {
            childpos.fY = pAlignTopTarget->GetPosition().fY + child->GetMarginTop();
        }

        const auto alignRightID = child->GetPropAlignRight();
        const auto pAlignRightTarget = AUIWidget::FindByRuntimeID(alignRightID);
        if (pAlignRightTarget)
        {
            childpos.fX = pAlignRightTarget->GetPosition().fX + pAlignRightTarget->GetWidth() - child->GetWidth() - child->GetMarginRight();
        }

        const auto alignBottomID = child->GetPropAlignBottom();
        const auto pAlignBottomTarget = AUIWidget::FindByRuntimeID(alignBottomID);
        if (pAlignBottomTarget)
        {
            childpos.fY = pAlignBottomTarget->GetPosition().fY + pAlignBottomTarget->GetHeight() - child->GetHeight() - child->GetMarginBottom();
        }

        const auto alignBaselineID = child->GetPropAlignBaseline();
        const auto pAlignBaselineTarget = AUIWidget::FindByRuntimeID(alignBaselineID);
        if (pAlignBaselineTarget)
        {
            // TODO 
            AUIAssert(!"Not yet");
        }


        child->SetPosition(childpos + pTarget->GetScrollVal());
    }
}
