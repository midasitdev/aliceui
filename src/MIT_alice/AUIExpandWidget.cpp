#include "pch.h"
#include "AUIExpandWidget.h"
#include "AUIExpandHeaderWidget.h"
#include "AUIColor.h"
#include "AUIColorDrawable.h"
#include "AUISmootherStepInterpolator.h"
#include "AUIDebug.h"

namespace
{
    constexpr std::chrono::milliseconds AnimTickLength(300);
    SkScalar CalcHeightWithMargin(const std::shared_ptr<AUIWidget>& pWidget)
    {
        return (std::max)(0.0f, pWidget->GetHeight() + pWidget->GetMarginTop() + pWidget->GetMarginBottom());
    }
}

AUIExpandWidget::AUIExpandWidget()
    : m_pHeader(std::make_shared<AUIExpandHeaderWidget>())
    , m_bExpanded(false)
    , m_PendingExpand(false)
    , m_PendingCollapse(false)
    , m_PendingSizeUpdate(false)
    , m_AnimStartHeight(0.0f)
    , m_AnimCurHeight(0.0f)
    , m_AnimTargetHeight(0.0f)
{
    SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kContent);

    m_pHeader->SetPropParentTop(true);

    SetContent(nullptr);


    Connect(m_pHeader->ClickSignal, [&](AUIWidget*) {
        ExpandOrCollapse();
    });

    Expand(true);
}

AUIExpandWidget::~AUIExpandWidget()
{

}

void AUIExpandWidget::AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos)
{
    AUIAssert(!"Use SetContent!");
}

void AUIExpandWidget::DelSubWidget(const std::shared_ptr< AUIWidget >& widget)
{
    AUIAssert(!"Use SetContent!");
}

void AUIExpandWidget::PopSubWidget()
{
    AUIAssert(!"Use SetContent!");
}

void AUIExpandWidget::ClearSubWidget()
{
    AUIAssert(!"Use SetContent!");
}

std::shared_ptr< AUIWidget > AUIExpandWidget::FindSubWidget(size_t pos)
{
    AUIAssert(!"Use SetContent!"); return nullptr;
}

size_t AUIExpandWidget::SubWidgetCount() const
{
    AUIAssert(!"Use SetContent!"); return 0;
}

void AUIExpandWidget::SetContent(const std::shared_ptr<AUIWidget>& pWidget)
{
    m_pContent = pWidget;
    ClearChild();
    AddChild(m_pHeader);
    if (m_pContent)
    {
        AUIAssert(m_pContent);
        m_pContent->SetPropBelow(m_pHeader->GetRuntimeID());
        AddChild(m_pContent);
    }
    RecalcExpandOrCollapse();
}

void AUIExpandWidget::ExpandOrCollapse()
{
    if (IsExpanded())
        Collapse(false);
    else
        Expand(false);
}

void AUIExpandWidget::Expand(bool force)
{
    if (m_bExpanded && false == force)
        return;

    m_bExpanded = true;
    m_PendingExpand = true;
    m_PendingCollapse = false;

    // Reset state
    m_PendingSizeUpdate = false;

    if (m_pContent)
        m_pContent->UnFreeze();

    m_pHeader->SetExpandState(true);

    ResetAnimRunning();

    UpdateSize();
    UpdateChildPosition();
    Invalidate();
}

void AUIExpandWidget::Collapse(bool force)
{
    if (false == m_bExpanded && false == force)
        return;

    m_bExpanded = false;
    m_PendingExpand = false;
    m_PendingCollapse = true;

    // Reset state
    m_PendingSizeUpdate = false;

    if (m_pContent)
        m_pContent->Freeze();

    m_pHeader->SetExpandState(false);

    ResetAnimRunning();

    UpdateSize();
    UpdateChildPosition();
    Invalidate();
}

void AUIExpandWidget::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
    SuperWidget::OnTickTime(prevTime, curTime);
    if (m_PendingSizeUpdate)
    {
        //AUIDebugPrint(L"On Pending Size Update\n");
        float animWeight = 1.0f;
        auto animStartTick = GetAnimStartTick();
        if (0 == animStartTick.count())
        {
            // Initial time
            StartAnimRunning();
            animStartTick = GetAnimStartTick();
        }

        AUISmootherStepInterpolator interpolator;
        animWeight = interpolator.GetValueByTime(animStartTick, animStartTick + AnimTickLength, GetTimeTick());
        if (animWeight >= 1.0f)
        {
            animWeight = 1.0f;
            StopAnimRunning();
            m_PendingSizeUpdate = false;
            //AUIDebugPrint(L"Finished Animation - Target size %f, Current size %f\n", m_AnimTargetHeight, m_AnimStartHeight + (m_AnimTargetHeight - m_AnimStartHeight) * animWeight);
        }

        // Calculate current height
        m_AnimCurHeight = m_AnimStartHeight + (m_AnimTargetHeight - m_AnimStartHeight) * animWeight;

        //AUIDebugPrint(L"On Pending Size Update. Weight(%f), CurrentHeight(%f), Start Tick(%u), Current Tick(%u)\n", animWeight, m_AnimCurHeight, animStartTick.count(), GetTimeTick().count());

        UpdateSize();
        UpdateChildPosition();
        Invalidate();
    }
}

