#pragma once

#include "AUILayoutWidget.h"

class ALICEUI_API AUIFrameLayoutWidget : public AUILayoutWidget
{
    using SuperWidget = AUILayoutWidget;
public:
    AUIFrameLayoutWidget();
    ~AUIFrameLayoutWidget() override = default;
};
