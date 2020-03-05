#include "pch.h"
#include "AUIMFCInstance.h"
#include "AUIMFCWidget.h"
#include "AUIWidgetManager.h"
#include "AUIMFCHandle.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"

AUIMFCInstance::AUIMFCInstance( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
    : AUIInstance( pWidgetManager, pWidget )
    , m_bShowState( false )
{

}

AUIMFCInstance::~AUIMFCInstance()
{

}


void AUIMFCInstance::OnSetRootMatrix()
{

}

void AUIMFCInstance::OnSetPosition()
{
    auto pWidget = GetWidget()->DynCast< AUIMFCWidget >();
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Unsupported type");
        return;
    }

    const auto pos = pWidget->GetPositionAtRoot();
    const auto size = pWidget->GetSize();
    pWidget->GetWnd()->MoveWindow( (int)pos.fX, (int)pos.fY, (int)size.fX, (int)size.fY );
    pWidget->GetWnd()->Invalidate();
}

void AUIMFCInstance::OnCreateInstance()
{
    auto pWidget = GetWidget()->DynCast< AUIMFCWidget >();
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Unsupported type");
        return;
    }

    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    m_bShowState = false;
}

void AUIMFCInstance::OnDestroyInstance()
{
    auto pWidget = GetWidget()->DynCast< AUIMFCWidget >();
    if ( pWidget == nullptr )
    {
        AUIAssert( !"Unsupported type" );
        return;
    }

    // NOTE : Actual window must be destroyed by widget
    auto pWnd = pWidget->GetWnd();
    if (::IsWindow( pWnd->GetSafeHwnd() ))
        pWnd->ShowWindow(SW_HIDE);

    m_bShowState = false;
}

void AUIMFCInstance::OnUpdateInstance()
{
    auto pWidget = GetWidget()->DynCast< AUIMFCWidget >();
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Unsupported type");
        return;
    }


    auto pWnd = pWidget->GetWnd();
    if ( !::IsWindow( pWnd->GetSafeHwnd() ) )
    {
        AUIAssertFail();
        return;
    }

    bool showstate = false;
    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
	if ( widgettree.IsVisibleByParent( pWidget ) )
	{
        if ( widgettree.IsIgnoredByParent( pWidget ) )
            showstate = false;
        else
            showstate = true;
	}
	else
	{
        showstate = false;
    }

    if ( m_bShowState != showstate )
    {
        if ( showstate )
            pWnd->ShowWindow( SW_SHOWNA );
        else
            pWnd->ShowWindow( SW_HIDE );
        m_bShowState = showstate;

        // Force Invalidate Client Area
        pWnd->UpdateWindow();
    }
}
