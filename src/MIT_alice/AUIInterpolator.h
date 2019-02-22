#pragma once

#include "AUIAPIDef.h"

class ALICEUI_API AUIInterpolator
{
public:
    AUIInterpolator() noexcept = default;
    virtual ~AUIInterpolator() noexcept = default;
    virtual float GetValue(float input) const;
    virtual float GetValueByTime(const std::chrono::milliseconds& startTime, const std::chrono::milliseconds& endTime, const std::chrono::milliseconds& targetTime) const;
    virtual float GetValueByTime(long long startTime, long long endTime, long long targetTime) const;
    virtual float GetValueByDuration(const std::chrono::milliseconds& durationTime, const std::chrono::milliseconds& durationMax) const;
    static bool IsNearZero(float val);
protected:
    static float GetClamp(float x, float m = 0.0f, float M = 1.0f) { AUIAssert(M >= m); if (x < m) return m; else if (x > M) return M; else return x; }
};

typedef AUIInterpolator AUILinearInterpolator;
