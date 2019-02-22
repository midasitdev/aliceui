#pragma once

#include "AUIInnerGroupWidget.h"

class ALICEUI_API AUIGroupWidget : public AUIInnerGroupWidget
{
public:
    AUIGroupWidget() = default;
    ~AUIGroupWidget() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    void AddSubWidget(const std::shared_ptr< AUIWidget >& widget);
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos);
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget);
    virtual void PopSubWidget();
    virtual void ClearSubWidget();
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos);
    virtual size_t SubWidgetCount() const;
    void ClearSubWidgetRecursive();
    bool HasSubWidget(const std::shared_ptr<AUIWidget>& widget) const;
};
