#pragma once

#include "MAUICalendarTableWidget.h"


namespace mit::alice
{
    class ALICEUI_API MAUICalendarBodyWidget : public AUIWidget
    {
    public:
        MAUICalendarBodyWidget() noexcept;
        ~MAUICalendarBodyWidget() override = default;

        std::shared_ptr< MAUICalendarTableWidget > GetTable(const TableCriterion& criterion);
        void SetTable(const TableCriterion& criterion) { m_Criterion = criterion; }
        TableCriterion GetPresentState() { return m_Criterion; }
    private:
        void ReturnData(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay);

    public:
        AUISignal< void(TableCriterion, MonthType, int, int, int) > ReturnSignal;

    private:
        std::shared_ptr< MAUICalendarTableWidget > m_dayTable;
        std::shared_ptr< MAUICalendarTableWidget > m_monthTable;
        std::shared_ptr< MAUICalendarTableWidget > m_yearTable;

        TableCriterion m_Criterion = TableCriterion::DAY;
    };

}
