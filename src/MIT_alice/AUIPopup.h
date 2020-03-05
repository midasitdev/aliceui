#pragma once

#include "AUICommonDef.h"
#include "AUISignal.h"

class AUIWidgetManager;
class AUIWidget;

class ALICEUI_API AUIPopup
{
public:
    AUIPopup();
    virtual ~AUIPopup();


    //////////////////////////////////////////////////////////////////////////
    // Popup Widget
public:
    void SetPopupWidget(const std::shared_ptr< AUIWidget >& pWidget);
    AUIWidget* GetPopupWidget() { return m_pPopupWidget.get(); }
private:
    std::shared_ptr< AUIWidget > m_pPopupWidget;


    //////////////////////////////////////////////////////////////////////////
    // Popup Position
public:
    void SetPopupPosition(const glm::vec3& pos) { m_v3PopupPos = pos; }
    glm::vec3 GetPopupPosition() const { return m_v3PopupPos; }
private:
    glm::vec3 m_v3PopupPos;


    //////////////////////////////////////////////////////////////////////////
    // Invoke / Dismiss
public:
    bool IsInvoked() const;
    bool Invoke(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pParent, const AUIPopupPos& opt);
    bool Invoke(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pParent) {
        return Invoke(pWidgetManager, pParent, AUIPopupPos::kUnchanged);
    }
    bool Invoke(AUIWidgetManager* const pWidgetManager) { return Invoke(pWidgetManager, nullptr, AUIPopupPos::kUnchanged); }
    void Dismiss();
    AUISignal<void(void)> InvokeSignal;
    AUISignal<void(void)> DismissSignal;
private:
    AUIWidgetManager* m_pWidgetManager;
    std::weak_ptr< AUIWidget > m_wpParent;
};
