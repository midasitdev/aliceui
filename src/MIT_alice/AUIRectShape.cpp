#include "pch.h"
#include "AUIRectShape.h"

AUIRectShape::AUIRectShape()
{
    RefRect().setEmpty();
}

AUIRectShape::~AUIRectShape()
{

}

void AUIRectShape::OnDraw( SkCanvas* const canvas, const SkPaint& paint )
{
    if ( paint.getStyle() == SkPaint::kStroke_Style )
    {
        const auto strokeOffset = paint.getStrokeWidth() <= 1.0f ? 0.0f : paint.getStrokeWidth() - 1.0f;
        auto rect = SkRect::MakeLTRB( strokeOffset, strokeOffset, RefRect().right() - (std::max)( 1.0f, strokeOffset ), RefRect().bottom() - (std::max)( 1.0f, strokeOffset ) );
        canvas->drawRect( rect, paint );
    }
    else
    {
        canvas->drawRect( RefRect(), paint );
    }
}

void AUIRectShape::OnResize( float width, float height )
{
    m_Rect = SkRect::MakeWH( width, height );
}
