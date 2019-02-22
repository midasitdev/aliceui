#include "pch.h"
#include "AUIRecyclerWidget.h"
#include "AUIRecyclerLinearLayoutManager.h"
#include "AUIRecyclerAdapter.h"
#include "AUIRecyclerWidgetHolder.h"

AUIRecyclerWidget::AUIRecyclerWidget()
{
    SetLayoutManager( std::make_unique< AUIRecyclerLinearLayoutManager >() );
}

AUIRecyclerWidget::~AUIRecyclerWidget()
{
    m_spoolAdapter.DisconnectAll();
}

void AUIRecyclerWidget::SetAdapter( std::shared_ptr< AUIRecyclerAdapter > pAdapter )
{
    if ( m_pAdapter == pAdapter )
        return;

    m_spoolAdapter.DisconnectAll();

    m_pAdapter = pAdapter;

    SyncAdapter();

    if ( m_pAdapter )
    {
        m_spoolAdapter.Connect( m_pAdapter->signalDataChanged, this, &AUIRecyclerWidget::NotifyChange );
        m_spoolAdapter.Connect( m_pAdapter->signalItemChanged, this, &AUIRecyclerWidget::ItemChanged );
        m_spoolAdapter.Connect( m_pAdapter->signalItemInserted, this, &AUIRecyclerWidget::ItemInserted );
        m_spoolAdapter.Connect( m_pAdapter->signalItemMoved, this, &AUIRecyclerWidget::ItemMoved );
        m_spoolAdapter.Connect( m_pAdapter->signalItemRemoved, this, &AUIRecyclerWidget::ItemRemoved );
        m_spoolAdapter.Connect( m_pAdapter->signalRangeChanged, this, &AUIRecyclerWidget::ItemRangeChanged );
        m_spoolAdapter.Connect( m_pAdapter->signalRangeInserted, this, &AUIRecyclerWidget::ItemRangeInserted );
        m_spoolAdapter.Connect( m_pAdapter->signalRangeRemoved, this, &AUIRecyclerWidget::ItemRangeRemoved );
    }
}

void AUIRecyclerWidget::SetLayoutManager( std::unique_ptr< LayoutManager > pLayoutManager )
{
    AUIAssert( pLayoutManager );
    m_pLayoutManager = std::move( pLayoutManager );
    m_pLayoutManager->SetRecyclerWidget( this );
}

void AUIRecyclerWidget::SyncAdapter()
{
    if (nullptr == m_pAdapter)
    {
        GetLayoutManager()->ClearWidget();
        m_WidgetHolders.clear();
        return;
    }

    const auto totalItemCount = m_pAdapter->GetItemCount();
    const auto totalHolderCount = m_WidgetHolders.size();
    if (totalItemCount != totalHolderCount)
    {
        // NOTE: Optimize
        // Rebuild All
        GetLayoutManager()->ClearWidget();
        m_WidgetHolders.clear();
        for (size_t idx = 0; idx < totalItemCount; ++idx)
        {
            auto pHolder = m_pAdapter->CreateWidgetHolder(this, m_pAdapter->GetItemWidgetType(idx));
            m_pAdapter->BindWidgetHolder(pHolder, idx);
            m_WidgetHolders.emplace_back(pHolder);
            GetLayoutManager()->AddWidget(pHolder->GetItemWidget());
        }
    }
    else
    {
        AUIAssert(totalItemCount == totalHolderCount);
        for (size_t idx = 0; idx < totalItemCount; ++idx)
        {
            auto pHolder = m_WidgetHolders[idx];
            if (m_pAdapter->GetItemWidgetType(idx) != pHolder->GetItemWidgetType())
            {
                // Remove original
                AUIAssert(pHolder->GetItemWidget());
                GetLayoutManager()->DelWidget(pHolder->GetItemWidget());

                // Only when widget type changed
                pHolder = m_pAdapter->CreateWidgetHolder(this, m_pAdapter->GetItemWidgetType(idx));
                m_WidgetHolders[idx] = pHolder;
                GetLayoutManager()->AddWidget(pHolder->GetItemWidget(), idx);
                GetLayoutManager()->UpdateChildPosition();
            }
            AUIAssert(pHolder);
            m_pAdapter->BindWidgetHolder(pHolder, idx);
        }
    }
}

void AUIRecyclerWidget::OnMeasureSize( SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    GetLayoutManager()->MeasureSize(width, widthSpec, height, heightSpec);
}

void AUIRecyclerWidget::OnUpdateChildPosition()
{
    GetLayoutManager()->UpdateChildPosition();
}

void AUIRecyclerWidget::NotifyChange()
{
    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemChanged( size_t pos )
{
    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemInserted( size_t pos )
{

    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemMoved( size_t fromPos, size_t toPos )
{

    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemRemoved( size_t pos )
{

    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemRangeChanged( size_t startPos, size_t itemCount )
{

    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemRangeInserted( size_t startPos, size_t itemCount )
{

    // TODO : Optimize
    SyncAdapter();
}

void AUIRecyclerWidget::ItemRangeRemoved( size_t startPos, size_t itemCount )
{

    // TODO : Optimize
    SyncAdapter();
}
//
//void AUIRecyclerWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
//{
//    auto pLayoutManager = GetLayoutManager();
//    AUIAssert( pLayoutManager );
//    pLayoutManager->AddWidget( widget, pos );
//}
//
//void AUIRecyclerWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
//{
//    auto pLayoutManager = GetLayoutManager();
//    AUIAssert( pLayoutManager );
//    pLayoutManager->DelWidget( widget );
//}
//
//void AUIRecyclerWidget::PopSubWidget()
//{
//    const auto children = GetChildren();
//    const auto childCount = GetChildren().size();
//    if ( childCount == 0 )
//        return;
//    DelSubWidget( children.back() );
//}
//
//void AUIRecyclerWidget::ClearSubWidget()
//{
//    auto pLayoutManager = GetLayoutManager();
//    AUIAssert( pLayoutManager );
//    pLayoutManager->ClearWidget();
//}
//
//std::shared_ptr< AUIWidget > AUIRecyclerWidget::FindSubWidget( size_t pos )
//{
//    return nullptr;
//}
//
//size_t AUIRecyclerWidget::SubWidgetCount() const
//{
//    return 0;
//}
