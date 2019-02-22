#include "pch.h"
#include "AUIRelativeLayoutWidget.h"
#include "AUIRelativeLayout.h"


AUIRelativeLayoutWidget::AUIRelativeLayoutWidget()
{
    this->SetLayout(std::make_shared<AUIRelativeLayout>());
}
