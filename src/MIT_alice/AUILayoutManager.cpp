#include "pch.h"
#include "AUILayoutManager.h"
#include "AUILayoutBase.h"

void AUILayoutManager::SetLayout(const std::shared_ptr<AUILayoutBase>& pLayout)
{
    if (m_pLayout)
        m_pLayout->m_pLayoutManager = nullptr;
    if (pLayout)
        pLayout->m_pLayoutManager = this;
    m_pLayout = pLayout;
}

bool AUILayoutManager::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    if (nullptr == m_pLayout)
        return false;

    m_pLayout->OnMeasureSize(width, widthSpec, height, heightSpec);
    return true;
}

bool AUILayoutManager::OnUpdateChildPosition()
{
    if (nullptr == m_pLayout)
        return false;

    m_pLayout->OnUpdateChildPosition();
    return true;
}

bool AUILayoutManager::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
    if (nullptr == m_pLayout)
        return false;

    m_pLayout->OnTickTime(prevTime, curTime);
    return true;
}
