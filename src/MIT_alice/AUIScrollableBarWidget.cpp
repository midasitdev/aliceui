#include "pch.h"
#include "AUIScrollableBarWidget.h"
#include "AUIJsonDrawableParser.h"

namespace
{

    std::shared_ptr< AUIDrawable > GetScrollThumbDrawable()
    {
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(L"drawable/scroll_thumb.json"))
            return *refDrawable;

        return std::make_shared< AUIDrawable >();
    }
}

AUIScrollableBarWidget::AUIScrollableBarWidget()
    : m_ContentHeight( 0.0f )
    , m_ScrollPos( 0.0f )
    , m_pThumbDrawable( ::GetScrollThumbDrawable() )
    , m_bShowThumbOnHit( false )
{
    SetSizePolicy( AUISizePolicy::kParent, AUISizePolicy::kParent );
    //Freeze();
    m_ThumbState.SetClickable( true );
}

AUIScrollableBarWidget::~AUIScrollableBarWidget()
{

}

void AUIScrollableBarWidget::OnDraw( SkCanvas* const canvas )
{
    SuperClass::OnDraw( canvas );

    AUIAssert( m_pThumbDrawable );

    if ( IsScrollable() )
    {
        const auto thumbRect = GetThumbRect();
        if ( IsShowThumbOnHit() )
        {
            if ( HasMouseLocPos() )
            {
                if (AUISkiaUtil::IsInRect( thumbRect, GetMouseLocPos() ) ||
                    IsGrabMouseEvent() )    // Grab Scroll Thumb
                {
                    m_pThumbDrawable->SetDrawUIState( m_ThumbState );
                    m_pThumbDrawable->SetDrawBound( thumbRect );
                    m_pThumbDrawable->Draw( canvas );
                }
            }
        }
        else
        {
            m_pThumbDrawable->SetDrawUIState( m_ThumbState );
            m_pThumbDrawable->SetDrawBound( thumbRect );
            m_pThumbDrawable->Draw( canvas );
        }
    }
}

void AUIScrollableBarWidget::OnMouseEnter()
{
    if ( IsScrollable() )
    {
        m_ThumbState.SetMouseHovered( true );
    }
    Invalidate();
}

void AUIScrollableBarWidget::OnMouseHover()
{
    if ( IsShowThumbOnHit() )
    {
        const auto thumbRect = GetThumbRect();
        if (AUISkiaUtil::IsInRect( thumbRect, GetMouseLocPos() ) )
        {
            Invalidate();
        }
    }
}

void AUIScrollableBarWidget::OnMouseLeave()
{
    m_ThumbState.ResetMouse();
    m_ThumbState.SetPressed( false );
    //m_ThumbState.SetMouseHovered( false );
    Invalidate();
}

bool AUIScrollableBarWidget::OnMouseLBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseRBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseMBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    if ( false == IsScrollable() )
        return false;

    bool retval = false;
    const auto thumbRect = GetThumbRect();
    const auto mousePtX = GetMouseLocPosX();
    const auto mousePtY = GetMouseLocPosY();
    if (AUISkiaUtil::IsInRect( thumbRect, SkPoint::Make( mousePtX, mousePtY ) ) )
    {
        m_PrevLDownPos = GetMouseAbsPos();
        m_ThumbState.SetPressed( true );
        Invalidate();

        GrabMouseEvent();

        retval = true;
    }
    else
    {

    }

    return retval;
}

bool AUIScrollableBarWidget::OnMouseRBtnDown( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseMBtnDown( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    if ( false == IsScrollable() )
        return false;

    bool retval = false;
    if ( m_ThumbState.IsPressed() )
    {
        ReleaseMouseEvent();
        retval = true;
    }
    m_ThumbState.SetPressed( false );
    Invalidate();

    return retval;
}

bool AUIScrollableBarWidget::OnMouseRBtnUp( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseMBtnUp( MAUIMouseEvent::EventFlag flag )
{
    return false;
}

bool AUIScrollableBarWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    if ( false == IsScrollable() )
        return false;

    bool retval = false;
    if ( m_ThumbState.IsPressed() )
    {
        const auto mouseCurPos = GetMouseAbsPos();
        const auto diffPos = mouseCurPos - m_PrevLDownPos;

        const auto diffY = diffPos.y();

        const auto myHeight = GetHeight();
        SkScalar diffWeight = 1.0f;
        if ( myHeight > 0.0f )
            diffWeight = diffY / myHeight;

        m_PrevLDownPos = mouseCurPos;

        ThumbScrollSignal.Send( diffWeight );

        retval = true;
    }
    return retval;
}

bool AUIScrollableBarWidget::OnMouseWheel( MAUIMouseEvent::EventFlag flag, float delta )
{
    return false;
}

bool AUIScrollableBarWidget::IsScrollable() const
{
    const auto contentHeight = m_ContentHeight;
    const auto myHeight = GetHeight();
    const auto diffHeight = contentHeight - myHeight;
    return diffHeight > 0;
}

bool AUIScrollableBarWidget::OnChangeCursorIcon( AUICursorIcon& cursoricon )
{
    return false;
}

SkRect AUIScrollableBarWidget::GetThumbRect() const
{
    const auto rect = GetDrawBound();
    const auto contentHeight = m_ContentHeight;
    const auto myHeight = GetHeight();
    const auto diffHeight = contentHeight - myHeight;

    SkScalar thumbWeight = 1.0f;
    if ( contentHeight > 0.0f )
        thumbWeight = myHeight / contentHeight;

    constexpr SkScalar thumbMarginRight = 3.0f;
    constexpr SkScalar thumbWidth = 8.0f;
    constexpr SkScalar thumbMinimumHeight = 15.0f;
    const auto scrollWeight = std::abs( m_ScrollPos ) / diffHeight;
    const auto thumbHeight = std::clamp( myHeight * thumbWeight, thumbMinimumHeight, ( std::max )( myHeight, thumbMinimumHeight) );
    const auto thumbRect = SkRect::MakeLTRB( rect.fRight - thumbWidth - thumbMarginRight, scrollWeight * ( myHeight - thumbHeight ), rect.fRight - thumbMarginRight, scrollWeight * ( myHeight - thumbHeight ) + thumbHeight );

    return thumbRect;
}
