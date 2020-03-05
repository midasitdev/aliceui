#pragma once

#include "AUIAPIDef.h"

class AUIWindowManager;

class ALICEUI_API AUIWindowLifeState final
{
public:
    AUIWindowLifeState() noexcept;
    ~AUIWindowLifeState() = default;

public:
    void ResetWindowManagers() noexcept;
    AUIWindowManager* GetCurWindowManager() const noexcept
    {
        return m_pCurWindowManager;
    }
    void SetCurWindowManager(AUIWindowManager* pWindowManager) noexcept
    {
        m_pCurWindowManager = pWindowManager;
    }

private:
    AUIWindowManager* m_pCurWindowManager = nullptr;
};