#pragma once

#include "AUIInterpolator.h"

class ALICEUI_API AUIDecelerateInterpolator : public AUIInterpolator
{
public:
    AUIDecelerateInterpolator(float factor = 1.0f) noexcept;
    ~AUIDecelerateInterpolator() noexcept override = default;
    float GetValue(float input) const override;
private:
    float m_fFactor;
};
