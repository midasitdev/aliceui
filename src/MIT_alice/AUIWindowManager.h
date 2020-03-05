#pragma once
#include "AUIWindow.h"

class ALICEUI_API AUIWindowManager
{
public: 
    AUIWindowManager();
    virtual ~AUIWindowManager();


private:
    void RegisterWindow(const std::shared_ptr<AUIWindow>& pWindow);
    void UnregisterWindow(const std::shared_ptr<AUIWindow>& pWindow);
};