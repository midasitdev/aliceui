#pragma once


#include "AUICommonDef.h"
#include "AUIDeviceEvents.h"
#include "AUICursorIcon.h"
#include "AUISensorManager.h"


class AUIWidget;
class AUIHandle;
class AUIWidgetSelection;
class AUIInstance;
class AUIWidgetLazyTaskManager;
class AUITooltip;
class AUITooltipWidget;

class ALICEUI_API AUIWidgetManager
{
public:
    AUIWidgetManager();
    virtual ~AUIWidgetManager();


    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_AUIAssert(std::is_base_of<AUIWidgetManager, _Derived>::value, "Must be derived from AUIWidget");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIWidgetManager*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIWidgetManager*>(this));
    }

    //////////////////////////////////////////////////////////////////////////
    // Handle
public:
    void SetHandle(const std::shared_ptr< AUIHandle >& pHandle);
    AUIHandle* const GetHandle() const { return m_wpHandle.lock().get(); }
private:
    std::weak_ptr< AUIHandle > m_wpHandle;


    //////////////////////////////////////////////////////////////////////////
    // Widget selection control
public:
    AUIWidgetSelection& GetWidgetSelection() const { return *m_pWidgetSelection; }
    void SetGrabMouseEvent(bool state);
    bool IsGrabMouseEvent() const { return m_bGrabMouseEvent; }
private:
    std::unique_ptr< AUIWidgetSelection > m_pWidgetSelection;
    bool m_bGrabMouseEvent;


    //////////////////////////////////////////////////////////////////////////
    // Popup
public:
    bool IsInvoked(const std::shared_ptr< AUIWidget >& pWidget) const;
    bool Invoke(const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos) {
        return Invoke(pWidget, pParent, pos, AUIPopupPos::kUnchanged);
    }
    bool Invoke(const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt);
    bool Dismiss(const std::shared_ptr< AUIWidget >& pWidget);
protected:
    virtual bool OnInvoke(const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt);
    virtual bool OnDismiss(const std::shared_ptr< AUIWidget >& pWidget);
private:
    std::vector< std::shared_ptr< AUIWidget > > m_InvokedWidgets;


    //////////////////////////////////////////////////////////////////////////
    // State
public:
    bool IsEnabled() const { return m_bEnabled; }
protected:
    void SetEnabled(bool state) { m_bEnabled = state; }
private:
    bool m_bEnabled;



    //////////////////////////////////////////////////////////////////////////
    // Camera Info
public:
    void InvalidateCamera();
    virtual glm::mat4 GetViewingMatrix() const { return glm::mat4(1.f); }
    virtual glm::mat4 GetProjectionMatrix() const { return glm::mat4(1.f); }
    virtual glm::vec4 GetViewport() const { return glm::vec4(0.f); }
	virtual double GetPixelSize() const { return 0.; }

private:
    //////////////////////////////////////////////////////////////////////////
    // Focus control
public:
    void SetFocusTarget(const std::weak_ptr< AUIWidget >& pWidget = std::weak_ptr< AUIWidget >());
    std::weak_ptr< AUIWidget > GetFocusedTarget() const { return m_pFocusWidget; }
private:
    std::weak_ptr< AUIWidget > m_pFocusWidget;


    //////////////////////////////////////////////////////////////////////////
    // Event sender
public:
    bool SendMouseEvent(const MAUIMouseEvent& evt);
    bool SendKeyboardEvent(const AUIKeyboardEvent& evt);
    void SendTickTimeEvent(const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick);
    bool SendSetCursorEvent(AUICursorIcon& cursoricon);

    glm::dvec2 GetMousePos() const { return glm::dvec2(m_MousePosX, m_MousePosY); }
    glm::dvec3 GetMouseOrg() const { return m_MouseOrg; }
	glm::dvec3 GetMouseDir() const { return m_MouseDir; }

private:
    bool SendMouseHoverEventToWidget(const MAUIMouseEvent& evt);
    bool SendMouseEventToWidget(AUIInstance* const pInstance, const MAUIMouseEvent& evt);
    bool SendKeyboardEventToWidget(AUIInstance* const pInstance, const AUIKeyboardEvent& evt);
    void SendTickTimeToWidget(AUIInstance* const pInstance, const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick);
    bool SendSetCursorEventToWidget(AUIInstance* const pInstance, AUICursorIcon& cursoricon);
    int m_MousePosX;
    int m_MousePosY;
    glm::dvec3 m_MouseOrg;
    glm::dvec3 m_MouseDir;



    //////////////////////////////////////////////////////////////////////////
    // Tooltip
