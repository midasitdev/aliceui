#pragma once


#include "AUILinearLayoutWidget.h"
#include "MAUICalendarElementWidget.h"


namespace mit::alice
{
    class ALICEUI_API MAUICalendarRowWidget : public AUILinearLayoutWidget
    {
        // function
    public:
        MAUICalendarRowWidget();
        MAUICalendarRowWidget(TableCriterion criterion);
        ~MAUICalendarRowWidget() override = default;

        void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
        void SetTableData(const TableCriterion& criterion, const int32_t& tempYear, const mit::i18n::MICUMonths& tempMonth,
            const mit::i18n::MICUDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek);
        void SetYearData(const TableCriterion& criterion, const int& year, const int& temp);
        void SetDecadeData(const TableCriterion& criterion, const int& year, const int& temp);
    protected:

    private:
        void ReturnData(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay);
        // variable
    public:
        AUISignal<void(TableCriterion, MonthType, int, int, int)> ReturnSignal;
    private:
        std::vector< std::shared_ptr< MAUICalendarElementWidget > > m_vpRow;
    };
}

