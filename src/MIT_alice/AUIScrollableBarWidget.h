#pragma once

#include "AUIDrawableWidget.h"
#include "AUICompass.h"

class ALICEUI_API AUIScrollableBarWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperClass;
public:
    AUIScrollableBarWidget();
    virtual ~AUIScrollableBarWidget();


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnDblClk(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnDblClk(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseWheel(MAUIMouseEvent::EventFlag flag, float delta) override;
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Values
public:
    void SetContentHeight(const SkScalar& val) { m_ContentHeight = val; }
    void SetScrollPos(const SkScalar& val) { m_ScrollPos = val; }
private:
    SkScalar m_ContentHeight;
    SkScalar m_ScrollPos;
    std::shared_ptr< AUIDrawable > m_pThumbDrawable;
    std::shared_ptr<AUIPlaneCompass> m_pPlaneCompass;

    //////////////////////////////////////////////////////////////////////////
    // Thumb
public:
    void SetShowThumbOnHit(bool show) { m_bShowThumbOnHit = show; }
    bool IsShowThumbOnHit() const { return m_bShowThumbOnHit; }
    SkRect GetThumbRect() const;
    AUISignal<void(const SkScalar&)> ThumbScrollSignal;
    bool IsScrollable() const;
private:
    AUIState m_ThumbState;
    glm::vec2 m_PrevLDownPos = { 0, 0 };
    bool m_bShowThumbOnHit;
};
