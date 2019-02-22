#include "pch.h"
#include "AUIGalleriaImgProc.h"

AUIGalleriaImgProc::AUIGalleriaImgProc(const sk_sp<SkImage>& pImage)
    : m_pImage(pImage)
{
    AUIAssert(m_pImage);
}

sk_sp<SkImage> AUIGalleriaImgProc::Resize( int width, int height )
{
    if ( width <= 0 || height <= 0 )
    {
        AUIAssert( false );
        return {};
    }
    SkPixmap pixmap;
    if (!m_pImage->peekPixels(&pixmap))
    {
        AUIAssert(!"Bad pixmap");
        return {};
    }

    auto pSurface = SkSurface::MakeRaster(SkImageInfo::Make(width, height, pixmap.colorType(), pixmap.alphaType()));
    SkPaint paint;
    paint.setFilterQuality(kHigh_SkFilterQuality);
    pSurface->getCanvas()->drawImageRect(m_pImage, SkRect::MakeWH(SkIntToScalar(width), SkIntToScalar(height)), &paint);
    return pSurface->makeImageSnapshot();
}

sk_sp<SkImage> AUIGalleriaImgProc::Rotate( float degree, float pivotX, float pivotY )
{
    SkPixmap pixmap;
    if (!m_pImage->peekPixels(&pixmap))
    {
        AUIAssert(!"Bad pixmap");
        return {};
    }

    auto pSurface = SkSurface::MakeRaster(SkImageInfo::Make(pixmap.width(), pixmap.height(), pixmap.colorType(), pixmap.alphaType()));

    SkPaint paint;
    paint.setFilterQuality(kHigh_SkFilterQuality);
    pSurface->getCanvas()->rotate(degree, pivotX, pivotY);
    pSurface->getCanvas()->drawImage(m_pImage, 0.0f, 0.0f, &paint);
    return pSurface->makeImageSnapshot();
}

sk_sp<SkImage> AUIGalleriaImgProc::ResizeCenterInside( int width, int height )
{
    if (width <= 0 || height <= 0)
    {
        AUIAssertFail();
        return {};
    }
    SkPixmap pixmap;
    if (!m_pImage->peekPixels(&pixmap))
    {
        AUIAssert(!"Bad pixmap");
        return {};
    }


    const auto imageWidth = SkIntToScalar(m_pImage->width());
    const auto imageHeight = SkIntToScalar(m_pImage->height());

    const auto widthIsLonger = width >= height;
    const auto imageWidthIsLonger = imageWidth >= imageHeight;

    const auto scale = SkIntToScalar(imageWidth) / SkIntToScalar(imageWidth >= imageHeight ? imageWidth : imageHeight);

    SkRect roi;
    if (imageWidthIsLonger)
    {
        roi = SkRect::MakeXYWH(0.0f, (SkIntToScalar(width) - imageHeight * scale) * 0.5f, SkIntToScalar(width), imageHeight * scale);
    }
    else
    {
        roi = SkRect::MakeXYWH((SkIntToScalar(width) - imageWidth * scale) * 0.5f, 0.0f, imageWidth * scale, SkIntToScalar(height));
    }

    auto pSurface = SkSurface::MakeRaster(SkImageInfo::Make(width, height, pixmap.colorType(), pixmap.alphaType()));
    SkPaint paint;
    paint.setFilterQuality(kHigh_SkFilterQuality);
    pSurface->getCanvas()->drawImageRect(m_pImage, roi, &paint);
    return pSurface->makeImageSnapshot();
}

sk_sp<SkImage> AUIGalleriaImgProc::ResizeCenterCrop( int width, int height )
{
    if (width <= 0 || height <= 0)
    {
        AUIAssertFail();
        return {};
    }
    SkPixmap pixmap;
    if (!m_pImage->peekPixels(&pixmap))
    {
        AUIAssert(!"Bad pixmap");
        return {};
    }

    const auto imageWidth = SkIntToScalar(m_pImage->width());
    const auto imageHeight = SkIntToScalar(m_pImage->height());


    const auto scale = SkIntToScalar(width) / SkIntToScalar( width >= height ? width : height );


    SkRect roi;
    if (imageWidth >= imageHeight)
    {
        roi = SkRect::MakeXYWH((imageHeight - imageWidth * scale) * 0.5f, 0.0f, imageWidth * scale, imageHeight);
    }
    else
    {
        roi = SkRect::MakeXYWH(0.0f, (imageWidth - imageHeight * scale) * 0.5f, imageWidth, imageHeight * scale);
    }

    auto pSurface = SkSurface::MakeRaster(SkImageInfo::Make(width, height, pixmap.colorType(), pixmap.alphaType()));
    SkPaint paint;
    paint.setFilterQuality(kHigh_SkFilterQuality);
    pSurface->getCanvas()->drawImageRect(m_pImage, roi, &paint);
    return pSurface->makeImageSnapshot();
}
