#pragma once

#include "AUILayoutBase.h"


class ALICEUI_API AUIRelativeLayout : public AUILayoutBase
{
public:
    AUIRelativeLayout() = default;
    ~AUIRelativeLayout() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;
};

