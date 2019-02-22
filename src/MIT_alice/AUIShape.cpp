#include "pch.h"
#include "AUIShape.h"

void AUIShape::Draw( SkCanvas* const canvas, const SkPaint& paint )
{
    AUIAssert( canvas );
    OnDraw( canvas, paint );
}

void AUIShape::Resize( float width, float height )
{
    AUIAssert( width >= 0.0f );
    AUIAssert( height >= 0.0f );
    m_fWidth = width;
    m_fHeight = height;

    OnResize( width, height );
}
