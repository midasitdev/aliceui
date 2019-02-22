#include "pch.h"

#include "MAUICalendarTableWidget.h"

using namespace mit::alice;
using namespace mit::i18n;

MAUICalendarTableWidget::MAUICalendarTableWidget(TableCriterion criterion)
	: AUILinearLayoutWidget(false)
{
	SetMarginLeft(5.0f);
	if (criterion == TableCriterion::DAY)
	{
		auto tempDayOfWeek = std::make_shared< MAUICalendarRowWidget >(); // ¿äÀÏ
		tempDayOfWeek->SetMarginBottom(1.0f);
		m_vpTable.emplace_back(tempDayOfWeek);
		AddSubWidget(m_vpTable[0]);

		for (int i = 1; i < 7; i++)
		{
			auto tempRow = std::make_shared< MAUICalendarRowWidget >(criterion);
			if (i != 6)
				tempRow->SetMarginBottom(1.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &MAUICalendarTableWidget::ReturnData);
		}
	}
	else if (criterion == TableCriterion::MONTH)
	{
		for (int i = 0; i < 3; i++)
		{
			auto tempRow = std::make_shared< MAUICalendarRowWidget >(criterion);
			if (i != 2)
				tempRow->SetMarginBottom(4.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &MAUICalendarTableWidget::ReturnData);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			auto tempRow = std::make_shared< MAUICalendarRowWidget >(criterion);
			if (i != 2)
				tempRow->SetMarginBottom(4.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &MAUICalendarTableWidget::ReturnData);
		}
	}
}

void MAUICalendarTableWidget::SetTableData(const TableCriterion& criterion, const int32_t& tempYear, const mit::i18n::MICUMonths& tempMonth, const mit::i18n::MICUDaysOfWeek& tempFirstDay, const int32_t& tempMaximum)
{
	for (int i = 1; i < 7; i++)
		m_vpTable[i]->SetTableData(criterion, tempYear, tempMonth, tempFirstDay, tempMaximum, i);
}

void MAUICalendarTableWidget::SetYearData(const TableCriterion& criterion, const int& year)
{
	for (int i = 0; i < 3; i++)
		m_vpTable[i]->SetYearData(criterion, year, i);
}

void MAUICalendarTableWidget::SetDecadeData(const TableCriterion& criterion, const int& year)
{
	for (int i = 0; i < 3; i++)
		m_vpTable[i]->SetDecadeData(criterion, year, i);
}


void MAUICalendarTableWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	for (int i = 1; i < 7; i++)
		m_vpTable[i]->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void MAUICalendarTableWidget::ReturnData(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	ReturnSignal.Send(criterion, tempType, tempYear, tempMonth, tempDay);
}