#pragma once

#include "AUIDrawableWidget.h"


class ALICEUI_API AUISliderIndicatorWidget : public AUIDrawableWidget
{
    using SuperWidget = AUIDrawableWidget;
public:
    AUISliderIndicatorWidget();
    ~AUISliderIndicatorWidget() override;



    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
};
