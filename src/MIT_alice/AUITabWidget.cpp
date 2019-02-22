#include "pch.h"
#include "AUITabWidget.h"
#include "AUITabBarWidget.h"
#include "AUITabButtonWidget.h"
#include "AUITab.h"
#include "AUITransitionWidget.h"
#include "AUIWidgetStyle.h"


namespace
{
    constexpr SkScalar DefaultWidth = 100.0f;
    constexpr SkScalar DefaultHeight = 200.0f;
}

AUITabWidget::AUITabWidget()
    : m_pBarWidget( std::make_shared< AUITabBarWidget >() )
    , m_pContentWidget( std::make_shared< AUITransitionWidget >() )
{
    SetDefaultSize( DefaultWidth, DefaultHeight );

    AddChild( m_pBarWidget );
    AddChild( m_pContentWidget );

    Connect( m_pBarWidget->TabClickSignal, this, &AUITabWidget::TabClicked );
}

AUITabWidget::AUITabWidget(const std::shared_ptr< AUITabBarWidget >& pTabBar)
    : m_pBarWidget(pTabBar)
    , m_pContentWidget(std::make_shared< AUITransitionWidget >())
{
    AUIAssert(m_pBarWidget);

    SetDefaultSize(DefaultWidth, DefaultHeight);

    AddChild(m_pBarWidget);
    AddChild(m_pContentWidget);

    Connect(m_pBarWidget->TabClickSignal, this, &AUITabWidget::TabClicked);
}

AUITabWidget::~AUITabWidget()
{

}

void AUITabWidget::OnSetDefaultSize(const AUIScalar2& size)
{
    m_pBarWidget->SetDefaultWidth( size.fX );
    const auto barsize = m_pBarWidget->GetDefaultSize();
    m_pContentWidget->SetDefaultSize( size.fX, size.fY - barsize.fY );
}

void AUITabWidget::AddTab( const std::shared_ptr< AUITab >& pTab )
{
    if ( pTab == nullptr )
    {
        AUIAssert( false );
        return;
    }
    //AUIDebugPrint( "MAUITabWidget::AddTab : %p\n", pTab->GetWidget() );

	m_pBarWidget->AddTab(pTab);
	if (m_TabButtonStyle)
		pTab->SetButtonStyleSheet(m_TabButtonStyle);
	if (m_TabImageStyle)
		pTab->SetImageStyleSheet(m_TabImageStyle);
	if (m_TabTextStyle)
		pTab->SetTextStyleSheet(m_TabTextStyle);
    //m_arrTabs.push_back( pTab );
    //auto pTabBtn = std::make_shared< MAUITabButtonWidget >( pTab );

    //m_slotTabs.Connect( pTabBtn->ButtonReleaseSignal, this, &MAUITabWidget::TabClicked );

    //m_pBarWidget->AddSubWidget( pTabBtn );
    //m_mapTabBar2Tab.emplace( pTabBtn.get(), pTab );

    if ( m_pContentWidget->GetCurrentWidget() == nullptr )
    {
        m_pBarWidget->SetCurrentTab( pTab );
        m_pContentWidget->ReplaceWidget( pTab->GetWidget(), false );
    }
}

void AUITabWidget::RemoveTab( const std::shared_ptr< AUITab >& pTab )
{
    if ( pTab == nullptr )
    {
        AUIAssert( false );
        return;
    }
    //AUIDebugPrint( "MAUITabWidget::RemoveTab : %p\n", pTab->GetWidget() );

    m_pBarWidget->RemoveTab( pTab );

    if ( m_pContentWidget->GetCurrentWidget() == pTab->GetWidget() )
    {
        m_pBarWidget->SetCurrentTab( nullptr );
        m_pContentWidget->ReplaceWidget( nullptr, false );
    }
}

void AUITabWidget::RemoveTab( const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( pWidget == nullptr )
    {
        AUIAssert( false );
        return;
    }
    //AUIDebugPrint( "MAUITabWidget::RemoveTab : %p\n", pWidget.get() );

    m_pBarWidget->RemoveTab( pWidget );

    if ( m_pContentWidget->GetCurrentWidget() == pWidget )
    {
        m_pBarWidget->SetCurrentTab( nullptr );
        m_pContentWidget->ReplaceWidget( nullptr, false );
    }
}


bool AUITabWidget::IsHiddenTab(const std::shared_ptr< AUITab >& pTab) const
{
	if (pTab == nullptr)
	{
		AUIAssertFail();
		return true;
	}

	return m_pBarWidget->IsHiddenTab(pTab);
}

std::shared_ptr< AUITab > AUITabWidget::GetCurrentTab() const
{
	return m_pBarWidget->GetCurrentTab();
}

std::shared_ptr< AUITab > AUITabWidget::FindTabByIndex(const size_t idx) const
{

	return m_pBarWidget->FindTabByIndex(idx);
}

