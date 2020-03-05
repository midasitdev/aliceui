#pragma once

#include <glm/glm.hpp>
#include "AUIBasicEnumDef.h"
#include "AUISkiaConfig.h"
#include "AUILifeState.h"
#include "AUIProperty.h"
#include "AUIState.h"

#include "AUIDeviceEvents.h"
#include "AUICursorIcon.h"
#include "AUISignal.h"
#include "AUISlotPool.h"
#include "AUIStyleNotion.h"
#include "AUIDebug.h"
#include "AUISensorManager.h"

class AUIDrawable;
class AUIWidgetManager;
class AUICompass;
class AUISensor;
class AUIWidgetRootInfo;
class AUIInstance;
class AUITooltip;
class AUIWidgetStyle;
class AUIStyleUpdator;
class AUICursorIcon;
class AUISensorManager;

class ALICEUI_API AUIWidget : public AUISlotPool, public std::enable_shared_from_this<AUIWidget>
{
public:
    AUIWidget();
    virtual ~AUIWidget();

    //////////////////////////////////////////////////////////////////////////
    // Common Signals
public:
    AUISignal<void(AUIWidget*)> EnterSignal;
    AUISignal<void(AUIWidget*)> LeaveSignal;
    AUISignal<void(AUIWidget*)> ClickSignal;
    AUISignal<void(AUIWidget*)> DblClickSignal;
    AUISignal<void(AUIWidget*)> PressSignal;
    AUISignal<void(AUIWidget*)> DragSignal;
    AUISignal<void(AUIWidget*)> FocusInSignal;
    AUISignal<void(AUIWidget*)> FocusOutSignal;
    AUISignal<void(AUIWidget*)> MouseRBtnClickSignal;

    //////////////////////////////////////////////////////////////////////////
    // Runtime Helper
public:
    AUIRuntimeID GetRuntimeID() const noexcept {
        return m_RuntimeID;
    }
    static AUIWidget* FindByRuntimeID(const AUIRuntimeID id);
private:
    AUIRuntimeID m_RuntimeID = 0;


    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_assert(std::is_base_of<AUIWidget, _Derived>::value, "Must be derived from AUIWidget");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIWidget*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIWidget*>(this));
    }
    template<typename _Derived>
    std::shared_ptr<_Derived> CastShared() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return std::static_pointer_cast<_Derived>(shared_from_this());
    }
    template<typename _Derived>
    std::shared_ptr<_Derived> DynCastShared() const {
        return std::dynamic_pointer_cast<_Derived>(shared_from_this());
    }


    //////////////////////////////////////////////////////////////////////////
    // Tooltip
public:
    void SetShowTooltip(bool show) noexcept {
        m_bShowTooltip = show;
    }
    bool IsShowTooltip() const noexcept {
        return m_bShowTooltip;
    }
    void SetTooltipText(const std::wstring& message);
    void SetTooltip(const std::shared_ptr< AUITooltip >& pTooltip) {
        m_pTooltip = pTooltip;
    }
    std::shared_ptr< AUITooltip > GetTooltip() const {
        return m_pTooltip;
    }
private:
    std::shared_ptr< AUITooltip > m_pTooltip;
    bool m_bShowTooltip;



    //////////////////////////////////////////////////////////////////////////
    // Hotkey support
public:
    bool IsUseHotkeyCopy() const noexcept {
        return m_bUseHotkeyCopy;
    }
    bool IsUseHotkeyPaste() const noexcept {
        return m_bUseHotkeyPaste;
    }
    bool IsUseHotkeyCut() const noexcept {
        return m_bUseHotkeyCut;
    }
    void SetUseHotkeyCopy(bool use) noexcept {
        m_bUseHotkeyCopy = use;
    }
    void SetUseHotkeyPaste(bool use) noexcept {
        m_bUseHotkeyPaste = use;
    }
    void SetUseHotkeyCut(bool use) noexcept {
        m_bUseHotkeyCut = use;
    }
private:
    bool m_bUseHotkeyCopy;
    bool m_bUseHotkeyPaste;
    bool m_bUseHotkeyCut;



    //////////////////////////////////////////////////////////////////////////
    // Transformation
public:
    void SetPosition(const SkScalar x, const SkScalar y, const SkScalar z = 0.0f) { SetPosition(AUIScalar3(x, y, z)); }
    void SetPosition(const AUIScalar2& pos) { SetPosition(AUIScalar3(pos)); }
    virtual void SetPosition(const AUIScalar3& pos);
    virtual AUIScalar3 GetPosition() const {
        return m_vPos;
    }
    AUIScalar3 GetPositionAtRoot() const;
    SkScalar GetPosX() const noexcept {
        return m_vPos.fZ;
    }
    SkScalar GetPosY() const noexcept {
        return m_vPos.fY;
    }
    SkScalar GetPosZ() const noexcept {
        return m_vPos.fZ;
    }
private:
    virtual void OnPositionChange() { }
    AUIScalar3 m_vPos;




    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnSetDefaultSize(const AUIScalar2& size);
    virtual void OnBeforeMeasureSize() { /* Implement in subclass */ }
    virtual void OnAfterMeasureSize(SkScalar width, SkScalar height) { /* Implement in subclass */ }


    //////////////////////////////////////////////////////////////////////////
    // Focus control
