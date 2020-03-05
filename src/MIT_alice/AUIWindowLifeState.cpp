#include "pch.h"
#include "AUIWindowLifeState.h"


AUIWindowLifeState::AUIWindowLifeState() noexcept
{
    ResetWindowManagers();
}

void AUIWindowLifeState::ResetWindowManagers() noexcept
{
    m_pCurWindowManager = nullptr;
}

