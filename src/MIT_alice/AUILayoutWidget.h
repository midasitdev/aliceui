#pragma once

#include "AUIGroupWidget.h"
#include "AUILayerDrawable.h"


class AUILayoutBase;
class AUILayoutManager;
class ALICEUI_API AUILayoutWidget : public AUIGroupWidget, public AUILayerDrawable
{
    using SuperWidget = AUIGroupWidget;
public:
    AUILayoutWidget();
    ~AUILayoutWidget() override;


    // Drawable
public:
    AUIDrawable * GetAsDrawable() const override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;

protected:
    void OnUpdateChildPosition() override;
public:
    void SetLayout(const std::shared_ptr<AUILayoutBase>& pLayout);
private:
    std::unique_ptr<AUILayoutManager> m_pLayoutManager;


    //////////////////////////////////////////////////////////////////////////
    // Rect
public:
    SkRect GetRect() const;


    //////////////////////////////////////////////////////////////////////////
    // Style Sheet
protected:
    void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value) override;

    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    enum DrawableLayer
    {
        BackgroundLayer = 0,
        ForegroundLayer,
        LayerCount
    };
protected:
    std::shared_ptr<AUIDrawable> GetBackgroundLayer() const {
        return GetLayerAt(BackgroundLayer);
    }
    std::shared_ptr<AUIDrawable> GetForegroundLayer() const {
        return GetLayerAt(ForegroundLayer);
    }

    //////////////////////////////////////////////////////////////////////////
    // Mouse Event
protected:
    void OnMouseHover() override;
    void OnMouseLeave() override;


    //////////////////////////////////////////////////////////////////////////
    // Status
protected:
    void OnUpdate() override;


    //////////////////////////////////////////////////////////////////////////
    // Debug Tool
private:
    SkColor m_DebugColor;



    //////////////////////////////////////////////////////////////////////////
    // Tick time event
protected:
    void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;


    //////////////////////////////////////////////////////////////////////////
    // Only layout parent is supported!
protected:
    bool OnSetParent(AUIWidget* const pParent) override;


    //////////////////////////////////////////////////////////////////////////
    // Background drawable
public:
    void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
    void SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);


    //////////////////////////////////////////////////////////////////////////
    // Layout information
public:
    bool IsLayoutRoot() const;


    //////////////////////////////////////////////////////////////////////////
    // NOTE : milestone
public:
    void SetAllDisabled(bool state);
    void SetAllIgnored(bool state);
protected:
    virtual void OnSetAllDisabled(bool state);
    virtual void OnSetAllIgnored(bool state);
};
