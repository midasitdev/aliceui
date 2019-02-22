#pragma once

#include "AUICommonDef.h"
#include "AUIState.h"
#include "AUISkiaConfig.h"

class ALICEUI_API AUIDrawable
{
public:
    AUIDrawable() = default;
    virtual ~AUIDrawable() = default;



    //////////////////////////////////////////////////////////////////////////
    // Draw
public:
    void Draw(int x, int y, int width, int height);
    void Draw(SkCanvas* canvas);
    virtual bool IsRefreshDraw() const;     // TODO: replace with better interface
protected:
    virtual void OnDraw(SkCanvas* canvas) { /* Implement in subclass */ }


    //////////////////////////////////////////////////////////////////////////
    // UI State
public:
    void SetDrawUIState(const AUIState& state);
    const AUIState& GetDrawUIState() const { return m_DrawUIState; }
protected:
    virtual void OnChangeDrawUIState() { /* Implement in subclass */ }
private:
    AUIState m_DrawUIState;


    //////////////////////////////////////////////////////////////////////////
    // Level
public:
    void SetLevelIndex(int val);
    int GetLevelIndex() const noexcept { return m_LevelIndex; }
protected:
    virtual void OnChangeLevelIndex() { /* Implement in sublcass */ }
private:
    int m_LevelIndex = 0;

    //////////////////////////////////////////////////////////////////////////
    // Weight
public:
    void SetBlendFactor(float w) { m_fWeight = std::clamp(w, 0.0f, 1.0f); }
    float GetBlendFactor() const noexcept { return m_fWeight; }
private:
    float m_fWeight = 0.0f;


    //////////////////////////////////////////////////////////////////////////
    // Bitmap Buffer
public:
    sk_sp<SkImage> GetImageBuffer() const;
private:
    sk_sp<SkSurface> m_pSurface;

    //////////////////////////////////////////////////////////////////////////
    // Anti-Aliasing
public:
    bool IsUseAA() const noexcept { return m_bUseAA; }
    void SetUseAA(bool aa) noexcept { m_bUseAA = aa; }
private:
    bool m_bUseAA = false;


    //////////////////////////////////////////////////////////////////////////
    // Bound
public:
    void SetDrawBound(const SkRect& bound);
    void SetDrawPadding(const SkRect& padding);
    SkRect GetDrawBound() const { return m_DrawBound; }
    SkRect GetDrawPadding() const { return m_DrawPadding; }
    SkRect GetContentRect() const;
protected:
    virtual void OnSetDrawBound() { /* Implement in subclass */ }
    virtual void OnSetDrawPadding() { /* Implement in subclass */ }
private:
    SkRect m_DrawBound = SkRect::MakeEmpty();
    SkRect m_DrawPadding = SkRect::MakeEmpty();

};
