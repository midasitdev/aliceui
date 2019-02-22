#include "pch.h"
#include "AUIGridLayout.h"
#include "AUIWidget.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIApplication.h"


void AUIGridLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    SkScalar basePosX = pTarget->GetMarginLeft();
    SkScalar basePosY = pTarget->GetMarginTop();

    SkScalar totalWidth = pTarget->GetMarginLeft() + pTarget->GetMarginRight();
    SkScalar totalHeight = pTarget->GetMarginTop() + pTarget->GetMarginBottom();

    for (const auto& divInfo : m_DivisionInfos)
    {
        SkScalar divisionMaxWidth = 0.0f;
        SkScalar divisionMaxHeight = 0.0f;
        SkScalar divisionTotalWeight = 0.0f;
        for (size_t idx = 0; idx < divInfo.fSubDivisionCount; ++idx)
        {
            if (idx >= divInfo.fWidgets.size())
            {
                divisionTotalWeight += 1.0f;
                continue;
            }
            const auto& pWidget = divInfo.fWidgets[idx];
            divisionTotalWeight += pWidget->GetWeight();
        }
        if (divisionTotalWeight <= 0.0f)
            divisionTotalWeight = 1.0f;

        for (size_t idx = 0; idx < divInfo.fSubDivisionCount; ++idx)
        {
            if (idx >= divInfo.fWidgets.size())
                continue;
            const auto& pWidget = divInfo.fWidgets[idx];
            if (nullptr == pWidget)
            {
                AUIAssert(pWidget);
                continue;
            }

            AUIAssert(AUIApplication::Instance().GetWidgetTree().IsChild(pTarget, pWidget.get()));

            // TODO : weighted
            SkScalar targetWidth = IsHorizontal() ? divInfo.fDefaultSize : pWidget->GetWeight() * width / divisionTotalWeight;
            SkScalar targetHeight = IsHorizontal() ? pWidget->GetWeight() * height / divisionTotalWeight : divInfo.fDefaultSize;
            SkScalar targetDepth = 0.0f;

            AUIWidget::OnCallMeasureAndUpdateSize(pWidget.get(), targetWidth, AUIMeasureSpec::kAtMost, targetHeight, AUIMeasureSpec::kAtMost);

            const auto divisionChildPos = pWidget->GetPosition();
            const auto divisionChildSize = pWidget->GetMeasureSize();
            const auto divisionChildWidth = pWidget->GetMarginLeft() + pWidget->GetMarginRight() + divisionChildSize.fX;
            const auto divisionChildHeight = pWidget->GetMarginTop() + pWidget->GetMarginBottom() + divisionChildSize.fY;

            divisionMaxWidth = (std::max)(divisionMaxWidth, divisionChildWidth);
            divisionMaxHeight = (std::max)(divisionMaxHeight, divisionChildHeight);
        }

        if (IsHorizontal())
        {
            totalWidth += divInfo.fDefaultSize;
            totalHeight = (std::max)(totalHeight, divisionMaxWidth);
        }
        else
        {
            totalWidth = (std::max)(totalWidth, divisionMaxHeight);
            totalHeight += divInfo.fDefaultSize;
        }
    }

    SkScalar resultWidth = 0.0f;
    SkScalar resultHeight = 0.0f;
    SkScalar resultDepth = 0.0f;
    if (AUIMeasureSpec::kExactly == widthSpec)
    {
        resultWidth = width;
    }
    else if (AUIMeasureSpec::kAtMost == widthSpec)
    {
        resultWidth = totalWidth;
    }
    else
    {

    }
    if (AUIMeasureSpec::kExactly == heightSpec)
    {
        resultHeight = height;
    }
    else if (AUIMeasureSpec::kAtMost == heightSpec)
    {
        resultHeight = totalHeight;
    }
    else
    {

    }
    // TODO : Size policy
    pTarget->SetMeasureSize(resultWidth, resultHeight);
}

void AUIGridLayout::OnUpdateChildPosition()
{
    auto pTarget = GetTargetWidget();
    if (nullptr == pTarget)
    {
        AUIAssert(pTarget);
        return;
    }

    SkScalar basePosX = pTarget->GetMarginLeft();
    SkScalar basePosY = pTarget->GetMarginTop();


    SkScalar divisionOffsetX = 0.0f;
    SkScalar divisionOffsetY = 0.0f;

    for (const auto& divInfo : m_DivisionInfos)
    {
        for (size_t idx = 0; idx < divInfo.fSubDivisionCount; ++idx)
        {
            if (idx >= divInfo.fWidgets.size())
                continue;
            const auto& pWidget = divInfo.fWidgets[idx];
            if (nullptr == pWidget)
            {
                AUIAssert(pWidget);
                continue;
            }
            AUIAssert(AUIApplication::Instance().GetWidgetTree().IsChild(pTarget, pWidget.get()));

            pWidget->SetPosition(
                basePosX + divisionOffsetX,
                basePosY + divisionOffsetY
            );
            if (IsHorizontal())
            {
                divisionOffsetY += pWidget->GetMeasureHeight() + pWidget->GetMarginTop() + pWidget->GetMarginBottom();
            }
            else
            {
                divisionOffsetX += pWidget->GetMeasureWidth() + pWidget->GetMarginLeft() + pWidget->GetMarginRight();
            }
        }

        if (IsHorizontal())
        {
            divisionOffsetX += divInfo.fDefaultSize;
            divisionOffsetY = 0.0f;
        }
        else
        {
            divisionOffsetX = 0.0f;
            divisionOffsetY += divInfo.fDefaultSize;
        }
    }
}
