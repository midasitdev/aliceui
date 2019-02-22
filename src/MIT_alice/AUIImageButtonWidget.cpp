#include "pch.h"
#include "AUIImageButtonWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"
#include "AUIStateDrawable.h"

namespace {
    constexpr SkScalar DefaultWidth = 23.0f;
    constexpr SkScalar DefaultHeight = 23.0f;
}

AUIImageButtonWidget::AUIImageButtonWidget()
{
    SetClickable( true );
    SetDefaultSize( DefaultWidth, DefaultHeight );

    constexpr SkScalar radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };

    auto pDefaultBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pDefaultBG->SetColor( SkColorSetRGB( 253, 253, 253 ) );
    //pDefaultBG->SetUseAA( true );

    auto pHoverBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pHoverBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    //pHoverBG->SetUseAA( true );

    auto pPressBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pPressBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
    //pPressBG->SetUseAA( true );

    auto pDisableBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pDisableBG->SetColor( SkColorSetRGB( 221, 221, 221 ) );
    //pDisableBG->SetUseAA( true );

    auto pCheckBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pCheckBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    //pCheckBG->SetUseAA( true );

    auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pOutline->SetColor( SkColorSetRGB( 177, 177, 177 ) );
    pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    //pOutline->SetStrokeWidth( 1.0f );
    //pOutline->SetUseAA( true );


    auto pHoverOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pHoverOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
    pHoverOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pHoverOutline->SetStrokeWidth( 2.0f );
    //pHoverOutline->SetUseAA( true );

    auto pPressOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pPressOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
    pPressOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pPressOutline->SetStrokeWidth( 2.0f );
    //pPressOutline->SetUseAA( true );


    auto pCheckOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pCheckOutline->SetColor( SkColorSetRGB( 161, 174, 194 ) );
    pCheckOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pCheckOutline->SetStrokeWidth( 2.0f );
    //pCheckOutline->SetUseAA( true );


    auto pDisableOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pDisableOutline->SetColor( SkColorSetRGB( 204, 204, 204 ) );
    pDisableOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pDisableOutline->SetStrokeWidth( 2.0f );
    //pDisableOutline->SetUseAA( true );

    auto pBackground = std::make_shared< AUILayerDrawable >();
    pBackground->InsertLayer( pDefaultBG );
    pBackground->InsertLayer( pOutline );

    auto pHoverBackground = std::make_shared< AUILayerDrawable >();
    pHoverBackground->InsertLayer( pHoverBG );
    pHoverBackground->InsertLayer( pHoverOutline );

    auto pPressBackground = std::make_shared< AUILayerDrawable >();
    pPressBackground->InsertLayer( pPressBG );
    pPressBackground->InsertLayer( pPressOutline );

    auto pDisabledBackground = std::make_shared< AUILayerDrawable >();
    pDisabledBackground->InsertLayer( pDisableBG );
    pDisabledBackground->InsertLayer( pDisableOutline );

    auto pCheckBackground = std::make_shared< AUILayerDrawable >();
    pCheckBackground->InsertLayer( pCheckBG );
    pCheckBackground->InsertLayer( pCheckOutline );


    auto pStateDrawable = std::make_shared< AUIStateDrawable >();
    pStateDrawable->SetTrueStateDrawable( AUIState::kDefault, pBackground );
    pStateDrawable->SetTrueStateDrawable( AUIState::kMouseHovered, pHoverBackground );
    pStateDrawable->SetTrueStateDrawable( AUIState::kPressed, pPressBackground );
    pStateDrawable->SetTrueStateDrawable( AUIState::kDisabled, pDisabledBackground );
    pStateDrawable->SetTrueStateDrawable( AUIState::kChecked, pCheckBackground );

    SetBackgroundDrawable( pStateDrawable );


}

AUIImageButtonWidget::~AUIImageButtonWidget()
{

}

void AUIImageButtonWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();

    Invalidate();
    InvalidateChildren();
}

void AUIImageButtonWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();

    Invalidate();
    InvalidateChildren();

}

bool AUIImageButtonWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );



    Invalidate();
    InvalidateChildren();

    return true;

}

bool AUIImageButtonWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{

    SuperWidget::OnMouseLBtnUp( flag );


    Invalidate();
    InvalidateChildren();

    return true;
}

bool AUIImageButtonWidget::OnMouseLBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDblClk( flag );

    Invalidate();
    InvalidateChildren();

    return true;
}

bool AUIImageButtonWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseMove( flag );

    Invalidate();
    InvalidateChildren();

    return true;
}