protected:
    virtual void OnShowTooltip(const std::shared_ptr< AUITooltip >& pTooltip, int x, int y);
    virtual void OnHideTooltip();
    bool HasTooltipInstance() const {
        return m_bHasTooltipInst;
    }
private:
    void LazyUpdateTooltip();
    void ShowTooltip(const std::shared_ptr< AUITooltip >& pTooltip);
    void HideTooltip();
    std::chrono::milliseconds m_TooltipTimerStart = std::chrono::milliseconds::zero();
    std::weak_ptr< AUIWidget > m_wpTooltipTarget;
    std::weak_ptr< AUIWidget > m_wpTooltipTimerTarget;
    std::shared_ptr< AUITooltip > m_pTooltip;
    bool m_bShowTooltip;
    bool m_bHasTooltipInst;
    int m_TooltipOffsetX;
    int m_TooltipOffsetY;


    //////////////////////////////////////////////////////////////////////////
    // Hit Test Buffer
private:
    void RefreshHitTestBuffer(int x, int y);

    //std::multimap< float, std::weak_ptr< MAUIInstance > > m_HitTestBuffer;
    std::vector<HitBufferData> m_HitTestBuffer;

    //////////////////////////////////////////////////////////////////////////
    // Widget control
public:
    void CreateInstance(const std::shared_ptr< AUIWidget >& pWidget);
    void DestroyInstance(const std::shared_ptr< AUIWidget >& pWidget);
    void ClearInstance();
    size_t GetInstanceCount() const { return m_mapWidget2Instance.size(); }
    AUIInstance* const FindInstance(AUIWidget* const pWidget);
    const AUIInstance* const FindInstance(AUIWidget* const pWidget) const;
    void GetInstances(std::vector<std::shared_ptr<AUIInstance>>& arrInstances) const;
protected:
    virtual std::shared_ptr< AUIInstance > OnRegisterWidget(const std::shared_ptr< AUIWidget >& pWidget);
    std::vector< std::shared_ptr< AUIInstance > >::const_iterator InstBegin() const { return m_Instances.cbegin(); }
    std::vector< std::shared_ptr< AUIInstance > >::const_iterator InstEnd() const { return m_Instances.cend(); }
    virtual void OnPreRegisterWidget() { /* Implement in subclass */ }
    virtual void OnPostRegisterWidget() { /* Implement in subclass */ }
    virtual void OnPreUnregisterWidget() { /* Implement in subclass */ }
    virtual void OnPostUnregisterWidget() { /* Implement in subclass */ }
private:
    void RegisterWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void UnregisterWidget(const std::shared_ptr< AUIWidget >& pWidget);
    mutable std::recursive_mutex m_mtxInstances;
    std::vector< std::shared_ptr< AUIInstance > > m_Instances;
    std::vector< std::weak_ptr< AUIInstance > > m_HoverInstances;

    std::unordered_map< AUIWidget*, std::shared_ptr< AUIInstance > > m_mapWidget2Instance;




 public:
     AUISensorManager* GetSensorManager(AUICoordSpace eType) { return m_aSensorManager[(size_t)eType].get(); }
	 void InvalidateSensor(AUIWidget* pWidget);
	 void InvalidateUIState(AUIWidget* pWidget);
 private:
    std::unique_ptr<AUISensorManager> m_aSensorManager[AUICoordSpaceNum];
    //////////////////////////////////////////////////////////////////////////
    // Update
public:
    bool UpdateAllInstance();
protected:
    virtual void OnPreUpdateAllInstance() { /* Implement in subclass */ }
    virtual void OnPostUpdateAllInstance() { /* Implement in subclass */ }
private:
    void UpdateInstance(AUIWidget* const pWidget);
    void UpdateInstance(const std::shared_ptr<AUIInstance>& pInstance);


    //////////////////////////////////////////////////////////////////////////
    // Dirty
public:
    bool IsDirty() const { return m_bDirty; }
    void SetDirty() { m_bDirty = true; }
private:
    bool m_bDirty;


    //////////////////////////////////////////////////////////////////////////
    // Magic
public:
    bool IsLastHovered() const {
        return m_bLastHovered;
    }
    bool IsLastHandled() const {
        return m_bLastHandled;
    }
private:
    bool m_bLastHovered = false;
    bool m_bLastHandled = false;


    friend class AUIApplication;
};
