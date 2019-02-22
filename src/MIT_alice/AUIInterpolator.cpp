#include "pch.h"
#include "AUIInterpolator.h"


float AUIInterpolator::GetValue( float input ) const
{
    return AUIInterpolator::GetClamp( input );
}

float AUIInterpolator::GetValueByTime( const std::chrono::milliseconds& startTime, const std::chrono::milliseconds& endTime, const std::chrono::milliseconds& targetTime ) const
{
    const auto diff = static_cast<float>((targetTime - startTime).count());
    const auto weight = static_cast<float>((endTime - startTime).count());
    if (AUIInterpolator::IsNearZero(weight))
        return GetValue(1.0f);
    return GetValue(diff / weight);
}

float AUIInterpolator::GetValueByTime( long long startTime, long long endTime, long long targetTime ) const
{
    const auto diff = static_cast<float>(targetTime - startTime);
    const auto weight = static_cast<float>(endTime - startTime);
    if (AUIInterpolator::IsNearZero(weight))
        return GetValue(1.0f);
    return GetValue(diff / weight);
}

float AUIInterpolator::GetValueByDuration(const std::chrono::milliseconds& durationTime, const std::chrono::milliseconds& durationMax ) const
{
    return GetValue( float( durationTime.count() ) / float( durationMax.count() ) );
}

bool AUIInterpolator::IsNearZero(float val)
{
    const float eps = std::numeric_limits<float>::epsilon();// 1.0e-6f;
    if (eps > std::abs(val))
        return true;
    else
        return false;
}
