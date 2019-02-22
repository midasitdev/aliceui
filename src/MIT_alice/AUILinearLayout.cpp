#include "pch.h"
#include "AUILinearLayout.h"
#include "AUIWidget.h"

void AUILinearLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    const auto isHorizontal = IsHorizontal();

    const auto spWidth = pTarget->GetSizePolicyWidth();
    const auto spHeight = pTarget->GetSizePolicyHeight();

    const auto defaultSize = pTarget->GetDefaultSize();


    auto targetWidth = defaultSize.fX;
    auto targetHeight = defaultSize.fY;

    auto childWidthSpec = AUIMeasureSpec::kUnspecified;
    auto childHeightSpec = AUIMeasureSpec::kUnspecified;

    auto needWidthFitting = false;
    auto needHeightFitting = false;

    auto needWidthFitParent = false;
    auto needHeightFitParent = false;

    if (isHorizontal)
    {
        if (widthSpec == AUIMeasureSpec::kExactly)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
        else if (widthSpec == AUIMeasureSpec::kAtMost)
        {
            if (spWidth == AUISizePolicy::kParent)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = width;
                needWidthFitParent = true;
            }
            else if (spWidth == AUISizePolicy::kFixed)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = (std::min)(defaultSize.fX, width);
            }
            else if (spWidth == AUISizePolicy::kContent)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = width;
                needWidthFitting = true;
            }
            else
            {
                AUIAssertFail();
            }
        }
        else if (widthSpec == AUIMeasureSpec::kUnspecified)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = defaultSize.fX;
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
            if (spHeight == AUISizePolicy::kParent)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = height;
                needHeightFitParent = true;
            }
            else if (spHeight == AUISizePolicy::kFixed)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = (std::min)(defaultSize.fY, height);
            }
            else if (spHeight == AUISizePolicy::kContent)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = height;
                needHeightFitting = true;
            }
            else
            {
                AUIAssertFail();
            }
        }
        else if (heightSpec == AUIMeasureSpec::kUnspecified)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = defaultSize.fY;
        }
        else
        {
            AUIAssertFail();
        }
    }
    else
    {
        if (widthSpec == AUIMeasureSpec::kExactly)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
        else if (widthSpec == AUIMeasureSpec::kAtMost)
        {
            if (spWidth == AUISizePolicy::kParent)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = width;
                needWidthFitParent = true;
            }
            else if (spWidth == AUISizePolicy::kFixed)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = (std::min)(defaultSize.fX, width);
            }
            else if (spWidth == AUISizePolicy::kContent)
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = width;
                needWidthFitting = true;
            }
            else
            {
                AUIAssertFail();
            }
        }
        else if (widthSpec == AUIMeasureSpec::kUnspecified)
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = defaultSize.fX;
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
            if (spHeight == AUISizePolicy::kParent)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = height;
                needHeightFitParent = true;
            }
            else if (spHeight == AUISizePolicy::kFixed)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = (std::min)(defaultSize.fY, height);
            }
            else if (spHeight == AUISizePolicy::kContent)
            {
                childHeightSpec = AUIMeasureSpec::kAtMost;
                targetHeight = height;
                needHeightFitting = true;
            }
            else
            {
                AUIAssertFail();
            }
        }
        else if (heightSpec == AUIMeasureSpec::kUnspecified)
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = defaultSize.fY;
        }
        else
        {
            AUIAssertFail();
        }
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

        const auto childSize = pChildWidget->GetSize();
        if (isHorizontal)
        {
            availableWidth -= (childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
            requiredHeight = (std::max)(requiredHeight, childSize.fY + pTarget->GetPaddingTop() + pTarget->GetPaddingBottom() + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());
        }
        else
        {
            availableHeight -= (childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom());
            requiredWidth = (std::max)(requiredWidth, childSize.fX + pTarget->GetPaddingLeft() + pTarget->GetPaddingRight() + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight());
        }
    }

    if (isHorizontal)
    {
        requiredWidth = targetWidth - availableWidth;
    }
    else
    {
        requiredHeight = targetHeight - availableHeight;
    }

    // Only none or one option
    AUIAssert(!(needWidthFitting && needWidthFitParent));
    AUIAssert(!(needHeightFitting && needHeightFitParent));

    if (needWidthFitting)
    {
        targetWidth = requiredWidth;
    }
    else if (needWidthFitParent)
    {
        targetWidth = width;
    }
    if (needHeightFitting)
    {
        targetHeight = requiredHeight;
    }
    else if (needHeightFitParent)
    {
        targetHeight = height;
    }

    pTarget->SetMeasureSize(targetWidth, targetHeight);
}

void AUILinearLayout::OnUpdateChildPosition()
{
    if (IsHorizontal())
        OnUpdateChildPosition_Horizontal();
    else
        OnUpdateChildPosition_Vertical();
}

