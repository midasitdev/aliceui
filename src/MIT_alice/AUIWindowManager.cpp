#include "pch.h"
#include "AUIWindowManager.h"

AUIWindowManager::AUIWindowManager()
{

}

AUIWindowManager::~AUIWindowManager()
{

}

void AUIWindowManager::RegisterWindow(const std::shared_ptr<AUIWindow>& pWindow)
{
    if (pWindow == nullptr)
    {
        AUIAssertFailReason("Invalid Window");
        return;
    }
    pWindow->m_LifeState.SetCurWindowManager(this);

    
}

void AUIWindowManager::UnregisterWindow(const std::shared_ptr<AUIWindow>& pWindow)
{
}
