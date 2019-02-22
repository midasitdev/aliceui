#pragma once

#include "AUICommonDef.h"

class AUIDrawable;
class AUIWidget;
class AUIWidgetStyle;

class ALICEUI_API AUITab : public std::enable_shared_from_this< AUITab >
{
public:
    AUITab();
    virtual ~AUITab();


    //////////////////////////////////////////////////////////////////////////
    // Create
public:
    static std::shared_ptr< AUITab > CreateTab(const std::shared_ptr< AUIWidget >& pWidget);
    static std::shared_ptr< AUITab > CreateTab(const std::wstring& name, const std::shared_ptr< AUIWidget >& pWidget);
    static std::shared_ptr< AUITab > CreateTab(const std::wstring& name, const sk_sp<SkImage>& pIcon, const std::shared_ptr< AUIWidget >& pWidget);
    static std::shared_ptr< AUITab > CreateTab(const std::wstring& name, const std::shared_ptr< AUIDrawable >& pIcon, const std::shared_ptr< AUIWidget >& pWidget);
    static std::shared_ptr< AUITab > CreateTab(const std::shared_ptr< AUIWidget >& pTabButtonWidget, const std::shared_ptr< AUIWidget >& pContentWidget);


    //////////////////////////////////////////////////////////////////////////
    // MSS Support
public:
    void SetButtonStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetImageStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);

	//////////////////////////////////////////////////////////////////////////
    // Tab 순서를 위한 대환장의 몸짓
	void SetFirst() { m_bFirst = true; }
	void SetLast() { m_bLast = true; }
	bool GetFirst() const { return m_bFirst; }
	bool GetLast() const { return m_bLast; }

    //////////////////////////////////////////////////////////////////////////
    // Tab Button
public:
    void SetTabButtonWidget(const std::shared_ptr< AUIWidget >& pTabButtonWidget) { m_pTabButtonWidget = pTabButtonWidget; }
    std::shared_ptr< AUIWidget > GetTabButtonWidget() const { return m_pTabButtonWidget; }
private:
    std::shared_ptr< AUIWidget > m_pTabButtonWidget;
	bool m_bFirst;
	bool m_bLast;


    //////////////////////////////////////////////////////////////////////////
    // Name
public:
    void SetName(const std::wstring& name) { m_Name = name; }
    std::wstring GetName() const { return m_Name; }
private:
    std::wstring m_Name;


    //////////////////////////////////////////////////////////////////////////
    // Icon
public:
    void SetIcon(const std::shared_ptr< AUIDrawable >& pIcon);
    std::shared_ptr< AUIDrawable > GetIcon() const { return m_pIcon; }
private:
    std::shared_ptr< AUIDrawable > m_pIcon;


    //////////////////////////////////////////////////////////////////////////
    // Widget
public:
    void SetWidget(const std::shared_ptr< AUIWidget >& pWidget) { m_pWidget = pWidget; }
    std::shared_ptr< AUIWidget > GetWidget() const { return m_pWidget; }
private:
    std::shared_ptr< AUIWidget > m_pWidget;
};
