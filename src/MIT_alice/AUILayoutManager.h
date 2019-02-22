#pragma once

#include "AUICommonDef.h"

class AUIWidget;
class AUILayoutBase;
class ALICEUI_API AUILayoutManager final
{
public:
    AUILayoutManager() noexcept = default;
    ~AUILayoutManager() noexcept = default;

public:
    bool OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);
    bool OnUpdateChildPosition();
    bool OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime);
public:
    void SetLayout(const std::shared_ptr<AUILayoutBase>& pLayout);
    AUIWidget* GetTargetWidget() const {
        return m_pBase;
    }
    void SetTargetWidget(AUIWidget* pBase) {
        m_pBase = pBase;
    }
private:
    std::shared_ptr<AUILayoutBase> m_pLayout;
    AUIWidget* m_pBase = nullptr;
};
