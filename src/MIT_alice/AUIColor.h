#pragma once

#include "AUIAPIDef.h"
#include "AUIColorDef.h"


class ALICEUI_API AUIColor
{
    //////////////////////////////////////////////////////////////////////////
    // Named color
public:
    static bool FindNamed(const std::string& name, SkColor& color);
    static bool FindNamed(const std::wstring& name, SkColor& color);
    static SkColor GetRandomColor();
    static SkColor GetRandomColor(SkScalar alpha);    // 0.0 ~ 1.0
    static SkColor GetRandomColorSeed(int seed);
private:
    static SkColor ConvertHSVtoRGB(float h, float s, float v);
};
