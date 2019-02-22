#include "pch.h"
#include "AUIFlowLayoutWidget.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIFlowLayout.h"

AUIFlowLayoutWidget::AUIFlowLayoutWidget()
    : m_pFlowLayout(std::make_shared<AUIFlowLayout>())
{
    this->SetLayout(m_pFlowLayout);
}

AUIFlowLayoutWidget::AUIFlowLayoutWidget(bool horizontal)
    : m_pFlowLayout(std::make_shared<AUIFlowLayout>(horizontal))
{
    this->SetLayout(m_pFlowLayout);
}

void AUIFlowLayoutWidget::SetHorizontal(bool horizontal)
{
    m_pFlowLayout->SetHorizontal(horizontal);
    UpdateSize();
    UpdateChildPosition();
    Invalidate();

}

bool AUIFlowLayoutWidget::IsHorizontal() const
{
    return m_pFlowLayout->IsHorizontal();
}
