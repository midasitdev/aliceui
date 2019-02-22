#include "pch.h"
#include "AUIImageDrawable.h"
#include "AUIStringConvert.h"

AUIImageDrawable::AUIImageDrawable()
    : m_eImageStretch( AUIImageStretch::kUniform )
    , m_Opacity(kAUIAlpha100 )
{

}

AUIImageDrawable::AUIImageDrawable(const sk_sp<SkImage>& image,const AUIImageStretch stretch)
    : m_eImageStretch(stretch)
    , m_Opacity(kAUIAlpha100)
{
    SetImage(image);
}

void AUIImageDrawable::OnDraw( SkCanvas* const canvas )
{
    if ( GetImage() == nullptr )
        return;

    const auto bound = GetDrawBound();


    const auto stretch = GetImageStretch();
    auto bitmapRect = SkRect::MakeWH( static_cast< SkScalar >( GetImage()->width() ), static_cast< SkScalar >( GetImage()->height() ) );
    const auto rectWidth = bound.width();
    const auto rectHeight = bound.height();
    const auto imageWidth = GetImage()->width();
    const auto imageHeight = GetImage()->height();
    if ( AUIImageStretch::kOriginal == stretch )
    {
        const auto offsetX = (std::max)( 0.0f, ( rectWidth - float( imageWidth ) ) / 2.0f );
        const auto offsetY = (std::max)( 0.0f, ( rectHeight - float( imageHeight ) ) / 2.0f );
        bitmapRect.offset( offsetX, offsetY );
    }
    else if ( AUIImageStretch::kUniform == stretch )
    {
        AUIAssert( imageHeight > 0.0f );
        if ( rectWidth >= rectHeight )
        {
            const auto aspect = float( imageHeight ) / float( imageWidth );
            const auto targetWidth = rectHeight;
            const auto targetHeight = rectHeight * aspect;
            const auto offsetTop = ( rectHeight - targetHeight ) * 0.5f;
            bitmapRect = SkRect::MakeXYWH( rectWidth * 0.5f - targetWidth * 0.5f, offsetTop, targetWidth, targetHeight );
        }
        else
        {
            const auto aspect = float( imageHeight ) / float( imageWidth );
            const auto targetWidth = rectWidth;
            const auto targetHeight = rectWidth * aspect;
            const auto offsetLeft = ( rectWidth - targetWidth ) * 0.5f;
            bitmapRect = SkRect::MakeXYWH( offsetLeft, rectHeight * 0.5f - targetHeight * 0.5f, targetWidth, targetHeight );
        }
    }
    else if ( AUIImageStretch::kUniformToFill == stretch )
    {
        if ( rectWidth >= rectHeight )
        {
            AUIAssert( rectWidth > 0.0f );
            const auto weight = rectWidth / imageWidth;
            const auto expectHeight = weight * imageHeight;
            bitmapRect = SkRect::MakeXYWH( 0.0f, ( rectHeight - expectHeight ) * 0.5f, rectWidth, expectHeight );
        }
        else
        {
            AUIAssert( imageHeight > 0.0f );
            const auto weight = rectHeight / imageHeight;
            const auto expectWidth = weight * imageWidth;

            bitmapRect = SkRect::MakeXYWH( ( rectWidth - expectWidth ) * 0.5f, 0.0f, expectWidth, rectHeight );
        }
    }
    else if ( AUIImageStretch::kFill == stretch )
    {
        bitmapRect = bound;
    }

    bitmapRect.fLeft = SkScalarCeilToScalar(bitmapRect.fLeft);
    bitmapRect.fTop = SkScalarCeilToScalar(bitmapRect.fTop);
    bitmapRect.fRight = SkScalarCeilToScalar(bitmapRect.fRight);
    bitmapRect.fBottom = SkScalarCeilToScalar(bitmapRect.fBottom);


	auto bmpPaint = SkPaint();
	bmpPaint.setFilterQuality(kHigh_SkFilterQuality);
    bmpPaint.setAntiAlias( true );
    bmpPaint.setAlpha( GetOpacity() );
    canvas->drawImageRect( GetImage(), bitmapRect, &bmpPaint );
}

bool AUIImageDrawable::LoadBitmapFromPath( const std::string& absolutepath )
{
    auto pBitmap = std::make_shared< SkBitmap >();
    auto pImageData = SkData::MakeFromFileName(absolutepath.c_str());
    auto pImage = SkImage::MakeFromEncoded(pImageData);
    m_pImage = pImage;
    return nullptr != m_pImage;
}

bool AUIImageDrawable::LoadBitmapFromPath(const std::wstring& absolutepath)
{
    return LoadBitmapFromPath(AUIStringConvert::WCSToACP(absolutepath));
}

void AUIImageDrawable::SetImage(const sk_sp<SkImage>& image)
{
    m_pImage = image;
}
