#include "pch.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"

namespace {
    constexpr SkColor DefaultColor = kAUIColorBlack;
    constexpr float DefaultStrokeWidth = 1.0f;
}

AUIShapeDrawable::AUIShapeDrawable()
    : m_pShape(std::make_shared<AUIRectShape>() )
    , m_StrokeStyle( SkPaint::kFill_Style )
    , m_Color( DefaultColor )
    , m_fStrokeWidth( DefaultStrokeWidth )
{

}

AUIShapeDrawable::AUIShapeDrawable( const std::shared_ptr< AUIShape >& shape )
    : m_pShape( shape )
    , m_StrokeStyle( SkPaint::kFill_Style )
    , m_Color( DefaultColor )
    , m_fStrokeWidth( DefaultStrokeWidth )
{

}

AUIShapeDrawable::~AUIShapeDrawable()
{

}

void AUIShapeDrawable::OnDraw( SkCanvas* const canvas )
{
    AUIAssert( GetShape() );

    SkPaint paint;
    paint.setAntiAlias( IsUseAA() );
    paint.setStyle( GetStrokeStyle() );
    paint.setStrokeWidth( GetStrokeWidth() );
    paint.setColor( GetColor() );

    const auto bound = GetDrawBound();
    const auto padding = GetDrawPadding();

    const auto shaperect = SkRect::MakeLTRB( bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom() );

    canvas->translate( bound.left() + padding.left(), bound.top() + padding.top () );

    GetShape()->Resize( shaperect.width(), shaperect.height() );
    GetShape()->Draw( canvas, paint );
}
 