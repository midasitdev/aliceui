#pragma once

#include "AUILayoutWidget.h"


class AUIFlowLayout;
class ALICEUI_API AUIFlowLayoutWidget : public AUILayoutWidget
{
    using SuperWidget = AUILayoutWidget;
public:
    AUIFlowLayoutWidget();
    explicit AUIFlowLayoutWidget(bool horizontal);
    ~AUIFlowLayoutWidget() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Orientation
public:
    bool IsHorizontal() const;
    void SetHorizontal(bool horizontal);
private:
    std::shared_ptr<AUIFlowLayout> m_pFlowLayout;
};
