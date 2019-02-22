#include "pch.h"
#include "AUITriangleShape.h"

AUITriangleShape::AUITriangleShape()
    : m_fAngle( 0.0f )
{

}

AUITriangleShape::~AUITriangleShape()
{

}

void AUITriangleShape::OnDraw( SkCanvas* const canvas, const SkPaint& paint )
{
    const auto width = GetWidth();
    const auto height = GetHeight();


    SkPath triangle;
    triangle.moveTo( SkPoint::Make( 0.0f, height ) );
    triangle.lineTo( SkPoint::Make( width * 0.5f, 0.0f ) );
    triangle.lineTo( SkPoint::Make( width, height ) );
    triangle.close();

    if ( GetAngle() != 0.0f )
    {
        SkMatrix rotMat;
        rotMat.reset();
        rotMat.postRotate( GetAngle(), width * 0.5f, height * 0.5f );
        triangle.transform( rotMat );
    }

    canvas->drawPath( triangle, paint );
}
