#include "pch.h"
#include "MAUICalendarQuickButtonWidget.h"

using namespace mit::alice;

MAUICalendarQuickButtonWidget::MAUICalendarQuickButtonWidget(const TableCriterion& criterion, const std::wstring& val)
{
	m_Criterion = criterion;
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
	SetCaption(val);
}

bool MAUICalendarQuickButtonWidget::OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag)
{
	if (m_Criterion == TableCriterion::DAY)
		m_Criterion = TableCriterion::MONTH;
	else if (m_Criterion == TableCriterion::MONTH)
		m_Criterion = TableCriterion::YEAR;

	BodyChangeUpSignal.Send(m_Criterion);
	return true;
}

void MAUICalendarQuickButtonWidget::DownCriterion(const TableCriterion& criterion)
{
	if (criterion == TableCriterion::MONTH)
		m_Criterion = TableCriterion::DAY;
	else if (criterion == TableCriterion::YEAR)
		m_Criterion = TableCriterion::MONTH;
}
