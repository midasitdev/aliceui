#pragma once

#include "AUILayoutBase.h"

class ALICEUI_API AUIFlowLayout : public AUILayoutBase
{
public:
    AUIFlowLayout() = default;
    explicit AUIFlowLayout(bool horizontal) : m_bHorizontal(horizontal) {}
    ~AUIFlowLayout() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Orientation
public:
    bool IsHorizontal() const {
        return m_bHorizontal;
    }
    void SetHorizontal(bool horizontal) {
        m_bHorizontal = horizontal;
    }
private:
    void UpdateChild_Horizontal();
    void UpdateChild_Vertical();
    bool m_bHorizontal = false;

private:
    std::unordered_set<AUIWidget*> m_NewlineMark;
    std::vector<SkScalar> m_LineOffsets;
};

