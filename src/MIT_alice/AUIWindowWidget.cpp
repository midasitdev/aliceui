#include "pch.h"
#include "AUIWindowWidget.h"
#include "AUITitleBarTitleWidget.h"
#include "AUILinearLayoutWidget.h"
#include "AUIImageButtonWidget.h"
#include "AUIImageDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIGalleria.h"
#include "AUIJsonDrawableParser.h"
#include "AUIWindowTitleBarWidget.h"

namespace {
    constexpr wchar_t kDefaultBackground[] = L"ui_frame/window/window_BG.9.png";
    constexpr SkScalar DefaultWidth = 640.0f;
    constexpr SkScalar DefaultHeight = 480.0f;

    constexpr SkScalar DefaultTitleBarHeight = 29.0f;
    constexpr SkScalar DefaultSystemButtonWidth = 24.0f;
    constexpr SkScalar DefaultSystemButtonHeight = 24.0f;
}


AUIWindowWidget::AUIWindowWidget()
    : m_pTitleBar( std::make_shared< AUIWindowTitleBarWidget >() )
    , m_pContent( std::make_shared< AUILinearLayoutWidget >() )
{
    SetPaddingLTRB(1.0f, 1.0f, 1.0f, 1.0f);
    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);

    m_pContent->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);

    AddChild(m_pTitleBar);
    AddChild( m_pContent );

    AUIJsonDrawableParser parser;
    if (auto refDrawable = parser.LoadFromPath(kDefaultBackground))
        SetBackgroundDrawable(*refDrawable);
}

AUIWindowWidget::~AUIWindowWidget()
{

}

AUISignal<void(AUIWidget*)>& AUIWindowWidget::GetTitleBarDblClickSignal() const
{
	return m_pTitleBar->DblClickSignal;
}

void AUIWindowWidget::SetIgnoreTitleBar(bool ignore)
{
    m_pTitleBar->SetIgnored(ignore);
    UpdateChildPosition();
    UpdateSize();
}

AUISignal< void( AUIWidget* ) >& AUIWindowWidget::GetDragStartSignal() const
{

    return m_pTitleBar->DragPressSignal;
}

AUISignal< void( AUIWidget* ) >& AUIWindowWidget::GetDragEndSignal() const
{

    return m_pTitleBar->DragReleaseSignal;
}

AUISignal< void(AUIWidget* ) >& AUIWindowWidget::GetDraggingSignal() const
{

    return m_pTitleBar->DragMoveSignal;
}

AUISignal< void( AUIWidget* ) >& AUIWindowWidget::GetMinimizeSignal() const
{

    return m_pTitleBar->GetMinimizeButtonWidget()->ClickSignal;
}

AUISignal< void(AUIWidget* ) >& AUIWindowWidget::GetMaximizeSignal() const
{

	return m_pTitleBar->GetMaximizeButtonWidget()->ClickSignal;
}

AUISignal< void( AUIWidget* ) >& AUIWindowWidget::GetCloseSignal() const
{

    return m_pTitleBar->GetCloseButtonWidget()->ClickSignal;
}

void AUIWindowWidget::SetTitle( const std::wstring& caption )
{
    m_pTitleBar->GetTitleTextWidget()->SetCaption( caption );
}

std::wstring AUIWindowWidget::GetTitle() const
{
    return m_pTitleBar->GetTitleTextWidget()->GetCaption();
}

void AUIWindowWidget::SetTitleColor(const SkColor& titleColor)
{
    m_pTitleBar->GetTitleTextWidget()->SetCaptionColor(titleColor);
}

void AUIWindowWidget::SetTitleStyle(const SkFontStyle& titleStyle)
{
    m_pTitleBar->GetTitleTextWidget()->SetCaptionStyle(titleStyle);
}

void AUIWindowWidget::SetTitleFontName(const std::wstring& fontName)
{
    m_pTitleBar->GetTitleTextWidget()->SetCaptionFontName(fontName);
}

void AUIWindowWidget::SetIgnoreSysButton( bool ignore)
{
    m_pTitleBar->GetMinimizeButtonWidget()->SetIgnored(ignore);
    m_pTitleBar->GetMaximizeButtonWidget()->SetIgnored(ignore);
    m_pTitleBar->GetCloseButtonWidget()->SetIgnored(ignore);

    UpdateSize();
    UpdateChildPosition();
}

void AUIWindowWidget::SetIgnoreSysButton(bool ignoreMinimize, bool ignoreMaximize, bool ignoreClose)
{
    m_pTitleBar->GetMinimizeButtonWidget()->SetIgnored(ignoreMinimize);
    m_pTitleBar->GetMaximizeButtonWidget()->SetIgnored(ignoreMaximize);
    m_pTitleBar->GetCloseButtonWidget()->SetIgnored(ignoreClose);

    UpdateSize();
    UpdateChildPosition();
}

void AUIWindowWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    m_pContent->AddSubWidgetAt( widget, pos );
}

void AUIWindowWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
{
    m_pContent->DelSubWidget( widget );
}

void AUIWindowWidget::PopSubWidget()
{
    m_pContent->PopSubWidget();
}

void AUIWindowWidget::ClearSubWidget()
{
    m_pContent->ClearSubWidget();
}

std::shared_ptr< AUIWidget > AUIWindowWidget::FindSubWidget( size_t pos )
{
    return m_pContent->FindSubWidget( pos );
}

size_t AUIWindowWidget::SubWidgetCount() const 
{
    return m_pContent->SubWidgetCount();
}

void AUIWindowWidget::OnDraw( SkCanvas* const canvas )
{

    const auto rect = GetRect();
    auto borderrect = SkRect::MakeLTRB( rect.left(), rect.top(), rect.right() - 1, rect.bottom() - 1 );

    SkPaint paint;
    //paint.setAntiAlias( true );
    paint.setColor(kAUIColorBlack );
    paint.setStrokeWidth( 1.0f );
    paint.setStyle( SkPaint::kStroke_Style );

    canvas->drawRect( borderrect, paint );

    SuperWidget::OnDraw( canvas );
}

void AUIWindowWidget::OnUpdateChildPosition()
{
    SuperWidget::OnUpdateChildPosition();
    //m_pContent->SetPosition(0.0f, m_pTitleBar->GetHeight());
}

void AUIWindowWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    SuperWidget::OnMeasureSize(width, widthSpec, height, heightSpec);
    //m_pContent->SetMeasureSize(m_pContent->GetMeasureWidth(), m_pContent->GetMeasureHeight() - m_pTitleBar->GetMeasureHeight(), m_pContent->GetMeasureDepth());
}
