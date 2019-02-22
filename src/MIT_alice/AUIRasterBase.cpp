#include "pch.h"
#include "AUIRasterBase.h"
#include "AUIWidget.h"
#include "AUIRasterWidgetManager.h"
#include "AUIInnerGroupWidget.h"
#include "AUIApplication.h"
#include "AUICursorIcon.h"

AUIRasterBase::AUIRasterBase()
    : m_pWidgetManager(std::make_unique<AUIRasterWidgetManager>())
{

}

AUIRasterBase::~AUIRasterBase()
{

}

AUIRasterWidgetManager* AUIRasterBase::GetWidgetManager() const
{
    return m_pWidgetManager.get();
}

void AUIRasterBase::SetRootWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    // Check
    if ( m_pRootWidget == pWidget )
        return;
    if ( pWidget )
    {
        if ( pWidget->IsCreated() )
        {
            AUIAssertFailReason("Already created!!");
            return;
        }
    }

    // Remove previous
    if ( m_pRootWidget )
    {
        if ( m_pRootWidget->IsCreated() )
        {
            GetWidgetManager()->DestroyInstance( m_pRootWidget );
        }
    }

    // Set & Create
    m_pRootWidget = pWidget;
    if ( m_pRootWidget )
        GetWidgetManager()->CreateInstance( m_pRootWidget );
    GetWidgetManager()->SetFocusTarget( m_pRootWidget );

    MakeNeedRedraw();
}

void AUIRasterBase::UpdateWidgetSize()
{
    if ( auto pRoot = GetRootWidget() )
        pRoot->UpdateSize();
}

void AUIRasterBase::UpdateWidgetChildPosition()
{
    if ( auto pRoot = GetRootWidget() )
    {
        pRoot->UpdateChildPosition();
    }
}

void AUIRasterBase::AsyncUpdate()
{
    // Update instance task queue
    AUIApplication::Instance().RunUpdateInstanceTask();

    // Update
    if (GetWidgetManager()->UpdateAllInstance())
        MakeNeedRedraw();
}

void AUIRasterBase::SendTickTimeEvent()
{
    m_PrevTickTime = m_CurTickTime;
    m_CurTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    // Initial previous time
    if (std::chrono::milliseconds::zero() == m_PrevTickTime)
        m_PrevTickTime = m_CurTickTime;

    GetWidgetManager()->SendTickTimeEvent(m_PrevTickTime, m_CurTickTime);
}

void AUIRasterBase::Render(const sk_sp<SkSurface>& pSurface, bool eraseBackground /*= true*/)
{
    if (nullptr == pSurface)
        return;
    if (!IsNeedRedraw())
        return;

    auto pCanvas = pSurface->getCanvas();
    if (eraseBackground)
        pCanvas->clear(GetBackgroundColor());

    const auto saveCnt = pCanvas->getSaveCount();
    pCanvas->save();
    GetWidgetManager()->Render(pCanvas);
    pCanvas->restore();

    // Check save count
    AUIAssert(saveCnt == pCanvas->getSaveCount());

    m_bNeedRedraw = false;
}

bool AUIRasterBase::SendSetCursorEvent()
{
    AUICursorIcon cursoricon;
    cursoricon.ResetCursorIcon();
    const auto handled = GetWidgetManager()->SendSetCursorEvent(cursoricon);
    if (handled)
        cursoricon.ApplyCursorIcon();

    return handled;
}

void AUIRasterBase::SetViewport(int width, int height)
{
    GetWidgetManager()->SetSize(width, height);
}
