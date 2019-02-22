#pragma once

#include "AUILinearLayoutWidget.h"

class AUITab;
class AUITabButtonWidget;

class ALICEUI_API AUITabBarWidget : public AUILinearLayoutWidget
{
    typedef AUILinearLayoutWidget SuperClass;
public:
    AUITabBarWidget();
    virtual ~AUITabBarWidget();

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    AUITabButtonWidget* GetCurrentTabButton();

    //////////////////////////////////////////////////////////////////////////
    // Tab Style
public:
    void SetTabStyle(AUIImageCaptionStyle style);
    AUIImageCaptionStyle GetTabStyle() const;
    void SetTabDefaultTextColor(SkColor color);
    void SetTabUncheckTextColor(SkColor color);
    void SetTabHoverTextColor(SkColor color);
private:
    AUIImageCaptionStyle m_TabStyle;
    SkColor m_TabDefaultTextColor;
    SkColor m_TabUncheckTextColor;
    SkColor m_TabHoverTextColor;

	//////////////////////////////////////////////////////////////////////////
	// UnderLine
public:
	bool IsUnderLine() const { return m_bUnderLine; }
	void SetUnderLine(const bool& val) { m_bUnderLine = val; }
	SkColor GetUnderLineColor() const { return m_UnderLineColor; }
	void SetUnderLineColor(const SkColor& val) { m_UnderLineColor = val; }
private:
	bool m_bUnderLine;
	SkColor m_UnderLineColor;
    //////////////////////////////////////////////////////////////////////////
    // Tab
public:
    void AddTab(const std::shared_ptr< AUITab >& pTab);
    void RemoveTab(const std::shared_ptr< AUITab >& pTab);
    void RemoveTab(const std::shared_ptr< AUIWidget >& pWidget);
    void SetVisibleTab(const std::shared_ptr< AUITab >& pTab, bool bVisible);
    void HideTab(const std::shared_ptr< AUITab >& pTab, bool bHide);
    bool IsHiddenTab(const std::shared_ptr< AUITab >& pTab) const;
    bool IsHiddenTab(const size_t idx) const;
    void ClearTab();
    void SetCurrentTab(const std::shared_ptr< AUITab >& pTab);
    void ReplaceTab(size_t idx, const std::shared_ptr< AUITab >& pTab);
    const std::shared_ptr< AUITab > GetCurrentTab() const { return m_pCurTab; }
    size_t GetTabCount() const { return m_arrTabs.size(); }
    std::shared_ptr< AUITab > FindTabByWidget(const std::shared_ptr< AUIWidget >& pWidget);
    std::shared_ptr< AUITab > FindTabByIndex(const size_t idx) const;
    const std::vector< std::shared_ptr< AUITab > >& GetTabs() const { return m_arrTabs; }
protected:
    virtual std::shared_ptr< AUITabButtonWidget > OnCreateTabButton();
    void OnClickTabButton(AUIWidget* const pWidget);
private:
    std::shared_ptr< AUITab > m_pCurTab;
    std::vector< std::shared_ptr< AUITab > > m_arrTabs;
    std::unordered_map< AUITab*, std::weak_ptr< AUITabButtonWidget > > m_mapTab2Button;


    //////////////////////////////////////////////////////////////////////////
    // Signal
public:
    AUISignal<void(AUITab*)> TabClickSignal;



    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos) override;
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget) override;
    virtual void PopSubWidget() override;
    virtual void ClearSubWidget() override;
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override;
    virtual size_t SubWidgetCount() const override;
};
