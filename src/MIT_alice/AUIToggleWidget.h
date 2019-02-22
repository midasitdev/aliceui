#pragma once


#include "AUICheckboxWidget.h"

class ALICEUI_API AUIToggleWidget : public AUICheckboxWidget
{
public:
    AUIToggleWidget();
    explicit AUIToggleWidget(bool state);
    virtual ~AUIToggleWidget();
};
