#pragma once


#include "AUIAPIDef.h"
#include "AUIWidgetManager.h"

class AUITooltip;
class AUIWidget;
class AUIForm;
class AUIInstance;
class AUILinearLayoutWidget;
class AUIRasterTooltipWidget;

class ALICEUI_API AUIRasterWidgetManager : public AUIWidgetManager
{
public:
    AUIRasterWidgetManager();
    ~AUIRasterWidgetManager() override;


    //////////////////////////////////////////////////////////////////////////
    // Invoke / Dismiss
protected:
    bool OnInvoke(const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt) override;
    bool OnDismiss(const std::shared_ptr< AUIWidget >& pWidget) override;
private:
    std::unordered_map< AUIWidget*, std::shared_ptr< AUIForm > > m_Popups;


    //////////////////////////////////////////////////////////////////////////
    // Tooltip
protected:
    void OnShowTooltip(const std::shared_ptr< AUITooltip >& pTooltip, int x, int y) override;
    void OnHideTooltip() override;
private:
    std::weak_ptr<AUITooltip> m_wpCurTooltip;
    std::shared_ptr<AUIRasterTooltipWidget> m_pTooltipBase;
    std::shared_ptr<AUIForm> m_pTooltipForm;


    //////////////////////////////////////////////////////////////////////////
    // Camera Info
public:
    glm::mat4 GetViewingMatrix() const override;
    glm::mat4 GetProjectionMatrix() const override;
    glm::vec4 GetViewport() const override;
private:
    glm::vec4 m_Viewport;

    //////////////////////////////////////////////////////////////////////////
    // Instance
protected:
    std::shared_ptr< AUIInstance > OnRegisterWidget(const std::shared_ptr< AUIWidget >& pWidget) override;

    //////////////////////////////////////////////////////////////////////////
    // Rendering
public:
    void Render(SkCanvas* canvas);
    void SetSize(int width, int height);
};
