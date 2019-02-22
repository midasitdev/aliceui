#pragma once


#include "AUIDrawable.h"

class ALICEUI_API AUIExpandToggleDrawable : public AUIDrawable
{
public:
    AUIExpandToggleDrawable();
    virtual ~AUIExpandToggleDrawable();



    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Toggle color
private:
    SkColor m_DefaultColor;
    SkColor m_HoverColor;
    SkColor m_PressColor;
};