void AUILinearLayout::OnUpdateChildPosition_Horizontal()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    const auto height = pTarget->GetHeight();
    const auto startX = pTarget->GetPaddingLeft();
    const auto startY = pTarget->GetPaddingTop();
    const auto endY = height - pTarget->GetPaddingBottom();


    const auto toParentLeft = pTarget->GetPropGravityLeft();
    const auto toParentTop = pTarget->GetPropGravityTop();
    const auto toParentRight = pTarget->GetPropGravityRight();
    const auto toParentBottom = pTarget->GetPropGravityBottom();
    const auto toParentCenterHorizontal = pTarget->GetPropGravityCenterHorizontal();
    const auto toParentCenterVertical = pTarget->GetPropGravityCenterVertical();
    const auto toParentCenter = pTarget->GetPropGravityCenter();

    auto childPosX = startX;

    const auto arrChildren = pTarget->GetChildren();

    if (toParentRight)
    {
        SkScalar totalChildrenWidth = 0.0f;
        for (size_t idx = 0; idx < arrChildren.size(); idx++)
        {
            totalChildrenWidth += arrChildren[idx]->GetMarginLeft() + arrChildren[idx]->GetWidth() + arrChildren[idx]->GetMarginRight();
        }
        childPosX = pTarget->GetWidth() - pTarget->GetPaddingLeft() - pTarget->GetPaddingRight() - totalChildrenWidth;
    }

    for (auto& child : arrChildren)
    {
        if (child->IsIgnored())
            continue;

        const auto toLeft = child->GetPropLayoutGravityLeft();
        const auto toTop = child->GetPropLayoutGravityTop();
        const auto toRight = child->GetPropLayoutGravityRight();
        const auto toBottom = child->GetPropLayoutGravityBottom();
        const auto toCenterHorizontal = child->GetPropLayoutGravityCenterHorizontal();
        const auto toCenterVertical = child->GetPropLayoutGravityCenterVertical();
        const auto toCenter = child->GetPropLayoutGravityCenter();

        childPosX += child->GetMarginLeft();

        auto childPosY = startY + child->GetMarginTop();

        if (toLeft || toTop || toRight || toBottom || toCenterHorizontal || toCenterVertical || toCenter)
        {
            // Use child's option
            if (toBottom)
            {
                childPosY = endY - child->GetHeight() - child->GetMarginBottom();
            }
            if (toCenterVertical || toCenter)
            {
                childPosY = pTarget->GetHeight() * 0.5f - child->GetHeight() * 0.5f;
            }
        }
        else
        {
            // Use parent's option
            if (toParentBottom)
            {
                childPosY = endY - child->GetHeight() - child->GetMarginBottom();
            }
            if (toParentCenterVertical || toParentCenter)
            {
                childPosY = pTarget->GetHeight() * 0.5f - child->GetHeight() * 0.5f;
            }
        }

        // Set Child Position
        child->SetPosition(childPosX + pTarget->GetScrollX(), childPosY + pTarget->GetScrollY());

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition(child);

        childPosX += child->GetWidth() + child->GetMarginRight();
    }
}

void AUILinearLayout::OnUpdateChildPosition_Vertical()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    const auto width = pTarget->GetWidth();
    const auto startX = pTarget->GetPaddingLeft();
    const auto endX = width - pTarget->GetPaddingRight();
    const auto startY = pTarget->GetPaddingTop();

    const auto toParentLeft = pTarget->GetPropGravityLeft();
    const auto toParentTop = pTarget->GetPropGravityTop();
    const auto toParentRight = pTarget->GetPropGravityRight();
    const auto toParentBottom = pTarget->GetPropGravityBottom();
    const auto toParentCenterHorizontal = pTarget->GetPropGravityCenterHorizontal();
    const auto toParentCenterVertical = pTarget->GetPropGravityCenterVertical();
    const auto toParentCenter = pTarget->GetPropGravityCenter();

    auto childPosY = startY;

    const auto arrChildren = pTarget->GetChildren();

    if (toParentBottom)
    {
        SkScalar totalChildrenHeight = 0.0f;
        for (size_t idx = 0; idx < arrChildren.size(); idx++)
        {
            totalChildrenHeight += arrChildren[idx]->GetMarginTop() + arrChildren[idx]->GetHeight() + arrChildren[idx]->GetMarginBottom();
        }
        childPosY = pTarget->GetHeight() - pTarget->GetPaddingTop() - pTarget->GetPaddingBottom() - totalChildrenHeight;
    }


    for (auto& child : arrChildren)
    {
        if (child->IsIgnored())
            continue;

        const auto toLeft = child->GetPropLayoutGravityLeft();
        const auto toTop = child->GetPropLayoutGravityTop();
        const auto toRight = child->GetPropLayoutGravityRight();
        const auto toBottom = child->GetPropLayoutGravityBottom();
        const auto toCenterHorizontal = child->GetPropLayoutGravityCenterHorizontal();
        const auto toCenterVertical = child->GetPropLayoutGravityCenterVertical();
        const auto toCenter = child->GetPropLayoutGravityCenter();


        childPosY += child->GetMarginTop();

        auto childPosX = startX + child->GetMarginLeft();

        if (toLeft || toTop || toRight || toBottom || toCenterHorizontal || toCenterVertical || toCenter)
        {
            // Use child's option
            if (toRight)
            {
                childPosX = endX - child->GetWidth() - child->GetMarginRight();
            }
            if (toCenterHorizontal || toCenter)
            {
                childPosX = pTarget->GetWidth() * 0.5f - child->GetWidth() * 0.5f;
            }
        }
        else
        {
            // Use parent's option
            if (toParentRight)
            {
                childPosX = endX - child->GetWidth() - child->GetMarginRight();
            }
            if (toParentCenterHorizontal || toParentCenter)
            {
                childPosX = pTarget->GetWidth() * 0.5f - child->GetWidth() * 0.5f;
            }
        }

        // Set Child Position
        child->SetPosition(childPosX + pTarget->GetScrollX(), childPosY + pTarget->GetScrollY());

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition(child);

        childPosY += child->GetHeight() + child->GetMarginBottom();
    }
}
