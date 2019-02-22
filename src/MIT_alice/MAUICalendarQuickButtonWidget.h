#pragma once


#include "AUIButtonWidget.h"
#include "MAUICalendarCommonDef.h"

namespace mit::alice
{
    class ALICEUI_API MAUICalendarQuickButtonWidget : public AUIButtonWidget
    {
        // function
    public:
        MAUICalendarQuickButtonWidget(const TableCriterion& criterion, const std::wstring& val);
        ~MAUICalendarQuickButtonWidget() override = default;

        void DownCriterion(const TableCriterion& criterion);

    protected:
        virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;

        // variable
    public:
        AUISignal<void(const TableCriterion&)> BodyChangeUpSignal;
    private:
        TableCriterion m_Criterion;
    };
}
