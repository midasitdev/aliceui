#pragma once

#include "AUIAPIDef.h"
#include "AUISkiaConfig.h"

class ALICEUI_API AUIShape
{
public:
    AUIShape() noexcept = default;
    virtual ~AUIShape() noexcept = default;


    //////////////////////////////////////////////////////////////////////////
    // Draw
public:
    void Draw(SkCanvas* const canvas, const SkPaint& paint);
protected:
    virtual void OnDraw(SkCanvas* const canvas, const SkPaint& paint) { /* Implement in subclass */ }


    //////////////////////////////////////////////////////////////////////////
    // Size
public:
    void Resize(float width, float height);
    float GetWidth() const noexcept { return m_fWidth; }
    float GetHeight() const noexcept { return m_fHeight; }
protected:
    virtual void OnResize(float width, float height) { /* Implement in subclass */ }
private:
    float m_fWidth = 0.0f;
    float m_fHeight = 0.0f;


    //////////////////////////////////////////////////////////////////////////
    // Alpha
public:
    virtual bool HasAlpha() const { return false; }
};
