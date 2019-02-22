#pragma once

#include "AUILayoutWidget.h"


class AUILinearLayout;
class ALICEUI_API AUILinearLayoutWidget : public AUILayoutWidget
{
    using SuperWidget = AUILayoutWidget;
public:
    AUILinearLayoutWidget();
    explicit AUILinearLayoutWidget(bool horizontal);
    ~AUILinearLayoutWidget() override = default;

    //////////////////////////////////////////////////////////////////////////
    // Orientation
public:
    bool IsHorizontal() const;
    void SetHorizontal(bool horizontal);

private:
    std::shared_ptr<AUILinearLayout> m_pLinearLayout;
};
