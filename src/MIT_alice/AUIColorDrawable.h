#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUIColorDrawable : public AUIDrawable
{
public:
    AUIColorDrawable();
    explicit AUIColorDrawable(const SkColor color);
    virtual ~AUIColorDrawable();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Color
public:
    void SetColor(SkColor color) { m_Color = color; }
    SkColor GetColor() const { return m_Color; }
private:
    SkColor m_Color = SK_ColorTRANSPARENT;
};


