#pragma once

#include "AUIInterpolator.h"

class ALICEUI_API AUIAccelDecelInterpolator : public AUIInterpolator
{
public:
    AUIAccelDecelInterpolator(float factor = 1.0f) noexcept;
    ~AUIAccelDecelInterpolator() noexcept override = default;
    float GetValue(float input) const override;
private:
    float m_fFactor;
};
