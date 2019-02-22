#include "pch.h"
#include "AUILayoutBase.h"
#include "AUILayoutManager.h"

AUIWidget * AUILayoutBase::GetTargetWidget() const
{
    if (nullptr == m_pLayoutManager)
        return nullptr;

    return m_pLayoutManager->GetTargetWidget();
}
