#include "pch.h"
#include "AUIRasterTooltipWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"

AUIRasterTooltipWidget::AUIRasterTooltipWidget()
{
    // Tooltip Base Color
    auto pDefaultBG = std::make_shared<AUIShapeDrawable>(std::make_shared<AUIRectShape>());
    pDefaultBG->SetColor(SkColorSetRGB(255, 255, 178));
    auto pOutline = std::make_shared<AUIShapeDrawable>(std::make_shared<AUIRectShape>());
    pOutline->SetColor(SkColorSetRGB(0, 0, 0));
    pOutline->SetStrokeStyle(SkPaint::kStroke_Style);
    auto pBackground = std::make_shared<AUILayerDrawable>();
    pBackground->InsertLayer(pDefaultBG);
    pBackground->InsertLayer(pOutline);

    SetBackgroundDrawable(pBackground);
}
