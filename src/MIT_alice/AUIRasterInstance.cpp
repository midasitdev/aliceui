#include "pch.h"
#include "AUIRasterInstance.h"
#include "AUIRasterWidgetManager.h"
#include "AUIWidget.h"
#include "AUIDrawableWidget.h"
#include "MAUI3DDrawableWidget.h"
#include "AUIInnerGroupWidget.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIApplication.h"
#include "AUISkiaRender.h"
#include "AUIDrawable.h"

AUIRasterInstance::AUIRasterInstance( AUIRasterWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
    : AUIInstance( pWidgetManager, pWidget )
{
    AUIAssert(dynamic_cast<AUIRasterWidgetManager*>(pWidgetManager));
}

AUIRasterWidgetManager* AUIRasterInstance::GetUIRasterWidgetManager() const
{
    return static_cast<AUIRasterWidgetManager*>(GetWidgetManager());
}

void AUIRasterInstance::OnCreateInstance()
{
    AUIInstance::OnCreateInstance();

    m_bDrawableRoot = true;
    auto pWidget = GetWidget();
    m_wpDrawableRootWidget = pWidget->shared_from_this();

    while (pWidget->GetParent() != nullptr)
    {
        pWidget = pWidget->GetParent();
        if (nullptr != pWidget->GetAsDrawable())
        {
            m_bDrawableRoot = false;
            m_wpDrawableRootWidget = pWidget->shared_from_this();
        }
    }
    if ( IsDrawableRoot() == false )
        return;
}

void AUIRasterInstance::OnDestroyInstance()
{
    AUIInstance::OnDestroyInstance();
}

void AUIRasterInstance::OnUpdateInstance()
{
    AUIInstance::OnUpdateInstance();
}

void AUIRasterInstance::OnSetDirty()
{
    if ( IsDrawableRoot() )
        return;

    if ( auto pDrawableRoot = m_wpDrawableRootWidget.lock() )
    {
        if ( auto pDrawableRootInst = GetWidgetManager()->FindInstance( pDrawableRoot.get() ) )
        {
            pDrawableRootInst->SetDirty();
        }
    }
}
