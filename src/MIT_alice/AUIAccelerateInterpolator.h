#pragma once

#include "AUIInterpolator.h"

class ALICEUI_API AUIAccelerateInterpolator : public AUIInterpolator
{
public:
    AUIAccelerateInterpolator(float factor = 1.0f) noexcept;
    ~AUIAccelerateInterpolator() noexcept override = default;
    float GetValue(float input) const override;
private:
    float m_fFactor;
};
