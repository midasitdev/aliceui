#include "pch.h"
#include "AUIFrameLayout.h"
#include "AUIWidget.h"

void AUIFrameLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
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
    auto needDepthFitting = false;

    auto needWidthFitParent = false;
    auto needHeightFitParent = false;
    auto needDepthFitParent = false;


    if (AUIMeasureSpec::kExactly == widthSpec)
    {
        if (AUISizePolicy::kParent == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kExactly;
            targetWidth = width;
        }
        else if (AUISizePolicy::kFixed == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kExactly;
            targetWidth = width;
        }
        else if (AUISizePolicy::kContent == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
        else
        {
            AUIAssertFail();
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
    }
    else if (AUIMeasureSpec::kAtMost == widthSpec)
    {
        if (AUISizePolicy::kParent == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
        else if (AUISizePolicy::kFixed == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = (std::min)(width, defaultSize.fX);
            if (SkScalarNearlyEqual(targetWidth, width))
                needWidthFitting = true;
        }
        else if (AUISizePolicy::kContent == spWidth)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
            needWidthFitting = true;
        }
        else
        {
            AUIAssertFail();
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
            needWidthFitting = true;
        }
    }
    else if (AUIMeasureSpec::kUnspecified == widthSpec)
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = defaultSize.fX;
        needWidthFitting = true;
    }
    else
    {
        AUIAssertFail();
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = defaultSize.fX;
        needWidthFitting = true;
    }


    if (AUIMeasureSpec::kExactly == heightSpec)
    {
        if (AUISizePolicy::kParent == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kExactly;
            targetHeight = height;
        }
        else if (AUISizePolicy::kFixed == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kExactly;
            targetHeight = height;
        }
        else if (AUISizePolicy::kContent == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
        }
        else
        {
            AUIAssertFail();
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
        }
    }
    else if (AUIMeasureSpec::kAtMost == heightSpec)
    {
        if (AUISizePolicy::kParent == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
        }
        else if (AUISizePolicy::kFixed == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = (std::min)(height, defaultSize.fY);
            if (SkScalarNearlyEqual(targetHeight, height))
                needHeightFitting = true;
        }
        else if (AUISizePolicy::kContent == spHeight)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
            needHeightFitting = true;
        }
        else
        {
            AUIAssertFail();
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
            needHeightFitting = true;
        }
    }
    else if (AUIMeasureSpec::kUnspecified == heightSpec)
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = height;
        needHeightFitting = true;
    }
    else
    {
        AUIAssertFail();
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = height;
        needHeightFitting = true;
    }


    auto availableWidth = targetWidth - (pTarget->GetPaddingLeft() + pTarget->GetPaddingRight());
    auto availableHeight = targetHeight - (pTarget->GetPaddingTop() + pTarget->GetPaddingBottom());


    auto requiredWidth = 0.0f;
    auto requiredHeight = 0.0f;
    auto requiredDepth = 0.0f;

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
        const auto childSize = pChildWidget->GetSize();

        requiredWidth = (std::max)(requiredWidth, childPos.fX + childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
        requiredHeight = (std::max)(requiredHeight, childPos.fY + childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());
    }

    if (AUIMeasureSpec::kAtMost == widthSpec)
        requiredWidth = (std::min)(requiredWidth, width);
    if (AUIMeasureSpec::kAtMost == heightSpec)
        requiredHeight = (std::min)(requiredHeight, height);

	if (needWidthFitting)
        targetWidth = requiredWidth;
    if (needHeightFitting)
        targetHeight = requiredHeight;

    pTarget->SetMeasureSize(targetWidth, targetHeight);
}

void AUIFrameLayout::OnUpdateChildPosition()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    const auto startX = pTarget->GetPaddingLeft();
    const auto startY = pTarget->GetPaddingTop();

    const auto arrChildren = pTarget->GetChildren();
    for (auto& child : arrChildren)
    {
        child->SetPosition(startX + child->GetMarginLeft() + pTarget->GetScrollX(), startY + child->GetMarginTop() + pTarget->GetScrollY());

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition(child);
    }
}
