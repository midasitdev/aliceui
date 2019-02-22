#pragma once

#include "AUIFrameLayoutWidget.h"

class ALICEUI_API AUITransitionWidget : public AUIFrameLayoutWidget
{
    typedef AUIFrameLayoutWidget SuperWidget;
public:
    AUITransitionWidget();
    virtual ~AUITransitionWidget();


    //////////////////////////////////////////////////////////////////////////
    // Transition
public:
    void ReplaceWidget(const std::shared_ptr< AUIWidget >& pWidget, bool animate = true);
    std::shared_ptr< AUIWidget > GetCurrentWidget() const { return m_pCurrentWidget; }
private:
    void BeforeTransition(const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget);
    void AfterTransition(const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget);
    std::shared_ptr< AUIWidget > m_pCurrentWidget;


    //////////////////////////////////////////////////////////////////////////
    // Transition state
public:
    bool IsInTransition() const { return m_bInTransition; }
    void StartTransition(const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget, bool animate);
    void EndTransition();
private:
    bool m_bInTransition;
    std::shared_ptr< AUIWidget > m_pFromWidget;
    std::shared_ptr< AUIWidget > m_pToWidget;
    bool m_bFromFreezed;
    float m_fFromTargetOpacity;
    bool m_bToFreezed;
    float m_fToTargetOpacity;


    //////////////////////////////////////////////////////////////////////////
    // Time tick
protected:
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;
};
