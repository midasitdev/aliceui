#include "pch.h"
#include "AUITitleBarWidget.h"
#include "AUITitleBarTitleWidget.h"
#include "AUILinearLayoutWidget.h"
#include "AUIImageButtonWidget.h"
#include "AUIImageDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIGalleria.h"
#include "AUIJsonDrawableParser.h"
#include "AUITitleBarDefaultValue.h"

static void SetSysButtonStyle(AUIImageButtonWidget* pBtn)
{
	pBtn->SetDefaultSize(TitleBar::SysButton::kWidth, TitleBar::SysButton::kHeight);
    pBtn->SetSizePolicy(TitleBar::SysButton::kWidthPolicy, TitleBar::SysButton::kHeightPolicy);
	pBtn->SetMarginLTRB(
		TitleBar::SysButton::kMarginLeft,
		TitleBar::SysButton::kMarginTop,
		TitleBar::SysButton::kMarginRight,
		TitleBar::SysButton::kMarginBottom);
}

class MaximizeButtonWidget : public AUIImageButtonWidget
{
public:
	MaximizeButtonWidget()
    {
		UpdateMaximizeState();
		//background
		AUIJsonDrawableParser parser;
		if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
			SetBackgroundDrawable(*refDrawable);

		SetSysButtonStyle(this);
	}

	virtual void OnPostMeasureSize() override
	{
		UpdateMaximizeState();
	}

private:
	void UpdateMaximizeState()
	{
		AUIGalleria galleria;
		auto pMainWnd = ::AfxGetApp()->GetMainWnd();
		if (pMainWnd && pMainWnd->GetSafeHwnd())
			m_bZoomed = ::AfxGetApp()->GetMainWnd()->IsZoomed();
		if (m_bZoomed)
			SetRestoreIcon();
		else
			SetMaximizeIcon();
	}
	bool m_bZoomed = false;

	void SetMaximizeIcon()
	{
		AUIGalleria galleria;
		auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kMaximizeIcon);
		auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
		SetImageDrawable(pDefaultDrawable);
	}

	void SetRestoreIcon()
	{
		AUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kRestoreIcon);
		auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
		SetImageDrawable(pDefaultDrawable);
	}
};

class CloseButtonWidget : public AUIImageButtonWidget
{
public:
	CloseButtonWidget()
	{
		AUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kCloseIcon);
		auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
		SetImageDrawable(pDefaultDrawable);

		//background
		AUIJsonDrawableParser parser;
		if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
			SetBackgroundDrawable(*refDrawable);

		SetSysButtonStyle(this);


        SetMarginRight(15.0f);
	}
};

class HideButtonWidget : public AUIImageButtonWidget
{
public:
	HideButtonWidget()
	{
		AUIGalleria galleria;

		auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kMinimizeIcon);
		auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
		pDefaultDrawable->SetImage(pDefaultIcon);
		pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
		SetImageDrawable(pDefaultDrawable);

		//background
		AUIJsonDrawableParser parser;
		if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
			SetBackgroundDrawable(*refDrawable);

		SetSysButtonStyle(this);
	}
};


AUITitleBarWidget::AUITitleBarWidget()
	: m_pTitleBar(std::make_shared< AUITitleBarTitleWidget >())
	, m_pMinimizeButton(std::make_shared< HideButtonWidget >())
	, m_pMaximizeButton(std::make_shared< MaximizeButtonWidget>())
	, m_pCloseButton(std::make_shared< CloseButtonWidget >())
{

	SetDefaultSize(TitleBar::kWidth, TitleBar::kHeight);
	SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);

	m_pTitleBar->SetDefaultSize(TitleBar::kWidth, TitleBar::kHeight);
	m_pTitleBar->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kFixed);
	//m_pTitleBar->SetCaptionColor(ColorBlack);



	SetVisibleSysButton();

	AddChild(m_pTitleBar);

	AddChild(m_pCloseButton);
	AddChild(m_pMaximizeButton);
	AddChild(m_pMinimizeButton);

	//SetPaddingLTRB(1.0f, 1.0f, 1.0f, 1.0f);
}

AUITitleBarWidget::~AUITitleBarWidget()
{

}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetTitleBarDblClickSignal() const
{
	return m_pTitleBar->TitleBarDblClickSignal;
}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetDragStartSignal() const
{

	return m_pTitleBar->DragPressSignal;
}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetDragEndSignal() const
{

	return m_pTitleBar->DragReleaseSignal;
}

AUISignal< void(AUIWidget* , float, float) >& AUITitleBarWidget::GetDraggingSignal() const
{

	return m_pTitleBar->DragMoveSignal;
}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetMinimizeSignal() const
{

	return m_pMinimizeButton->ClickSignal;
}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetMaximizeSignal() const
{

	return m_pMaximizeButton->ClickSignal;
}

AUISignal< void(AUIWidget* ) >& AUITitleBarWidget::GetCloseSignal() const
{

	return m_pCloseButton->ClickSignal;
}

void AUITitleBarWidget::SetTitle(const std::wstring& caption)
{
	m_pTitleBar->SetCaption(caption);

}

std::wstring AUITitleBarWidget::GetTitle() const
{
	return m_pTitleBar->GetCaption();
}

void AUITitleBarWidget::SetVisibleSysButton(SysBtnFlag sysbtnFlag)
{
	auto funcSetupButton = [](std::shared_ptr<AUIImageButtonWidget>* ppBtnBefore, const SysBtnFlag flag, const SysBtnFlag target, const std::shared_ptr<AUIImageButtonWidget>& curBtn) {
        AUIAssert(ppBtnBefore);
		if (!AUICheckEnumFlag(flag & target)) {
			curBtn->SetIgnored(true);
			return;
		}

		if (nullptr == *ppBtnBefore)
            curBtn->SetPropParentRight(true);
		else
			curBtn->SetPropToLeftOf((*ppBtnBefore)->GetRuntimeID());
        *ppBtnBefore = curBtn;
	};

    std::shared_ptr<AUIImageButtonWidget> pTmp;
    funcSetupButton(&pTmp, sysbtnFlag, SysBtnFlag::kClose, m_pCloseButton);
    funcSetupButton(&pTmp, sysbtnFlag, SysBtnFlag::kMaximize, m_pMaximizeButton);
    funcSetupButton(&pTmp, sysbtnFlag, SysBtnFlag::kMinimize, m_pMinimizeButton);
}
