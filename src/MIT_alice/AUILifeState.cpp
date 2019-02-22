#include "pch.h"
#include "AUILifeState.h"


AUILifeState::AUILifeState() noexcept
{
    Reset();
}

AUILifeState::AUILifeState(const AUILifeState& state) noexcept
{
    m_pCurWidgetManager = state.m_pCurWidgetManager;
    m_pPendingCreateWidgetManager = state.m_pPendingCreateWidgetManager;
    m_pPendingDestroyWidgetManager = state.m_pPendingDestroyWidgetManager;
    m_States = state.m_States;
}

void AUILifeState::Reset()
{
    ResetWidgetManagers();
    ResetCurInstance();
    ResetState();
}

void AUILifeState::ResetWidgetManagers() noexcept
{
    m_pCurWidgetManager = nullptr;
    m_pPendingCreateWidgetManager = nullptr;
    m_pPendingDestroyWidgetManager = nullptr;
}

void AUILifeState::ResetCurInstance() noexcept
{
    m_wpCurInstance.reset();
}
