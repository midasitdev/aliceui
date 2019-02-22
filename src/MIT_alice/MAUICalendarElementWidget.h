#pragma once


#include "AUIButtonWidget.h"
#include "AUIJsonDrawableParser.h"
#include "AUINinePatchDrawable.h"
#include "AUIStateDrawable.h"
#include "MAUICalendarCommonDef.h"

#include "..\MIT_i18n\MICUCommonDef.h"
#include "..\MIT_i18n\MICUCalendar.h"

namespace mit::alice
{
    class ALICEUI_API MAUICalendarElementWidget : public AUIButtonWidget
    {
        // function
    public:
        MAUICalendarElementWidget(const std::wstring& dayofWeek);
        MAUICalendarElementWidget(TableCriterion criterion, const int& val);
        ~MAUICalendarElementWidget() override = default;

        void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
        void SetTableData(const TableCriterion& criterion, const int32_t& tempYear, const mit::i18n::MICUMonths& tempMonth,
            const mit::i18n::MICUDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek, const int32_t& tempDay);
        void SetYearData(const TableCriterion& criterion, const int& tempYear, const int& tempMonth);
        void SetDecadeData(const TableCriterion& criterion, const int& tempYear);
    protected:
        virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    private:
        // variable
    public:
        AUISignal<void(TableCriterion, MonthType, int, int, int)> ReturnSignal;

    private:
        TableCriterion m_Criterion = TableCriterion::DAY;
        MonthType m_MonthType = MonthType::THISMONTH;
        int m_Year = 2000;
        int m_Month = 1;
        int m_Day = 1;

        int m_iStartYear = -1;
        int m_iStartMonth = -1;
        int m_iStartDay = -1;
        int m_iEndYear = -1;
        int m_iEndMonth = -1;
        int m_iEndDay = -1;
    };

}
