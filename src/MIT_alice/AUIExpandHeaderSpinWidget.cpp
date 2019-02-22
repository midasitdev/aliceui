#include "pch.h"
#include "AUIExpandHeaderSpinWidget.h"
#include "AUIColor.h"
#include "AUIColorDrawable.h"
#include "AUIExpandToggleDrawable.h"


AUIExpandHeaderSpinWidget::AUIExpandHeaderSpinWidget()
{
    SetCheckable(true);
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetDefaultSize(20.0f, 20.0f);

    SetBackgroundDrawable(std::make_shared< AUIExpandToggleDrawable >());
}

AUIExpandHeaderSpinWidget::~AUIExpandHeaderSpinWidget()
{

}
