#pragma once


#include "MAUICalendarRowWidget.h"
#include "AUILinearLayoutWidget.h"
#include "../MIT_i18n/MICUCommonDef.h"
#include "MAUICalendarCommonDef.h"

namespace mit::alice
{
    class ALICEUI_API MAUICalendarTableWidget : public AUILinearLayoutWidget
    {
        // function
    public:
        MAUICalendarTableWidget(TableCriterion criterion);
        ~MAUICalendarTableWidget() override = default;
        void SetTableData(const TableCriterion& criterion, const int32_t& tempYear, const mit::i18n::MICUMonths& tempMonth,
            const mit::i18n::MICUDaysOfWeek& tempFirstDay, const int32_t& tempMaximum);
        void SetYearData(const TableCriterion& criterion, const int& year);
        void SetDecadeData(const TableCriterion& criterion, const int& year);
        void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
    protected:

    private:
        void ReturnData(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay);

        // variable
    public:
        AUISignal<void(TableCriterion, MonthType, int, int, int)> ReturnSignal;
    private:
        std::vector< std::shared_ptr< MAUICalendarRowWidget > > m_vpTable;
    };
}
