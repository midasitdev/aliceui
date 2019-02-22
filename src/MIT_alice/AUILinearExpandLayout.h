#pragma once

#include "AUILinearLayout.h"
#include "AUIAutomata.h"

class ALICEUI_API AUILinearExpandLayout : public AUILinearLayout
{
    using __SuperLayout = AUILinearLayout;
public:
    AUILinearExpandLayout() = default;
    ~AUILinearExpandLayout() noexcept override = default;

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;
    void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;
private:
    void OnMeasureSize_Horizontal(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);
    void OnMeasureSize_Vertical(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);

public:
    void ToggleExpandOrCollapse();
    void Expand();
    void Collapse();
    bool IsCollapsedOrCollpasing() const {
        return this->IsCollpased() || this->IsCollpasing();
    }
    bool IsCollpased() const {
        return kCollpased_ExpandState == m_CurrentState.GetState();
    }
    bool IsCollpasing() const {
        return kCollapsing_ExpandState == m_CurrentState.GetState();
    }
    bool IsExpandedOrExpanding() const {
        return this->IsExpanded() || this->IsExpanding();
    }
    bool IsExpanded() const {
        return kExpanded_ExpandState == m_CurrentState.GetState();
    }
    bool IsExpanding() const {
        return kExpanding_ExpandState == m_CurrentState.GetState();
    }
    bool IsAnimating() const {
        return this->IsExpanding() || this->IsCollpasing();
    }
    void SetAnimDuration(const std::chrono::milliseconds& ms) {
        m_AnimDuration = ms;
        AUIAssert(0 != m_AnimDuration.count());
    }
    void SetInterpolationFunction(const std::function<float(float)>& func) {
        m_FuncInterpolator = func;
        AUIAssert(m_FuncInterpolator);
    }
private:
    enum ExpandState
    {
        // Finished state
        kCollpased_ExpandState = 0,
        kExpanded_ExpandState,
        // Animating state
        kExpanding_ExpandState,
        kCollapsing_ExpandState,
    };
    enum Trigger
    {
        kExpand_Trigger = 0,
        kCollpase_Trigger,
        kDone_Trigger,
    };
    AUIAutomata<ExpandState, Trigger> m_CurrentState{ kCollpased_ExpandState, {
        // Expanding
        { kExpanding_ExpandState,       kDone_Trigger,          kExpanded_ExpandState       },
        { kExpanding_ExpandState,       kExpand_Trigger,        kExpanding_ExpandState      },
        { kExpanding_ExpandState,       kCollpase_Trigger,      kCollapsing_ExpandState     },
        // Collapsing
        { kCollapsing_ExpandState,      kDone_Trigger,          kCollpased_ExpandState      },
        { kCollapsing_ExpandState,      kExpand_Trigger,        kExpanding_ExpandState      },
        { kCollapsing_ExpandState,      kCollpase_Trigger,      kCollapsing_ExpandState     },
        // Expanded
        { kExpanded_ExpandState,        kDone_Trigger,          kExpanded_ExpandState       },
        { kExpanded_ExpandState,        kExpand_Trigger,        kExpanding_ExpandState      },
        { kExpanded_ExpandState,        kCollpase_Trigger,      kCollapsing_ExpandState     },
        // Collapsed
        { kCollpased_ExpandState,       kDone_Trigger,          kCollpased_ExpandState      },
        { kCollpased_ExpandState,       kExpand_Trigger,        kExpanding_ExpandState      },
        { kCollpased_ExpandState,       kCollpase_Trigger,      kCollapsing_ExpandState     },
    } };
    bool m_bFirstTransitionMark = false;
    SkScalar m_AnimStartSize = -1.0f;
    SkScalar m_AnimTargetSize = -1.0f;
    std::chrono::milliseconds m_AnimDuration{ 300 };
    std::chrono::milliseconds m_AnimStartTime{ 0 };
    std::function<float(float)> m_FuncInterpolator{ [](float _v) -> float {
        _v = std::clamp(_v, 0.0f, 1.0f);
        return _v * _v * _v * (_v *(_v * 6.0f - 15.0f) + 10.0f); }
    };
};
