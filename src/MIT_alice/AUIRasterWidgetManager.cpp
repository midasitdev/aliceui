#include "pch.h"
#include "AUIRasterWidgetManager.h"
#include "AUIInstance.h"
#include "AUICanvasHelper.h"
#include "AUIWidget.h"
#include "AUIRasterInstance.h"
#include "AUIForm.h"
#include "AUIHandle.h"

#if defined( _MSC_VER )
#include "AUIMFCWidget.h"
#include "AUIMFCInstance.h"
#endif
#include "AUIApplication.h"
#include "AUITooltipWidget.h"
#include "AUILinearLayoutWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"
#include "AUILayerDrawable.h"
#include "AUIWidgetTreeHelper.h"
#include "AUISkiaRender.h"
#include "AUITooltip.h"
#include "AUIRasterTooltipWidget.h"

AUIRasterWidgetManager::AUIRasterWidgetManager()
    : m_pTooltipBase(std::make_shared<AUIRasterTooltipWidget>())
{

}

AUIRasterWidgetManager::~AUIRasterWidgetManager()
{

}

bool AUIRasterWidgetManager::OnInvoke( const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt )
{
    // Clear all previous Forms
    std::vector< AUIWidget* > arrErasePopup;
    for ( auto& popup : m_Popups )
    {
        if ( popup.second->IsActivated() == false )
            arrErasePopup.emplace_back( popup.first );
    }
    for ( auto& itr : arrErasePopup )
    {
        m_Popups.erase( itr );
    }

    auto pHandle = GetHandle();
    if ( pHandle == nullptr )
    {
        AUIAssertFailReason("Popup not supported!");
        return false;
    }
    int windowX;
    int windowY;
    pHandle->GetPosition( windowX, windowY );

    auto posRoot = pParent->GetPositionAtRoot();

    pWidget->UpdateSize();
    const auto size = pWidget->GetMeasureSize();


    auto tmpPos = pos;
    if (AUIPopupPos::kParentOptimalBottom == opt)
    {
        tmpPos.fY = pParent->GetMeasureHeight();
    }
    else if (AUIPopupPos::kParentOptimalAbove == opt)
    {
        tmpPos.fY = -size.fY;
    }


    auto popupPosX = windowX + SkScalarRoundToInt( posRoot.fX + tmpPos.fX );
    auto popupPosY = windowY + SkScalarRoundToInt( posRoot.fY + tmpPos.fY );
    const auto widgetWidth = SkScalarRoundToInt( size.fX );
    const auto widgetHeight = SkScalarRoundToInt( size.fY );


    if (AUIPopupPos::kOptimal == opt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint( monitorRect, popupPosX, popupPosY );

        if ( popupPosX + widgetWidth > monitorRect.right() )
        {
            popupPosX -= ( popupPosX + widgetWidth - SkScalarRoundToInt( monitorRect.right() ) );
        }
        if ( popupPosY + widgetHeight > monitorRect.bottom() )
        {
            popupPosY -= ( popupPosY + widgetHeight - SkScalarRoundToInt( monitorRect.bottom() ) );
        }
    }
    else if (AUIPopupPos::kParentOptimalAbove == opt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint(monitorRect, popupPosX, popupPosY);

        if (popupPosX + widgetWidth > monitorRect.right())
        {
            popupPosX -= (popupPosX + widgetWidth - SkScalarRoundToInt(monitorRect.right()));
        }
        if (popupPosY < monitorRect.top())
        {
            popupPosY = SkScalarRoundToInt(monitorRect.top());
        }
    }
    else if (AUIPopupPos::kParentOptimalBottom == opt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint(monitorRect, popupPosX, popupPosY);

        if (popupPosX + widgetWidth > monitorRect.right())
        {
            popupPosX -= (popupPosX + widgetWidth - SkScalarRoundToInt(monitorRect.right()));
        }
        if (popupPosY + widgetHeight > monitorRect.bottom())
        {
            popupPosY -= (popupPosY + widgetHeight - SkScalarRoundToInt(monitorRect.bottom()));
        }
    }

    auto pForm = std::make_shared< AUIForm >();
    pForm->SetRootWidget( pWidget );
    pForm->SetPositionAndSize( popupPosX, popupPosY, widgetWidth, widgetHeight );
    pForm->Activate( pHandle );

    m_Popups[pWidget.get()] = std::move( pForm );

    return true;
}

bool AUIRasterWidgetManager::OnDismiss( const std::shared_ptr< AUIWidget >& pWidget )
{
    const auto found = m_Popups.find( pWidget.get() );
    AUIAssert( found != m_Popups.end() );
    found->second->SetRootWidget( nullptr );
    found->second->Deactivate();
    return true;
}

void AUIRasterWidgetManager::Render( SkCanvas* const canvas )
{
    std::vector<AUIWidget*> arrRootWidgets;
    arrRootWidgets.reserve(100);
    for ( auto inst = InstBegin() ; inst != InstEnd() ; ++inst )
    {
        auto pInst = (*inst).get();
        auto pWidget = pInst->GetWidget();
        if ( false == pInst->IsDrawableRoot() )
            continue;
        arrRootWidgets.emplace_back(pWidget);
    }
    for (const auto& pWidget : arrRootWidgets)
    {
        AUISkiaRenderer::RenderWidget(canvas, pWidget);
    }
}

std::shared_ptr< AUIInstance > AUIRasterWidgetManager::OnRegisterWidget(const std::shared_ptr< AUIWidget >& pWidget)
{
#if defined( _MSC_VER )
    if (pWidget->IsKindOf< AUIMFCWidget >())
        return std::make_shared< AUIMFCInstance >(this, pWidget);
#endif
    if (nullptr != pWidget->GetAsDrawable())
        return std::make_shared< AUIRasterInstance >( this, pWidget );
    else
        return std::make_shared< AUIInstance >( this, pWidget );
}

