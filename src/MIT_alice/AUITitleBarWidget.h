#pragma once

#include "AUIRelativeLayoutWidget.h"

class AUITitleBarTitleWidget;
class AUIImageButtonWidget;
class AUILinearLayoutWidget;

class ALICEUI_API AUITitleBarWidget : public AUIRelativeLayoutWidget
{
    using SuperWidget = AUIRelativeLayoutWidget;
public:
    AUITitleBarWidget();
    virtual ~AUITitleBarWidget();

    //////////////////////////////////////////////////////////////////////////
    // Signals
public:
    AUISignal<void(AUIWidget*)>& GetTitleBarDblClickSignal() const;
    AUISignal<void(AUIWidget*)>& GetDragStartSignal() const;
    AUISignal<void(AUIWidget*)>& GetDragEndSignal() const;
    AUISignal<void(AUIWidget*)>& GetDraggingSignal() const;
    AUISignal<void(AUIWidget*)>& GetMinimizeSignal() const;
    AUISignal<void(AUIWidget*)>& GetMaximizeSignal() const;
    AUISignal<void(AUIWidget*)>& GetCloseSignal() const;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& caption);
    std::wstring GetTitle() const;

    //////////////////////////////////////////////////////////////////////////
    // Widgets
public:
    enum class SysBtnFlag {
        kNone = 0x0,
        kMinimize = 0x1,
        kMaximize = 0x2,
        kClose = 0x4,
        kAll = kMinimize | kMaximize | kClose
    };

    void SetVisibleSysButton(SysBtnFlag sysbtnFlag = SysBtnFlag::kAll);
    AUITitleBarTitleWidget* const GetTitleBar() const { return m_pTitleBar.get(); }
private:
    std::shared_ptr< AUITitleBarTitleWidget > m_pTitleBar;
    std::shared_ptr< AUIImageButtonWidget > m_pMinimizeButton;
    std::shared_ptr< AUIImageButtonWidget > m_pMaximizeButton;
    std::shared_ptr< AUIImageButtonWidget > m_pCloseButton;
};

AUIEnableEnumClassOperator(AUITitleBarWidget::SysBtnFlag);

