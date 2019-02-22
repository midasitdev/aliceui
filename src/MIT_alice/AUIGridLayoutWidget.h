#pragma once


#include "AUILayoutWidget.h"
#include "AUIGridLayout.h"

class ALICEUI_API AUIGridLayoutWidget : public AUILayoutWidget
{
    using SuperWidget = AUILayoutWidget;
public:
    AUIGridLayoutWidget();
    ~AUIGridLayoutWidget() override = default;

    // Division information
public:
    void SetDivisionCount(const size_t count);
    void SetDivisionInfo(const size_t idx, const AUIGridLayout::DivisionInfo& info);
    const AUIGridLayout::DivisionInfo& GetDivisionInfo(const size_t idx) const;
    AUIGridLayout::DivisionInfo& GetDivisionInfo(const size_t idx);
    bool IsHorizontal() const;
    void SetHorizontal(bool horizontal);
protected:
    void UpdateDivisionInfo();
private:
    std::shared_ptr<AUIGridLayout> m_pGridLayout;
};

