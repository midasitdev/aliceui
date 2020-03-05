#pragma once

#include "AUIScrollableWidget.h"
#include "AUIPopup.h"

class AUIComboAdapter;
class AUILinearLayoutWidget;

class ALICEUI_API AUIComboPopupWidget : public AUIScrollableWidget
{
    using SuperWidget = AUIScrollableWidget;
public:
    AUIComboPopupWidget();
    ~AUIComboPopupWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Combo adapter
public:
    void SetAdapter(const std::shared_ptr< AUIComboAdapter >& pAdapter);
    std::shared_ptr< AUIComboAdapter > GetAdapter() const { return m_pAdapter; }
protected:
    virtual void OnAdapterDataChanged(AUIComboAdapter*);
private:
    std::shared_ptr< AUIComboAdapter > m_pAdapter;
    AUISlotPool m_spoolAdapterDataChanged;


    //////////////////////////////////////////////////////////////////////////
    // Focus signal
public:
    AUISignal<void()> PopupFocusLostSignal;
protected:
    virtual void OnFocusOut() override;
private:
    void OnItemFocusChange(AUIWidget*);


    //////////////////////////////////////////////////////////////////////////
    // TODO : Content
public:
    void SetPopupItemBG(const std::wstring& itemBG) { m_wsItemBG = itemBG; }
    const std::wstring& GetPopupItemBG() const { return m_wsItemBG; }
private:
    std::wstring m_wsItemBG = L"";
    //////////////////////////////////////////////////////////////////////////
    // TODO : Content
public:
    void ResetContentWidgetPadding(SkScalar leftPadding = 0, SkScalar topPadding = 0, SkScalar rightPadding = 0, SkScalar bottomPadding = 0);
protected:
    AUILinearLayoutWidget* const GetContentWidget() const { return m_pContent.get(); }
    virtual void OnItemClicked(AUIWidget*, size_t pos);
private:
    std::shared_ptr< AUILinearLayoutWidget > m_pContent;

    //////////////////////////////////////////////////////////////////////////
    // Marquee
public:
    void SetUseMarquee(bool val);
    bool IsUseMarquee() const { return m_bUseMarquee; }
private:
    bool m_bUseMarquee;
};