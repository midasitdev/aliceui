#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUIRadioboxDrawable : public AUIDrawable
{
public:
    AUIRadioboxDrawable();
    virtual ~AUIRadioboxDrawable();

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;



    //////////////////////////////////////////////////////////////////////////
    // Toggle color
private:
    SkColor m_DisabledBGColor;
    SkColor m_DisabledBorderColor;
    SkColor m_OffDefaultBGColor;
    SkColor m_OffDefaultBorderColor;
    SkColor m_OffHoverBorderColor;
    SkColor m_OffPressBorderColor;
    SkColor m_OnDefaultBGColor;
    SkColor m_OnHoverBGColor;
    SkColor m_OnPressBGColor;
    SkColor m_OnBorderColor;
    SkColor m_OnHoverBorderColor;
    SkColor m_OnPressBorderColor;
};
