#include "pch.h"
#include "AUIRadioboxDrawable.h"

AUIRadioboxDrawable::AUIRadioboxDrawable()
    : m_DisabledBGColor( SkColorSetRGB( 215, 215, 215 ) )
    , m_DisabledBorderColor( SkColorSetRGB( 181, 181, 181 ) )
    , m_OffDefaultBGColor( SkColorSetRGB( 255, 255, 255 ) )
    , m_OffDefaultBorderColor( SkColorSetRGB( 173, 173, 173 ) )
    , m_OffHoverBorderColor( SkColorSetRGB( 146, 146, 146 ) )
    , m_OffPressBorderColor( SkColorSetRGB( 146, 146, 146 ) )
    , m_OnBorderColor( SkColorSetRGB( 130, 186, 255 ) )
    , m_OnDefaultBGColor( SkColorSetRGB( 255, 255, 255 ) )
    , m_OnHoverBGColor( SkColorSetRGB( 255, 255, 255 ) )
    , m_OnHoverBorderColor( SkColorSetRGB( 144, 194, 255 ) )
    , m_OnPressBGColor( SkColorSetRGB( 255, 255, 255 ) )
    , m_OnPressBorderColor( SkColorSetRGB( 118, 179, 255 ) )
{

}

AUIRadioboxDrawable::~AUIRadioboxDrawable()
{

}

void AUIRadioboxDrawable::OnDraw( SkCanvas* const canvas )
{
    const auto bound = GetDrawBound();
    const auto uistate = GetDrawUIState();


    const auto width = bound.width();
    const auto height = bound.height();

    SkColor bgColor = m_OffDefaultBGColor;
    SkColor borderColor = m_OffDefaultBorderColor;
    if ( uistate.IsDisabled() )
    {
        bgColor = m_DisabledBGColor;
        borderColor = m_DisabledBorderColor;
    }
    else
    {
        borderColor = AUISkiaUtil::MixColor( m_OnBorderColor, m_OffDefaultBorderColor, GetBlendFactor() );
        bgColor = AUISkiaUtil::MixColor( m_OnDefaultBGColor, m_OffDefaultBGColor, GetBlendFactor() );
        if ( uistate.IsMouseHovered() )
        {
            bgColor = AUISkiaUtil::MixColor( m_OnHoverBGColor, borderColor, GetBlendFactor() );
            borderColor = AUISkiaUtil::MixColor( m_OnHoverBorderColor, borderColor , GetBlendFactor() );
        }
        if ( uistate.IsPressed() )
        {
            bgColor = AUISkiaUtil::MixColor( m_OnPressBGColor, borderColor, GetBlendFactor() );
            borderColor = AUISkiaUtil::MixColor( m_OnPressBorderColor, borderColor, GetBlendFactor() );
        }
    }


    const auto borderRadius = (std::min)( std::floor( width * 0.4f ) - GetBlendFactor(), std::floor( height * 0.4f ) - GetBlendFactor() );
    const auto borderWidth = 1.0f + 3.0f * GetBlendFactor();

    SkPaint bgPaint;
    bgPaint.setAntiAlias( true );
    bgPaint.setColor( bgColor );
    canvas->drawCircle( bound.centerX(), bound.centerY(), borderRadius, bgPaint );

    SkPaint borderPaint;
    borderPaint.setAntiAlias( true );
    borderPaint.setColor( borderColor );
    borderPaint.setStrokeWidth( borderWidth );
    borderPaint.setStyle( SkPaint::kStroke_Style );
    canvas->drawCircle( bound.centerX(), bound.centerY(), borderRadius, borderPaint );

}
