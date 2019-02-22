#pragma once


#include "AUILinearLayoutWidget.h"
#include <queue>

class AUIScrollableWidget;
class AUIEditWidget;
class ALICEUI_API AUIConsoleWidget : public AUILinearLayoutWidget
{
public:
    AUIConsoleWidget();
    virtual ~AUIConsoleWidget();




public:
    AUISignal<void(AUIWidget*, const std::wstring&)> SignalAddInput;
    void AddText(const std::wstring& text);
    void AddText(const std::wstring& text, const SkColor& color);
    void ClearScreen();
    void SetMaxListSize(size_t size);
    void SetMultilineType(AUITextLineFeed multilineType);
    AUITextLineFeed GetMultilineType() const {
        return m_MultilineType;
    }
private:
    void OnEditReturn(AUIWidget*);
    std::shared_ptr< AUIScrollableWidget > m_pScroll;
    std::shared_ptr< AUIEditWidget > m_pEdit;
    std::queue< std::shared_ptr< AUIWidget > > m_InputLists;
    size_t m_MaxListSize;
    AUITextLineFeed m_MultilineType = AUITextLineFeed::kNone;

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
