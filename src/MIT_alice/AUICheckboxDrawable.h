#pragma once

#include "AUIDrawable.h"


class ALICEUI_API AUICheckboxDrawable : public AUIDrawable
{
public:
    AUICheckboxDrawable();
    virtual ~AUICheckboxDrawable();

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


    //////////////////////////////////////////////////////////////////////////
    // State & animation
protected:
    bool IsPrevChecked() const { return m_bPrevChecked; }
    void SetPrevChecked(bool state) { m_bPrevChecked = state; }
    bool IsPrevCheckedIndeterminate() const { return m_bPrevCheckedIndeterminate; }
    void SetPrevCheckedIndeterminate(bool state) { m_bPrevCheckedIndeterminate = state; }
private:
    bool m_bPrevChecked;
    bool m_bPrevCheckedIndeterminate;
};
