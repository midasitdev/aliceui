#include "pch.h"
#include "AUIGridLayoutWidget.h"

AUIGridLayoutWidget::AUIGridLayoutWidget()
    : m_pGridLayout(std::make_shared<AUIGridLayout>())
{
    this->SetLayout(m_pGridLayout);
}

void AUIGridLayoutWidget::UpdateDivisionInfo()
{
    // Clear for now
    ClearSubWidget();

    const auto& divisionInfos = m_pGridLayout->GetAllDivisionInfo();
    for (const auto& divInfo : divisionInfos)
    {
        for (size_t idx = 0; idx < divInfo.fSubDivisionCount; ++idx)
        {
            if (idx >= divInfo.fWidgets.size())
                continue;
            AddSubWidget(divInfo.fWidgets[idx]);
        }
    }

    UpdateSize();
    UpdateChildPosition();
    Invalidate();
}

void AUIGridLayoutWidget::SetDivisionCount(const size_t count)
{
    m_pGridLayout->SetDivisionCount(count);
    this->UpdateDivisionInfo();
}

void AUIGridLayoutWidget::SetDivisionInfo(const size_t idx, const AUIGridLayout::DivisionInfo& info)
{
    m_pGridLayout->SetDivisionInfo(idx, info);
    this->UpdateDivisionInfo();
}

const AUIGridLayout::DivisionInfo& AUIGridLayoutWidget::GetDivisionInfo(const size_t idx) const
{
    return m_pGridLayout->GetDivisionInfo(idx);
}

AUIGridLayout::DivisionInfo& AUIGridLayoutWidget::GetDivisionInfo(const size_t idx)
{
    return m_pGridLayout->GetDivisionInfo(idx);
}

bool AUIGridLayoutWidget::IsHorizontal() const
{
    return m_pGridLayout->IsHorizontal();
}

void AUIGridLayoutWidget::SetHorizontal(bool horizontal)
{
    m_pGridLayout->SetHorizontal(horizontal);
    this->UpdateDivisionInfo();
}
