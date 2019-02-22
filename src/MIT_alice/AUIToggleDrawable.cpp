#include "pch.h"
#include "AUIToggleDrawable.h"


AUIToggleDrawable::AUIToggleDrawable()
    : m_ColorBGOn( SkColorSetRGB( 130, 186, 255 ) )
    , m_ColorBGOff( SkColorSetRGB( 208, 213, 221 ) )
    , m_ColorToggleOn( SkColorSetRGB( 240, 240, 240 ) )
    , m_ColorToggleOff( SkColorSetRGB( 240, 240, 240 ) )
{

}

AUIToggleDrawable::~AUIToggleDrawable()
{

}

void AUIToggleDrawable::OnDraw( SkCanvas* const canvas )
{
    const auto bound = GetDrawBound();

    auto centerY = bound.height() * 0.5f;
    auto toggleOffset = bound.height() * 0.1f;
    auto toggleRadius = bound.height() * 0.45f;
    auto stripRadius = bound.height() * 0.5f;
    auto stripWidth = bound.height();

    SkPaint stripPaint;
    stripPaint.setAntiAlias( true );
    stripPaint.setStyle( SkPaint::kStroke_Style );
    stripPaint.setStrokeWidth( stripWidth );
    stripPaint.setStrokeCap( SkPaint::kRound_Cap );
    stripPaint.setStrokeMiter( stripRadius );

    stripPaint.setColor(AUISkiaUtil::MixColor( GetColorBGOn(), GetColorBGOff(), GetBlendFactor() ) );

    canvas->drawLine( stripWidth * 0.5f, centerY, bound.width() - stripWidth * 0.5f, centerY, stripPaint );

    float toggleCenterX = 0.0f;


    toggleCenterX = toggleOffset + toggleRadius + ( bound.width() - 2.0f * toggleRadius - 2.0f * toggleOffset ) * GetBlendFactor();

    SkPaint toggleOuter;
    toggleOuter.setAntiAlias( true );
    toggleOuter.setStrokeWidth( 1.0f );
    toggleOuter.setColor( 0xFF708090 );
    SkPaint togglePaint;
    togglePaint.setAntiAlias( true );
    togglePaint.setColor(AUISkiaUtil::MixColor( GetColorToggleOn(), GetColorToggleOff(), GetBlendFactor() ) );

    canvas->drawCircle( toggleCenterX, centerY, toggleRadius + 0.3f, toggleOuter );
    canvas->drawCircle( toggleCenterX, centerY, toggleRadius, togglePaint );
}
