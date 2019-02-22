#pragma once

#include "AUILinearLayoutWidget.h"

class AUITab;
class AUITabBarWidget;
class AUITransitionWidget;

class ALICEUI_API AUITabWidget : public AUILinearLayoutWidget
{
public:
    AUITabWidget();
    explicit AUITabWidget(const std::shared_ptr< AUITabBarWidget >& pTabBar);
    virtual ~AUITabWidget();


    //////////////////////////////////////////////////////////////////////////
    // Default Size
protected:
    virtual void OnSetDefaultSize(const AUIScalar2& size) override;


    //////////////////////////////////////////////////////////////////////////
    // Tab Style
public:
    void SetTabImageCaptionStyle(AUIImageCaptionStyle style);
    AUIImageCaptionStyle GetTabImageCaptionStyle() const;


    //////////////////////////////////////////////////////////////////////////
    // Tabs
public:
    void AddTab(const std::shared_ptr< AUITab >& pTab);
    void RemoveTab(const std::shared_ptr< AUITab >& pTab);
    void RemoveTab(const std::shared_ptr< AUIWidget >& pWidget);
    void SetVisibleTab(const std::shared_ptr< AUITab >& pTab, bool bVisible);
    void HideTab(const std::shared_ptr< AUITab >& pTab, bool bHide);
    bool IsHiddenTab(const std::shared_ptr< AUITab >& pTab) const;
    bool IsHiddenTab(const size_t idx) const;
    void ClearTab();
    void ReplaceTab(size_t idx, const std::shared_ptr< AUITab >& pTab);
    size_t GetTabCount() const;
	std::shared_ptr< AUITabBarWidget > GetTabBar() const { return m_pBarWidget; }
private:
    std::shared_ptr< AUITabBarWidget > m_pBarWidget;

	//////////////////////////////////////////////////////////////////////////
	// UnderLine
	void SetUnderLine(std::shared_ptr<const AUIWidgetStyle> style);

    //////////////////////////////////////////////////////////////////////////
    // SubWidget
public:
    void SetCurrentTab(AUITab* const pTab) { TabClicked(pTab); }
    void SetCurrentTab(const std::shared_ptr< AUITab >& pTab) { TabClicked(pTab.get()); }
    std::shared_ptr< AUITab > GetCurrentTab() const;
    std::shared_ptr< AUITab > FindTabByWidget(const std::shared_ptr< AUIWidget >& pWidget) const;
    std::shared_ptr< AUITab > FindTabByIndex(const size_t idx) const;
protected:
    AUITransitionWidget* GetContentWidget() const {
        return m_pContentWidget.get();
    }
private:
    void TabClicked(AUITab* const pTab);
    std::shared_ptr<AUITransitionWidget> m_pContentWidget;


    //////////////////////////////////////////////////////////////////////////
    // Public child interface
private:
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos) override;
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget) override;
    virtual void PopSubWidget() override;
    virtual void ClearSubWidget() override;
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override;
    virtual size_t SubWidgetCount() const override;


    //////////////////////////////////////////////////////////////////////////
    // MSS Support
public:
    void SetHeaderStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetHeaderTabButtonStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetHeaderTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetHeaderImageStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
private:
    std::shared_ptr<const AUIWidgetStyle> m_TabButtonStyle;
    std::shared_ptr<const AUIWidgetStyle> m_TabImageStyle;
    std::shared_ptr<const AUIWidgetStyle> m_TabTextStyle;
};
