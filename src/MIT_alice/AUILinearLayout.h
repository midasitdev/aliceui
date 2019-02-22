#pragma once


#include "AUILayoutBase.h"

class ALICEUI_API AUILinearLayout : public AUILayoutBase
{
public:
    AUILinearLayout() = default;
    constexpr explicit AUILinearLayout(bool horizontal) : m_bHorizontal(horizontal) {}
    ~AUILinearLayout() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;
private:
    void OnUpdateChildPosition_Horizontal();
    void OnUpdateChildPosition_Vertical();

public:
    bool IsHorizontal() const {
        return m_bHorizontal;
    }
    void SetHorizontal(bool val) {
        m_bHorizontal = val;
    }
private:
    bool m_bHorizontal = false;
};


