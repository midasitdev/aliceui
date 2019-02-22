#pragma once

#include "AUIInstance.h"

class ALICEUI_API AUIMFCInstance : public AUIInstance
{
public:
    AUIMFCInstance(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    virtual ~AUIMFCInstance();


    //////////////////////////////////////////////////////////////////////////
    // Coordinate
public:
    virtual void OnSetCoordSpace() override;
    virtual void OnSetRootMatrix() override;
    virtual void OnSetPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Instance Lifecycle
protected:
    virtual void OnCreateInstance() override;
    virtual void OnDestroyInstance() override;
    virtual void OnUpdateInstance() override;

private:
    bool m_bShowState;
};
