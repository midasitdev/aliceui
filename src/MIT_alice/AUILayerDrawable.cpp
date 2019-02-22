#include "pch.h"
#include "AUILayerDrawable.h"

AUILayerDrawable::AUILayerDrawable()
    : m_bRefreshDraw(false)
{

}

AUILayerDrawable::~AUILayerDrawable()
{

}

void AUILayerDrawable::OnDraw( SkCanvas* canvas )
{
    m_bRefreshDraw = false;
    const auto padding = GetDrawPadding();
    canvas->translate( padding.left(), padding.top() );

    for ( auto& pLayer : m_Layers )
    {
        if ( pLayer )
            pLayer->Draw( canvas );
    }

}

void AUILayerDrawable::OnChangeDrawUIState()
{
    for ( auto& pLayer : m_Layers )
    {
        if ( pLayer )
            pLayer->SetDrawUIState( GetDrawUIState() );
    }
}

void AUILayerDrawable::InsertLayer( const std::shared_ptr< AUIDrawable >& pLayer )
{
    if ( pLayer )
        pLayer->SetDrawUIState( GetDrawUIState() );
    m_Layers.emplace_back( pLayer );
}

void AUILayerDrawable::InsertLayer( size_t pos, const std::shared_ptr< AUIDrawable >& pLayer )
{
    AUIAssert( pos <= m_Layers.size() );
    auto itrPos = m_Layers.begin();
    std::advance( itrPos, pos );
    if ( pLayer )
        pLayer->SetDrawUIState( GetDrawUIState() );
    m_Layers.insert( itrPos, pLayer );
}

void AUILayerDrawable::SetLayer( size_t pos, const std::shared_ptr< AUIDrawable >& pLayer )
{
    AUIAssert( pos < m_Layers.size() );
    auto itrPos = m_Layers.begin();
    std::advance( itrPos, pos );
    if ( pLayer )
        pLayer->SetDrawUIState( GetDrawUIState() );
    (*itrPos) = pLayer;
}

void AUILayerDrawable::EraseLayer( const std::shared_ptr< AUIDrawable >& pLayer )
{
    const auto found = std::find( m_Layers.begin(), m_Layers.end(), pLayer );
    if ( found == m_Layers.end() )
    {
        AUIAssert( false );
        return;
    }
    m_Layers.erase( found );
}

void AUILayerDrawable::EraseLayer( size_t pos )
{
    auto itrPos = m_Layers.begin();
    std::advance( itrPos, pos );
    m_Layers.erase( itrPos );
}

long long AUILayerDrawable::GetLayerPos( const std::shared_ptr< AUIDrawable >& pLayer )
{
    const auto found = std::find( m_Layers.begin(), m_Layers.end(), pLayer );
    if ( found == m_Layers.end() )
    {
        AUIAssert( false );
        return -1;
    }
    const auto pos = std::distance( m_Layers.begin(), found );
    AUIAssert( pos >= 0 );
    return pos;
}

void AUILayerDrawable::OnSetDrawBound()
{
    const auto bound = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto subbound = SkRect::MakeLTRB( bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom() );
    for ( auto& pLayer : m_Layers )
    {
        if ( pLayer )
            pLayer->SetDrawBound( subbound );
    }
}

void AUILayerDrawable::OnSetDrawPadding()
{
    //for ( auto& pLayer : m_Layers )
    //{
    //    pLayer->SetDrawPadding( GetDrawPadding() );
    //}
}

void AUILayerDrawable::ClearLayer()
{
    m_Layers.clear();
}

void AUILayerDrawable::OnChangeLevelIndex()
{
    for ( auto& pLayer : m_Layers )
    {
        if ( pLayer )
            pLayer->SetLevelIndex( GetLevelIndex() );
    }
}

bool AUILayerDrawable::IsRefreshDraw() const
{
    for (auto& pLayer : m_Layers)
    {
        if (pLayer)
        {
            if (pLayer->IsRefreshDraw())
            {
                return true;
            }
        }
    }
    return m_bRefreshDraw;
}
