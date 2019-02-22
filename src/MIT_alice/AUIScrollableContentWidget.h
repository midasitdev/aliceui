#pragma once

#include "AUILinearLayoutWidget.h"

class ALICEUI_API AUIScrollableContentWidget : public AUILinearLayoutWidget
{
    typedef AUILinearLayoutWidget SuperWidget;
public:
    AUIScrollableContentWidget();
    virtual ~AUIScrollableContentWidget();


    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    bool OnMouseWheel(MAUIMouseEvent::EventFlag flag, float delta) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;

    //////////////////////////////////////////////////////////////////////////
    // Scrolling
public:
    void OnScrolling(float delta);
    AUISignal<void(AUIScrollableContentWidget*, float) > ScrollSignal;
};
