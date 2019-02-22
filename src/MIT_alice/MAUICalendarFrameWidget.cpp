#include "pch.h"
#include "MAUICalendarFrameWidget.h"
#include "..\MIT_i18n\MICUDateFormatSymbols.h"
#include "..\MIT_i18n\MICULocale.h"

using namespace mit::alice;
using namespace mit::i18n;

MAUICalendarFrameWidget::MAUICalendarFrameWidget() noexcept
	: AUILinearLayoutWidget( false )
	, m_pPImpl( std::make_shared< MICUCalendar >() )
	, m_Header( std::make_shared< AUILinearLayoutWidget >( true ) )
	, m_Quick( std::make_shared< MAUICalendarQuickButtonWidget >( TableCriterion::DAY, L"Calendar" ) )
	, m_Body( std::make_shared< MAUICalendarBodyWidget >() )
	, m_UBtn( std::make_shared< MAUICalendarChangeButtonWidget >( true ) ) // Up
	, m_DBtn( std::make_shared< MAUICalendarChangeButtonWidget >( false ) ) // Down
	, m_Day( 1 )
{
	SetDefaultSize(228.0f, 195.0f);
	m_Header->SetMarginLTRB(5.0f, 3.0f, 5.0f, 3.0f);
	m_Header->SetDefaultSize(218.0f, 20.0f);
	m_Quick->SetDefaultSize(100.0f, 20.0f);
	m_Quick->SetMarginRight(55.0f);
	m_UBtn->SetDefaultSize(30.0f, 20.0f);
	m_UBtn->SetMarginRight(1.0f);
	m_UBtn->SetCaption(L"▲");
	m_DBtn->SetDefaultSize(30.0f, 20.0f);
	m_DBtn->SetCaption(L"▼");

	m_Header->AddSubWidget(m_Quick);
	m_Header->AddSubWidget(m_UBtn);
	m_Header->AddSubWidget(m_DBtn);

	m_Year = m_pPImpl->GetYear();
	m_Month = m_pPImpl->GetMonth();

	m_pPImpl->Set(m_Year, m_Month, m_Day);
	m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
	m_MaximumOfMonth = m_pPImpl->GetActualMaximum(MICUDateFields::kDate);

	Connect(m_UBtn->ClickSignal, this, &MAUICalendarFrameWidget::OnClickUBtn);
	Connect(m_DBtn->ClickSignal, this, &MAUICalendarFrameWidget::OnClickDBtn);
	Connect(m_Body->ReturnSignal, this, &MAUICalendarFrameWidget::OnClickDate);
	Connect(m_Quick->BodyChangeUpSignal, this, &MAUICalendarFrameWidget::OnClickQuickBtn);

	SetTableData(TableCriterion::DAY);
	m_Body->SetTable(TableCriterion::DAY);
	AddSubWidget(m_Header);
	AddSubWidget(m_Body->GetTable(TableCriterion::DAY));
}

void MAUICalendarFrameWidget::SetTableData(const TableCriterion& criterion)
{
	m_Body->SetTable(criterion);
	
	if (criterion == TableCriterion::DAY)
	{
		MICULocale locale;
		locale.SetDefault();
		MICUDateFormatSymbols dfmtsym(locale);
		const auto wsMonth = dfmtsym.GetShortMonths();
		auto text = wsMonth[MonthToNumber(m_Month) - 1] + L" " + std::to_wstring(m_Year);
		SetQuickCaption(text);

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(MICUDateFields::kDate);
		m_Body->GetTable(criterion)->SetTableData(criterion, m_Year, m_Month, m_FirstDayOfWeek, m_MaximumOfMonth);
	}
	else if (criterion == TableCriterion::MONTH)
	{
		auto text = std::to_wstring(m_Year);
		SetQuickCaption(text);
		m_Body->GetTable(criterion)->SetYearData(criterion, m_Year);
	}
	else if (criterion == TableCriterion::YEAR)
	{
		auto frontYear = m_Year / 10 * 10;
		auto behindYear = frontYear + 9;
		auto text = std::to_wstring(frontYear) + L" ~ " + std::to_wstring(behindYear);
		SetQuickCaption(text);
		m_Body->GetTable(criterion)->SetDecadeData(criterion, m_Year);
	}

	Invalidate();
	InvalidateChildren();
}

