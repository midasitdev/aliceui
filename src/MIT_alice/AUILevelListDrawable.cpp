#include "pch.h"
#include "AUILevelListDrawable.h"

AUILevelListDrawable::AUILevelListDrawable()
    : m_bRefreshDraw(false)
{

}

AUILevelListDrawable::~AUILevelListDrawable()
{

}

void AUILevelListDrawable::OnDraw( SkCanvas* const canvas )
{
    m_bRefreshDraw = false;
    auto pDrawable = GetCurDrawable();
    if ( nullptr == pDrawable )
        return;

    const auto padding = GetDrawPadding();
    //canvas->translate( padding.left(), padding.top() );
    const auto bound = GetDrawBound();
    canvas->clipRect( SkRect::MakeLTRB( bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom() ) );

    pDrawable->Draw( canvas );

}

void AUILevelListDrawable::OnChangeLevelIndex()
{
    const auto levelIndex = GetLevelIndex();
    for ( const auto& indexData : m_IndexData )
    {
        if ( levelIndex >= indexData.fLowBound &&
            levelIndex <= indexData.fHighBound )
        {
            m_pCurDrawable = indexData.fDrawable;
            m_bRefreshDraw = true;
            break;
        }
    }
    if (m_pCurDrawable)
        m_bRefreshDraw |= m_pCurDrawable->IsRefreshDraw();
}

void AUILevelListDrawable::ClearLevel()
{
    m_pCurDrawable.reset();
    m_IndexData.clear();
}

void AUILevelListDrawable::AddLevel( int low, int high, const std::shared_ptr< AUIDrawable >& pDrawable )
{
    if ( nullptr == pDrawable )
    {
        AUIAssertFailReason("No drawable");
        return;
    }
    AUIAssert( this != pDrawable.get() );
    if ( low > high )
    {
        AUIAssert( low <= high );
        return;
    }
    m_IndexData.emplace_back( low, high, pDrawable );
}
