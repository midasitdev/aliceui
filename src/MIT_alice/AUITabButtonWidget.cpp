#include "pch.h"
#include "AUITabButtonWidget.h"
#include "AUITab.h"
#include "AUIDrawable.h"
#include "AUIShapeDrawable.h"
#include "AUIRoundRectShape.h"
#include "AUILayerDrawable.h"
#include "AUIStateDrawable.h"
#include "AUITextWidget.h"

AUITabButtonWidget::AUITabButtonWidget()
{
	SetCheckable(true);
	GetCaptionWidget()->SetCheckable(true);
	GetImageWidget()->SetCheckable(true);
	SetImageMarginLTRB(4.0f, 4.0f, 4.0f, 4.0f);
	SetCaptionColor(AUIState::kDefault, true, SkColorSetRGB(152, 152, 152));
	SetCaptionColor(AUIState::kDefault, false, SkColorSetRGB(152, 152, 152));
	SetCaptionColor(AUIState::kChecked, true, SkColorSetRGB(63, 63, 63));
	SetCaptionColor(AUIState::kMouseHovered, true, SkColorSetRGB(107, 127, 145));
	SetCaptionColor(AUIState::kPressed, true, SkColorSetRGB(152, 152, 152));

	SetCaptionVertAlign(AUITextVertAlign::kCenter);
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
}

AUITabButtonWidget::~AUITabButtonWidget()
{

}

void AUITabButtonWidget::InitializeTab(const std::shared_ptr< AUITab >& pTab)
{
	m_pTab = pTab;

	AUIAssert(pTab);

	SetCaption(pTab->GetName());
	SetImageDrawable(pTab->GetIcon());

	OnInitializeTab(pTab);
}

void AUITabButtonWidget::OnInitializeTab(const std::shared_ptr< AUITab >& pTab)
{

}

void AUITabButtonWidget::OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value)
{
	if (GetTab()->GetFirst() && uiKey == MNV_BACKGROUND_IMAGE_TOP)
	{
		std::shared_ptr<AUIDrawable> pDrawable;
		if (value.GetValue(pDrawable))
			SetBackgroundDrawable(pDrawable);
	}
	else if (GetTab()->GetLast() && uiKey == MNV_BACKGROUND_IMAGE_BOTTOM)
	{
		std::shared_ptr<AUIDrawable> pDrawable;
		if (value.GetValue(pDrawable))
			SetBackgroundDrawable(pDrawable);
	}
	else if (!GetTab()->GetLast() && !GetTab()->GetFirst() && (uiKey == MNV_BACKGROUND_IMAGE_MID || uiKey == MNV_BACKGROUND_IMAGE))
	{
		std::shared_ptr<AUIDrawable> pDrawable;
		if (value.GetValue(pDrawable))
			SetBackgroundDrawable(pDrawable);
	}
	else
		AUIImageCaptionButtonWidget::OnSetStyleNotion(uiKey, value);
}
