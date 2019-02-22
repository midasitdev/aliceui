#include "pch.h"
#include "AUITransitionWidget.h"

namespace {
    constexpr long long DefaultTransitionAnimDelay = 200;
}

AUITransitionWidget::AUITransitionWidget()
    : m_bInTransition( false )
    , m_fFromTargetOpacity( 1.0f )
    , m_fToTargetOpacity( 1.0f )
    , m_bFromFreezed( false )
    , m_bToFreezed( false )
{

}

AUITransitionWidget::~AUITransitionWidget()
{

}

void AUITransitionWidget::ReplaceWidget( const std::shared_ptr< AUIWidget >& pWidget, bool animate )
{
    if ( IsInTransition() )
    {
        // End transition
        EndTransition();
    }
    if ( m_pCurrentWidget == pWidget )
        return;


    AUIAssert( IsInTransition() == false );
    StartTransition( m_pCurrentWidget, pWidget, animate );
}


void AUITransitionWidget::BeforeTransition( const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget )
{
    if ( pToWidget != nullptr )
        AddChild( pToWidget );
}

void AUITransitionWidget::AfterTransition(const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget)
{
    if ( pFromWidget != nullptr )
        DelChild( pFromWidget );

    m_pCurrentWidget = pToWidget;

    UpdateSize();
    UpdateChildPosition();
}

void AUITransitionWidget::StartTransition( const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget, bool animate )
{
    m_pFromWidget = pFromWidget;
    m_pToWidget = pToWidget;

    // Save opacity
    if ( m_pFromWidget )
    {
        m_fFromTargetOpacity = m_pFromWidget->GetOpacity();
        m_bFromFreezed = m_pFromWidget->IsFreezed();
    }
    else
    {
        m_fFromTargetOpacity = 1.0f;
        m_bFromFreezed = false;
    }
    if ( m_pToWidget )
    {
        m_fToTargetOpacity = m_pToWidget->GetOpacity();
        m_bToFreezed = m_pToWidget->IsFreezed();
    }
    else
    {
        m_fToTargetOpacity = 1.0f;
        m_bToFreezed = false;
    }

    BeforeTransition( pFromWidget, pToWidget );
    if ( animate && pToWidget != nullptr )
    {
        m_bInTransition = true;
        StartAnimRunning();
        if ( m_pToWidget )
            m_pToWidget->SetOpacity( 0.0f );
        if ( m_pFromWidget )
            m_pFromWidget->Freeze();
    }
    else
    {
        if ( pToWidget )
            pToWidget->SetPosition( 0.0f, 0.0f );
        EndTransition();
    }

}

void AUITransitionWidget::EndTransition()
{
    m_bInTransition = false;
    StopAnimRunning();

    AfterTransition( m_pFromWidget, m_pToWidget );

    if ( m_pFromWidget )
    {
        m_pFromWidget->SetFreeze( m_bFromFreezed );
        m_pFromWidget->SetOpacity( m_fFromTargetOpacity );
    }
    if ( m_pToWidget )
    {
        m_pToWidget->SetOpacity( m_fToTargetOpacity );
    }

    m_pFromWidget.reset();
    m_pToWidget.reset();
}

void AUITransitionWidget::OnTickTime( const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime )
{
    SuperWidget::OnTickTime( prevTime, curTime );

    if ( IsInTransition() && IsAnimRunning() )
    {
        const auto startTick = GetAnimStartTick();
        const auto curTick = curTime;
        const auto diffTick = curTick - startTick;

        if ( diffTick.count() < DefaultTransitionAnimDelay )
        {
            const auto animWeight = static_cast<float>( diffTick.count() ) / static_cast<float>( DefaultTransitionAnimDelay );
            if ( m_pToWidget )
                m_pToWidget->SetOpacity( animWeight * m_fToTargetOpacity );
        }
        else
        {
            EndTransition();
        }
        Invalidate();
    }


}
