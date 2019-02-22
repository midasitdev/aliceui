#pragma once

#include "AUIDrawableWidget.h"

class AUIShapeDrawable;
class ALICEUI_API AUIShapedWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperWidget;
public:
    AUIShapedWidget();
    virtual ~AUIShapedWidget();

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Shape
public:
    void SetColor(const SkColor color);
    AUIShapeDrawable* const GetShapeDrawable() const { return m_pShapeDrawable.get(); }
private:
    std::shared_ptr< AUIShapeDrawable > m_pShapeDrawable;

};