void AUIRasterWidgetManager::OnShowTooltip( const std::shared_ptr< AUITooltip >& pTooltip, int x, int y )
{
    if (nullptr == m_pTooltipForm)
    {
        m_pTooltipForm = AUIApplication::Instance().GetTooltipForm();
        if (nullptr == m_pTooltipForm)
        {
            m_pTooltipForm = std::make_shared< AUIForm >();
            m_pTooltipForm->SetRootWidget(m_pTooltipBase);
            m_pTooltipForm->SetNonActivate(true);
            m_pTooltipForm->SetTopMost(true);
        }
    }
    AUIAssert(m_pTooltipForm);

    auto pHandle = GetHandle();
    if (pHandle == nullptr)
    {
        AUIAssert(!"Popup not supported!");
        return;
    }

    m_wpCurTooltip = pTooltip;

    AUIAssert( m_pTooltipBase );

    m_pTooltipForm->SetRootWidget(m_pTooltipBase);

    int windowX;
    int windowY;
    pHandle->GetPosition( windowX, windowY );

    if ( false == m_pTooltipForm->IsActivated() )
    {
        //m_pTooltipForm->Activate( pHandle );
        m_pTooltipForm->Activate();
    }

    constexpr SkScalar kTooltipMaxWidth = 1920.0f;
    constexpr SkScalar kTooltipMaxHeight = 1080.0f;
    constexpr SkScalar kTooltipDefaultWidth = 10.0f;
    constexpr SkScalar kTooltipDefaultHeight = 10.0f;

    auto pTooltipWidget = std::make_shared< AUITooltipWidget >();
    pTooltipWidget->SetData( pTooltip );
    pTooltipWidget->SetSizePolicy( AUISizePolicy::kContent, AUISizePolicy::kContent );
    // TODO : Need better way to esitmate size
    AUIWidget::OnCallMeasureAndUpdateSize(pTooltipWidget.get(), kTooltipMaxWidth, AUIMeasureSpec::kAtMost, kTooltipMaxHeight, AUIMeasureSpec::kAtMost);
    const auto expectSize = pTooltipWidget->GetSize();
    if (SkScalarNearlyEqual(expectSize.fX, kTooltipMaxWidth) && SkScalarNearlyEqual(expectSize.fY, kTooltipMaxHeight))
        pTooltipWidget->SetDefaultSize(kTooltipDefaultWidth, kTooltipDefaultHeight);
    else
        pTooltipWidget->SetDefaultSize(pTooltipWidget->GetSize());
    pTooltipWidget->UpdateSize();
    pTooltipWidget->UpdateChildPosition();

    const auto widgetWidth = SkScalarRoundToInt(pTooltipWidget->GetWidth());
    const auto widgetHeight = SkScalarRoundToInt(pTooltipWidget->GetHeight());

    auto popupPosX = windowX + x;
    auto popupPosY = windowY + y;

    const auto popupOpt = pTooltip->GetPopupOpt();


    if (AUIPopupPos::kOptimal == popupOpt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint(monitorRect, popupPosX, popupPosY);
        if (popupPosX + widgetWidth > monitorRect.right())
        {
            popupPosX -= (popupPosX + widgetWidth - SkScalarRoundToInt(monitorRect.right()));
        }
        if (popupPosY + widgetHeight > monitorRect.bottom())
        {
            popupPosY -= (popupPosY + widgetHeight - SkScalarRoundToInt(monitorRect.bottom()));
        }
    }
    else if (AUIPopupPos::kParentOptimalAbove == popupOpt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint(monitorRect, popupPosX, popupPosY);

        if (popupPosX + widgetWidth > monitorRect.right())
        {
            popupPosX -= (popupPosX + widgetWidth - SkScalarRoundToInt(monitorRect.right()));
        }
        if (popupPosY < monitorRect.top())
        {
            popupPosY = SkScalarRoundToInt(monitorRect.top());
        }
    }
    else if (AUIPopupPos::kParentOptimalBottom == popupOpt)
    {
        SkRect monitorRect;
        AUIApplication::Instance().GetMonitorRectFromPoint(monitorRect, popupPosX, popupPosY);

        if (popupPosX + widgetWidth > monitorRect.right())
        {
            popupPosX -= (popupPosX + widgetWidth - SkScalarRoundToInt(monitorRect.right()));
        }
        if (popupPosY + widgetHeight > monitorRect.bottom())
        {
            popupPosY -= (popupPosY + widgetHeight - SkScalarRoundToInt(monitorRect.bottom()));
        }
    }

    m_pTooltipForm->SetPositionAndSize(popupPosX, popupPosY, widgetWidth, widgetHeight);
    m_pTooltipForm->SetVisible(true);
    m_pTooltipForm->UpdateWindow();
    m_pTooltipForm->Invalidate();

    m_pTooltipBase->ClearSubWidget();
    m_pTooltipBase->AddSubWidget( pTooltipWidget );
}

void AUIRasterWidgetManager::OnHideTooltip()
{
    if ( m_pTooltipForm )
    {
        m_pTooltipForm->SetVisible( false );
    }
}

void AUIRasterWidgetManager::SetSize(int width, int height)
{
    m_Viewport = glm::vec4(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
}

glm::mat4 AUIRasterWidgetManager::GetViewingMatrix() const
{
    return glm::mat4(1.0f);
}

glm::mat4 AUIRasterWidgetManager::GetProjectionMatrix() const
{
    return glm::mat4(1.0f);
}

glm::vec4 AUIRasterWidgetManager::GetViewport() const
{
    return m_Viewport;
}
