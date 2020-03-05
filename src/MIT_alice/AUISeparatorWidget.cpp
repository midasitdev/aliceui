#include "pch.h"
#include "AUISeparatorWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRoundRectShape.h"

namespace
{
    constexpr SkScalar DefaultWidth = 5.0f;
    constexpr SkScalar DefaultHeight = 5.0f;
    constexpr SkScalar DefaultDragDiffMin = 0.0f;
}


AUISeparatorWidget::AUISeparatorWidget()
    : m_bHorizontal( false )
{
    SetHorizontal( false );
    SetDraggable( false );
    SetDefaultSize( DefaultWidth, DefaultHeight );
    //  SetDragDiffMin( DefaultDragDiffMin, DefaultDragDiffMin );

    constexpr SkScalar radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };

    auto pBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pBG->SetColor( SkColorSetRGB( 204, 204, 204 ) );
    SetBackgroundDrawable( pBG );
}

AUISeparatorWidget::AUISeparatorWidget( bool horizontal )
    : m_bHorizontal( horizontal )
{
    SetHorizontal( horizontal );

    SetDraggable( false );
    SetDefaultSize( DefaultWidth, DefaultHeight );
    //  SetDragDiffMin( DefaultDragDiffMin, DefaultDragDiffMin );

    const float radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };

    auto pBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pBG->SetColor( SkColorSetRGB( 204, 204, 204 ) );
    SetBackgroundDrawable( pBG );
}

AUISeparatorWidget::~AUISeparatorWidget()
{

}

void AUISeparatorWidget::SetHorizontal( bool state )
{
    m_bHorizontal = state;

    if (m_bHorizontal)
        SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kFixed);
    else
        SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kParent);
}

void AUISeparatorWidget::SetColor( const SkColor color )
{
    const float radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    auto pBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pBG->SetColor( color );

    SetBackgroundDrawable( pBG );
}

bool AUISeparatorWidget::IsHorizontal() const
{


    return m_bHorizontal;
}

bool AUISeparatorWidget::OnChangeCursorIcon( AUICursorIcon& cursoricon )
{

    if ( IsDraggable() == false )
        return false;

    if ( IsHorizontal() )
    {
        cursoricon.SetCursorIcon( AUICursorIcon::kSizeNS_CursorIcon );
    }
    else
    {
        cursoricon.SetCursorIcon( AUICursorIcon::kSizeWE_CursorIcon );
    }

    return true;
}

bool AUISeparatorWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{

    //m_fAbsPrevX = GetMouseAbsPosX();
    //m_fAbsPrevY = GetMouseAbsPosY();
    SuperWidget::OnMouseLBtnDown( flag );

    DragPressSignal.Send( this );

    return true;
}

bool AUISeparatorWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );

    DragReleaseSignal.Send( this );

    return true;
}

bool AUISeparatorWidget::OnDragging()
{


    //const auto curAbsX = GetMouseAbsPosX();
    //const auto curAbsY = GetMouseAbsPosY();

    //if ( m_fAbsPrevX < 0.0f )
    //    m_fAbsPrevX = curAbsX;
    //if ( m_fAbsPrevY < 0.0f )
    //    m_fAbsPrevY = curAbsY;
    //const auto diffX = curAbsX - m_fAbsPrevX;
    //const auto diffY = curAbsY - m_fAbsPrevY;

    //m_fAbsPrevX = curAbsX;
    //m_fAbsPrevY = curAbsY;

    //DragMoveSignal.Send( this, diffX, diffY );
    DragMoveSignal.Send(this);

    return true;
}

