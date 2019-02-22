#pragma once

#include "AUIAbsoluteLayoutWidget.h"


class AUISliderIndicatorWidget;
class ALICEUI_API AUISliderWidget : public AUIAbsoluteLayoutWidget
{
    using SuperWidget = AUIAbsoluteLayoutWidget;
public:
    AUISliderWidget();
    ~AUISliderWidget() override;



    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;

    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(MAUIMouseEvent::EventFlag flag) override;


    //////////////////////////////////////////////////////////////////////////
    // Horizontal
public:
    void SetHorizontal(bool val);
    bool IsHorizontal() const { return m_bHorizontal; }
private:
    bool m_bHorizontal;


    //////////////////////////////////////////////////////////////////////////
    // Range
public:
    void SetSlideRange(SkScalar minVal, SkScalar maxVal) { m_RangeMin = minVal; m_RangeMax = maxVal; }
    SkScalar GetSlideRangeMin() const { return m_RangeMin; }
    SkScalar GetSlideRangeMax() const { return m_RangeMax; }
private:
    SkScalar m_RangeMin;
    SkScalar m_RangeMax;


    //////////////////////////////////////////////////////////////////////////
    // Value
public:
    void SetValue(SkScalar val);
    SkScalar GetValue() const;
private:
    SkScalar m_Value;


    //////////////////////////////////////////////////////////////////////////
    // Indicator
public:
private:
    std::shared_ptr< AUISliderIndicatorWidget > m_pIndicator;
};
