#include "pch.h"
#include "AUIColorDrawable.h"

AUIColorDrawable::AUIColorDrawable()
{

}

AUIColorDrawable::AUIColorDrawable( const SkColor color )
    : m_Color( color )
{

}

AUIColorDrawable::~AUIColorDrawable()
{

}

void AUIColorDrawable::OnDraw( SkCanvas* const canvas )
{
    const auto bounds = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto rect = SkRect::MakeLTRB( bounds.left() + padding.left(), bounds.top() + padding.top(), bounds.right() - padding.right(), bounds.bottom() - padding.bottom() );


    SkPaint paint;
    paint.setAntiAlias( IsUseAA() );
    paint.setColor( GetColor() );

    canvas->translate( padding.left(), padding.top() );
    canvas->drawRect( rect, paint );
}