protected:
    virtual void OnFocusIn() { /* Implement in subclass */ }
    virtual void OnFocusOut() { /* Implement in subclass */ }
private:
    void FocusIn();
    void FocusOut();


    //////////////////////////////////////////////////////////////////////////
    // Update
public:
    void PreUpdate();
    void PostUpdate();
protected:
    virtual void OnPreUpdate() { /* Implement in subclass */ }
    virtual void OnPostUpdate() { /* Implement in subclass */ }
    bool WasDirty() const { return m_bWasDirty; }
private:
    bool m_bWasDirty;


    //////////////////////////////////////////////////////////////////////////
    // Parent
public:
    AUIWidget* const GetParent() const;
    AUIWidget* const GetRoot() const;
    bool IsRoot() const;
    bool IsHitTestAffectToChild() const noexcept {
        return m_bHitTestAffectToChild;
    }
protected:
    virtual bool OnSetParent(AUIWidget* const pParent);
    void SetHitTestAffectToChild(bool val) noexcept {
        m_bHitTestAffectToChild = val;
        Invalidate();
    }
private:
    bool m_bHitTestAffectToChild = false;


    //////////////////////////////////////////////////////////////////////////
    // Children
public:
    bool IsNeedUpdateChildPosition() const noexcept {
        return m_bUpdateChildPosition;
    }
    void UpdateChildPosition();
    const std::vector< std::shared_ptr< AUIWidget > > GetChildren() const;
protected:
    std::shared_ptr< AUIWidget > FindChild(size_t pos) const;
    size_t ChildCount() const;
public:
    virtual void OnUpdateChildPosition();  // NOTE: Use careful
public: // TODO : Move To WidgetTreeHelper
    static void CallOnUpdateChildPosition(AUIWidget* const pWidget);
    static void CallOnUpdateChildPosition(const std::shared_ptr< AUIWidget >& pWidget) { AUIWidget::CallOnUpdateChildPosition(pWidget.get()); }
private:
    bool m_bUpdateChildPosition;


    //////////////////////////////////////////////////////////////////////////
    // Focus
public:
    virtual const std::shared_ptr< AUIWidget > GetNextFocusable();
    virtual const std::shared_ptr< AUIWidget > GetPrevFocusable();


    //////////////////////////////////////////////////////////////////////////
    // Life cycle management
public:
    bool IsCreated() const;
    bool IsPendingCreate() const { return m_LifeState.IsPendingCreate(); }
    bool IsPendingDestroy() const { return m_LifeState.IsPendingDestory(); }
private:
    void Create();      // Create widget
    void Destroy();     // Destroy widget
protected:
    virtual void OnCreate() { /* Implement in subclass */ }
    virtual void OnDestroy() { /* Implement in subclass */ }
    AUIWidgetManager* GetWidgetManager() const noexcept;
private:
    AUILifeState m_LifeState;


    //////////////////////////////////////////////////////////////////////////
    // Coordinate
public:



    void SetRootTargetCoord(AUICoordSpace eTargetCoord);
    void SetRootMatrix(const glm::mat4& mat);
    bool IsRootCoord()const;

    const AUIWidgetRootInfo* GetRootCoordInfo() const;
    AUICoordSpace GetRootTargetCoord() const;
    const glm::mat4& GetRootMatrix() const;
    //const glm::mat4 GetAccumulatedMatrix() const;

    // const glm::vec3& GetRootCoord();
    void SetForceDepthTest(bool state) noexcept {
        m_bForceDepthTest = state;
        Invalidate();
    }
    bool IsForceDepthTest() const noexcept {
        return m_bForceDepthTest;
    }
    void SetForceDepthMask(bool state) noexcept {
        m_bForceDepthMask = state;
        Invalidate();
    }
    bool IsForceDepthMask() const noexcept {
        return m_bForceDepthMask;
    }
private:
    std::shared_ptr< AUIWidgetRootInfo > m_spRootInfo;
	const static AUIWidgetRootInfo s_DefualtRootInfo;
    bool m_bForceDepthTest;
    bool m_bForceDepthMask;


    //////////////////////////////////////////////////////////////////////////
    // Scroll
public:
    void SetScrollTo(const SkScalar& x, const SkScalar& y);
    void SetScrollBy(const SkScalar& dx, const SkScalar& dy) {
        this->SetScrollTo(m_ScrollX + dx, m_ScrollY + dy);
    }
    void SetScrollX(const SkScalar& x) {
        this->SetScrollTo(x, m_ScrollY);
    }
    void SetScrollY(const SkScalar& y) {
        this->SetScrollTo(m_ScrollX, y);
    }
    SkScalar GetScrollX() const noexcept {
        return m_ScrollX;
    }
    SkScalar GetScrollY() const noexcept {
        return m_ScrollY;
    }
    AUIScalar3 GetScrollVal() const noexcept {
        return AUIScalar3(GetScrollX(), GetScrollY(), 0.0f);
    }
