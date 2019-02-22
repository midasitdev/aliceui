#pragma once

#include "AUIButtonWidget.h"

namespace mit::alice
{
    class ALICEUI_API MAUICalendarChangeButtonWidget : public AUIButtonWidget
    {
        // function
    public:
        MAUICalendarChangeButtonWidget(const bool& direction);
        ~MAUICalendarChangeButtonWidget() override = default;
    protected:

    private:

        // variable
    public:
    private:
        bool m_Direction;
    };
}
