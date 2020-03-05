#include "pch.h"
#include "AUIButtonWidget.h"
#include "AUIShapeDrawable.h"
#include "AUILayerDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIRectShape.h"
#include "AUIJsonDrawableParser.h"

namespace {
    constexpr wchar_t DefaultCaption[] = L"Button";
    constexpr bool DefaultFocusable = true;

    std::shared_ptr< AUIDrawable > GetButtonDrawable()
    {
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(L"drawable/button.json"))
            return *refDrawable;

        auto pDefaultBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDefaultBG->SetColor( SkColorSetRGB( 253, 253, 253 ) );
        auto pHoverBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pHoverBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
        auto pPressBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pPressBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
        auto pDisableBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDisableBG->SetColor( SkColorSetRGB( 221, 221, 221 ) );
        auto pCheckBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pCheckBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
        auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pOutline->SetColor( SkColorSetRGB( 177, 177, 177 ) );
        pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        auto pHoverOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pHoverOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
        pHoverOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pHoverOutline->SetStrokeWidth( 2.0f );
        auto pPressOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pPressOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
        pPressOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pPressOutline->SetStrokeWidth( 2.0f );
        auto pCheckOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pCheckOutline->SetColor( SkColorSetRGB( 161, 174, 194 ) );
        pCheckOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pCheckOutline->SetStrokeWidth( 2.0f );
        auto pDisableOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDisableOutline->SetColor( SkColorSetRGB( 204, 204, 204 ) );
        pDisableOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pDisableOutline->SetStrokeWidth( 2.0f );
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

        return pStateDrawable;
    }
}

AUIButtonWidget::AUIButtonWidget()
    : AUITextWidget( DefaultCaption )
{
    SetClickable( true );
    SetFocusable( DefaultFocusable );
    SetBackgroundDrawable( ::GetButtonDrawable() );

    SetCaptionColor( AUIState::kDefault, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kDefault, false, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kMouseHovered, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kPressed, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kDisabled, true, SkColorSetRGB( 137, 144, 148 ) );
}

AUIButtonWidget::AUIButtonWidget( const std::wstring& caption )
    : AUITextWidget( caption )
{
    SetClickable( true );
    SetFocusable( DefaultFocusable );
    SetBackgroundDrawable( ::GetButtonDrawable() );

    SetCaptionColor( AUIState::kDefault, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kDefault, false, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kMouseHovered, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kPressed, true, SkColorSetRGB( 201, 211, 219 ) );
    SetCaptionColor( AUIState::kDisabled, true, SkColorSetRGB( 137, 144, 148 ) );
}

AUIButtonWidget::~AUIButtonWidget()
{

}

void AUIButtonWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();
    Invalidate();
}

void AUIButtonWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();
    Invalidate();
}

bool AUIButtonWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );
    Invalidate();
    return true;
}

bool AUIButtonWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    auto ret = SuperWidget::OnMouseLBtnUp( flag );

    if ( IsDisabled() )
        return ret;

    Invalidate();
    return true;
}

bool AUIButtonWidget::OnMouseLBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDblClk( flag );
    Invalidate();
    return true;
}

bool AUIButtonWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    auto ret = SuperWidget::OnMouseMove( flag );

    if ( IsDisabled() )
        return ret;

    Invalidate();
    return true;
}
