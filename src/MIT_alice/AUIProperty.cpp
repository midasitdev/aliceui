#include "pch.h"
#include "AUIProperty.h"

AUIProperty::AUIProperty() noexcept
{
    m_WidthPolicy = AUISizePolicy::kFixed;
    m_HeightPolicy = AUISizePolicy::kFixed;

    ResetRange();
    ResetMinimumSize();
    ResetMaximumSize();
    ResetDefaultSize();
    ResetMeasureSize();
    ResetWeight();
    ResetPadding();
    ResetMargin();
    ResetParentOption();
    ResetTargetOption();
    ResetLayoutGravityOption();
    ResetGravityOption();
}
