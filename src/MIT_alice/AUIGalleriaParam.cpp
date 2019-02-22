#include "pch.h"
#include "AUIGalleriaParam.h"

AUIGalleriaParam AUIGalleriaParam::Make()
{
    AUIGalleriaParam param;
    return param;
}

AUIGalleriaParam::AUIGalleriaParam()
    : m_bCenterCrop( false )
    , m_bCenterInside( false )
    , m_bOnlyScaleDown( false )
    , m_RotateDegree( 0.0f )
    , m_RotatePivotX( 0.0f )
    , m_RotatePivotY( 0.0f )
    , m_TargetWidth( -1 )
    , m_TargetHeight( -1 )
    , m_bTargetFit( false )
{

}

AUIGalleriaParam::~AUIGalleriaParam()
{

}

AUIGalleriaParam& AUIGalleriaParam::ClearCenterCrop()
{
    m_bCenterCrop = false;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearCenterInside()
{
    m_bCenterInside = false;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearOnlyScaleDown()
{
    m_bOnlyScaleDown = false;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearResize()
{
    m_TargetWidth = -1;
    m_TargetHeight = -1;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearRotation()
{
    m_RotateDegree = 0.0f;
    m_RotatePivotX = 0.0f;
    m_RotatePivotY = 0.0f;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearFit()
{
    m_bTargetFit = false;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::ClearAll()
{
    ClearCenterCrop();
    ClearCenterInside();
    ClearOnlyScaleDown();
    ClearResize();
    ClearRotation();
    ClearFit();
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::CenterCrop()
{
    m_bCenterCrop = true;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::CenterInside()
{
    m_bCenterInside = true;
    return *this;
}

//MAUIGalleriaParam& MAUIGalleriaParam::Fit()
//{
//    m_bTargetFit = true;
//    return *this;
//}

AUIGalleriaParam& AUIGalleriaParam::OnlyScaleDown()
{
    m_bOnlyScaleDown = true;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::Resize( int width, int height )
{
    m_TargetWidth = width;
    m_TargetHeight = height;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::Rotate( float degree )
{
    m_RotateDegree = degree;
    m_RotatePivotX = 0.0f;
    m_RotatePivotY = 0.0f;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::Rotate( float degree, float pivotX, float pivotY )
{
    m_RotateDegree = degree;
    m_RotatePivotX = pivotX;
    m_RotatePivotY = pivotY;
    return *this;
}

AUIGalleriaParam& AUIGalleriaParam::Fallback( const std::wstring& fallbackPath )
{
    m_FallbackPath = fallbackPath;
    return *this;
}

AUIGalleriaParam AUIGalleriaParam::Clone() const
{
    return *this;
}

bool AUIGalleriaParam::IsNoOp() const
{
    return
        (m_bCenterCrop == false) &&
        (m_bCenterInside == false) &&
        (m_bOnlyScaleDown == false) &&
        (SkScalarNearlyEqual(m_RotateDegree, 0.0f)) &&
        (SkScalarNearlyEqual(m_RotatePivotX, 0.0f)) &&
        (SkScalarNearlyEqual(m_RotatePivotY, 0.0f)) &&
        (m_TargetWidth == -1) &&
        (m_TargetHeight == -1) &&
        (m_bTargetFit == false);
}
