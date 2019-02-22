#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUIToggleDrawable : public AUIDrawable
{
public:
    AUIToggleDrawable();
    virtual ~AUIToggleDrawable();

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;



    //////////////////////////////////////////////////////////////////////////
    // Toggle color
public:
    SkColor GetColorBGOn() const { return m_ColorBGOn; }
    SkColor GetColorBGOff() const { return m_ColorBGOff; }
    SkColor GetColorToggleOn() const { return m_ColorToggleOn; }
    SkColor GetColorToggleOff() const { return m_ColorToggleOff; }
private:
    SkColor m_ColorBGOn;
    SkColor m_ColorBGOff;
    SkColor m_ColorToggleOn;
    SkColor m_ColorToggleOff;
};
