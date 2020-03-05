#pragma once

#include "AUIRelativeLayoutWidget.h"


class AUIImageWidget;
class AUITextWidget;
class AUIImageButtonWidget;
class ALICEUI_API AUIWindowTitleBarWidget : public AUIRelativeLayoutWidget
{
    using SuperWidget = AUIRelativeLayoutWidget;
public:
    AUIWindowTitleBarWidget();
    virtual ~AUIWindowTitleBarWidget();



    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    //virtual bool OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag) override;

    //////////////////////////////////////////////////////////////////////////
    // Move state
protected:
    virtual bool OnDragging() override;
private:
    float m_fAbsPrevX;
    float m_fAbsPrevY;

    //////////////////////////////////////////////////////////////////////////
    // Dragging signal
public:
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*)> DragMoveSignal;

    //////////////////////////////////////////////////////////////////////////
    // Widgets
public:
    std::shared_ptr<AUIImageWidget> GetIconWidget() const {
        return m_pIcon;
    }
    std::shared_ptr<AUITextWidget> GetTitleTextWidget() const {
        return m_pTitleText;
    }
    std::shared_ptr<AUIImageButtonWidget> GetMinimizeButtonWidget() const {
        return m_pMinimizeButton;
    }
    std::shared_ptr<AUIImageButtonWidget> GetMaximizeButtonWidget() const {
        return m_pMaximizeButton;
    }
    std::shared_ptr<AUIImageButtonWidget> GetCloseButtonWidget() const {
        return m_pCloseButton;
    }
private:
    std::shared_ptr<AUIImageWidget> m_pIcon;
    std::shared_ptr<AUITextWidget> m_pTitleText;
    std::shared_ptr<AUIImageButtonWidget> m_pMinimizeButton;
    std::shared_ptr<AUIImageButtonWidget> m_pMaximizeButton;
    std::shared_ptr<AUIImageButtonWidget> m_pCloseButton;
};
