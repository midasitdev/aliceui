#pragma once

#include "AUILayoutBase.h"

class ALICEUI_API AUIFrameLayout : public AUILayoutBase
{
public:
    AUIFrameLayout() noexcept = default;
    ~AUIFrameLayout() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;
};
