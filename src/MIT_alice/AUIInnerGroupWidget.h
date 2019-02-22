#pragma once

#include "AUICommonDef.h"
#include "AUIWidget.h"


class ALICEUI_API AUIInnerGroupWidget : public AUIWidget
{
    using SuperWidget = AUIWidget;
public:
    AUIInnerGroupWidget() = default;
    ~AUIInnerGroupWidget() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Protected child interface
protected:
    void AddChild(const std::shared_ptr< AUIWidget >& widget) {
        AddChild(widget, kAUIChildPosEnd);
    }
    void AddChild(const std::shared_ptr< AUIWidget >& widget, const size_t pos);
    void DelChild(const std::shared_ptr< AUIWidget >& widget);
    void PopChild();
    void ClearChild();
    void ClearChildRecursive();
    bool HasChild(const std::shared_ptr< AUIWidget >& widget) const;


    //////////////////////////////////////////////////////////////////////////
    // Focus
public:
    const std::shared_ptr<AUIWidget> GetNextFocusable() override;
    const std::shared_ptr<AUIWidget> GetPrevFocusable() override;
    const std::shared_ptr<AUIWidget> GetNextChildFocusable() const;
    const std::shared_ptr<AUIWidget> GetPrevChildFocusable() const;
};
