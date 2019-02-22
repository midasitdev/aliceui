#pragma once

#include "AUISkiaConfig.h"
#include "AUIGalleria.h"

//////////////////////////////////////////////////////////////////////////
// Galleria - Image processing module
class AUIGalleriaImgProc final
{
public:
    AUIGalleriaImgProc(const sk_sp<SkImage>& pImage);

public:
    sk_sp<SkImage> Resize(int width, int height);
    sk_sp<SkImage> ResizeCenterInside(int width, int height);
    sk_sp<SkImage> ResizeCenterCrop(int width, int height);
    sk_sp<SkImage> Rotate(float degree, float pivotX, float pivotY);

private:
    sk_sp<SkImage> m_pImage;
};
