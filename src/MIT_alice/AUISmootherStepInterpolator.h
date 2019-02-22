#pragma once

#include "AUIInterpolator.h"

class ALICEUI_API AUISmootherStepInterpolator : public AUIInterpolator
{
public:
    AUISmootherStepInterpolator() noexcept = default;
    ~AUISmootherStepInterpolator() noexcept override = default;
    float GetValue(float input) const override;
};
