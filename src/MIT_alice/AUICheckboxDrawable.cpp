#include "pch.h"
#include "AUICheckboxDrawable.h"

AUICheckboxDrawable::AUICheckboxDrawable()
    : m_ColorBGOn( 0xFF90EE90 )
    , m_ColorBGOff( 0xFFD3D3D3 )
    , m_ColorToggleOn( SkColorSetRGB( 130, 186, 255 ) )
    , m_ColorToggleOff( SkColorSetRGB( 208, 213, 221 ) )
    , m_bPrevChecked( false )
    , m_bPrevCheckedIndeterminate( false )
{

}

AUICheckboxDrawable::~AUICheckboxDrawable()
{

}

void AUICheckboxDrawable::OnDraw( SkCanvas* const canvas )
{
    const auto baseBound = GetDrawBound();
    const auto bound = SkRect::MakeLTRB( baseBound.left() + 1.0f, baseBound.top() + 1.0f, baseBound.right() - 1.0f, baseBound.bottom() - 1.0f );
    const auto uistate = GetDrawUIState();


    SkPaint bgPaint;
    bgPaint.setColor( SkColorSetRGB( 255, 255, 255 ) );
    const auto bgRect = SkRect::MakeLTRB( bound.left(), bound.top(), bound.right() - 1.0f, bound.bottom() - 1.0f );
    SkVector raii[] = { SkVector::Make( 3.0f, 3.0f ), SkVector::Make( 3.0f, 3.0f ), SkVector::Make( 3.0f, 3.0f ), SkVector::Make( 3.0f, 3.0f ) };
    SkRRect bgRRect;
    bgRRect.setRectRadii( bgRect, raii );
    //canvas->drawRect( bgRect, bgPaint );
    canvas->drawRRect( bgRRect, bgPaint );


    SkPaint borderPaint;
    borderPaint.setAntiAlias( true );
    borderPaint.setColor( SkColorSetARGB(static_cast<U8CPU>(std::clamp(255.0f * (1.0f - GetBlendFactor()), 0.0f, 255.0f)), 197, 197, 197 ) );
    borderPaint.setStyle( SkPaint::kStroke_Style );
    canvas->drawRect( SkRect::MakeLTRB( bound.left(), bound.top(), bound.right() - 1.0f, bound.bottom() - 1.0f ), borderPaint );

    if ( uistate.IsCheckedIndeterminate() )
    {
        SkPaint iconPaint;
        iconPaint.setAntiAlias( true );
        iconPaint.setColor(AUISkiaUtil::MixColor( GetColorToggleOn(), kAUIColorTransparent, GetBlendFactor() ) );

        const auto innerrect = SkRect::MakeLTRB( bound.left() + 3.0f, bound.top() + 3.0f, bound.right() - 4.0f, bound.bottom() - 4.0f );

        canvas->drawRect( innerrect, iconPaint );
    }
    else if ( uistate.IsChecked() || IsPrevChecked() )
    {
        SkPaint iconBGPaint;
        iconBGPaint.setAntiAlias( true );
        iconBGPaint.setColor(AUISkiaUtil::MixColor( GetColorToggleOn(), kAUIColorTransparent, GetBlendFactor() ) );
        const auto innerBGRect = SkRect::MakeLTRB( bound.left(), bound.top(), bound.right() - 1.0f, bound.bottom() - 1.0f );
        SkRRect innerBGRRect;
        innerBGRRect.setRectRadii( innerBGRect, raii );
        //canvas->drawRect( innerBGRect, iconBGPaint );
        canvas->drawRRect( innerBGRRect, iconBGPaint );

        SkPaint iconPaint;
        iconPaint.setAntiAlias( true );
        iconPaint.setColor(kAUIColorWhite );
        iconPaint.setStrokeWidth( 2.0f );
        iconPaint.setStyle( SkPaint::kStroke_Style );
        iconPaint.setStrokeCap( SkPaint::kRound_Cap );

        const auto innerrect = SkRect::MakeLTRB( bound.left() + 3.0f, bound.top() + 3.0f, bound.right() - 4.0f, bound.bottom() - 4.0f );

        const auto checkStartPosX = ( innerrect.left() - innerrect.centerX() ) * GetBlendFactor() + innerrect.centerX();
        const auto checkStartPosY = innerrect.centerY();
        const auto checkMidPosX = innerrect.centerX();
        const auto checkMidPosY = ( innerrect.bottom() - innerrect.centerY() ) * GetBlendFactor() + innerrect.centerY();
        const auto checkEndPosX = ( innerrect.right() - innerrect.centerX() ) * GetBlendFactor() + innerrect.centerX();
        const auto checkEndPosY = ( innerrect.top() - innerrect.centerY() ) * GetBlendFactor() + innerrect.centerY();
        canvas->drawLine( checkStartPosX, checkStartPosY, checkMidPosX, checkMidPosY, iconPaint );
        canvas->drawLine( checkMidPosX, checkMidPosY, checkEndPosX, checkEndPosY, iconPaint );

        if ( GetBlendFactor() >= 1.0f )
            SetPrevChecked( true );
        else if ( GetBlendFactor() <= 0.0f )
            SetPrevChecked( false );
    }
    else
    {

    }


}
