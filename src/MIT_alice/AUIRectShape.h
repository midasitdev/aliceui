#pragma once

#include "AUIShape.h"

class ALICEUI_API AUIRectShape : public AUIShape
{
public:
    AUIRectShape();
    virtual ~AUIRectShape();


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
    SkRect& RefRect() { return m_Rect; }
    const SkRect& RefRect() const { return m_Rect; }
private:
    SkRect m_Rect;
};
