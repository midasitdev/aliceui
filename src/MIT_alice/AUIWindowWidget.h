#pragma once

#include "AUILinearLayoutWidget.h"

class AUIWindowTitleBarWidget;

class ALICEUI_API AUIWindowWidget : public AUILinearLayoutWidget
{
    using SuperWidget = AUILinearLayoutWidget;
public:
    AUIWindowWidget();
    virtual ~AUIWindowWidget();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;

    //////////////////////////////////////////////////////////////////////////
    // Signals
public:
    AUISignal<void(AUIWidget*) >& GetTitleBarDblClickSignal() const;
    AUISignal<void(AUIWidget*) >& GetDragStartSignal() const;
    AUISignal<void(AUIWidget*) >& GetDragEndSignal() const;
    AUISignal<void(AUIWidget*)>& GetDraggingSignal() const;
    AUISignal<void(AUIWidget*) >& GetMinimizeSignal() const;
    AUISignal<void(AUIWidget*) >& GetMaximizeSignal() const;
    AUISignal<void(AUIWidget*) >& GetCloseSignal() const;

    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;

    //////////////////////////////////////////////////////////////////////////
    // Position
protected:
    virtual void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos) override;
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget) override;
    virtual void PopSubWidget() override;
    virtual void ClearSubWidget() override;
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override;
    virtual size_t SubWidgetCount() const override;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& caption);
    std::wstring GetTitle() const;
    void SetTitleColor(const SkColor& titleColor);
    void SetTitleStyle(const SkFontStyle& titleStyle);
    void SetTitleFontName(const std::wstring& fontName);

    //////////////////////////////////////////////////////////////////////////
    // Widgets
public:
    void SetIgnoreTitleBar(bool ignore);
    void SetIgnoreSysButton(bool ignore);
    void SetIgnoreSysButton(bool ignoreMinimize, bool ignoreMaximize, bool ignoreClose);
    std::shared_ptr< AUIWindowTitleBarWidget > GetTitleBarWidget() const {
        return m_pTitleBar;
    }
private:
    std::shared_ptr< AUIWindowTitleBarWidget > m_pTitleBar;
    std::shared_ptr< AUILinearLayoutWidget > m_pContent;
};