protected:
    virtual void OnScrollChanged(const SkScalar& x, const SkScalar& y, const SkScalar& oldX, const SkScalar& oldY) { /* Implement in subclass */ }
private:
    SkScalar m_ScrollX;
    SkScalar m_ScrollY;



    //////////////////////////////////////////////////////////////////////////
    // Midas Style Sheet v2
public:
    void SetStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    std::shared_ptr<const AUIWidgetStyle> GetStyleSheet() const;

    virtual void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value);
private:
    void UpdateStyle();
    void SetStyleNotion(const AUIStyleNotion& notion);
    std::shared_ptr<AUIStyleUpdator> m_pStyleUpdator;


    //////////////////////////////////////////////////////////////////////////
    // UI State
public:
    const AUIState GetUIState() const noexcept {
        return m_UIState;
    }
    bool IsInstanced() const noexcept;
    bool IsVisible() const noexcept {
        return m_UIState.IsVisible();
    }
    bool IsFreezed() const noexcept {
        return m_UIState.IsFreezed();
    }
    bool IsPressed() const noexcept {
        return m_UIState.IsPressed();
    }
    bool IsDraggable() const noexcept {
        return m_UIState.IsDraggable();
    }
    bool IsFocused() const noexcept {
        return m_UIState.IsFocused();
    }
    bool IsFocusable() const noexcept {
        return m_UIState.IsFocusable();
    }
    bool IsCheckable() const noexcept {
        return m_UIState.IsCheckable();
    }
    bool IsChecked() const noexcept {
        return m_UIState.IsChecked();
    }
    bool IsCheckedIndeterminate() const noexcept {
        return m_UIState.IsCheckedIndeterminate();
    }
    bool IsDisabled() const noexcept {
        return m_UIState.IsDisabled();
    }
    bool IsMouseHover() const noexcept {
        return m_UIState.IsMouseHovered();
    }
    bool IsMouseLDown() const noexcept {
        return m_UIState.IsMouseLDown();
    }
    bool IsMouseMDown() const noexcept {
        return m_UIState.IsMouseMDown();
    }
    bool IsMouseRDown() const noexcept {
        return m_UIState.IsMouseRDown();
	}
	void SetVisible(bool state) noexcept { m_UIState.SetVisible(state); OnSetVisible(state); _invalidate_ui_state(); Invalidate(); }
	void SetFreeze(bool state) noexcept { m_UIState.SetFreeze(state); _invalidate_ui_state(); Invalidate(); }
    void MakeVisible() noexcept {
        SetVisible(true);
    }
    void MakeInvisible() noexcept {
        SetVisible(false);
    }
    void Freeze() noexcept {
        SetFreeze(true);
    }
    void UnFreeze() noexcept {
        SetFreeze(false);
    }
    void SetCheckable(bool state) noexcept {
        m_UIState.SetCheckable(state);
        Invalidate();
    }
    void SetChecked(bool state) {
        m_UIState.SetChecked(state);
        OnSetChecked(state);
        Invalidate();
    }
    void SetCheckedIndeterminate(bool state) noexcept {
        m_UIState.SetCheckedIndeterminate(state);
        Invalidate();
    }
    bool IsIgnored() const noexcept {
        return m_UIState.IsIgnored();
    }
    void SetIgnored(bool state) {
        m_UIState.SetIgnored(state);
		OnSetIgnored(state);
		_invalidate_ui_state();
        Invalidate();
    }
    void SetDisabled(bool state) {
		m_UIState.SetDisabled(state);
		OnSetDisabled(state);
		_invalidate_ui_state();
        Invalidate();
    }
    bool IsClickable() const noexcept {
        return m_UIState.IsClickable();
    }
    void SetClickable(bool state) noexcept {
        m_UIState.SetClickable(state);
    }
    void SetDraggable(bool state) noexcept {
        m_UIState.SetDraggable(state);
    }
    void SetFocusable(bool state) noexcept {
        m_UIState.SetFocusable(state);
    }
protected:
    bool IsDragging() const noexcept {
        return m_UIState.IsDragging();
    }
protected:
    virtual void OnSetVisible(bool state) { /* Implement in subclass */ }
    virtual void OnSetIgnored(bool state) { /* Implement in subclass */ }
    virtual void OnSetDisabled(bool state) { /* Implement in subclass */ }
    virtual void OnSetChecked(bool state) { /* Implement in subclass */ }
public: // NOTE : Use at your own risk
    void SetCreated(bool state) noexcept {
        m_UIState.SetCreated(state);
    }
    void SetFocused(bool state) noexcept {
        m_UIState.SetFocused(state);
    }
    void SetDragging(bool state) noexcept {
        m_UIState.SetDragging(state);
    }
    void SetHovered(bool state) noexcept {
        m_UIState.SetMouseHovered(state);
    }
    void SetPressed(bool state) noexcept {
        m_UIState.SetPressed(state);
    }
    void SetMouseLDown(bool state) noexcept {
        m_UIState.SetMouseLDown(state);
    }
    void SetMouseMDown(bool state) noexcept {
        m_UIState.SetMouseMDown(state);
    }
    void SetMouseRDown(bool state) noexcept {
        m_UIState.SetMouseRDown(state);
    }
    void ResetMouseState() noexcept {
        m_UIState.SetPressed(false);
        m_UIState.ResetMouse();
    }
