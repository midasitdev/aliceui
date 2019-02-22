#pragma once

#include "AUIRectShape.h"

class ALICEUI_API AUIRoundRectShape : public AUIShape
{
    // TODO : Inner / Outer / Inset
public:
    AUIRoundRectShape();
    AUIRoundRectShape(const float radii[8]);
    AUIRoundRectShape(const SkVector radii[4]);
    virtual ~AUIRoundRectShape();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas, const SkPaint& paint) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnResize(float width, float height) override;


    //////////////////////////////////////////////////////////////////////////
    // Rect
protected:
    SkRRect& RefRRect() { return m_RRect; }
    const SkRRect& RefRRect() const { return m_RRect; }
private:
    SkRRect m_RRect;
};
