#pragma once

#include "AUIAPIDef.h"

#include <string>


class ALICEUI_API AUIGalleriaParam final
{
public:
    AUIGalleriaParam();
    ~AUIGalleriaParam();
    AUIGalleriaParam Clone() const;

    static AUIGalleriaParam Make();

    bool IsNoOp() const;

    //////////////////////////////////////////////////////////////////////////
    // Setter
public:
    AUIGalleriaParam& ClearCenterCrop();
    AUIGalleriaParam& ClearCenterInside();
    AUIGalleriaParam& ClearOnlyScaleDown();
    AUIGalleriaParam& ClearResize();
    AUIGalleriaParam& ClearRotation();
    AUIGalleriaParam& ClearFit();
    AUIGalleriaParam& ClearAll();
    AUIGalleriaParam& CenterCrop();
    AUIGalleriaParam& CenterInside();
    //MAUIGalleriaParam& Fit();
    AUIGalleriaParam& OnlyScaleDown();
    AUIGalleriaParam& Resize(int width, int height);
    AUIGalleriaParam& Rotate(float degree);
    AUIGalleriaParam& Rotate(float degree, float pivotX, float pivotY);
    AUIGalleriaParam& Fallback(const std::wstring& fallbackPath);


    //////////////////////////////////////////////////////////////////////////
    // Parameter
public:
    bool IsCenterCrop() const { return m_bCenterCrop; }
    bool IsCenterInside() const { return m_bCenterInside; }
    // Rotation
    float GetRotateDegree() const { return m_RotateDegree; }
    float GetRotatePivotX() const { return m_RotatePivotX; }
    float GetRotatePivotY() const { return m_RotatePivotY; }
    // Resize
    int GetTargetWidth() const { return m_TargetWidth; }
    int GetTargetHeight() const { return m_TargetHeight; }
    // Fitting
    bool IsTargetFit() const { return m_bTargetFit; }
    // Downscale Only
    bool IsOnlyScaleDown() const { return m_bOnlyScaleDown; }
    // Fallback
    std::wstring GetFallbackPath() const { return m_FallbackPath; }
private:
    bool m_bCenterCrop;
    bool m_bCenterInside;
    bool m_bOnlyScaleDown;
    float m_RotateDegree;
    float m_RotatePivotX;
    float m_RotatePivotY;
    int m_TargetWidth;
    int m_TargetHeight;
    bool m_bTargetFit;
    std::wstring m_FallbackPath;
};
