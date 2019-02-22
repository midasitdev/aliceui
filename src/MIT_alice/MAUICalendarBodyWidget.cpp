#include "pch.h"
#include "MAUICalendarBodyWidget.h"

using namespace mit::alice;

MAUICalendarBodyWidget::MAUICalendarBodyWidget() noexcept
	: m_dayTable(std::make_shared< MAUICalendarTableWidget >(TableCriterion::DAY))
	, m_monthTable(std::make_shared< MAUICalendarTableWidget >(TableCriterion::MONTH))
	, m_yearTable(std::make_shared< MAUICalendarTableWidget >(TableCriterion::YEAR))
{
	Connect(m_dayTable->ReturnSignal, this, &MAUICalendarBodyWidget::ReturnData);
	Connect(m_monthTable->ReturnSignal, this, &MAUICalendarBodyWidget::ReturnData);
	Connect(m_yearTable->ReturnSignal, this, &MAUICalendarBodyWidget::ReturnData);
}

std::shared_ptr< MAUICalendarTableWidget > MAUICalendarBodyWidget::GetTable(const TableCriterion& criterion)
{
	if (criterion == TableCriterion::DAY)
		return m_dayTable;
	else if (criterion == TableCriterion::MONTH)
		return m_monthTable;
	else
		return m_yearTable;
    AUIAssertFail();
    return {};
}

void MAUICalendarBodyWidget::ReturnData(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	ReturnSignal.Send(criterion, tempType, tempYear, tempMonth, tempDay);
}