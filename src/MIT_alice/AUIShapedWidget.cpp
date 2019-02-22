#include "pch.h"
#include "AUIShapedWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"

AUIShapedWidget::AUIShapedWidget()
    : m_pShapeDrawable( std::make_shared< AUIShapeDrawable >() )
{
    m_pShapeDrawable->SetShape( std::make_shared< AUIRectShape >() );
    m_pShapeDrawable->SetColor( 0xAF000000 );
    SetSizePolicy( AUISizePolicy::kFixed, AUISizePolicy::kFixed );
    SetDefaultSize( 100.0f, 100.0f );
}

AUIShapedWidget::~AUIShapedWidget()
{

}

void AUIShapedWidget::SetColor( const SkColor color )
{
    m_pShapeDrawable->SetColor( color );
}

void AUIShapedWidget::OnDraw( SkCanvas* const canvas )
{

    SuperWidget::OnDraw( canvas );
    if ( GetShapeDrawable() )
    {
        GetShapeDrawable()->SetDrawBound( GetDrawBound() );
        canvas->save();
        GetShapeDrawable()->Draw( canvas );
        canvas->restore();
    }


}
