#include "pch.h"
#include "AUILinearExpandLayout.h"
#include "AUILinearLayout.h"
#include "AUIWidget.h"
#include "AUIDebug.h"

void AUILinearExpandLayout::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    if (IsHorizontal())
        OnMeasureSize_Horizontal(width, widthSpec, height, heightSpec);
    else
        OnMeasureSize_Vertical(width, widthSpec, height, heightSpec);
}

void AUILinearExpandLayout::OnMeasureSize_Horizontal(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto pTargetWidget = GetTargetWidget();
    if (nullptr == pTargetWidget)
    {
        AUIAssert(pTargetWidget);
        return;
    }
    __SuperLayout::OnMeasureSize(width, widthSpec, height, heightSpec);

    // Setup values
    if (m_bFirstTransitionMark)
    {
        if (IsExpanding())
        {
            m_AnimStartSize = 0.0f;
            m_AnimTargetSize = pTargetWidget->GetMeasureWidth();
        }
        else if (IsCollpasing())
        {
            m_AnimStartSize = pTargetWidget->GetMeasureWidth();
            m_AnimTargetSize = 0.0f;
        }
        else
        {
            AUIAssertFail();
        }
        m_bFirstTransitionMark = false;
    }

    if (IsExpanded())
    {
        return;
    }
    if (IsCollpased())
    {
        pTargetWidget->SetMeasureSize(0.0f, pTargetWidget->GetMeasureHeight());
        return;
    }

    auto funcMix = [](SkScalar _x, SkScalar _y, SkScalar _a) -> SkScalar {
        return _x * (1.0f - _a) + _y * _a;
    };
    auto funcIsSame = [](float _a, float _b, float _tolerance = 0.001f) -> bool {
        return std::abs(_a - _b) <= _tolerance;
    };

    AUIAssert(0 != m_AnimDuration.count());
    AUIAssert(m_FuncInterpolator);
    const auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch());
    const auto timeOffset = static_cast<float>(((m_AnimStartTime + m_AnimDuration) - currentTime).count()) / static_cast<float>(m_AnimDuration.count());
    const auto weight = m_FuncInterpolator(1.0f - timeOffset);
    AUIDebugPrint(L"Expand anim time offset : %f\n", weight);

    const auto currentSize = funcMix(m_AnimStartSize, m_AnimTargetSize, weight);
    pTargetWidget->SetMeasureSize(currentSize, pTargetWidget->GetMeasureHeight());

    if (funcIsSame(weight, 1.0f))
    {
        AUIDebugPrint(L"Expand animation done!\n");
        m_CurrentState.Transition(kDone_Trigger);
    }
}

void AUILinearExpandLayout::OnMeasureSize_Vertical(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto pTargetWidget = GetTargetWidget();
    if (nullptr == pTargetWidget)
    {
        AUIAssert(pTargetWidget);
        return;
    }
    __SuperLayout::OnMeasureSize(width, widthSpec, height, heightSpec);

    // Setup values
    if (m_bFirstTransitionMark)
    {
        if (IsExpanding())
        {
            m_AnimStartSize = 0.0f;
            m_AnimTargetSize = pTargetWidget->GetMeasureHeight();
        }
        else if (IsCollpasing())
        {
            m_AnimStartSize = pTargetWidget->GetMeasureHeight();
            m_AnimTargetSize = 0.0f;
        }
        else
        {
            AUIAssertFail();
        }
        m_bFirstTransitionMark = false;
    }

    if (IsExpanded())
    {
        return;
    }
    if (IsCollpased())
    {
        pTargetWidget->SetMeasureSize(pTargetWidget->GetMeasureWidth(), 0.0f);
        return;
    }

    auto funcMix = [](SkScalar _x, SkScalar _y, SkScalar _a) -> SkScalar {
        return _x * (1.0f - _a) + _y * _a;
    };
    auto funcIsSame = [](float _a, float _b, float _tolerance = 0.001f) -> bool {
        return std::abs(_a - _b) <= _tolerance;
    };

    AUIAssert(0 != m_AnimDuration.count());
    AUIAssert(m_FuncInterpolator);
    const auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch());
    const auto timeOffset = static_cast<float>(((m_AnimStartTime + m_AnimDuration) - currentTime).count()) / static_cast<float>(m_AnimDuration.count());
    const auto weight = m_FuncInterpolator(1.0f - timeOffset);
    AUIDebugPrint(L"Expand anim time offset : %f\n", weight);

    const auto currentSize = funcMix(m_AnimStartSize, m_AnimTargetSize, weight);
    pTargetWidget->SetMeasureSize(pTargetWidget->GetMeasureWidth(), currentSize);

    if (funcIsSame(weight, 1.0f))
    {
        AUIDebugPrint(L"Expand animation done!\n");
        m_CurrentState.Transition(kDone_Trigger);
    }
}

void AUILinearExpandLayout::OnUpdateChildPosition()
{
    __SuperLayout::OnUpdateChildPosition();
}

void AUILinearExpandLayout::ToggleExpandOrCollapse()
{
    if (IsCollapsedOrCollpasing())
        this->Expand();
    else
        this->Collapse();
}

void AUILinearExpandLayout::Expand()
{
    m_CurrentState.Transition(kExpand_Trigger);
    m_bFirstTransitionMark = true;
    m_AnimStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch());

    if (auto pTargetWidget = GetTargetWidget())
    {
        pTargetWidget->UpdateSize();
        pTargetWidget->UpdateChildPosition();
        pTargetWidget->Invalidate();
    }
}

void AUILinearExpandLayout::Collapse()
{
    m_CurrentState.Transition(kCollpase_Trigger);
    m_bFirstTransitionMark = true;
    m_AnimStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch());

    if (auto pTargetWidget = GetTargetWidget())
    {
        pTargetWidget->UpdateSize();
        pTargetWidget->UpdateChildPosition();
        pTargetWidget->Invalidate();
    }
}

void AUILinearExpandLayout::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
    if (this->IsAnimating())
    {
        if (auto pTargetWidget = GetTargetWidget())
        {
            pTargetWidget->UpdateSize();
            pTargetWidget->UpdateChildPosition();
            pTargetWidget->Invalidate();
        }
    }
}
