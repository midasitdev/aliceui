#include "pch.h"
#include "MAUICalendarFoldButton.h"

using namespace mit::alice;

MAUICalendarFoldButton::MAUICalendarFoldButton() noexcept
	: m_pCalendar( std::make_shared< MAUICalendarFrameWidget >() )
	, m_bFold( true )
	, m_Date( L"Calendar" )
{
	SetCaption(m_Date);
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);

	SetPopupWidget(m_pCalendar);
	SetPopupPosition(glm::vec3(0.0f, GetHeight() + 25.0f, 0.0f));

	Connect(m_pCalendar->UserEventSignal, this, &MAUICalendarFoldButton::OnUserEvent);
}

bool MAUICalendarFoldButton::OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag)
{
	FoldCalendar();
	return true;
}

void MAUICalendarFoldButton::FoldCalendar()
{
	m_bFold = !m_bFold;

	if (m_bFold)
		Dismiss();
	else
	{
		Invoke(GetWidgetManager(), shared_from_this());
		m_pCalendar->SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kContent);
	}
}

void MAUICalendarFoldButton::OnUserEvent(MAUICalendarFrameWidget* pCal)
{
	int tempYear;
	int tempMonth;
	int tempDay;

	tempYear = pCal->GetYear();
	tempMonth = pCal->GetMonth();
	tempDay = pCal->GetDay();

	UserEventSignal.Send(tempYear, tempMonth, tempDay);
	FoldCalendar();
}

void MAUICalendarFoldButton::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	m_pCalendar->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void MAUICalendarFoldButton::SetFocus(const int& iYear, const int& iMonth)
{
	m_pCalendar->SetFocus(iYear, iMonth);
}
