#include "pch.h"
#include "MAUIRulerWidget.h"
#include "MAUIRulerDrawable.h"

using namespace mit::alice;

MAUIRulerWidget::MAUIRulerWidget()
    : m_pRulerDrawable( std::make_shared< MAUIRulerDrawable >() )
{
	SetBackgroundDrawable( m_pRulerDrawable );
    SetDefaultSize(50.0f, 50.0f);
}

MAUIRulerWidget::~MAUIRulerWidget()
{

}

void MAUIRulerWidget::SetRefPos( SkScalar pos )
{
    GetRulerDrawable()->SetRefPos( pos );
}

SkScalar MAUIRulerWidget::GetRefPos() const
{
    return GetRulerDrawable()->GetRefPos();
}

void MAUIRulerWidget::SetLocation( AUIRulerLocation location )
{
    GetRulerDrawable()->SetLocation( location );
    Invalidate();
}

AUIRulerLocation MAUIRulerWidget::GetLocation() const
{
    return GetRulerDrawable()->GetLocation();
}

void MAUIRulerWidget::SetScale( SkScalar val )
{
    GetRulerDrawable()->SetScale( val );
	Invalidate();
}

mit::alice::MAUIRulerDrawable* const mit::alice::MAUIRulerWidget::GetRulerDrawable() const
{
    return m_pRulerDrawable.get();
}

SkScalar mit::alice::MAUIRulerWidget::GetScale() const
{
    return GetRulerDrawable()->GetScale();
}

void mit::alice::MAUIRulerWidget::SetUseMarking(bool val)
{
    GetRulerDrawable()->SetUseMarking(val);
}

bool mit::alice::MAUIRulerWidget::IsUseMarking() const
{
    return GetRulerDrawable()->IsUseMarking();
}

void MAUIRulerWidget::SetBasis( SkScalar val )
{
    GetRulerDrawable()->SetBasis( val );
    Invalidate();
}

SkScalar MAUIRulerWidget::GetBasis() const
{
    return GetRulerDrawable()->GetBasis();
}

void MAUIRulerWidget::SetGradationSize( SkScalar val )
{
    GetRulerDrawable()->SetGradationSize( val );
    Invalidate();
}

SkScalar MAUIRulerWidget::GetGradationSize() const
{
    return GetRulerDrawable()->GetGradationSize();
}

void MAUIRulerWidget::SetMaxTextWidth( SkScalar val )
{
    GetRulerDrawable()->SetMaxTextWidth( val );
}

void MAUIRulerWidget::SetMaxTextHeight( SkScalar val )
{
    GetRulerDrawable()->SetMaxTextHeight( val );
}

SkScalar MAUIRulerWidget::GetMaxTextWidth() const
{
    return GetRulerDrawable()->GetMaxTextWidth();
}

SkScalar MAUIRulerWidget::GetMaxTextHeight() const
{
    return GetRulerDrawable()->GetMaxTextHeight();
}

void MAUIRulerWidget::SetLineColor( SkColor color )
{
    GetRulerDrawable()->RefLinePaint().setColor( color );
}

void MAUIRulerWidget::SetTextColor( SkColor color )
{
    GetRulerDrawable()->RefTextPaint().setColor( color );
}

SkColor MAUIRulerWidget::GetLineColor() const
{
    return GetRulerDrawable()->RefLinePaint().getColor();
}

SkColor MAUIRulerWidget::GetTextColor() const
{
    return GetRulerDrawable()->RefTextPaint().getColor();
}

void MAUIRulerWidget::SetTextSize( SkScalar size )
{
    GetRulerDrawable()->RefTextPaint().setTextSize( size );
}

SkScalar MAUIRulerWidget::GetTextSize() const
{
    return GetRulerDrawable()->RefTextPaint().getTextSize();
}

void MAUIRulerWidget::SetRulerPadding( SkScalar l, SkScalar t, SkScalar r, SkScalar b )
{
    GetRulerDrawable()->SetDrawPadding( SkRect::MakeLTRB( l, t, r, b ) );
}