private:
    AUIState m_UIState;
protected:
    void NotifyUIStateChange(); // For WidgetTree


    //////////////////////////////////////////////////////////////////////////
    // Default Color
public:
    void SetColor(SkColor color) noexcept {
        m_Color = color;
    }
    SkColor GetColor() const noexcept {
        return m_Color;
    }
private:
    SkColor m_Color;


    //////////////////////////////////////////////////////////////////////////
    // Property
public:
    void SetProperty(const AUIProperty& prop) {
        m_Property = prop;
        UpdateSize();
        UpdateChildPosition();
        Invalidate();
    }
    AUIProperty GetProperty() const noexcept {
        return m_Property;
    }
    void ResetPropParent() noexcept {
        m_Property.ResetParentOption();
    }
    void SetPropParentTop(const bool val) noexcept {
        m_Property.SetParentTop(val);
    }
    void SetPropParentBottom(const bool val) noexcept {
        m_Property.SetParentBottom(val);
    }
    void SetPropParentLeft(const bool val) noexcept {
        m_Property.SetParentLeft(val);
    }
    void SetPropParentRight(const bool val) noexcept {
        m_Property.SetParentRight(val);
    }
    void SetPropParentCenterHorizontal(const bool val) noexcept {
        m_Property.SetParentCenterHorizontal(val);
    }
    void SetPropParentCenterVertical(const bool val) noexcept {
        m_Property.SetParentCenterVertical(val);
    }
    void SetPropParentCenter(const bool val) noexcept {
        m_Property.SetParentCenter(val);
    }
    bool GetPropParentTop() const noexcept {
        return m_Property.GetParentTop();
    }
    bool GetPropParentBottom() const noexcept {
        return m_Property.GetParentBottom();
    }
    bool GetPropParentLeft() const noexcept {
        return m_Property.GetParentLeft();
    }
    bool GetPropParentRight() const noexcept {
        return m_Property.GetParentRight();
    }
    bool GetPropParentCenterHorizontal() const noexcept {
        return m_Property.GetParentCenterHorizontal();
    }
    bool GetPropParentCenterVertical() const noexcept {
        return m_Property.GetParentCenterVertical();
    }
    bool GetPropParentCenter() const noexcept {
        return m_Property.GetParentCenter();
    }
    void ResetPropTarget() noexcept {
        m_Property.ResetTargetOption();
    }
    void SetPropAbove(const AUIRuntimeID id) noexcept {
        m_Property.SetAbove(id);
    }
    void SetPropBelow(const AUIRuntimeID id) noexcept {
        m_Property.SetBelow(id);
    }
    void SetPropToLeftOf(const AUIRuntimeID id) noexcept {
        m_Property.SetToLeftOf(id);
    }
    void SetPropToRightOf(const AUIRuntimeID id) noexcept {
        m_Property.SetToRightOf(id);
    }
    void SetPropAlignLeft(const AUIRuntimeID id) noexcept {
        m_Property.SetAlignLeft(id);
    }
    void SetPropAlignTop(const AUIRuntimeID id) noexcept {
        m_Property.SetAlignTop(id);
    }
    void SetPropAlignRight(const AUIRuntimeID id) noexcept {
        m_Property.SetAlignRight(id);
    }
    void SetPropAlignBottom(const AUIRuntimeID id) noexcept {
        m_Property.SetAlignBottom(id);
    }
    void SetPropAlignBaseline(const AUIRuntimeID id) noexcept {
        m_Property.SetAlignBaseline(id);
    }
    const AUIRuntimeID GetPropAbove() const noexcept {
        return m_Property.GetAbove();
    }
    const AUIRuntimeID GetPropBelow() const noexcept {
        return m_Property.GetBelow();
    }
    const AUIRuntimeID GetPropToLeftOf() const noexcept {
        return m_Property.GetToLeftOf();
    }
    const AUIRuntimeID GetPropToRightOf() const noexcept {
        return m_Property.GetToRightOf();
    }
    const AUIRuntimeID GetPropAlignLeft() const noexcept {
        return m_Property.GetAlignLeft();
    }
    const AUIRuntimeID GetPropAlignTop() const noexcept {
        return m_Property.GetAlignTop();
    }
    const AUIRuntimeID GetPropAlignRight() const noexcept {
        return m_Property.GetAlignRight();
    }
    const AUIRuntimeID GetPropAlignBottom() const noexcept {
        return m_Property.GetAlignBottom();
    }
    const AUIRuntimeID GetPropAlignBaseline() const noexcept {
        return m_Property.GetAlignBaseline();
    }
    void ResetPropLayoutGravity() noexcept {
        m_Property.ResetLayoutGravityOption();
    }
    void SetPropLayoutGravityCenter(bool val) noexcept {
        m_Property.SetLayoutGravityCenter(val);
    }
    void SetPropLayoutGravityCenterHorizontal(bool val) noexcept {
        m_Property.SetLayoutGravityCenterHorizontal(val);
    }
    void SetPropLayoutGravityCenterVertical(bool val) noexcept {
        m_Property.SetLayoutGravityCenterVertical(val);
    }
    void SetPropLayoutGravityLeft(bool val) noexcept {
        m_Property.SetLayoutGravityLeft(val);
    }
    void SetPropLayoutGravityTop(bool val) noexcept {
        m_Property.SetLayoutGravityTop(val);
    }
    void SetPropLayoutGravityRight(bool val) noexcept {
        m_Property.SetLayoutGravityRight(val);
    }
    void SetPropLayoutGravityBottom(bool val) noexcept {
        m_Property.SetLayoutGravityBottom(val);
    }
    bool GetPropLayoutGravityCenter() const noexcept {
        return m_Property.GetLayoutGravityCenter();
    }
    bool GetPropLayoutGravityCenterHorizontal() const noexcept {
        return m_Property.GetLayoutGravityCenterHorizontal();
    }
    bool GetPropLayoutGravityCenterVertical() const noexcept {
        return m_Property.GetLayoutGravityCenterVertical();
    }
    bool GetPropLayoutGravityLeft() const noexcept {
        return m_Property.GetLayoutGravityLeft();
    }
    bool GetPropLayoutGravityTop() const noexcept {
        return m_Property.GetLayoutGravityTop();
    }
    bool GetPropLayoutGravityRight() const noexcept {
        return m_Property.GetLayoutGravityRight();
    }
    bool GetPropLayoutGravityBottom() const noexcept {
        return m_Property.GetLayoutGravityBottom();
    }
    void ResetPropGravity() noexcept {
        m_Property.ResetGravityOption();
    }
    void SetPropGravityCenter(bool val) noexcept {
        m_Property.SetGravityCenter(val);
    }
    void SetPropGravityCenterHorizontal(bool val) noexcept {
        m_Property.SetGravityCenterHorizontal(val);
    }
    void SetPropGravityCenterVertical(bool val) noexcept {
        m_Property.SetGravityCenterVertical(val);
    }
    void SetPropGravityLeft(bool val) noexcept {
        m_Property.SetGravityLeft(val);
    }
    void SetPropGravityTop(bool val) noexcept {
        m_Property.SetGravityTop(val);
    }
    void SetPropGravityRight(bool val) noexcept {
        m_Property.SetGravityRight(val);
    }
    void SetPropGravityBottom(bool val) noexcept {
        m_Property.SetGravityBottom(val);
    }
    bool GetPropGravityCenter() const noexcept {
        return m_Property.GetGravityCenter();
    }
    bool GetPropGravityCenterHorizontal() const noexcept {
        return m_Property.GetGravityCenterHorizontal();
    }
    bool GetPropGravityCenterVertical() const noexcept {
        return m_Property.GetGravityCenterVertical();
    }
    bool GetPropGravityLeft() const noexcept {
        return m_Property.GetGravityLeft();
    }
    bool GetPropGravityTop() const noexcept {
        return m_Property.GetGravityTop();
    }
    bool GetPropGravityRight() const noexcept {
        return m_Property.GetGravityRight();
    }
    bool GetPropGravityBottom() const noexcept {
        return m_Property.GetGravityBottom();
    }
    void ResetWeight() noexcept {
        m_Property.ResetWeight();
    }
    void SetWeight(const SkScalar val) noexcept {
        m_Property.SetWeight(val);
    }
    SkScalar GetWeight() const noexcept {
        return m_Property.GetWeight();
    }

    void ResetPadding() noexcept {
        return m_Property.ResetPadding();
    }
    void SetPadding(const SkScalar val) noexcept {
        m_Property.SetPadding(val);
    }
    void SetPaddingLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom) noexcept {
        m_Property.SetPaddingLTRB(left, top, right, bottom);
    }
    void SetPaddingLeft(const SkScalar val) noexcept {
        m_Property.SetPaddingLeft(val);
    }
    void SetPaddingTop(const SkScalar val) noexcept {
        m_Property.SetPaddingTop(val);
    }
    void SetPaddingRight(const SkScalar val) noexcept {
        m_Property.SetPaddingRight(val);
    }
    void SetPaddingBottom(const SkScalar val) noexcept {
        m_Property.SetPaddingBottom(val);
    }
    SkScalar GetPaddingLeft() const noexcept {
        return m_Property.GetPaddingLeft();
    }
    SkScalar GetPaddingTop() const noexcept {
        return m_Property.GetPaddingTop();
    }
    SkScalar GetPaddingRight() const noexcept {
        return m_Property.GetPaddingRight();
    }
    SkScalar GetPaddingBottom() const noexcept {
        return m_Property.GetPaddingBottom();
    }

    void ResetMargin() noexcept {
        return m_Property.ResetMargin();
    }
    void SetMargin(const SkScalar val) noexcept {
        m_Property.SetMargin(val);
    }
    void SetMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom) noexcept {
        m_Property.SetMarginLTRB(left, top, right, bottom);
    }
    void SetMarginLeft(const SkScalar val) noexcept {
        m_Property.SetMarginLeft(val);
    }
    void SetMarginTop(const SkScalar val) noexcept {
        m_Property.SetMarginTop(val);
    }
    void SetMarginRight(const SkScalar val) noexcept {
        m_Property.SetMarginRight(val);
    }
    void SetMarginBottom(const SkScalar val) noexcept {
        m_Property.SetMarginBottom(val);
    }
    SkScalar GetMarginLeft() const noexcept {
        return m_Property.GetMarginLeft();
    }
    SkScalar GetMarginTop() const noexcept {
        return m_Property.GetMarginTop();
    }
    SkScalar GetMarginRight() const noexcept {
        return m_Property.GetMarginRight();
    }
    SkScalar GetMarginBottom() const noexcept {
        return m_Property.GetMarginBottom();
    }

    void SetSizePolicy(const AUISizePolicy width, const AUISizePolicy height) noexcept {
        m_Property.SetSizePolicy(width, height);
    }
    void SetSizePolicyWidth(const AUISizePolicy sp) noexcept {
        m_Property.SetSizePolicyWidth(sp);
    }
    void SetSizePolicyHeight(const AUISizePolicy sp) noexcept {
        m_Property.SetSizePolicyHeight(sp);
    }
    AUISizePolicy GetSizePolicyWidth() const noexcept {
        return m_Property.GetSizePolicyWidth();
    }
    AUISizePolicy GetSizePolicyHeight() const noexcept {
        return m_Property.GetSizePolicyHeight();
    }
