#pragma once

#include "AUIDrawable.h"
#include "AUIStateFeature.h"


struct ALICEUI_API AUIImageSrcData
{
    std::shared_ptr<AUIDrawable> _drawable;
};

class ALICEUI_API AUIStateImgSrc : public AUIStateFeature<AUIImageSrcData>
{
public:
    AUIStateImgSrc() = default;
    ~AUIStateImgSrc() override = default;
};

class ALICEUI_API AUIStateImgSrcUpdator : public AUIStateFeatureUpdator<AUIImageSrcData>
{
public:
    AUIStateImgSrcUpdator(std::shared_ptr<AUIStateImgSrc> pSrc);
    ~AUIStateImgSrcUpdator() override = default;
};

class ALICEUI_API AUIStateListDrawable : public AUIDrawable
{
public:
    AUIStateListDrawable();
    ~AUIStateListDrawable() override;


    void SetStateImgsrc(std::shared_ptr<AUIStateImgSrc> pSrc);

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    void OnSetDrawBound() override;


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

    std::shared_ptr<AUIDrawable> m_pCurDrawable;
    std::shared_ptr<AUIStateImgSrcUpdator>  m_pStateUpdtator;
};
