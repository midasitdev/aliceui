#pragma once

#include "AUIAPIDef.h"

//////////////////////////////////////////////////////////////////////////
// UI State
class ALICEUI_API AUIState final
{
public:
    AUIState() noexcept;
    ~AUIState() = default;
    AUIState(const AUIState&) noexcept = default;
    AUIState(AUIState&&) noexcept = default;
    AUIState& operator=(const AUIState&) noexcept = default;
    AUIState& operator=(AUIState&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////////
    // States
public:
    enum Index : unsigned int
    {
        kDefault = 0,    // Default stuff (e.g. stateless value)

        // Basic widget state
        kCreated,        // Created or not
        kVisible,        // Visible or not
        kFreezed,        // Freezed or not
        kPressed,        // Pressed or not
        kIgnored,        // Ignored or not

        // Drag
        kDraggable,      // Draggable
        kDragging,       // Dragging or not

        // Focus
        kFocusable,      // Focusable
        kFocused,        // Focused or not

        // Check
        kCheckable,      // Checkable
        kChecked,        // Checked or not
        kCheckIndeterminate, // Checked but indeterminate

        // Select
        kSelectable,     // Selectable
        kSelected,       // Selected or not

        // Disable
        kDisabled,       // Disabled or not

        // Mouse
        kMouseHovered,   // Hovered or not
        kMouseLDown,     // Mouse left button down
        kMouseMDown,     // Mouse middle button down
        kMouseRDown,     // Mouse right button down

        // Click
        kClickable,      // Clickable

        // Total
        kTotalCount
    };
private:
    std::array< bool, kTotalCount > m_States = { false, };


    //////////////////////////////////////////////////////////////////////////
    // State Setter
public:
    void Set(Index idx, bool val) noexcept {
        m_States[idx] = val;
    }
    void SetCreated(bool state) noexcept {
        Set(kCreated, state);
    }
    void SetVisible(bool state) noexcept {
        Set(kVisible, state);
    }
    void SetFreeze(bool state) noexcept {
        Set(kFreezed, state);
    }
    void SetPressed(bool state) noexcept {
        Set(kPressed, state);
    }
    void SetIgnored(bool state) noexcept {
        Set(kIgnored, state);
    }
    void SetDraggable(bool state) noexcept {
        Set(kDraggable, state);
    }
    void SetDragging(bool state) noexcept {
        Set(kDragging, state);
    }
    void SetFocusable(bool state) noexcept {
        Set(kFocusable, state);
    }
    void SetFocused(bool state) noexcept {
        Set(kFocused, state);
    }
    void SetCheckable(bool state) noexcept {
        Set(kCheckable, state);
    }
    void SetChecked(bool state) noexcept {
        Set(kChecked, state);
    }
    void SetCheckedIndeterminate(bool state) noexcept {
        Set(kCheckIndeterminate, state);
    }
    void SetSelectable(bool state) noexcept {
        Set(kSelectable, state);
    }
    void SetSelected(bool state) noexcept {
        Set(kSelected, state);
    }
    void SetDisabled(bool state) noexcept {
        Set(kDisabled, state);
    }
    void SetMouseHovered(bool state) noexcept {
        Set(kMouseHovered, state);
    }
    void SetMouseLDown(bool state) noexcept {
        Set(kMouseLDown, state);
    }
    void SetMouseMDown(bool state) noexcept {
        Set(kMouseMDown, state);
    }
    void SetMouseRDown(bool state) noexcept {
        Set(kMouseRDown, state);
    }
    void SetClickable(bool state) noexcept {
        Set(kClickable, state);
    }


    //////////////////////////////////////////////////////////////////////////
    // State Getter
public:
    bool Get(Index idx) const noexcept {
        return m_States[idx];
    }
    bool IsCreated() const noexcept {
        return Get(kCreated);
    }
    bool IsDraggable() const noexcept {
        return Get(kDraggable);
    }
    bool IsDragging() const noexcept {
        return Get(kDragging);
    }
    bool IsVisible() const noexcept {
        return Get(kVisible);
    }
    bool IsFreezed() const noexcept {
        return Get(kFreezed);
    }
    bool IsPressed() const noexcept {
        return Get(kPressed);
    }
    bool IsIgnored() const noexcept {
        return Get(kIgnored);
    }
    bool IsFocusable() const noexcept {
        return Get(kFocusable);
    }
    bool IsFocused() const noexcept {
        return Get(kFocused);
    }
    bool IsCheckable() const noexcept {
        return Get(kCheckable);
    }
    bool IsChecked() const noexcept {
        return Get(kChecked);
    }
    bool IsCheckedIndeterminate() const noexcept {
        return Get(kCheckIndeterminate);
    }
    bool IsSelectable() const noexcept {
        return Get(kSelectable);
    }
    bool IsSelected() const noexcept {
        return Get(kSelected);
    }
    bool IsDisabled() const noexcept {
        return Get(kDisabled);
    }
    bool IsMouseHovered() const noexcept {
        return Get(kMouseHovered);
    }
    bool IsMouseLDown() const noexcept {
        return Get(kMouseLDown);
    }
    bool IsMouseMDown() const noexcept {
        return Get(kMouseMDown);
    }
    bool IsMouseRDown() const noexcept {
        return Get(kMouseRDown);
    }
    bool IsClickable() const noexcept {
        return Get(kClickable);
    }


    //////////////////////////////////////////////////////////////////////////
    // State Reset
public:
    void ResetWidgetState() noexcept;
    void ResetDrag() noexcept;
    void ResetFocus() noexcept;
    void ResetCheck() noexcept;
    void ResetSelect() noexcept;
    void ResetMouse() noexcept;
    void ResetAll() noexcept;


    size_t CheckState(const AUIState& b) noexcept;
    size_t StatePriority() const noexcept;

    bool operator<(const AUIState& b) const noexcept
    {
        return StatePriority() < b.StatePriority();
    }

    bool operator==(const AUIState& b) const noexcept
    {
        return m_States == b.m_States;
    }

    size_t ToHash() const noexcept;
};

struct ALICEUI_API AUIStateHasher
{
    bool operator()(const AUIState& _s) const noexcept {
        return _s.ToHash();
    }
};
