#include "pch.h"
#include "AUISkiaRender.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIWidget.h"
#include "AUIApplication.h"
#include "AUIDrawable.h"


void AUISkiaRenderer::RenderWidget( SkCanvas* const canvas, AUIWidget* const pWidget, float opacity )
{
    const auto pos = pWidget->GetPosition();
    AUISkiaRenderer::RenderWidget( canvas, pWidget, pos.fX, pos.fY, opacity );
}

void AUISkiaRenderer::RenderWidget( SkCanvas* const canvas, AUIWidget* const pWidget, float x, float y, float opacity /*= 1.0f */ )
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    if ( pWidget->IsCreated() == false )
        return;
    if (pWidget->IsIgnored())
        return;
    if (false == pWidget->IsVisible())
        return;

    const auto _transX = SkScalarFloorToScalar(x);
    const auto _transY = SkScalarFloorToScalar(y);
    const auto _width = pWidget->GetWidth();
    const auto _height = pWidget->GetHeight();
    SkRect _clipBound;
    const auto _hasClipBound = canvas->getLocalClipBounds(&_clipBound);
    if (_hasClipBound && (
        _transX + _width < _clipBound.fLeft ||
        _transX > _clipBound.fRight ||
        _transY + _height < _clipBound.fTop ||
        _transY > _clipBound.fBottom))
    {
        return;
    }

    canvas->save();
    canvas->translate(_transX, _transY);
    canvas->clipRect(SkRect::MakeWH(_width, _height));


    if (auto pDrawable = pWidget->GetAsDrawable())
    {
        pDrawable->Draw(canvas);
    }

    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    const auto& arrChildren = widgettree.RefChildren( pWidget );
    for ( auto& child : arrChildren )
    {
        auto pChildWidget = child.get();
        if (false == pChildWidget->IsCreated())
            continue;
        if (pChildWidget->IsIgnored())
            continue;
        if (false == pChildWidget->IsVisible())
            continue;

        AUISkiaRenderer::RenderWidget( canvas, pChildWidget, opacity );
    }
    canvas->restore();
}
