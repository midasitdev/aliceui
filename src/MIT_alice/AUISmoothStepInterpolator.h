#pragma once

#include "AUIInterpolator.h"


class ALICEUI_API AUISmoothStepInterpolator : public AUIInterpolator
{
public:
    AUISmoothStepInterpolator() noexcept = default;
    ~AUISmoothStepInterpolator() noexcept override = default;
    virtual float GetValue(float input) const override;
};
