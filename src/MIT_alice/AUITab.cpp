#include "pch.h"
#include "AUITab.h"
#include "AUIImageDrawable.h"
#include "AUITabButtonWidget.h"
#include "AUITextWidget.h"


AUITab::AUITab()
{
	m_bFirst = false;
	m_bLast = false;
}

AUITab::~AUITab()
{

}

std::shared_ptr< AUITab > AUITab::CreateTab( const std::shared_ptr< AUIWidget >& pWidget )
{
    auto pTab = std::make_shared< AUITab >();
    pTab->SetWidget( pWidget );
    return pTab;
}

std::shared_ptr< AUITab > AUITab::CreateTab( const std::wstring& name, const std::shared_ptr< AUIWidget >& pWidget )
{
    auto pTab = std::make_shared< AUITab >();
    pTab->SetName( name );
    pTab->SetWidget( pWidget );
    return pTab;
}

std::shared_ptr< AUITab > AUITab::CreateTab( const std::wstring& name, const sk_sp<SkImage>& pIcon, const std::shared_ptr< AUIWidget >& pWidget )
{
    auto pTab = std::make_shared< AUITab >();
    pTab->SetName( name );
    auto pImageDrawable = std::make_shared< AUIImageDrawable >();
    pImageDrawable->SetImage( pIcon );
    pImageDrawable->SetImageStretch( AUIImageStretch::kOriginal );
    pTab->SetIcon( pImageDrawable );
    pTab->SetWidget( pWidget );
    return pTab;
}

std::shared_ptr< AUITab > AUITab::CreateTab( const std::wstring& name, const std::shared_ptr< AUIDrawable >& pIcon, const std::shared_ptr< AUIWidget >& pWidget )
{
    auto pTab = std::make_shared< AUITab >();
    pTab->SetName( name );
    pTab->SetIcon( pIcon );
    pTab->SetWidget( pWidget );
    return pTab;
}

std::shared_ptr< AUITab > AUITab::CreateTab( const std::shared_ptr< AUIWidget >& pTabButtonWidget, const std::shared_ptr< AUIWidget >& pContentWidget )
{
    auto pTab = std::make_shared< AUITab >();
    pTab->SetTabButtonWidget( pTabButtonWidget );
    pTab->SetWidget( pContentWidget );
    return pTab;
}

void AUITab::SetIcon( const std::shared_ptr< AUIDrawable >& pIcon )
{
    m_pIcon = pIcon;
}

void AUITab::SetButtonStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	if (auto pBtnWidget = GetTabButtonWidget())
	{
		pBtnWidget->SetStyleSheet(style);
	}
}

void AUITab::SetTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	if (auto pBtnWidget = GetTabButtonWidget())
	{
		if (auto pTabBtn = pBtnWidget->DynCast<AUITabButtonWidget>())
		{
			pTabBtn->GetImageWidget()->SetStyleSheet(style);
		}
	}

}

void AUITab::SetImageStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
	if (auto pBtnWidget = GetTabButtonWidget())
	{
		if (auto pTabBtn = pBtnWidget->DynCast<AUITabButtonWidget>())
		{
			pTabBtn->GetCaptionWidget()->SetStyleSheet(style);
		}
	}
}
