#pragma once

#include "AUICommonDef.h"

class ALICEUI_API AUINinePatch
{
public:
    AUINinePatch() = default;
private:
    AUINinePatch(const SkBitmap& bitmap);
    AUINinePatch(const SkBitmap& bitmap, const SkIRect& center, const SkIRect& content);
    AUINinePatch(const sk_sp<SkImage>& image);
    AUINinePatch(const sk_sp<SkImage>& image, const SkIRect& center, const SkIRect& content);


    //////////////////////////////////////////////////////////////////////////
    // Make
public:
    static AUINinePatch MakeFromNinePatchBitmap(const SkBitmap& bitmap) { return { bitmap }; }
    static AUINinePatch MakeFromBitmap(const SkBitmap& bitmap, const SkIRect& center, const SkIRect& content) { return { bitmap, center, content }; }
    static AUINinePatch MakeFromBitmap(const SkBitmap& bitmap, const SkIRect& center) { return { bitmap, center, center }; }
    static AUINinePatch MakeFromNinePatchImage(const sk_sp<SkImage>& image) { return { image }; }
    static AUINinePatch MakeFromImage(const sk_sp<SkImage>& image, const SkIRect& center, const SkIRect& content) { return { image, center, content }; }
    static AUINinePatch MakeFromImage(const sk_sp<SkImage>& image, const SkIRect& center) { return { image, center, center }; }


    //////////////////////////////////////////////////////////////////////////
    // Draw
public:
    void Draw(SkCanvas* const canvas, const SkRect& rect, SkPaint* paint = nullptr);


    //////////////////////////////////////////////////////////////////////////
    // NinePatch data
public:
    operator const sk_sp<SkImage>& () const { return m_pImage; }
    bool IsValid() const;
    void SetNinePatchImage(const sk_sp<SkImage>& image);
    SkIRect GetCenter() const { return m_Center; }
    void SetCenter(const SkIRect& rect) { m_Center = rect; }
    SkIRect GetContent() const { return m_Content; }
    void SetContent(const SkIRect& rect) { m_Content = rect; }
private:
    SkIRect m_Center = SkIRect::MakeEmpty();
    SkIRect m_Content = SkIRect::MakeEmpty();
    sk_sp<SkImage> m_pImage;
};
