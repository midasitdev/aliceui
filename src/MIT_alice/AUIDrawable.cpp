#include "pch.h"
#include "AUIDrawable.h"

void AUIDrawable::Draw(int x, int y, int width, int height)
{
    width = width - x;
    height = height - y;

    if (width <= 0 || height <= 0)
        return;

    const SkSurfaceProps defaultProps(0, SkPixelGeometry::kUnknown_SkPixelGeometry);
    if (nullptr == m_pSurface) {
        m_pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(width, height, SkAlphaType::kOpaque_SkAlphaType), &defaultProps);
    }
    else {
        if (m_pSurface->width() != width || m_pSurface->height() != height)
            m_pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(width, height, SkAlphaType::kOpaque_SkAlphaType), &defaultProps);
    }
    AUIAssert(m_pSurface);

    auto canvas = m_pSurface->getCanvas();
    canvas->clear(SkColorSetARGB(0, 0, 0, 0));
    canvas->save();
    OnDraw(canvas);
    canvas->restore();
}

void AUIDrawable::Draw( SkCanvas* canvas )
{
    const auto bound = GetDrawBound();
    if (bound.isEmpty())
    {
        // Invalid size
        return;
    }
    canvas->save();
    AUIAssert( canvas );
    OnDraw( canvas );
    canvas->restore();
}

void AUIDrawable::SetDrawUIState( const AUIState& state )
{
    m_DrawUIState = state;
    OnChangeDrawUIState();
}

sk_sp<SkImage> AUIDrawable::GetImageBuffer() const
{
    if (nullptr == m_pSurface)
        return {};
    return m_pSurface->makeImageSnapshot();
}

void AUIDrawable::SetDrawBound( const SkRect& bound )
{
    m_DrawBound = bound;
    OnSetDrawBound();
}

void AUIDrawable::SetDrawPadding( const SkRect& padding )
{
    m_DrawPadding = padding;
    OnSetDrawPadding();
}

SkRect AUIDrawable::GetContentRect() const
{
     return SkRect::MakeLTRB( m_DrawBound.left() + m_DrawPadding.left(), m_DrawBound.top() + m_DrawPadding.top(), m_DrawBound.right() - m_DrawPadding.right(), m_DrawBound.bottom() - m_DrawPadding.bottom() );
}

void AUIDrawable::SetLevelIndex( int val )
{
    m_LevelIndex = val;
    OnChangeLevelIndex();
}

bool AUIDrawable::IsRefreshDraw() const
{
    return false;
}
