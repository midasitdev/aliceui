#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUISeparatorWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperWidget;
public:
    AUISeparatorWidget();
    explicit AUISeparatorWidget(bool horizontal);
    virtual ~AUISeparatorWidget();



    //////////////////////////////////////////////////////////////////////////
    // Mode
public:
    bool IsHorizontal() const;
private:
    bool m_bHorizontal;


    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
public:
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon);


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;


    //////////////////////////////////////////////////////////////////////////
    // Move state
protected:
    virtual bool OnDragging() override;
private:
    float m_fAbsPrevX;
    float m_fAbsPrevY;


    //////////////////////////////////////////////////////////////////////////
    // Mode
public:
    void SetHorizontal(bool state);
    void SetColor(const SkColor color);

    //////////////////////////////////////////////////////////////////////////
    // Dragging signal
public:
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*)> DragMoveSignal;
};
