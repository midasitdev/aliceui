#include "pch.h"
#include "AUITitleBarTitleWidget.h"
#include "AUIColorDrawable.h"
#include "AUITitleBarDefaultValue.h"

AUITitleBarTitleWidget::AUITitleBarTitleWidget()
	: AUITitleBarTitleWidget(L"")
{
    SetDraggable(true);
    SetCaptionSize(TitleBar::Caption::kTextSize);
    SetCaptionHorzAlign(TitleBar::Caption::kTextHorzAlign);
    SetCaptionVertAlign(TitleBar::Caption::kTextVertAlign);
    SetCaptionColor(TitleBar::Caption::kTextColor);
    //SetCaptionFontName(TitleBar::Caption::kTextFontFamily);
    SetCaptionStyle(TitleBar::Caption::kTextFontStyle);
}

AUITitleBarTitleWidget::AUITitleBarTitleWidget( const std::wstring& caption )
    : AUITextWidget( caption )
    , m_fAbsPrevX( -1.0f )
    , m_fAbsPrevY( -1.0f )
{
    SetDraggable( true );
    SetCaptionSize(TitleBar::Caption::kTextSize);
	SetCaptionHorzAlign(TitleBar::Caption::kTextHorzAlign);
    SetCaptionVertAlign(TitleBar::Caption::kTextVertAlign);
	SetCaptionColor(TitleBar::Caption::kTextColor);
	//SetCaptionFontName(TitleBar::Caption::kTextFontFamily);
    SetCaptionStyle(TitleBar::Caption::kTextFontStyle);

//     auto pBG = std::make_shared< MAUIColorDrawable >();
//     pBG->SetColor( 0xFFE1E5EA );
//     SetBackgroundDrawable( pBG );
}

AUITitleBarTitleWidget::~AUITitleBarTitleWidget()
{

}

bool AUITitleBarTitleWidget::OnChangeCursorIcon(AUICursorIcon& cursoricon)
{
	return AUITextWidget::OnChangeCursorIcon(cursoricon);
	//cursoricon.SetCursorIcon(MAUICursorIcon::CI_SizeAll);
	//return true;
}

bool AUITitleBarTitleWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    m_fAbsPrevX = GetMouseAbsPosX();
    m_fAbsPrevY = GetMouseAbsPosY();
    SuperWidget::OnMouseLBtnDown( flag );

    DragPressSignal.Send( this );
    return true;
}

bool AUITitleBarTitleWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );

    DragReleaseSignal.Send( this );
    return true;

}

bool AUITitleBarTitleWidget::OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag)
{
	SuperWidget::OnMouseLBtnDblClk(flag);

	TitleBarDblClickSignal.Send(this);
	return true;
}

bool AUITitleBarTitleWidget::OnDragging()
{
    const auto curAbsX = GetMouseAbsPosX();
    const auto curAbsY = GetMouseAbsPosY();

    if ( m_fAbsPrevX < 0.0f )
        m_fAbsPrevX = curAbsX;
    if ( m_fAbsPrevY < 0.0f )
        m_fAbsPrevY = curAbsY;
    const auto diffX = curAbsX - m_fAbsPrevX;
    const auto diffY = curAbsY - m_fAbsPrevY;

    m_fAbsPrevX = curAbsX;
    m_fAbsPrevY = curAbsY;

    DragMoveSignal.Send( this, diffX, diffY );

    return true;

}
