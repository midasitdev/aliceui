#include "pch.h"
#include "AUIFormWidget.h"
#include "AUITitleBarTitleWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRoundRectShape.h"


namespace
{
    constexpr SkScalar DefaultTitleBarHeight = 30.0f;
    constexpr SkScalar DefaultWidth = 640.0f;
    constexpr SkScalar DefaultHeight = 480.0f;
}

AUIFormWidget::AUIFormWidget()
    : AUILinearLayoutWidget( false )
    , m_pTitleBar( std::make_shared< AUITitleBarTitleWidget >() )
    , m_bMoveable( true )
{

    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);


    const float radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    auto pBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pBG->SetColor(kAUIColorWhiteSmoke );
    pBG->SetUseAA( true );
    auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pOutline->SetColor(kAUIColorBlack );
    pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pOutline->SetUseAA( true );
    auto pBackground = std::make_shared< AUILayerDrawable >();
    pBackground->InsertLayer( pBG );
    pBackground->InsertLayer( pOutline );

    SetBackgroundDrawable( pBackground );

    InitWidget(  );
}

AUIFormWidget::AUIFormWidget(bool moveable)
    : AUILinearLayoutWidget( false )
    , m_pTitleBar( std::make_shared< AUITitleBarTitleWidget >() )
    , m_bMoveable( moveable )
{

    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);


    const float radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    auto pBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pBG->SetColor(kAUIColorWhiteSmoke );
    pBG->SetUseAA( true );
    auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pOutline->SetColor(kAUIColorBlack );
    pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pOutline->SetUseAA( true );
    auto pBackground = std::make_shared< AUILayerDrawable >();
    pBackground->InsertLayer( pBG );
    pBackground->InsertLayer( pOutline );

    SetBackgroundDrawable( pBackground );

    InitWidget();
}

AUIFormWidget::~AUIFormWidget()
{

}

void AUIFormWidget::InitWidget()
{
    AddChild( m_pTitleBar );

    Connect( GetTitleBarWidget()->DragMoveSignal, this, &AUIFormWidget::OnDraggingTitleBar );
    GetTitleBarWidget()->SetDefaultSize( GetDefaultSize().fX, DefaultTitleBarHeight );
}

//void MUIFormWidget::OnSetSize( float& width, float& height, float& length )
//{
//    MUIAbstractGroupWidget::OnSetSize( width, height, length );
//    GetTitleBarWidget()->SetSize( width, GetTitleBarWidget()->GetHeight() );
//}

void AUIFormWidget::OnDraggingTitleBar( AUIWidget* const )
{
    //if ( IsMoveable() )
     //   SetPosition( GetPosition() + AUIScalar3( dx, dy, 0.0f ) );
}

void AUIFormWidget::SetTitleCaption( const std::wstring& text )
{
    GetTitleBarWidget()->SetCaption( text );
}

void AUIFormWidget::SetPosition(const AUIScalar3& pos)
{
	AUIWidget::SetPosition(pos);
}

AUIScalar3 AUIFormWidget::GetPosition() const
{
	return AUIWidget::GetPosition();
}
