#include "pch.h"
#include "AUIAbsoluteLayoutWidget.h"
#include "AUIAbsoluteLayout.h"

AUIAbsoluteLayoutWidget::AUIAbsoluteLayoutWidget()
{
    this->SetLayout(std::make_shared<AUIAbsoluteLayout>());
}
