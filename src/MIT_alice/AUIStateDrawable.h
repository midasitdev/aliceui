#pragma once

#include "AUIDrawable.h"
#include "AUIState.h"

#include <unordered_map>

class ALICEUI_API AUIStateDrawable : public AUIDrawable
{
public:
    AUIStateDrawable();
    ~AUIStateDrawable() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    bool IsRefreshDraw() const override {
        return m_bRefreshDraw;
    }
private:
    bool m_bRefreshDraw;


    //////////////////////////////////////////////////////////////////////////
    // UI State
    // Ignored state
    //      - None, Created
    // Selection order (we use last selected)
    //      - Default (true or false) -> Enabled -> Focusable -> Focused -> Checkable -> Checked -> Selectable
    //          -> Selected -> Draggable -> Dragging -> Hovered -> Pressed -> Left Down
    //          -> Middle Down -> Right Down -> Freezed -> Disabled(Not Enabled)
protected:
    void OnChangeDrawUIState() override;


    //////////////////////////////////////////////////////////////////////////
    // Level Index
protected:
    void OnChangeLevelIndex() override;

    //////////////////////////////////////////////////////////////////////////
    // Bound
protected:
    void OnSetDrawBound() override;
    void OnSetDrawPadding() override;


    //////////////////////////////////////////////////////////////////////////
    // Current Drawable
public:
    void SetTrueStateDrawable(AUIState::Index idx, const std::shared_ptr< AUIDrawable >& pDrawable);
    void SetFalseStateDrawable(AUIState::Index idx, const std::shared_ptr< AUIDrawable >& pDrawable);
protected:
    AUIDrawable* GetCurDrawable() const {
        return m_pCurDrawable.get();
    }
private:
    std::shared_ptr< AUIDrawable > FindFromTrueState(AUIState::Index idx) const;
    std::shared_ptr< AUIDrawable > FindFromFalseState(AUIState::Index idx) const;
    std::shared_ptr< AUIDrawable > m_pCurDrawable;
    std::unordered_map< AUIState::Index, std::shared_ptr< AUIDrawable > > m_mapTrueState2Drawable;
    std::unordered_map< AUIState::Index, std::shared_ptr< AUIDrawable > > m_mapFalseState2Drawable;
};
