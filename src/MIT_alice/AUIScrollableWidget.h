#pragma once

#include "AUIFrameLayoutWidget.h"


class AUIScrollableContentWidget;
class AUIScrollableBarWidget;

class ALICEUI_API AUIScrollableWidget : public AUIFrameLayoutWidget
{
    typedef AUIFrameLayoutWidget SuperClass;
public:
    AUIScrollableWidget();
    virtual ~AUIScrollableWidget();



    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;


    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos) override;
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget) override;
    virtual void PopSubWidget() override;
    virtual void ClearSubWidget() override;
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override;
    virtual size_t SubWidgetCount() const override;
protected:
    AUIScrollableContentWidget* const GetContent() const { return m_pContent.get(); }
private:
    std::shared_ptr< AUIScrollableContentWidget > m_pContent;


    //////////////////////////////////////////////////////////////////////////
    // ScrollBar
public:
    void SetShowThumbOnHit(bool show);
    bool IsShowThumbOnHit() const;
    AUIScrollableBarWidget* GetScrollBarWidget() const { return m_pScrollBar.get(); }
private:
    std::shared_ptr< AUIScrollableBarWidget > m_pScrollBar;


    //////////////////////////////////////////////////////////////////////////
    // Scroll Info
public:
    bool IsHorizontal() const { return m_bHorizontal; }
private:
    float m_fScrollPos;
    float m_fScrollOffset;
    bool m_bHorizontal;


    //////////////////////////////////////////////////////////////////////////
    // Inner Layout
public:
    enum ScrollBarPolicy
    {
        SBP_Auto,
        SBP_Show,
        SBP_Hide
    };
    ScrollBarPolicy GetScrollBarPolicy() const { return m_eScrollBarPolicy; }
protected:
    void OnSetDefaultSize(const AUIScalar2& size) override;
private:
    ScrollBarPolicy m_eScrollBarPolicy;


    //////////////////////////////////////////////////////////////////////////
    // Children
protected:
    virtual void OnUpdateChildPosition() override;


    //////////////////////////////////////////////////////////////////////////
    // Scrolling
public:
    void ScrollToTop();
    void ScrollToBottom();
protected:
    virtual void OnContentScroll(AUIScrollableContentWidget* const pWidget, float delta);
    virtual void OnAfterMeasureSize(SkScalar width, SkScalar height) override;
private:
    bool m_bPendingScrollToTop;
    bool m_bPendingScrolllToBottom;

    void OnThumbScroll(const SkScalar& val);
};
