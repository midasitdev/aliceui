#include "pch.h"
#include "AUITabBarWidget.h"
#include "AUITextWidget.h"
#include "AUITabWidget.h"
#include "AUITabButtonWidget.h"
#include "AUITab.h"

namespace
{
    constexpr SkScalar DefaultWidth = 100.0f;
    constexpr SkScalar DefaultHeight = 50.0f;
}

AUITabBarWidget::AUITabBarWidget()
    : AUILinearLayoutWidget( true )
    , m_TabStyle( AUIImageCaptionStyle::kTextOnly )
	, m_TabDefaultTextColor(SkColorSetRGB(63, 63, 63))
	, m_TabUncheckTextColor(SkColorSetRGB(152, 152, 152))
	, m_TabHoverTextColor(SkColorSetRGB(107, 127, 145))
	, m_bUnderLine( false )
{
    SetDefaultSize( DefaultWidth, DefaultHeight );
	SetUnderLineColor(SkColorSetRGB(26, 135, 220));
}

AUITabBarWidget::~AUITabBarWidget()
{

}

void AUITabBarWidget::AddTab( const std::shared_ptr< AUITab >& pTab )
{
    AUIAssert(pTab);
    m_arrTabs.emplace_back( pTab );

    auto pTabBtn = OnCreateTabButton();
    pTabBtn->InitializeTab( pTab );
    pTabBtn->SetImageCaptionStyle( GetTabStyle() );
    pTabBtn->SetCaptionColor( m_TabDefaultTextColor );
    pTabBtn->SetCaptionColor( AUIState::kChecked, false, m_TabUncheckTextColor );
    pTabBtn->SetCaptionColor( AUIState::kMouseHovered, true, m_TabHoverTextColor );

	pTab->SetTabButtonWidget(pTabBtn);

    Connect( pTabBtn->ClickSignal, this, &AUITabBarWidget::OnClickTabButton );
    AddChild( pTabBtn );
    m_mapTab2Button[pTab.get()] = pTabBtn;
}

void AUITabBarWidget::RemoveTab( const std::shared_ptr< AUITab >& pTab )
{
    const auto foundTab = std::find( m_arrTabs.begin(), m_arrTabs.end(), pTab );
    if ( foundTab == m_arrTabs.end() )
    {
        AUIAssert( false );
        return;
    }

    const auto foundButton = m_mapTab2Button.find( pTab.get() );
    if ( foundButton == m_mapTab2Button.end() )
    {
        AUIAssert( false );
        return;
    }

    auto pTabBtn = foundButton->second.lock();
    DelChild( pTabBtn );
    m_mapTab2Button.erase( foundButton );

    m_arrTabs.erase( foundTab );
}

void AUITabBarWidget::RemoveTab( const std::shared_ptr< AUIWidget >& pWidget )
{
    const auto foundTab = std::find_if( m_arrTabs.begin(), m_arrTabs.end(), [&pWidget]( const std::shared_ptr< AUITab >& _pTab )->bool {
        return _pTab->GetWidget() == pWidget;
    } );
    if ( foundTab == m_arrTabs.end() )
    {
        AUIAssert( false );
        return;
    }

    RemoveTab( *foundTab );
}

void AUITabBarWidget::SetVisibleTab(const std::shared_ptr< AUITab >& pTab, bool bVisible)
{
	const auto foundButton = m_mapTab2Button.find( pTab.get() );
	if ( foundButton == m_mapTab2Button.end() )
	{
		AUIAssert( false );
		return;
	}

	auto pTabBtn = foundButton->second.lock();
    AUIAssert( pTabBtn );
	pTabBtn->SetVisible(bVisible);
	
	pTab->GetWidget()->SetVisible(bVisible);
}

bool AUITabBarWidget::IsHiddenTab(const std::shared_ptr< AUITab >& pTab) const
{
	const auto foundButton = m_mapTab2Button.find(pTab.get());
	if (foundButton == m_mapTab2Button.end())
	{
		AUIAssertFail();
		return true;
	}

	auto pTabBtn = foundButton->second.lock();
	AUIAssert(pTabBtn);
	return pTabBtn->IsIgnored();
}

