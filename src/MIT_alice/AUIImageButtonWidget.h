#pragma once

#include "AUIImageWidget.h"

class ALICEUI_API AUIImageButtonWidget : public AUIImageWidget
{
    using SuperWidget = AUIImageWidget;
public:
    AUIImageButtonWidget();
    virtual ~AUIImageButtonWidget();



    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(MAUIMouseEvent::EventFlag flag) override;
};
