#pragma once

#include "AUIAbsoluteLayoutWidget.h"

class ALICEUI_API AUIComboItemWidget : public AUIAbsoluteLayoutWidget
{
    typedef AUIAbsoluteLayoutWidget SuperWidget;
public:
    AUIComboItemWidget();
    virtual ~AUIComboItemWidget();

    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;

    //////////////////////////////////////////////////////////////////////////
    // Item click signal
public:
    AUISignal<void(AUIWidget*, size_t)> ClickSignal;


    //////////////////////////////////////////////////////////////////////////
    // Content
public:
    void SetContent(const std::shared_ptr< AUIWidget >& pWidget, size_t pos);
    std::shared_ptr< AUIWidget > GetContentItem() const { return m_pContentItem; }
    size_t GetItemPos() const { return m_ItemPos; }
private:
    std::shared_ptr< AUIAbsoluteLayoutWidget > m_pContent;
    std::shared_ptr< AUIWidget > m_pContentItem;
    size_t m_ItemPos;


    //////////////////////////////////////////////////////////////////////////
    // Marquee
public:
    void SetUseMarquee(bool val) { m_bUseMarquee = val; }
    bool IsUseMarquee() const { return m_bUseMarquee; }
private:
    bool m_bUseMarquee;
};
