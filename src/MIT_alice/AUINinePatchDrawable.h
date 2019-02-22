#pragma once

#include "AUIDrawable.h"
#include "AUINinePatch.h"


class ALICEUI_API AUINinePatchDrawable : public AUIDrawable
{
public:
    AUINinePatchDrawable();
    AUINinePatchDrawable(const AUINinePatch& ninepatch);
    virtual ~AUINinePatchDrawable();

    //////////////////////////////////////////////////////////////////////////
    // Helper
public:
    static std::shared_ptr< AUINinePatchDrawable > CreateFromResourcePath(const std::wstring& path);

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // NinePatch
public:
private:
    AUINinePatch m_NinePatch;
};