private:
    AUIProperty m_Property;




    //////////////////////////////////////////////////////////////////////////
    // Size
public:
    SkScalar GetWidth() const noexcept {
        return m_Property.GetWidth();
    }
    SkScalar GetHeight() const noexcept {
        return m_Property.GetHeight();
    }
    AUIScalar2 GetSize() const noexcept {
        return m_Property.GetSize();
    }
    AUIScalar2 GetMinimumSize() const noexcept {
        return m_Property.GetMinimumSize();
    }
    AUIScalar2 GetMaximumSize() const noexcept {
        return m_Property.GetMaximumSize();
    }
    AUIScalar2 GetRangeMin() const noexcept {
        return m_Property.GetRangeMin();
    }
    SkScalar GetRangeMinX() const noexcept {
        return m_Property.GetRangeMinX();
    }
    SkScalar GetRangeMinY() const noexcept {
        return m_Property.GetRangeMinY();
    }
    AUIScalar2 GetRangeMax() const noexcept {
        return m_Property.GetRangeMax();
    }
    SkScalar GetRangeMaxX() const noexcept {
        return m_Property.GetRangeMaxX();
    }
    SkScalar GetRangeMaxY() const noexcept {
        return m_Property.GetRangeMaxY();
    }
    AUIScalar2 GetMeasureSize() const noexcept {
        return m_Property.GetMeasureSize();
    }
    SkScalar GetMeasureWidth() const noexcept {
        return m_Property.GetMeasureWidth();
    }
    SkScalar GetMeasureHeight() const noexcept {
        return m_Property.GetMeasureHeight();
    }
    AUIScalar2 GetDefaultSize() const noexcept {
        return m_Property.GetDefaultSize();
    }
    SkScalar GetDefaultWidth() const noexcept {
        return m_Property.GetDefaultWidth();
    }
    SkScalar GetDefaultHeight() const noexcept {
        return m_Property.GetDefaultHeight();
    }
    void SetMinimumSize(const AUIScalar2& size);
    void SetMinimumWidth(const SkScalar& val) {
        auto s = GetMinimumSize();
        s.fX = val;
        SetMinimumSize(s);
    }
    void SetMinimumHeight(const SkScalar& val) {
        auto s = GetMinimumSize();
        s.fY = val;
        SetMinimumSize(s);
    }
    void SetMaximumSize(const AUIScalar2& size);
    void SetMaximumWidth(const SkScalar& val) {
        auto s = GetMaximumSize();
        s.fX = val;
        SetMaximumSize(s);
    }
    void SetMaximumHeight(const SkScalar& val) {
        auto s = GetMaximumSize();
        s.fY = val;
        SetMaximumSize(s);
    }
    void SetDefaultSize(const AUIScalar2& size);
    void SetDefaultSize(const SkScalar width, const SkScalar height) {
        SetDefaultSize(AUIScalar2(width, height));
    }
    void SetDefaultWidth(const SkScalar val) {
        SetDefaultSize(AUIScalar2(val, GetDefaultSize().fY));
    }
    void SetDefaultHeight(const SkScalar val) {
        SetDefaultSize(AUIScalar2(GetDefaultSize().fX, val));
    }
    bool IsNeedUpdateSize() const noexcept {
        return m_bNeedUpdateSize;
    }
