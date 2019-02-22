#pragma once


#include "AUIButtonWidget.h"
#include "MAUICalendarFrameWidget.h"
#include "AUIPopup.h"

namespace mit::alice
{

    class MAUICalendarFrameWidget;
    class ALICEUI_API MAUICalendarFoldButton : public AUIButtonWidget, public AUIPopup
    {
    public:
        MAUICalendarFoldButton() noexcept;
        ~MAUICalendarFoldButton() override = default;
        void SetDate(const std::wstring& tempDate) { m_Date = tempDate; SetCaption(m_Date); }
        void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
        void SetFocus(const int& iYear, const int& iMonth);

    protected:
        virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    private:
        void OnUserEvent(MAUICalendarFrameWidget*);
        void FoldCalendar();
        ////////////////////////////////////////////////////////////////////////////////////////////////
    public:
        AUISignal<void(const int, const int, const int) > UserEventSignal;

    private:
        bool m_bFold;
        std::wstring m_Date;
        std::shared_ptr<MAUICalendarFrameWidget> m_pCalendar;
    };
}