bool AUITabWidget::IsHiddenTab(const size_t idx) const
{
	return m_pBarWidget->IsHiddenTab(idx);
}

void AUITabWidget::HideTab( const std::shared_ptr< AUITab >& pTab, bool bHide )
{
    if ( pTab == nullptr )
    {
        AUIAssert( false );
        return;
    }

    m_pBarWidget->HideTab( pTab, bHide );
}

void AUITabWidget::SetVisibleTab(const std::shared_ptr< AUITab >& pTab, bool bVisible )
{
	if ( pTab == nullptr )
	{
		AUIAssert( false );
		return;
	}


	m_pBarWidget->SetVisibleTab(pTab, bVisible);
}

void AUITabWidget::ReplaceTab( size_t idx, const std::shared_ptr< AUITab >& pTab )
{
    //AUIDebugPrint( "MAUITabWidget::ReplaceTab : %u\n", idx );

    m_pBarWidget->ReplaceTab( idx, pTab );
    const auto doReplace = m_pBarWidget->GetCurrentTab() == pTab;
    if( doReplace )
    {
        m_pContentWidget->ReplaceWidget( pTab->GetWidget(), false );
    }
}

void AUITabWidget::ClearTab()
{
    //AUIDebugPrint( "MAUITabWidget::ClearTab \n" );

    m_pBarWidget->ClearTab();
    m_pBarWidget->SetCurrentTab( nullptr );
    m_pContentWidget->ReplaceWidget( nullptr, false );
}

void AUITabWidget::TabClicked( AUITab* const pTab )
{
    if ( pTab == nullptr )
    {
        AUIAssert( false );
        return;
    }
    m_pBarWidget->SetCurrentTab( pTab->shared_from_this() );
    m_pContentWidget->ReplaceWidget( pTab->GetWidget(), false );
}

void AUITabWidget::SetTabImageCaptionStyle( AUIImageCaptionStyle style )
{
    m_pBarWidget->SetTabStyle( style );
}

AUIImageCaptionStyle AUITabWidget::GetTabImageCaptionStyle() const
{
    return m_pBarWidget->GetTabStyle();
}

size_t AUITabWidget::GetTabCount() const
{
    return m_pBarWidget->GetTabCount();
}

void AUITabWidget::SetUnderLine(std::shared_ptr<const AUIWidgetStyle> style)
{
	std::shared_ptr<AUIStyleUpdator> pStyleUpdator;

	if (style)
		pStyleUpdator = std::make_shared<AUIStyleUpdator>(style);
	else
		return;

	auto def_style_notion = style->GetDefaultFeature();
	auto& mapNotion = def_style_notion.GetValueMap();

	for (auto itr : mapNotion)
	{
		auto& key = itr.first;
		auto& value = itr.second;

		if (key == MNV_UNDERLINE)
		{
			bool bUnderLine = false;
			if (value.GetValue(bUnderLine))
				m_pBarWidget->SetUnderLine(bUnderLine);
		}
	}
}

std::shared_ptr< AUITab > AUITabWidget::FindTabByWidget( const std::shared_ptr< AUIWidget >& pWidget ) const
{
    return m_pBarWidget->FindTabByWidget( pWidget );
}

void AUITabWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    AUIAssert( !"DO NOT USE" );

}

void AUITabWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
{

    AUIAssert( !"DO NOT USE" );
}

void AUITabWidget::PopSubWidget()
{

    AUIAssert( !"DO NOT USE" );
}

void AUITabWidget::ClearSubWidget()
{
    AUIAssert( !"DO NOT USE" );
}

std::shared_ptr< AUIWidget > AUITabWidget::FindSubWidget( size_t pos )
{
    AUIAssert( !"DO NOT USE" );
    return nullptr;
}

size_t AUITabWidget::SubWidgetCount() const 
{
    AUIAssert( !"DO NOT USE" );
    return 0;
}

void AUITabWidget::SetHeaderStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	m_pBarWidget->SetStyleSheet(style);
}

void AUITabWidget::SetHeaderTabButtonStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	const auto& tabs = m_pBarWidget->GetTabs();
	m_TabButtonStyle = style;

	SetUnderLine(style);

	for (int i=0; i<tabs.size(); i++)
	{
		if (i == 0)
			tabs[i]->SetFirst();
		else if (i == tabs.size() - 1)
			tabs[i]->SetLast();

		tabs[i]->SetButtonStyleSheet(style);
	}
}

void AUITabWidget::SetHeaderTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	const auto& tabs = m_pBarWidget->GetTabs();
	m_TabTextStyle = style;
	for (auto& tab : tabs)
		tab->SetTextStyleSheet(style);

}

void AUITabWidget::SetHeaderImageStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	const auto& tabs = m_pBarWidget->GetTabs();
	m_TabImageStyle = style;
	for (auto& tab : tabs)
		tab->SetImageStyleSheet(style);
}
