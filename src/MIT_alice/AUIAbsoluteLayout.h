#pragma once

#include "AUILayoutBase.h"


class ALICEUI_API AUIAbsoluteLayout : public AUILayoutBase
{
public:
    AUIAbsoluteLayout() noexcept = default;
    ~AUIAbsoluteLayout() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;
};
