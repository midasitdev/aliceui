#pragma once

#include "AUIRecyclerCommonDef.h"

class AUIWidget;
class AUIRecyclerWidget;

class ALICEUI_API AUIRecyclerItemDecorator
{
public:
    AUIRecyclerItemDecorator();
    virtual ~AUIRecyclerItemDecorator();

    //////////////////////////////////////////////////////////////////////////
    // Getter
public:
    void GetItemOffset(SkRect& outRect, const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIRecyclerWidget >& pParent);
protected:
    virtual void OnGetItemOffset(SkRect& outRect, const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIRecyclerWidget >& pParent);

    //////////////////////////////////////////////////////////////////////////
    // Draw
public:
    void Draw(SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent);
    void DrawOver(SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent);
protected:
    virtual void OnDraw(SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent);
    virtual void OnDrawOver(SkCanvas* const canvas, const std::shared_ptr< AUIRecyclerWidget >& pParent);
};
