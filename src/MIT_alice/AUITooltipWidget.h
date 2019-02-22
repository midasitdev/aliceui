#pragma once


#include "AUILinearLayoutWidget.h"

class AUITooltip;

class ALICEUI_API AUITooltipWidget : public AUILinearLayoutWidget
{
public:
    AUITooltipWidget();
    virtual ~AUITooltipWidget();


    //////////////////////////////////////////////////////////////////////////
    // Set
public:
    void SetData(const std::shared_ptr< AUITooltip >& pTooltip);
private:
    std::shared_ptr< AUITooltip > m_pTooltip;
};
