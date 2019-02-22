#pragma once
#include "AUIDrawable.h"

class AUIShape;

class ALICEUI_API AUIShapeDrawable : public AUIDrawable
{
public:
    AUIShapeDrawable();
    AUIShapeDrawable(const std::shared_ptr< AUIShape >& shape);
    ~AUIShapeDrawable() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Shape
public:
    std::shared_ptr< AUIShape > GetShape() const { return m_pShape; }
    void SetShape(const std::shared_ptr< AUIShape >& shape) { m_pShape = shape; }
private:
    std::shared_ptr< AUIShape > m_pShape;


    //////////////////////////////////////////////////////////////////////////
    // Color
public:
    SkColor GetColor() const { return m_Color; }
    void SetColor(const SkColor color) { m_Color = color; }
private:
    SkColor m_Color;


    //////////////////////////////////////////////////////////////////////////
    // Stroke Style
public:
    SkPaint::Style GetStrokeStyle() const { return m_StrokeStyle; }
    float GetStrokeWidth() const { return m_fStrokeWidth; }
    void SetStrokeStyle(const SkPaint::Style style) { m_StrokeStyle = style; }
    void SetStrokeWidth(const float val) { m_fStrokeWidth = val; }
private:
    SkPaint::Style m_StrokeStyle;
    float m_fStrokeWidth;

};