bool AUITabBarWidget::IsHiddenTab(const size_t idx) const
{
	if (m_mapTab2Button.size() < idx)
	{
		AUIAssertFail();
		return true;
	}
	
	auto itrTab = m_arrTabs.begin();
	std::advance(itrTab, idx);
	const auto foundButton = m_mapTab2Button.find((*itrTab).get());
	auto pTabBtn = foundButton->second.lock();
	AUIAssert(pTabBtn);
	return pTabBtn->IsIgnored();

}

void AUITabBarWidget::HideTab( const std::shared_ptr< AUITab >& pTab, bool bHide )
{
    const auto foundButton = m_mapTab2Button.find( pTab.get() );
    if ( foundButton == m_mapTab2Button.end() )
    {
        AUIAssertFail();
        return;
    }

    auto pTabBtn = foundButton->second.lock();
    AUIAssert( pTabBtn );
    pTabBtn->SetIgnored( bHide );
}

void AUITabBarWidget::ReplaceTab( size_t idx, const std::shared_ptr< AUITab >& pTab )
{
    if ( GetTabCount() <= idx )
    {
        AUIAssertFailReason("Invalid tab count");
        return;
    }
    if ( nullptr == pTab )
    {
        AUIAssertFailReason("Empty Tab");
        return;
    }

    bool doReplace = false;
    if ( GetCurrentTab() == m_arrTabs[idx] )
    {
        doReplace = true;
    }

    auto pPrevTab = m_arrTabs[idx];
    AUIAssert( pPrevTab );

    // Add First
    m_arrTabs.emplace( m_arrTabs.begin() + idx, pTab );

    auto pTabBtn = OnCreateTabButton();
    pTabBtn->InitializeTab( pTab );
    pTabBtn->SetImageCaptionStyle( GetTabStyle() );
    pTabBtn->SetCaptionColor( m_TabDefaultTextColor );
    pTabBtn->SetCaptionColor( AUIState::kChecked, false, m_TabUncheckTextColor );
    pTabBtn->SetCaptionColor( AUIState::kMouseHovered, true, m_TabHoverTextColor );

    Connect( pTabBtn->ClickSignal, this, &AUITabBarWidget::OnClickTabButton );
    AddChild( pTabBtn, idx );
    m_mapTab2Button[pTab.get()] = pTabBtn;


    RemoveTab( pPrevTab );

    if ( doReplace )
    {
        TabClickSignal.Send( pTab.get() );
    }
}

std::shared_ptr< AUITab > AUITabBarWidget::FindTabByWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidget )
        return nullptr;

    for ( const auto& tab : m_arrTabs )
    {
        if ( tab->GetWidget() == pWidget )
            return tab;
    }
    return nullptr;
}

std::shared_ptr< AUITab > AUITabBarWidget::FindTabByIndex(const size_t idx) const
{
	if (m_arrTabs.size() < idx)
		return nullptr;
	return m_arrTabs[idx];
}

void AUITabBarWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    AUIAssertFailReason("DO NOT USE");
}

void AUITabBarWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
{
    AUIAssertFailReason("DO NOT USE");
}

void AUITabBarWidget::PopSubWidget()
{
    AUIAssertFailReason("DO NOT USE");
}

void AUITabBarWidget::ClearSubWidget()
{
    AUIAssertFailReason("DO NOT USE");
}

std::shared_ptr< AUIWidget > AUITabBarWidget::FindSubWidget( size_t pos )
{
    AUIAssertFailReason("DO NOT USE");
    return nullptr;
}

size_t AUITabBarWidget::SubWidgetCount() const 
{
    AUIAssertFailReason("DO NOT USE");
    return 0;
}

void AUITabBarWidget::ClearTab()
{
    m_mapTab2Button.clear();
    m_arrTabs.clear();
    m_pCurTab.reset();
    ClearChild();
}

void AUITabBarWidget::OnClickTabButton( AUIWidget* const pWidget )
{
    AUIAssert( pWidget->IsKindOf< AUITabButtonWidget >() );
    auto pTabButton = pWidget->Cast< AUITabButtonWidget >();
    TabClickSignal.Send( pTabButton->GetTab() );
}

