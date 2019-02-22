#include "pch.h"
#include "AUIState.h"

AUIState::AUIState() noexcept
{
    ResetAll();
}

void AUIState::ResetWidgetState() noexcept
{
    SetCreated(false);
    SetVisible(true);
    SetIgnored(false);
    SetFreeze(false);
    SetPressed(false);
    SetDisabled(false);
}

void AUIState::ResetDrag() noexcept
{
    SetDraggable(false);
    SetDragging(false);
}

void AUIState::ResetFocus() noexcept
{
    SetFocusable(true);
    SetFocused(false);
}

void AUIState::ResetCheck() noexcept
{
    SetCheckable(false);
    SetChecked(false);
    SetCheckedIndeterminate(false);
}

void AUIState::ResetSelect() noexcept
{
    SetSelectable(false);
    SetSelected(false);
}

void AUIState::ResetMouse() noexcept
{
    SetMouseHovered(false);
    SetMouseLDown(false);
    SetMouseMDown(false);
    SetMouseRDown(false);
}

void AUIState::ResetAll() noexcept
{
    Set(kDefault, true); // Default
    ResetWidgetState();
    ResetDrag();
    ResetFocus();
    ResetCheck();
    ResetSelect();
    ResetMouse();
    SetClickable(false);
}

size_t AUIState::CheckState(const AUIState& b) noexcept
{
    size_t iRes = 0;
    size_t iFlagNum = 0;
    for (size_t idx = 0; idx < m_States.size(); ++idx)
    {
        iFlagNum += m_States[idx] ? 1 : 0;
        iRes += (m_States[idx] && b.m_States[idx]) ? 1 : 0;
    }
    if (iFlagNum == iRes)
        return iRes;
    return 0;
}

size_t AUIState::StatePriority() const noexcept
{
    // TOOD : Combined state priority
    if (m_States[kFreezed])
        return 15;
    else if (m_States[kMouseRDown])
        return 14;
    else if (m_States[kMouseMDown])
        return 13;
    else if (m_States[kMouseLDown])
        return 12;
    else if (m_States[kPressed])
        return 11;
    else if (m_States[kMouseHovered])
        return 10;
    else if (m_States[kDragging])
        return 9;
    else if (m_States[kDraggable])
        return 8;
    else if (m_States[kSelected])
        return 7;
    else if (m_States[kSelectable])
        return 6;
    else if (m_States[kChecked])
        return 5;
    else if (m_States[kCheckable])
        return 4;
    else if (m_States[kFocused])
        return 3;
    else if (m_States[kFocusable])
        return 2;
    else if (m_States[kDisabled])
        return 1;
    else
        return 0;
}

size_t AUIState::ToHash() const noexcept
{
    static_assert(AUIState::kTotalCount < 64, "Check total");
    size_t _hashval = 0;
    for (size_t idx = 0; idx < m_States.size(); ++idx)
    {
        const auto s = static_cast<size_t>(m_States[idx]);
        _hashval |= size_t(s << idx);
    }
    return _hashval;
}
