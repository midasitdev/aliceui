#pragma once

#include "AUIShape.h"

class ALICEUI_API AUITriangleShape : public AUIShape
{
public:
    AUITriangleShape();
    virtual ~AUITriangleShape();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas, const SkPaint& paint) override;


    //////////////////////////////////////////////////////////////////////////
    // Angle
public:
    void SetAngle(float angle) { m_fAngle = angle; }
    float GetAngle() const { return m_fAngle; }
private:
    float m_fAngle;
};
