#pragma once

#include "AUICommonDef.h"

class AUIWidget;
class AUILayoutManager;

class ALICEUI_API AUILayoutBase
{
protected:
    AUILayoutBase() noexcept = default;
public:
    virtual ~AUILayoutBase() noexcept = default;

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) = 0;
    virtual void OnUpdateChildPosition() = 0;
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) {}
protected:
    AUIWidget * GetTargetWidget() const;
private:
    AUILayoutManager * m_pLayoutManager = nullptr;
    friend class AUILayoutManager;
};