void AUIExpandWidget::OnBeforeMeasureSize()
{
    SuperWidget::OnBeforeMeasureSize();
    const SkScalar MaximumExpandHeight = 5000.0f;
    if (m_PendingExpand || m_PendingCollapse)
    {
        if (m_PendingSizeUpdate)
            return;

        const auto spHeight = GetSizePolicyHeight();

        SuperWidget::OnMeasureSize(0, AUIMeasureSpec::kUnspecified, MaximumExpandHeight, AUIMeasureSpec::kAtMost);

        if (m_PendingExpand)
            m_AnimTargetHeight = GetMeasureHeight();
        m_AnimStartHeight = 0.0f;
    }
}

void AUIExpandWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    if (m_PendingSizeUpdate)
    {
        height = (std::min)(m_AnimCurHeight + GetPaddingTop() + GetPaddingBottom(), height);
        heightSpec = AUIMeasureSpec::kAtMost;
    }
    else
    {
        if (false == m_PendingExpand && false == m_PendingCollapse)
        {
            if (false == IsExpanded())
                height = m_AnimTargetHeight + GetPaddingTop() + GetPaddingBottom();// (std::min)(::CalcHeightWithMargin(m_pHeader), height);
        }
        else if (m_PendingExpand)
        {
            if (SkScalarNearlyZero(m_AnimStartHeight))
                m_AnimStartHeight = ::CalcHeightWithMargin(m_pHeader);
            height = (std::min)(m_AnimStartHeight + GetPaddingTop() + GetPaddingBottom(), height);
        }
        else if (m_PendingCollapse)
        {
            if (SkScalarNearlyZero(m_AnimStartHeight))
                m_AnimStartHeight = GetHeight();
            m_AnimTargetHeight = ::CalcHeightWithMargin(m_pHeader);
        }
    }
    //AUIDebugPrint(L"Requesting Height %f\n", height);

    SuperWidget::OnMeasureSize(width, widthSpec, height, heightSpec);

    //AUIDebugPrint(L"Measured Height %f\n", GetMeasureHeight());
}

void AUIExpandWidget::OnAfterMeasureSize(SkScalar width, SkScalar height)
{
    SuperWidget::OnAfterMeasureSize(width, height);

    if (m_PendingExpand || m_PendingCollapse)
    {
        if (m_PendingSizeUpdate)
            return;

        //if (m_PendingCollapse)
        //{
        //    if (SkScalarNearlyZero(m_AnimStartHeight))
        //        m_AnimStartHeight = GetHeight();
        //    m_AnimTargetHeight = ::CalcHeightWithMargin(m_pHeader);
        //}
        if (SkScalarNearlyZero(m_AnimCurHeight))
            m_AnimCurHeight = m_AnimStartHeight;

        m_PendingSizeUpdate = true;

        m_PendingExpand = false;
        m_PendingCollapse = false;

        //StartAnimRunning();
        UpdateSize();
        UpdateChildPosition();
        Invalidate();


        //AUIDebugPrint(L"Target Height : %f\n", m_AnimTargetHeight);
    }
}

