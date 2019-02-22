#pragma once

#include "AUICommonDef.h"
#include "AUIDrawableWidget.h"


class AUIImageDrawable;

class ALICEUI_API AUIImageWidget : public AUIDrawableWidget
{
public:
    AUIImageWidget();
    ~AUIImageWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;



    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
	//////////////////////////////////////////////////////////////////////////
    // Image Drawable
public:
    void SetImage(const SkBitmap& bitmap) {
        SetImage(SkImage::MakeFromBitmap(bitmap));
    }
    void SetImage(const sk_sp<SkImage>& image);
    sk_sp<SkImage> GetImage() const;
    void SetImageDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
private:
    std::shared_ptr< AUIImageDrawable > m_pBaseDrawable;
    sk_sp<SkImage> m_pImage;

    //////////////////////////////////////////////////////////////////////////
    // Image stretch
public:
    void SetImageStretch(AUIImageStretch stretch);
    AUIImageStretch GetImageStretch() const;


    //////////////////////////////////////////////////////////////////////////
    // Image Opacity
public:
    void SetImageOpacity(SkAlpha val);
    SkAlpha GetImageOpacity() const;
};
