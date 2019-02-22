#include "pch.h"
#include "AUIAbsoluteLayout.h"
#include "AUIWidget.h"

void AUIAbsoluteLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
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
        targetWidth = width;

        if (AUISizePolicy::kParent != spWidth)
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
        targetHeight = height;

        if (AUISizePolicy::kParent != spHeight)
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
        const auto childSize = pChildWidget->GetMeasureSize();

        requiredWidth = (std::max)(requiredWidth, childPos.fX + childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
        requiredHeight = (std::max)(requiredHeight, childPos.fY + childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());
    }

    if (widthSpec == AUIMeasureSpec::kAtMost)
    {
        if (AUISizePolicy::kFixed == spWidth)
        {
            requiredWidth = (std::min)(defaultSize.fX, width);
        }
        else
        {
            requiredWidth = (std::min)(requiredWidth, width);
        }
    }
    if (heightSpec == AUIMeasureSpec::kAtMost)
    {
        if (AUISizePolicy::kFixed == spHeight)
        {
            requiredHeight = (std::min)(defaultSize.fY, height);
        }
        else
        {
            requiredHeight = (std::min)(requiredHeight, height);
        }
    }

    if (needWidthFitting)
        targetWidth = requiredWidth;
    if (needHeightFitting)
        targetHeight = requiredHeight;

    pTarget->SetMeasureSize(targetWidth, targetHeight);
}

void AUIAbsoluteLayout::OnUpdateChildPosition()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    const auto arrChildren = pTarget->GetChildren();

    for (auto child = arrChildren.begin(); child != arrChildren.end(); ++child)
    {
        auto pChildWidget = (*child);
        pChildWidget->OnUpdateChildPosition();
        pChildWidget->Invalidate();
    }
}
