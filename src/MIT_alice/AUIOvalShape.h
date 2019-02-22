#pragma once

#include "AUIRoundRectShape.h"

class ALICEUI_API AUIOvalShape : public AUIRoundRectShape
{
public:
    AUIOvalShape();
    virtual ~AUIOvalShape();


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnResize(float width, float height) override;
};
