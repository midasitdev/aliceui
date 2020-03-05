#include "pch.h"
#include "AUINinePatch.h"

AUINinePatch::AUINinePatch(const SkBitmap& bitmap)
{
    SetNinePatchImage(SkImage::MakeFromBitmap(bitmap));
}

AUINinePatch::AUINinePatch(const SkBitmap& bitmap, const SkIRect& center, const SkIRect& content)
    : m_pImage(SkImage::MakeFromBitmap(bitmap))
    , m_Center(center)
    , m_Content(content)
{

}

AUINinePatch::AUINinePatch(const sk_sp<SkImage>& image)
{
    SetNinePatchImage(image);
}

AUINinePatch::AUINinePatch(const sk_sp<SkImage>& image, const SkIRect& center, const SkIRect& content)
    : m_pImage(image)
    , m_Center(center)
    , m_Content(content)
{

}

void AUINinePatch::Draw(SkCanvas* const canvas, const SkRect& rect, SkPaint* paint)
{
    if (!m_pImage)
    {
#ifdef _DEBUG
        if (paint)
            canvas->drawRect(rect, *paint);
#endif
        return;
    }
    canvas->drawImageNine(m_pImage, m_Center, rect, paint);
}

bool AUINinePatch::IsValid() const
{
    if (!m_pImage)
        return false;
    if (m_Center.isEmpty() == false)
        return false;
    if (m_Content.isEmpty() == false)
        return false;
    return true;
}

void AUINinePatch::SetNinePatchImage(const sk_sp<SkImage>& image)
{
    if (!image)
        return;

    auto pRaster = image->makeRasterImage();
    SkPixmap pixmap;
    if (!pRaster->peekPixels(&pixmap))
        return;

    const auto w = pixmap.width();
    const auto h = pixmap.height();

    // Find scalable width
    int scaleLeft = 0;
    int scaleRight = 0;
    bool scaleWidthStarted = false;
    for (auto idx = 1; idx < w - 1; idx++)
    {
        if (pixmap.getColor(idx, 0) == kAUIColorBlack)
        {
            scaleWidthStarted = true;
            scaleRight = idx;
        }
        if (scaleWidthStarted == false)
            scaleLeft++;
    }
    // Find scalable height
    int scaleTop = 0;
    int scaleBottom = 0;
    bool scaleHeightStarted = false;
    for (auto idx = 1; idx < h - 1; idx++)
    {
        if (pixmap.getColor(0, idx) == kAUIColorBlack)
        {
            scaleHeightStarted = true;
            scaleBottom = idx;
        }
        if (scaleHeightStarted == false)
            scaleTop++;
    }
    if (scaleTop > scaleBottom)
        m_Center = SkIRect::MakeLTRB(scaleLeft, scaleBottom, scaleRight, scaleTop);
    else
        m_Center = SkIRect::MakeLTRB(scaleLeft, scaleTop, scaleRight, scaleBottom);


    // Find content width
    int contentLeft = 0;
    int contentRight = 0;
    bool contentWidthStarted = false;
    for (auto idx = 1; idx < w - 1; idx++)
    {
        if (pixmap.getColor(idx, h - 1) == kAUIColorBlack)
        {
            contentWidthStarted = true;
            contentRight = idx;
        }
        if (contentWidthStarted == false)
            contentLeft++;
    }
    // Find content height
    int contentTop = 0;
    int contentBottom = 0;
    bool contentHeightStarted = false;
    for (auto idx = 1; idx < h - 1; idx++)
    {
        if (pixmap.getColor(w - 1, idx) == kAUIColorBlack)
        {
            contentHeightStarted = true;
            contentBottom = idx;
        }
        if (contentHeightStarted == false)
            contentTop++;
    }

    if (contentTop > contentBottom)
        m_Content = SkIRect::MakeLTRB(contentLeft, contentBottom, contentRight, contentTop);
    else
        m_Content = SkIRect::MakeLTRB(contentLeft, contentTop, contentRight, contentBottom);

    SkIRect region(pixmap.bounds());
    region.inset(1, 1);

    m_pImage = pRaster->makeSubset(region);
}
