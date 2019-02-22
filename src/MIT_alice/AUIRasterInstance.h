#pragma once


#include "AUIAPIDef.h"
#include "AUIInstance.h"

class AUIRasterWidgetManager;
class AUIWidget;

class ALICEUI_API AUIRasterInstance : public AUIInstance
{
public:
    AUIRasterInstance(AUIRasterWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    ~AUIRasterInstance() override = default;

    //////////////////////////////////////////////////////////////////////////
    // Instance Lifecycle
protected:
    void OnCreateInstance() override;
    void OnDestroyInstance() override;
    void OnUpdateInstance() override;
    void OnSetDirty() override;

private:
    std::weak_ptr< AUIWidget > m_wpDrawableRootWidget;


    //////////////////////////////////////////////////////////////////////////
    // Widget Manager
public:
    AUIRasterWidgetManager* GetUIRasterWidgetManager() const;
};