void MAUICalendarFrameWidget::OnClickUBtn(AUIWidget*)
{
	if (m_Body->GetPresentState() == TableCriterion::DAY)
	{
		if (m_Month == MICUMonths::kDecember)
		{
			m_Month = MICUMonths::kJanuary;
			m_Year++;
		}
		else
		{
			auto tempMonth = static_cast<int>(m_Month);
			m_Month = static_cast<MICUMonths>(tempMonth + 1);
		}

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(MICUDateFields::kDate);

		SetTableData(TableCriterion::DAY);
	}
	else if (m_Body->GetPresentState() == TableCriterion::MONTH)
	{
		m_Year++;
		SetTableData(TableCriterion::MONTH);
	}
	else if (m_Body->GetPresentState() == TableCriterion::YEAR)
	{
		m_Year += 10;
		SetTableData(TableCriterion::YEAR);
	}
}

void MAUICalendarFrameWidget::OnClickDBtn(AUIWidget*)
{
	if (m_Body->GetPresentState() == TableCriterion::DAY)
	{
		if (m_Month == MICUMonths::kJanuary)
		{
			m_Month = MICUMonths::kDecember;
			m_Year--;
		}
		else
		{
			auto tempMonth = static_cast<int>(m_Month);
			m_Month = static_cast<MICUMonths>(tempMonth - 1);
		}

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(MICUDateFields::kDate);

		SetTableData(TableCriterion::DAY);
	}
	else if (m_Body->GetPresentState() == TableCriterion::MONTH)
	{
		m_Year--;
		SetTableData(TableCriterion::MONTH);
	}
	else if (m_Body->GetPresentState() == TableCriterion::YEAR)
	{
		m_Year -= 10;
		SetTableData(TableCriterion::YEAR);
	}
}

void MAUICalendarFrameWidget::OnClickDate(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	if (criterion == TableCriterion::DAY)
	{
		if (tempType == MonthType::NEXTMONTH) // 다음 달
			OnClickUBtn(nullptr);
		else if (tempType == MonthType::LASTMONTH) // 지난 달
			OnClickDBtn(nullptr);

		SetYear(tempYear);
		SetMonth(tempMonth);
		SetDay(tempDay);

		UserEventSignal.Send(this);
	}
	else if (criterion == TableCriterion::MONTH)
	{
		SetYear(tempYear);
		SetMonth(tempMonth);

		DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
		SetTableData(TableCriterion::DAY);
		AddSubWidget(m_Body->GetTable(TableCriterion::DAY));
	}
	else if (criterion == TableCriterion::YEAR)
	{
		SetYear(tempYear);

		DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
		SetTableData(TableCriterion::MONTH);
		AddSubWidget(m_Body->GetTable(TableCriterion::MONTH));
	}

	m_Quick->DownCriterion(criterion);
}

void MAUICalendarFrameWidget::OnClickQuickBtn(const TableCriterion& criterion)
{
	DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
	SetTableData(criterion);
	AddSubWidget(m_Body->GetTable(criterion));
}

void MAUICalendarFrameWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	m_Body->GetTable(TableCriterion::DAY)->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void MAUICalendarFrameWidget::SetFocus(const int& iYear, const int& iMonth)
{
	m_Year = iYear;
	m_Month = static_cast<MICUMonths>(iMonth - 1);
	m_Day = 1;

	DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
	SetTableData(TableCriterion::DAY);
	AddSubWidget(m_Body->GetTable(TableCriterion::DAY));
}