protected:
    void SetRangeMin(const AUIScalar2& val) noexcept {
        m_Property.SetRangeMin(val);
    }
    void SetRangeMin(const SkScalar x, const SkScalar y) noexcept {
        SetRangeMin(AUIScalar2(x, y));
    }
    void SetRangeMax(const AUIScalar2& val) noexcept {
        m_Property.SetRangeMax(val);
    }
    void SetRangeMax(const SkScalar x, const SkScalar y) noexcept {
        SetRangeMax(AUIScalar2(x, y));
    }
    AUIScalar2 GetDefaultMeasureSize(const SkScalar width, AUIMeasureSpec widthSpec, const SkScalar height, AUIMeasureSpec heightSpec) const;
public: // NOTE : changed from LinearLayoutManager -> TODO : Alias
    void SetMeasureSize(const AUIScalar2& size) noexcept {
        m_Property.SetMeasureSize(size);
        Invalidate();
    }
    void SetMeasureSize(const SkScalar width, const SkScalar height) noexcept {
        SetMeasureSize(AUIScalar2(width, height));
    }
protected:
    virtual void OnPreMeasureSize();
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);
    virtual void OnPostMeasureSize();
private:
    void SetSize(const AUIScalar2& size) noexcept {
        m_Property.SetSize(size);
    }
    bool m_bNeedUpdateSize;

    //////////////////////////////////////////////////////////////////////////
    // Size Update
