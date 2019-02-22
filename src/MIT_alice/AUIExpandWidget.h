#pragma once

#include "AUILinearLayoutWidget.h"
#include "AUITextWidget.h"
#include "AUIDrawableWidget.h"


class AUIExpandHeaderWidget;
class ALICEUI_API AUIExpandWidget : public AUILinearLayoutWidget
{
    using SuperWidget = AUILinearLayoutWidget;
public:
    AUIExpandWidget();
    ~AUIExpandWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Header
public:
    void ExpandOrCollapse();
    void Expand(bool force = false);    // with 'force' it will trigger from scratch
    void Collapse(bool force = false);  // with 'force' it will trigger from scratch
    bool IsExpanded() const {
        return m_bExpanded;
    }
    void RecalcExpandOrCollapse();
private:
    bool m_bExpanded;
    bool m_PendingExpand;
    bool m_PendingCollapse;
    SkScalar m_AnimStartHeight;
    SkScalar m_AnimCurHeight;
    SkScalar m_AnimTargetHeight;

    //////////////////////////////////////////////////////////////////////////
    // Header
public:
    void SetHeaderCaption(const std::wstring& text);
	void SetHeaderCaptionColor(const SkColor& captionColor);

    void SetHeaderHeight(SkScalar height);
    void SetHeaderStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetHeaderSpinStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetHeaderTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
private:
    std::shared_ptr<AUIExpandHeaderWidget> m_pHeader;
    // WORKSTREE...
public:
    AUIExpandHeaderWidget * GetHeaderWidget() const {
        return m_pHeader.get();
    }

    //////////////////////////////////////////////////////////////////////////
    // Style
public:
    virtual void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value) override {
        SuperWidget::OnSetStyleNotion(uiKey, value);
    }

    //////////////////////////////////////////////////////////////////////////
    // Time Event
protected:
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;
private:
    bool m_PendingSizeUpdate;





    //////////////////////////////////////////////////////////////////////////
    // Content
public:
    void SetContent(const std::shared_ptr<AUIWidget>& pWidget);
    std::shared_ptr<AUIWidget> GetContent() const {
        return m_pContent;
    }
private:
    std::shared_ptr<AUIWidget> m_pContent;



    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    virtual void OnBeforeMeasureSize() override;
    virtual void OnAfterMeasureSize(SkScalar width, SkScalar height) override;

    //////////////////////////////////////////////////////////////////////////
    // Child position
protected:
    void OnUpdateChildPosition() override;

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