void AUIExpandWidget::OnUpdateChildPosition()
{
    // Intent to call MAUILayoutWidget::OnUpdateChildPosition
    // We are skipping RelativeLayoutWidget::OnUpdateChildPosition
    SuperWidget::OnUpdateChildPosition();
    return;

    const auto width = GetWidth();
    const auto height = GetHeight();


    // Header
    auto posHeader = m_pHeader->GetPosition();
    if (m_pHeader->GetPropParentLeft())
    {
        posHeader.fX = GetPaddingLeft() + m_pHeader->GetMarginLeft();
    }
    else if (m_pHeader->GetPropParentRight())
    {
        posHeader.fX = GetWidth() - m_pHeader->GetWidth() - GetPaddingRight() - m_pHeader->GetMarginRight();
    }
    else
    {
        posHeader.fX = (std::min)(posHeader.fX, width - m_pHeader->GetWidth() - GetPaddingRight() - m_pHeader->GetMarginRight());
        posHeader.fX = (std::max)(posHeader.fX, GetPaddingLeft() + m_pHeader->GetMarginLeft());
    }
    // Align Top
    posHeader.fY = GetPaddingTop() + m_pHeader->GetMarginTop();
    if (m_pHeader->GetPropParentCenterHorizontal())
    {
        posHeader.fX = std::floor(width * 0.5f - m_pHeader->GetWidth() * 0.5f);
    }
    if (m_pHeader->GetPropParentCenterVertical())
    {
        posHeader.fY = std::floor(height * 0.5f - m_pHeader->GetHeight() * 0.5f);
    }
    if (m_pHeader->GetPropParentCenter())
    {
        posHeader.fX = std::floor(width * 0.5f - m_pHeader->GetWidth() * 0.5f);
        posHeader.fY = std::floor(height * 0.5f - m_pHeader->GetHeight() * 0.5f);
    }
    m_pHeader->SetPosition(posHeader + GetScrollVal());


    // Content
    if (m_pContent)
    {
        auto posContent = m_pContent->GetPosition();

        if (m_pContent->GetPropParentLeft())
        {
            posContent.fX = GetPaddingLeft() + m_pContent->GetMarginLeft();
        }
        else if (m_pContent->GetPropParentRight())
        {
            posContent.fX = GetWidth() - m_pContent->GetWidth() - GetPaddingRight() - m_pContent->GetMarginRight();
        }
        else
        {
            posContent.fX = (std::min)(posContent.fX, width - m_pContent->GetWidth() - GetPaddingRight() - m_pContent->GetMarginRight());
            posContent.fX = (std::max)(posContent.fX, GetPaddingLeft() + m_pContent->GetMarginLeft());
        }

        if (m_pContent->GetPropParentTop())
        {
            posContent.fY = GetPaddingTop() + m_pContent->GetMarginTop();
        }
        else if (m_pContent->GetPropParentBottom())
        {
            posContent.fY = height - m_pContent->GetHeight() - GetPaddingBottom() - m_pContent->GetMarginBottom();
        }
        else
        {
            posContent.fY = (std::min)(posContent.fY, height - m_pContent->GetHeight() - GetPaddingBottom() - m_pContent->GetMarginBottom());
            posContent.fY = (std::max)(posContent.fY, GetPaddingTop() + m_pContent->GetMarginTop());
        }

        if (m_pContent->GetPropParentCenterHorizontal())
        {
            posContent.fX = std::floor(width * 0.5f - m_pContent->GetWidth() * 0.5f);
        }
        if (m_pContent->GetPropParentCenterVertical())
        {
            posContent.fY = std::floor(height * 0.5f - m_pContent->GetHeight() * 0.5f);
        }
        if (m_pContent->GetPropParentCenter())
        {
            posContent.fX = std::floor(width * 0.5f - m_pContent->GetWidth() * 0.5f);
            posContent.fY = std::floor(height * 0.5f - m_pContent->GetHeight() * 0.5f);
        }

        const auto belowID = m_pContent->GetPropBelow();
        const auto pBelowTarget = AUIWidget::FindByRuntimeID(belowID);
        if (pBelowTarget)   // == m_pHeader
        {
            posContent.fY = pBelowTarget->GetPosition().fY + pBelowTarget->GetHeight() + pBelowTarget->GetMarginBottom() + m_pContent->GetMarginTop();
        }

        m_pContent->SetPosition(posContent + GetScrollVal());
    }
}

void AUIExpandWidget::SetHeaderHeight(SkScalar height)
{
    m_pHeader->SetDefaultHeight(height);
}

void AUIExpandWidget::SetHeaderCaption(const std::wstring& text)
{
    m_pHeader->SetText(text);

}

void AUIExpandWidget::SetHeaderCaptionColor(const SkColor& captionColor)
{
	m_pHeader->SetTextFontColor(captionColor);
}

void AUIExpandWidget::SetHeaderStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
    m_pHeader->SetStyleSheet(style);
}

void AUIExpandWidget::SetHeaderSpinStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
    m_pHeader->SetSpinStyleSheet(style);
}

void AUIExpandWidget::SetHeaderTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
    m_pHeader->SetTextStyleSheet(style);
}

void AUIExpandWidget::RecalcExpandOrCollapse()
{
    if (IsExpanded())
        Expand(true);
    else
        Collapse(true);
}