void AUITabBarWidget::SetTabStyle( AUIImageCaptionStyle style )
{
    m_TabStyle = style;

    for ( auto& itrTab2Btn : m_mapTab2Button )
    {
        auto pTabBtn = itrTab2Btn.second.lock();
        if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
            continue;
        }

        pTabBtn->SetImageCaptionStyle( m_TabStyle );
    }
}

AUIImageCaptionStyle AUITabBarWidget::GetTabStyle() const
{
    return m_TabStyle;
}

std::shared_ptr< AUITabButtonWidget > AUITabBarWidget::OnCreateTabButton()
{
    return std::make_shared< AUITabButtonWidget >();
}

void AUITabBarWidget::SetTabDefaultTextColor( SkColor color )
{
    m_TabDefaultTextColor = color;

    for ( auto& itrTab2Btn : m_mapTab2Button )
    {
        auto pTabBtn = itrTab2Btn.second.lock();
        if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
            continue;
        }

        pTabBtn->SetCaptionColor( m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, true, m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, false, m_TabUncheckTextColor );
        pTabBtn->SetCaptionColor( AUIState::kMouseHovered, true, m_TabHoverTextColor );
        pTabBtn->Invalidate();
    }
}

void AUITabBarWidget::SetTabUncheckTextColor( SkColor color )
{
    m_TabUncheckTextColor = color;

    for ( auto& itrTab2Btn : m_mapTab2Button )
    {
        auto pTabBtn = itrTab2Btn.second.lock();
        if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
            continue;
        }

        pTabBtn->SetCaptionColor( m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, true, m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, false, m_TabUncheckTextColor );
        pTabBtn->SetCaptionColor( AUIState::kMouseHovered, true, m_TabHoverTextColor );
        pTabBtn->Invalidate();
    }
}

void AUITabBarWidget::SetTabHoverTextColor( SkColor color )
{
    m_TabHoverTextColor = color;

    for ( auto& itrTab2Btn : m_mapTab2Button )
    {
        auto pTabBtn = itrTab2Btn.second.lock();
        if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
            continue;
        }

        pTabBtn->SetCaptionColor( m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, true, m_TabDefaultTextColor );
        pTabBtn->SetCaptionColor( AUIState::kChecked, false, m_TabUncheckTextColor );
        pTabBtn->SetCaptionColor( AUIState::kMouseHovered, true, m_TabHoverTextColor );
        pTabBtn->Invalidate();
    }
}

void AUITabBarWidget::SetCurrentTab( const std::shared_ptr< AUITab >& pTab )
{
    if ( pTab == nullptr )
        return;

    const auto foundButton = m_mapTab2Button.find( pTab.get() );
    if ( foundButton == m_mapTab2Button.end() )
    {
        AUIAssertFail();
        return;
    }
    m_pCurTab = pTab;

    for ( auto& itrTab2Btn : m_mapTab2Button )
    {
        auto pTabBtn = itrTab2Btn.second.lock().get();
        if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
            continue;
        }
        if ( pTabBtn == foundButton->second.lock().get() )
        {
            pTabBtn->SetChecked( true );
        }
        else
        {
            pTabBtn->SetChecked( false );
        }
    }
}

void AUITabBarWidget::OnDraw( SkCanvas* const canvas )
{
	SuperClass::OnDraw(canvas);

	const auto rect = GetDrawBound();

	if (IsUnderLine())
	{
		SkPaint paint;
		paint.setColor(GetUnderLineColor());
		canvas->drawLine(rect.left() + 2, rect.bottom() - 4.0f, rect.right() - 2, rect.bottom() - 4.0f, paint); // 4 = 1px ¹Ø¼± °ãÄ¡´Â °Í + margin 3px
	}
}

AUITabButtonWidget* AUITabBarWidget::GetCurrentTabButton()
{
	for ( auto& itrTab2Btn : m_mapTab2Button )
	{
		auto pTabBtn = itrTab2Btn.second.lock().get();
		if ( pTabBtn == nullptr )
        {
            AUIAssertFail();
			continue;
		}
		if(pTabBtn->IsChecked())
			return pTabBtn;
	}

	return nullptr;
}
