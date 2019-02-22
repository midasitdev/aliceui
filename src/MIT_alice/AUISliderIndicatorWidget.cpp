#include "pch.h"
#include "AUISliderIndicatorWidget.h"

AUISliderIndicatorWidget::AUISliderIndicatorWidget()
{

    SetFreeze( true );
    SetDraggable( true );
    SetDefaultSize( 17.0f, 17.0f );
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
}

AUISliderIndicatorWidget::~AUISliderIndicatorWidget()
{

}

void AUISliderIndicatorWidget::OnDraw( SkCanvas* const canvas )
{

    SuperWidget::OnDraw( canvas );

    auto rect = GetRect();
    rect.inset(1.0f, 1.0f);

    SkPaint paint;
    paint.setAntiAlias( true );
    paint.setColor(kAUIColorWhite );

    canvas->drawCircle( rect.centerX(), rect.centerY(), ( std::min )( rect.width() * 0.5f, rect.height() * 0.5f ), paint );

    paint.setStyle( SkPaint::kStroke_Style );
    paint.setColor(kAUIColorGray );
    paint.setStrokeWidth(0.0f);
    canvas->drawCircle( rect.centerX(), rect.centerY(), ( std::min )( rect.width() * 0.5f, rect.height() * 0.5f ), paint );
}
