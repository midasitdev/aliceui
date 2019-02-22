#pragma once

#include "AUICommonDef.h"

class AUIWidget;
class ALICEUI_API AUISkiaRenderer
{
public:
    static void RenderWidget(SkCanvas* const canvas, AUIWidget* const pWidget, float opacity = 1.0f);
    static void RenderWidget(SkCanvas* const canvas, AUIWidget* const pWidget, float x, float y, float opacity = 1.0f);
};
