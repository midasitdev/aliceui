#pragma once

#include "AUIRecyclerLayoutManager.h"

class ALICEUI_API AUIRecyclerLinearLayoutManager : public AUIRecyclerLayoutManager
{
public:
    AUIRecyclerLinearLayoutManager();
    virtual ~AUIRecyclerLinearLayoutManager();

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    virtual void OnUpdateChildPosition() override;


    //////////////////////////////////////////////////////////////////////////
    // Update position
protected:
    void UpdateChild_Horizontal();
    void UpdateChild_Vertical();

    //////////////////////////////////////////////////////////////////////////
    // Orientation
public:
    bool IsHorizontal() const { return m_bHorizontal; }
    void SetHorizontal(bool horizontal) { m_bHorizontal = horizontal; }
private:
    bool m_bHorizontal;
};
