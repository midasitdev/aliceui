#pragma once

#include "AUIAPIDef.h"
#include "AUISkiaPreConfig.h"
#include <skia/core/SkScalar.h>

#include <glm/glm.hpp>

class ALICEUI_API AUITolerance
{
public:
    static SkScalar GetGlobalTolerance();
    static void SetGlobalTolerance(SkScalar val);
};

struct ALICEUI_API AUIScalar2
{
    SkScalar fX = 0.0f;
    SkScalar fY = 0.0f;

    AUIScalar2() noexcept = default;
    constexpr AUIScalar2(const SkScalar x, const SkScalar y) noexcept : fX(x), fY(y) {}

    // Operator
    AUIScalar2 operator*(SkScalar scalar) const noexcept {
        return AUIScalar2(scalar * fX, scalar * fY);
    }
    AUIScalar2 operator+(const AUIScalar2& val) const noexcept {
        return AUIScalar2(fX + val.fX, fY + val.fY);
    }
    AUIScalar2 operator-(const AUIScalar2& val) const noexcept {
        return AUIScalar2(fX - val.fX, fY - val.fY);
    }
    AUIScalar2& operator+=(const AUIScalar2& val) noexcept {
        fX += val.fX;
        fY += val.fY;
        return *this;
    }
    AUIScalar2& operator-=(const AUIScalar2& val) noexcept {
        fX -= val.fX;
        fY -= val.fY;
        return *this;
    }

    // Compare
    bool isEqual(const AUIScalar2& val) const noexcept;
    bool operator==(const AUIScalar2& val) const noexcept {
        return isEqual(val);
    }
    bool operator!=(const AUIScalar2& val) const noexcept {
        return !isEqual(val);
    }

    // Product
    SkScalar dot( const AUIScalar2& val ) const noexcept {
        return fX * val.fX + fY * val.fY;
    }
    AUIScalar2 mult( const AUIScalar2& val ) const noexcept {
        return AUIScalar2(fX * val.fX, fY * val.fY);
    }
    AUIScalar2 div( const AUIScalar2& val ) const;

    // State
    bool isZero() const noexcept;
    void setZero() noexcept;
    void setLowest() noexcept;
    void setMaximum() noexcept;

    // Getter
    SkScalar x() const noexcept {
        return fX;
    }
    SkScalar y() const noexcept {
        return fY;
    }

    // GLM Support
    constexpr AUIScalar2(const glm::vec2& val) noexcept : fX(val.x), fY(val.y) {}
    operator glm::vec2() const noexcept {
        return { fX,fY };
    }
    glm::vec2 toGlm() const noexcept {
        return { fX, fY };
    }

    // Utility
    static AUIScalar2 Smaller(const AUIScalar2& l, const AUIScalar2& r) noexcept {
        return AUIScalar2(l.fX < r.fX ? l.fX : r.fX, l.fY < r.fY ? l.fY : r.fY);
    }
    static AUIScalar2 Bigger(const AUIScalar2& l, const AUIScalar2& r) noexcept {
        return AUIScalar2(l.fX > r.fX ? l.fX : r.fX, l.fY > r.fY ? l.fY : r.fY);
    }
};

struct ALICEUI_API AUIScalar3
{
    SkScalar fX = 0.0f;
    SkScalar fY = 0.0f;
    SkScalar fZ = 0.0f;

    AUIScalar3() noexcept = default;
    constexpr AUIScalar3(const AUIScalar2& val) noexcept : fX(val.fX), fY(val.fY), fZ(0) {}
    constexpr AUIScalar3(const SkScalar x, const SkScalar y, const SkScalar z) noexcept : fX(x), fY(y), fZ(z) {}

    AUIScalar3 operator*(SkScalar scalar) const noexcept {
        return AUIScalar3(scalar * fX, scalar * fY, scalar * fZ);
    }
    AUIScalar3 operator+(const AUIScalar3& val) const noexcept {
        return AUIScalar3(fX + val.fX, fY + val.fY, fZ + val.fZ);
    }
    AUIScalar3& operator+=( const AUIScalar3& val ) noexcept {
        fX += val.fX;
        fY += val.fY;
        fZ += val.fZ;
        return *this;
    }
    AUIScalar3 operator-(const AUIScalar3& val) const noexcept {
        return AUIScalar3(fX - val.fX, fY - val.fY, fZ - val.fZ);
    }
    AUIScalar3& operator-=( const AUIScalar3& val ) noexcept {
        fX -= val.fX;
        fY -= val.fY;
        fZ -= val.fZ;
        return *this;
    }
    bool isEqual(const AUIScalar3& val) const noexcept;
    bool operator==( const AUIScalar3& val ) const noexcept {
        return isEqual(val);
    }
    bool operator!=( const AUIScalar3& val ) const noexcept {
        return !isEqual(val);
    }

    SkScalar dot( const AUIScalar3& val ) const noexcept {
        return fX * val.fX + fY * val.fY + fZ * val.fZ;
    }
    AUIScalar3 mult( const AUIScalar3& val ) const noexcept {
        return AUIScalar3( fX * val.fX, fY * val.fY, fZ * val.fZ );
    }
    AUIScalar3 div( const AUIScalar3& val ) const;

    // State
    bool isZero() const noexcept;
    void setZero() noexcept;
    void setLowest() noexcept;
    void setMaximum() noexcept;

    // Getter
    SkScalar x() const noexcept {
        return fX;
    }
    SkScalar y() const noexcept {
        return fY;
    }
    SkScalar z() const noexcept {
        return fZ;
    }
    AUIScalar2 xy() const noexcept {
        return AUIScalar2(fX, fY);
    }
    AUIScalar2 yz() const noexcept {
        return AUIScalar2(fY, fZ);
    }
    AUIScalar2 xz() const noexcept {
        return AUIScalar2(fX, fZ);
    }

    // GLM Support
    AUIScalar3(const glm::vec3& val) noexcept : fX(val.x), fY(val.y), fZ(val.z) {}
    operator glm::vec3() const noexcept {
        return { fX, fY, fZ };
    }
    glm::vec3 toGlm() const noexcept {
        return { fX, fY, fZ };
    }

    // Utility
    static AUIScalar3 Smaller(const AUIScalar3& l, const AUIScalar3& r) noexcept {
        return AUIScalar3(l.fX < r.fX ? l.fX : r.fX, l.fY < r.fY ? l.fY : r.fY, l.fZ < r.fZ ? l.fZ : r.fZ);
    }
    static AUIScalar3 Bigger(const AUIScalar3& l, const AUIScalar3& r) noexcept {
        return AUIScalar3(l.fX > r.fX ? l.fX : r.fX, l.fY > r.fY ? l.fY : r.fY, l.fZ > r.fZ ? l.fZ : r.fZ);
    }
};