public:
    static void CallMeasureAndUpdateSize(AUIWidget* const pWidget);
    //protected: // NOTE : LinearLayoutManager -> TODO : Alias
    static void OnCallMeasureAndUpdateSize(AUIWidget* const pWidget, SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);
private:
    SkScalar m_PrevUpdateWidth;
    SkScalar m_PrevUpdateHeight;
    AUIMeasureSpec m_PrevUpdateWidthSpec;
    AUIMeasureSpec m_PrevUpdateHeightSpec;




    //////////////////////////////////////////////////////////////////////////
    // Hit Test
public:
    virtual bool HitTest(glm::vec3& hit) const;
    bool HasHitTest() const noexcept {
        return m_bUseHitTest;
    }
    void SetUseHitTest(bool use) noexcept {
        m_bUseHitTest = use;
    }
private:
    bool m_bUseHitTest;


    //////////////////////////////////////////////////////////////////////////
    // Mouse status
public:
    //SkScalar GetMouseAbsPosX() const;
    //SkScalar GetMouseAbsPosY() const;
    //SkPoint GetMouseAbsPos() const;
    //bool HasMouseAbsPos() const;
    SkScalar GetMouseLocPosX() const;
    SkScalar GetMouseLocPosY() const;
    SkPoint GetMouseLocPos() const;
    bool HasMouseLocPos() const;

    //////////////////////////////////////////////////////////////////////////
    // Event receiver
public:
    bool IsGrabMouseEvent();
protected:
    void GrabMouseEvent();
    void ReleaseMouseEvent();
    void ClearPreviewMouseEventCallback();
    void SetupPreviewMouseEventCallback(std::function<bool(MAUIMouseEvent)>&& func);
    bool HasPreviewMouseEventCallback() const;
private:
    bool OnPreviewMouseEvent(const MAUIMouseEvent& evt);
    bool OnMouseEvent(const MAUIMouseEvent& evt);
    bool OnKeyboardEvent(const AUIKeyboardEvent& evt);
    void OnTickTimeEvent(const std::chrono::milliseconds& prevTickTime, const std::chrono::milliseconds& curTickTime);
    bool OnSetCursorEvent(AUICursorIcon& cursoricon);
    std::function<bool(MAUIMouseEvent)> m_PreviewMouseCallback;


    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
public:
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon);



    //////////////////////////////////////////////////////////////////////////
    // Mouse event
    // NOTE
    //      - return 'true' : Don't pass through this event anymore.
    //      - return 'false' : Pass through this event who can handle it.
private:
    void MouseEnter();
    void MouseLeave();
    void MouseHover();
    bool MouseLBtnDblClk(MAUIMouseEvent::EventFlag flag);
    bool MouseLBtnDown(MAUIMouseEvent::EventFlag flag);
    bool MouseLBtnUp(MAUIMouseEvent::EventFlag flag);
    bool MouseRBtnDblClk(MAUIMouseEvent::EventFlag flag);
    bool MouseRBtnDown(MAUIMouseEvent::EventFlag flag);
    bool MouseRBtnUp(MAUIMouseEvent::EventFlag flag);
    bool MouseMBtnDblClk(MAUIMouseEvent::EventFlag flag);
    bool MouseMBtnDown(MAUIMouseEvent::EventFlag flag);
    bool MouseMBtnUp(MAUIMouseEvent::EventFlag flag);
    bool MouseMove(MAUIMouseEvent::EventFlag flag);
    bool MouseWheel(MAUIMouseEvent::EventFlag flag, float delta);
