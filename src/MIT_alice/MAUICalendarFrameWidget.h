#pragma once


#include "AUIWindow.h"
#include "MAUICalendarChangeButtonWidget.h"
#include "MAUICalendarQuickButtonWidget.h"
#include "MAUICalendarBodyWidget.h"

namespace mit::alice
{
    class ALICEUI_API MAUICalendarFrameWidget : public AUILinearLayoutWidget
    {
        // function
    public:
        MAUICalendarFrameWidget() noexcept;
        ~MAUICalendarFrameWidget() override = default;

        int32_t GetYear() { return m_Year; }
        int32_t GetMonth() { return static_cast<int32_t>(m_Month) + 1; }
        int32_t GetDay() { return m_Day; }
        void SetYear(int32_t tempYear) { m_Year = tempYear; }
        void SetMonth(int32_t tempMonth) { m_Month = static_cast<mit::i18n::MICUMonths>(tempMonth - 1); }
        void SetDay(int32_t tempDay) { m_Day = tempDay; }
        void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
        void SetFocus(const int& iYear, const int& iMonth);

    private:
        void SetTableData(const TableCriterion& criterion);
        void SetQuickCaption(const std::wstring& quickCaption) { m_Quick->SetCaption(quickCaption); }
        void OnClickUBtn(AUIWidget*);
        void OnClickDBtn(AUIWidget*);
        void OnClickDate(TableCriterion criterion, MonthType tempType, int tempYear, int tempMonth, int tempDay);
        void OnClickQuickBtn(const TableCriterion& criterion);
        // variable
    public:
        AUISignal<void(MAUICalendarFrameWidget*)> UserEventSignal;

    private:
        std::shared_ptr< mit::i18n::MICUCalendar > m_pPImpl;
        std::shared_ptr< AUILinearLayoutWidget > m_Header;
        std::shared_ptr < MAUICalendarQuickButtonWidget > m_Quick;
        std::shared_ptr< MAUICalendarBodyWidget > m_Body;
        std::shared_ptr< MAUICalendarChangeButtonWidget > m_UBtn;
        std::shared_ptr< MAUICalendarChangeButtonWidget > m_DBtn;

        int32_t m_Year;
        mit::i18n::MICUMonths m_Month;
        int32_t m_Day;
        mit::i18n::MICUDaysOfWeek m_FirstDayOfWeek; // 시작하는 요일
        int32_t m_MaximumOfMonth; // 그 달의 날짜 수
    };

}