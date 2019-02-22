#include "stdafx.h"
#include "MMainAUITitleBarWIdget.h"
#include "MAUIWindowWidget.h"
#include "MAUITitleBarTitleWidget.h"
#include "MAUILinearLayoutWidget.h"
#include "MAUIImageButtonWidget.h"
#include "MAUIImageDrawable.h"
#include "MAUIStateDrawable.h"
#include "MAUIGalleria.h"
#include "MAUITextWidget.h"

using namespace mit::alice;

namespace {
	const float DefaultTitleBarHeight = 13.0f;
	const float DefaultSystemButtonWidth = 13.0f;
	const float DefaultSystemButtonHeight = 13.0f;
}

namespace {
	const float DefaultWidth = 640.0f;
	const float DefaultHeight = 480.0f;
}

class MaximizeButtonWidget : public MAUIImageButtonWidget
{
public:
	MaximizeButtonWidget()
	{
		MAUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(L"basic_images/mini_nor.png");
		auto pDefaultDrawable = std::make_shared< MAUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(ImageStretch::Original);

		auto pHoveredIcon = galleria.GetFromResource(L"basic_images/mini_over.png");
		auto pHoveredDrawable = std::make_shared< MAUIImageDrawable >();
		pHoveredDrawable->SetImage(pHoveredIcon);
		pHoveredDrawable->SetImageStretch(ImageStretch::Original);

		auto pPressedIcon = galleria.GetFromResource(L"basic_images/mini_click.png");
		auto pPressedDrawable = std::make_shared< MAUIImageDrawable >();
		pPressedDrawable->SetImage(pPressedIcon);
		pPressedDrawable->SetImageStretch(ImageStretch::Original);

		auto pIconDrawable = std::make_shared< MAUIStateDrawable >();
		pIconDrawable->SetTrueStateDrawable(MAUIState::Default, pDefaultDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::MouseHovered, pHoveredDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::Pressed, pPressedDrawable);

		SetImageDrawable(pIconDrawable);

		SetBackgroundDrawable(std::make_shared< MAUIDrawable >());
	}
};

class CloseButtonWidget : public MAUIImageButtonWidget
{
public:
	CloseButtonWidget()
	{
		MAUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(L"basic_images/close_nor.png");
		auto pDefaultDrawable = std::make_shared< MAUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(ImageStretch::Original);

		auto pHoveredIcon = galleria.GetFromResource(L"basic_images/close_over.png");
		auto pHoveredDrawable = std::make_shared< MAUIImageDrawable >();
		pHoveredDrawable->SetImage(pHoveredIcon);
		pHoveredDrawable->SetImageStretch(ImageStretch::Original);

		auto pPressedIcon = galleria.GetFromResource(L"basic_images/close_click.png");
		auto pPressedDrawable = std::make_shared< MAUIImageDrawable >();
		pPressedDrawable->SetImage(pPressedIcon);
		pPressedDrawable->SetImageStretch(ImageStretch::Original);

		auto pIconDrawable = std::make_shared< MAUIStateDrawable >();
		pIconDrawable->SetTrueStateDrawable(MAUIState::Default, pDefaultDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::MouseHovered, pHoveredDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::Pressed, pPressedDrawable);

		SetImageDrawable(pIconDrawable);

		SetBackgroundDrawable(std::make_shared< MAUIDrawable >());
	}
};
class HideButtonWidget : public MAUIImageButtonWidget
{
public:
	HideButtonWidget()
	{
		MAUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(L"basic_images/mini_nor.png");
		auto pDefaultDrawable = std::make_shared< MAUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(ImageStretch::Original);

		auto pHoveredIcon = galleria.GetFromResource(L"basic_images/mini_over.png");
		auto pHoveredDrawable = std::make_shared< MAUIImageDrawable >();
		pHoveredDrawable->SetImage(pHoveredIcon);
		pHoveredDrawable->SetImageStretch(ImageStretch::Original);

		auto pPressedIcon = galleria.GetFromResource(L"basic_images/mini_click.png");
		auto pPressedDrawable = std::make_shared< MAUIImageDrawable >();
		pPressedDrawable->SetImage(pPressedIcon);
		pPressedDrawable->SetImageStretch(ImageStretch::Original);

		auto pIconDrawable = std::make_shared< MAUIStateDrawable >();
		pIconDrawable->SetTrueStateDrawable(MAUIState::Default, pDefaultDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::MouseHovered, pHoveredDrawable);
		pIconDrawable->SetTrueStateDrawable(MAUIState::Pressed, pPressedDrawable);

		SetImageDrawable(pIconDrawable);

		SetBackgroundDrawable(std::make_shared< MAUIDrawable >());
	}
};

MRUNTIME_IMPL_KINDOF(MMainAUITitleBarWIdget, MAUIRelativeLayoutWidget);

MMainAUITitleBarWIdget::MMainAUITitleBarWIdget() 
: MMainAUITitleBarWIdget(L""){}

MMainAUITitleBarWIdget::MMainAUITitleBarWIdget(const std::wstring& caption)
	: m_pTitle(std::make_shared< MAUITextWidget >(caption))
	, m_pCloseButton(std::make_shared< CloseButtonWidget >())
	, m_pMaximizeButton(std::make_shared< MaximizeButtonWidget>())
	, m_pMinimizeButton(std::make_shared< HideButtonWidget >())
{
	SetDefaultSize(DefaultWidth, DefaultHeight);
	SetSizePolicy(SizePolicy::Parent, SizePolicy::Parent, SizePolicy::Fixed);

// 	m_pTitleBar->SetPaddingLTRB(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_pTitleBar->SetDefaultSize(GetWidth(), DefaultTitleBarHeight);
	m_pMinimizeButton->SetDefaultSize(DefaultSystemButtonWidth, DefaultTitleBarHeight);
	m_pMaximizeButton->SetDefaultSize(DefaultSystemButtonWidth, DefaultTitleBarHeight);
	m_pCloseButton->SetDefaultSize(DefaultSystemButtonWidth, DefaultTitleBarHeight);

// 	m_pTitleBar->SetSizePolicy(SizePolicy::Parent, SizePolicy::Fixed, SizePolicy::Parent);
// 	m_pTitleBar->SetCaptionColor(ColorBlack);
// 
// 	m_pContent->SetSizePolicy(SizePolicy::Parent, SizePolicy::Fixed, SizePolicy::Parent);

	//m_pMinimizeButton->SetPosition(0, 0);
	m_pCloseButton->SetPropParentRight(true);
	m_pMaximizeButton->SetPropToLeftOf(m_pCloseButton->GetRuntimeID());
	m_pMinimizeButton->SetPropToLeftOf(m_pMaximizeButton->GetRuntimeID());

	//m_pMaximizeButton->SetPosition(0, 0);
	

	//m_pCloseButton->SetPosition(0, 0);
	

	//AddChild(m_pContent);
	//AddChild(m_pTitleBar);
	AddSubWidget(m_pCloseButton);
	AddSubWidget(m_pMaximizeButton);
	AddSubWidget(m_pMinimizeButton);


	SetPaddingLTRB(1.0f, 1.0f, 1.0f, 1.0f);
}


MMainAUITitleBarWIdget::~MMainAUITitleBarWIdget()
{
}
