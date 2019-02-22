#include "pch.h"
#include "AUIFrameLayoutWidget.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIFrameLayout.h"

AUIFrameLayoutWidget::AUIFrameLayoutWidget()
{
    this->SetLayout(std::make_shared<AUIFrameLayout>());
}
