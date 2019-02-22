#pragma once

#include "AUITextWidget.h"

class ALICEUI_API AUIButtonWidget : public AUITextWidget
{
    typedef AUITextWidget SuperWidget;
public:
    AUIButtonWidget();
    explicit AUIButtonWidget(const std::wstring& caption);
    virtual ~AUIButtonWidget();

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
