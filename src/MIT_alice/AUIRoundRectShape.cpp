#include "pch.h"
#include "AUIRoundRectShape.h"

AUIRoundRectShape::AUIRoundRectShape()
{

}

AUIRoundRectShape::AUIRoundRectShape( const float radii[8] )
{
    const SkVector tmpRadii[4] = { SkVector::Make( radii[0], radii[1] ), SkVector::Make( radii[2], radii[3] ), SkVector::Make( radii[4], radii[5] ), SkVector::Make( radii[6], radii[7] ) };
    RefRRect().setRectRadii( SkRect::MakeWH( GetWidth(), GetHeight() ), tmpRadii );
}

AUIRoundRectShape::AUIRoundRectShape( const SkVector radii[4] )
{
    RefRRect().setRectRadii( SkRect::MakeWH( GetWidth(), GetHeight() ), radii );
}

AUIRoundRectShape::~AUIRoundRectShape()
{

}

void AUIRoundRectShape::OnDraw( SkCanvas* const canvas, const SkPaint& paint )
{
    if ( paint.getStyle() == SkPaint::kStroke_Style )
    {
        const auto strokeOffset = paint.getStrokeWidth() <= 1.0f ? 1.0f : paint.getStrokeWidth() - 1.0f;
        const SkVector radii[4] = { RefRRect().radii( SkRRect::kUpperLeft_Corner ), RefRRect().radii( SkRRect::kUpperRight_Corner ), RefRRect().radii( SkRRect::kLowerRight_Corner ), RefRRect().radii( SkRRect::kLowerLeft_Corner ) };
        SkRRect rrect;
        rrect.setRectRadii( SkRect::MakeLTRB( strokeOffset, strokeOffset, RefRRect().rect().right() - strokeOffset, RefRRect().rect().bottom() - strokeOffset ), radii );
        canvas->drawRRect( rrect, paint );
    }
    else
    {
        canvas->drawRRect( RefRRect(), paint );
    }
}

void AUIRoundRectShape::OnResize( float width, float height )
{
    const SkVector radii[4] = { RefRRect().radii( SkRRect::kUpperLeft_Corner ), RefRRect().radii( SkRRect::kUpperRight_Corner ), RefRRect().radii( SkRRect::kLowerRight_Corner ), RefRRect().radii( SkRRect::kLowerLeft_Corner ) };
    RefRRect().setRectRadii( SkRect::MakeWH( width, height ), radii );
}
