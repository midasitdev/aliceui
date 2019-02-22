#include "pch.h"
#include "AUIDrawableWidget.h"
#include "AUIApplication.h"
#include "AUIColorDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIColor.h"
#include "AUIGalleria.h"
#include "AUINinePatch.h"
#include "AUINinePatchDrawable.h"
#include "AUIJsonDrawableParser.h"
#include "AUIStyleNotion.h"
#include "AUIImageDrawable.h"

AUIDrawableWidget::AUIDrawableWidget()
{
	m_bEventPassthrough = false;
    m_DebugColor = SkColorSetA( AUIColor::GetRandomColor(), kAUIAlpha_20 );

    // Set default layers
    InsertLayer(nullptr);   // Background
    InsertLayer(nullptr);   // Foreground

    LoadDefault2DSensor();
}

void AUIDrawableWidget::OnDraw( SkCanvas* canvas )
{
    SetDrawBound( GetRect() );
    SetDrawUIState( GetUIState() );
    AUILayerDrawable::OnDraw( canvas );

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        if ( IsMouseHover() )
        {
            SkPaint paint;
            paint.setColor( m_DebugColor );
            canvas->drawRect( GetRect(), paint );
        }
    }

    if (IsRefreshDraw())
        Invalidate();
}

SkRect AUIDrawableWidget::GetRect() const
{
    const auto minRange = GetRangeMin();
    const auto maxRange = GetRangeMax();
    return SkRect::MakeLTRB( minRange.fX, minRange.fY, maxRange.fX, maxRange.fY );

}

void AUIDrawableWidget::SetBackgroundDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    SetLayer(kBackground_Layer, pDrawable);
    Invalidate();
}

void AUIDrawableWidget::SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable)
{
    SetLayer(kForeground_Layer, pDrawable);
    Invalidate();
}

void AUIDrawableWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        Invalidate();
    }

    if (IsRefreshDraw())
        Invalidate();
}

void AUIDrawableWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        Invalidate();
    }
}

void AUIDrawableWidget::OnUpdate()
{
    const auto opacity = GetOpacity();
    const auto minRange = GetRangeMin();
    if ( opacity > 0.0f )
        AUILayerDrawable::Draw( int( minRange.fX ), int( minRange.fY ), int( GetWidth() ), int( GetHeight() ) );
}

void AUIDrawableWidget::OnDestroy()
{
	SuperWidget::OnDestroy();
}

void AUIDrawableWidget::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
    SuperWidget::OnTickTime(prevTime, curTime);
}


void AUIDrawableWidget::OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value)
{
	if (uiKey == MNV_BACKGROUND_IMAGE)
	{
		std::shared_ptr<AUIDrawable> pDrawable;
		if (value.GetValue(pDrawable))
			SetBackgroundDrawable(pDrawable);
	}
	else
		SuperWidget::OnSetStyleNotion(uiKey, value);
}

void AUIDrawableWidget::OnSetMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom)
{
	AUIWidget::SetMarginLTRB(marginLeft, marginTop, marginRight, marginBottom);
}

AUIDrawable* AUIDrawableWidget::GetAsDrawable() const
{
    return static_cast<AUIDrawable*>(const_cast<AUIDrawableWidget*>(this));
}
