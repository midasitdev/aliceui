#pragma once


#include "AUIAPIDef.h"
#include "AUISkiaConfig.h"

class AUIWidget;
class AUIRasterWidgetManager;

class ALICEUI_API AUIRasterBase
{
public:
    AUIRasterBase();
    virtual ~AUIRasterBase();

    //////////////////////////////////////////////////////////////////////////
    // Update
public:
    void AsyncUpdate();
    void SendTickTimeEvent();
    bool SendSetCursorEvent();
private:
    std::chrono::milliseconds m_PrevTickTime = std::chrono::milliseconds::zero();
    std::chrono::milliseconds m_CurTickTime = std::chrono::milliseconds::zero();

    //////////////////////////////////////////////////////////////////////////
    // Render
public:
    void Render(const sk_sp<SkSurface>& pSurface, bool eraseBackground = true);
    void SetViewport(int width, int height);
    void SetBackgroundColor(const SkColor color) {
        m_BackgroundColor = color;
    }
    SkColor GetBackgroundColor() const {
        return m_BackgroundColor;
    }
    void MakeNeedRedraw() {
        m_bNeedRedraw = true;
    }
    bool IsNeedRedraw() const {
        return m_bNeedRedraw;
    }
private:
    SkColor m_BackgroundColor = SkColorSetRGB(255, 255, 255);
    bool m_bNeedRedraw = true;

    //////////////////////////////////////////////////////////////////////////
    // UI Manager
public:
    AUIRasterWidgetManager* GetWidgetManager() const;
private:
    std::unique_ptr<AUIRasterWidgetManager> m_pWidgetManager;


    //////////////////////////////////////////////////////////////////////////
    // Root Widget
public:
    void SetRootWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void UpdateWidgetSize();
    void UpdateWidgetChildPosition();
protected:
    AUIWidget* GetRootWidget() const {
        return m_pRootWidget.get();
    }
private:
    std::shared_ptr< AUIWidget > m_pRootWidget;

};
