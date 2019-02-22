#include "pch.h"
#include "MAUICalendarChangeButtonWidget.h"

using namespace mit::alice;

MAUICalendarChangeButtonWidget::MAUICalendarChangeButtonWidget(const bool& direction)
{
	SetCaptionVertAlign(AUITextVertAlign::kCenter);
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);

	m_Direction = direction;
}