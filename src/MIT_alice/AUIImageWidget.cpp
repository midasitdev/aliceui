#include "pch.h"
#include "AUIImageWidget.h"
#include "AUIImageDrawable.h"

namespace
{
    constexpr SkScalar DefaultWidth = 100.0f;
    constexpr SkScalar DefaultHeight = 100.0f;
}

AUIImageWidget::AUIImageWidget()
    : m_pBaseDrawable( std::make_shared< AUIImageDrawable >() )
{
    SetDefaultSize( DefaultWidth, DefaultHeight );
}

AUIImageWidget::~AUIImageWidget()
{

}

void AUIImageWidget::SetImage(const sk_sp<SkImage>& image)
{
    m_pImage = image;
    m_pBaseDrawable->SetImage(image);
    SetLayer(kForeground_Layer, m_pBaseDrawable);
    Invalidate();
}

sk_sp<SkImage> AUIImageWidget::GetImage() const
{
    return m_pBaseDrawable->GetImage();
}

void AUIImageWidget::SetImageDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    SetLayer(kForeground_Layer, pDrawable);
    Invalidate();
}

void AUIImageWidget::SetImageStretch( AUIImageStretch stretch )
{
    if (auto pDrawable = GetLayerAt(kBackground_Layer))
    {
        if (auto pImageDrawable = std::dynamic_pointer_cast<AUIImageDrawable>(pDrawable))
            pImageDrawable->SetImageStretch(stretch);
    }
    m_pBaseDrawable->SetImageStretch( stretch );
}

AUIImageStretch AUIImageWidget::GetImageStretch() const
{
    return m_pBaseDrawable->GetImageStretch();
}

void AUIImageWidget::SetImageOpacity( SkAlpha val )
{
    m_pBaseDrawable->SetOpacity( val );
    Invalidate();
}

SkAlpha AUIImageWidget::GetImageOpacity() const
{
    return m_pBaseDrawable->GetOpacity();
}

void AUIImageWidget::SetBackgroundDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    SetLayer(kBackground_Layer, pDrawable);
    Invalidate();
}

void AUIImageWidget::OnDraw( SkCanvas* const canvas )
{
    AUIDrawableWidget::OnDraw( canvas );
}