protected:
    virtual void OnMouseEnter() { /* Implement in subclass */ }
    virtual void OnMouseLeave() { /* Implement in subclass */ }
    virtual void OnMouseHover() { /* Implement in subclass */ }
    virtual bool OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseRBtnDblClk(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseMBtnDblClk(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseRBtnDown(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseMBtnDown(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseRBtnUp(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseMBtnUp(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseMove(MAUIMouseEvent::EventFlag flag) { /* Implement in subclass */ return true; }
    virtual bool OnMouseWheel(MAUIMouseEvent::EventFlag flag, float delta) { /* Implement in subclass */ return false; }


    //////////////////////////////////////////////////////////////////////////
    // Keyboard event
protected:
    bool KeyDown(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode);
    bool KeyUp(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode);
    bool KeyChar(AUIKeyboardEvent::MaskCode mask, unsigned int charcode, unsigned int repcount, unsigned int flag);
    bool KeyIMEStart();
    bool KeyIMEComp(unsigned int charcode, int64_t param);
    bool KeyIMEEnd();
    bool KeyIMEChar(unsigned int charcode, int64_t param);
protected:
    virtual bool OnKeyDown(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode) { return false; /* Implement in subclass */ }
    virtual bool OnKeyUp(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode) { return false; /* Implement in subclass */ }
    virtual bool OnChar(AUIKeyboardEvent::MaskCode mask, unsigned int charcode, unsigned int repcount, unsigned int flag) { return false; /* Implement in subclass */ }
    virtual bool OnKeyIMEStart() { return false; /* Implement in subclass */ }
    virtual bool OnKeyIMEComp(unsigned int charcode, int64_t param) { return false; /* Implement in subclass */ }
    virtual bool OnKeyIMEEnd() { return false; /* Implement in subclass */ }
    virtual bool OnKeyIMEChar(unsigned int charcode, int64_t param) { return false; /* Implement in subclass */ }
    virtual bool OnCopy() { return false; /* Implement in subclass */ }
    virtual bool OnPaste() { return false; /* Implement in subclass */ }
    virtual bool OnCut() { return false; /* Implement in subclass */ }



    //////////////////////////////////////////////////////////////////////////
    // Tick time event
protected:
    void TickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime);
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime);
    std::chrono::milliseconds GetTimeTick() const { return m_CurTimeTick; }
private:
    std::chrono::milliseconds m_CurTimeTick;


    //////////////////////////////////////////////////////////////////////////
    // Animation Helper
public:
    bool IsAnimRunning() const { return m_bAnimRunning; }
    std::chrono::milliseconds GetAnimStartTick() const { return m_AnimStartTick; }
protected:
    void StartAnimRunning();
    void StopAnimRunning();
    void ResetAnimRunning();
private:
    std::chrono::milliseconds m_AnimStartTick = std::chrono::milliseconds::zero();
    bool m_bAnimRunning;





    //////////////////////////////////////////////////////////////////////////
    // Timing
public:
    std::chrono::milliseconds GetPressTime() const;
private:
    std::chrono::milliseconds m_TimePressStart = std::chrono::milliseconds::zero();


    ///////////////////////////////////////////////////////////////////////////
    //  Sensor
public:
    void AddSensor(const std::shared_ptr< AUISensor >& pSensor) {
        if (IsInstanced())
            throw;
        pSensor->_set_owner_widget(this);
        m_aSensors.emplace_back(pSensor);
    }
    void ClearSensors() {
        if (IsInstanced())
            throw;
        m_aSensors.clear();
    }
    const std::vector<std::shared_ptr<AUISensor>>& GetSensors() const {
        return m_aSensors;
    }

	void _invalidate_sensor();
	void _invalidate_ui_state();
	//const AUISensor* GetCurSensor() const;
private:
    //AUISensorManager* GetSensorManager();
    std::vector<std::shared_ptr<AUISensor>> m_aSensors;

    ///////////////////////////////////////////////////////////////////////////
    //  Compass
public:
    void AddCompass(const std::shared_ptr< AUICompass >& pCompass);
    void ClearCompasses() {
        m_aCompasses.clear();
    }
    const std::vector<std::shared_ptr<AUICompass>>& GetCompasses() const {
        return m_aCompasses;
    }
private:
    void UpdateCompass();
    std::vector<std::shared_ptr<AUICompass>> m_aCompasses;



    ///////////////////////////////////////////////////////////////////////////
    //  Sensor & Compass 2D Visual Default Initialize

public:
    void LoadDefault2DSensor();
    void UpdateDefault2DSensorSize();
private:
    bool m_bDefault2DSensor;
    //bool m_bDefault2DCompass;




    //////////////////////////////////////////////////////////////////////////
    // Dragging
protected:
    virtual bool OnDragging() { return false; /* Implement in subclass */ }

    //////////////////////////////////////////////////////////////////////////
    // Update
public:
    bool Update();
    void UpdateSize();
    bool IsDirty() const noexcept {
        return m_bDirty;
    }
    void Invalidate() noexcept;
    void InvalidateChildren() noexcept;
protected:
    virtual void OnUpdate() { /* Implement in subclass */ }
private:
    bool m_bDirty;


    //////////////////////////////////////////////////////////////////////////
    // Opacity
public:
    void SetOpacity(SkScalar opacity) {
        m_Opacity = std::clamp(opacity, SkScalar(0), SkScalar(1));
        Invalidate();
    }
    SkScalar GetOpacity() const noexcept {
        return m_Opacity;
    }
private:
    SkScalar m_Opacity;


    //////////////////////////////////////////////////////////////////////////
    // Instance
protected:
    AUIInstance* GetInstance() const;


    // Drawable
public:
    virtual AUIDrawable* GetAsDrawable() const;



    //////////////////////////////////////////////////////////////////////////
    // Friend class
    friend class AUIApplication;
    friend class AUIWidgetManager;
    friend class AUIWidgetTreeHelper;
};
