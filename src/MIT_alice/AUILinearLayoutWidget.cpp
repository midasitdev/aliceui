#include "pch.h"
#include "AUILinearLayoutWidget.h"
#include "AUIInnerGroupWidget.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIApplication.h"
#include "AUILinearLayout.h"

AUILinearLayoutWidget::AUILinearLayoutWidget()
    : m_pLinearLayout(std::make_shared<AUILinearLayout>())
{
    this->SetLayout(m_pLinearLayout);
}

AUILinearLayoutWidget::AUILinearLayoutWidget(bool horizontal)
    : m_pLinearLayout(std::make_shared<AUILinearLayout>(horizontal))
{
    this->SetLayout(m_pLinearLayout);
}

bool AUILinearLayoutWidget::IsHorizontal() const
{
    return m_pLinearLayout->IsHorizontal();
}

void AUILinearLayoutWidget::SetHorizontal( bool horizontal )
{
    m_pLinearLayout->SetHorizontal(horizontal);
    UpdateSize();
    UpdateChildPosition();
    Invalidate();
}
