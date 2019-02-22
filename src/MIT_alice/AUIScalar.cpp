#include "pch.h"
#include "AUIScalar.h"

static SkScalar gGlobalTolerance = SK_ScalarNearlyZero;

SkScalar AUITolerance::GetGlobalTolerance()
{
    return gGlobalTolerance;
}

void AUITolerance::SetGlobalTolerance(SkScalar val)
{
    gGlobalTolerance = val;
}

bool AUIScalar2::isEqual(const AUIScalar2& val) const noexcept
{
    return SkScalarNearlyEqual(fX, val.fX, gGlobalTolerance) && SkScalarNearlyEqual(fY, val.fY, gGlobalTolerance);
}

AUIScalar2 AUIScalar2::div(const AUIScalar2& val) const
{
    AUIAssert(false == val.isZero());
    return AUIScalar2(fX / val.fX, fY / val.fY);
}

bool AUIScalar2::isZero() const noexcept
{
    return SkScalarNearlyEqual(fX, 0.0f, gGlobalTolerance) && SkScalarNearlyEqual(fY, 0.0f, gGlobalTolerance);
}

void AUIScalar2::setZero() noexcept
{
    fX = fY = SkScalar(0.0f);
}

void AUIScalar2::setLowest() noexcept
{
    fX = fY = std::numeric_limits<SkScalar>::lowest();
}

void AUIScalar2::setMaximum() noexcept
{
    fX = fY = (std::numeric_limits<SkScalar>::max)();
}

bool AUIScalar3::isEqual(const AUIScalar3& val) const noexcept
{
    return SkScalarNearlyEqual(fX, val.fX, gGlobalTolerance) && SkScalarNearlyEqual(fY, val.fY, gGlobalTolerance) && SkScalarNearlyEqual(fZ, val.fZ, gGlobalTolerance);
}

AUIScalar3 AUIScalar3::div(const AUIScalar3& val) const
{
    AUIAssert(false == val.isZero());
    return AUIScalar3(fX / val.fX, fY / val.fY, fZ / val.fZ);
}

bool AUIScalar3::isZero() const noexcept
{
    return SkScalarNearlyEqual(fX, 0.0f, gGlobalTolerance) && SkScalarNearlyEqual(fY, 0.0f, gGlobalTolerance) && SkScalarNearlyEqual(fZ, 0.0f, gGlobalTolerance);
}

void AUIScalar3::setZero() noexcept
{
    fX = fY = fZ = SkScalar(0.0f);
}

void AUIScalar3::setLowest() noexcept
{
    fX = fY = fZ = std::numeric_limits<SkScalar>::lowest();
}

void AUIScalar3::setMaximum() noexcept
{
    fX = fY = fZ = (std::numeric_limits<SkScalar>::max)();
}
