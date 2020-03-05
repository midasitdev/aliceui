#include "pch.h"
#include "AUIWidgetManager.h"
#include "AUIWidget.h"
#include "AUICursorIcon.h"
#include "AUIWidgetSelection.h"
#include "AUITooltip.h"
#include "AUIInnerGroupWidget.h"
#include "AUIInstance.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"
#include "AUITooltipWidget.h"
#include "AUIDrawable.h"
#include "AUIHandle.h"

#include <optional>
#include "AUIDebug.h"
#include "AUISensorManager.h"
#include "AUIWidgetRootInfo.h"
#include "AUIScreenSensorManager.h"
#include "AUIWorldPanelSensorManager.h"
#include "AUIWorldSensorManager.h"
#include "AUISteadyScaleSensorManager.h"


AUIWidgetManager::AUIWidgetManager()
    : m_pWidgetSelection( std::make_unique< AUIWidgetSelection >() )
    , m_MousePosX( 0 )
    , m_MousePosY( 0 )
    , m_bEnabled( true )
    , m_bGrabMouseEvent( false )
    , m_bShowTooltip( false )
    , m_bHasTooltipInst( false )
    , m_TooltipOffsetX( 20 )
    , m_TooltipOffsetY( 20 )
    , m_bDirty( false )
{
    AUIApplication::Instance().AttachWidgetManager(this);
    m_aSensorManager[(size_t)AUICoordSpace::kScreenSpace] = std::make_unique<AUIScreenSensorManager>();
    m_aSensorManager[(size_t)AUICoordSpace::kWorldPanel] = std::make_unique<AUIWorldPanelSensorManager>();
    m_aSensorManager[(size_t)AUICoordSpace::kWorld] = std::make_unique<AUIWorldSensorManager>();
    m_aSensorManager[(size_t)AUICoordSpace::kSteadyScale] = std::make_unique<AUISteadyScaleSensorManager>();

    for (auto i = 0; i < AUICoordSpaceNum; i++)
    {
        if(auto pSensorManager = m_aSensorManager[i].get())
            pSensorManager->SetWidgetManager(this);
    }
}

AUIWidgetManager::~AUIWidgetManager()
{
    AUIApplication::Instance().DetachWidgetmanager( this );
}

void AUIWidgetManager::SetHandle( const std::shared_ptr< AUIHandle >& pHandle )
{
    m_wpHandle = pHandle;
}

void AUIWidgetManager::CreateInstance( const std::shared_ptr< AUIWidget >& pWidget)
{
    AUIApplication::Instance().CreateInstance( this, pWidget );
}

void AUIWidgetManager::DestroyInstance( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIApplication::Instance().DestroyInstance( this, pWidget );
}

void AUIWidgetManager::ClearInstance()
{
    AUIApplication::Instance().ClearInstance( this );
}

bool AUIWidgetManager::SendMouseEvent( const MAUIMouseEvent& evt )
{
    bool handled = false;
    bool hovered = false;

    m_MousePosX = evt.fX;
    m_MousePosY = evt.fY;

    const auto vp = GetViewport();
    const auto matProj = GetProjectionMatrix();
    const auto matView = GetViewingMatrix();

    glm::vec4 vECOrg, vECDir;	//Eye좌표계 기준 Mouse Point Ray 시작점과 방향
    if (matProj[3][2] == 0.f)//is orthogonal
    {
        vECOrg = glm::vec4(glm::unProject(glm::vec3(m_MousePosX, vp[3] - m_MousePosY - 1.0f, 0.0), glm::mat4(1.f), matProj, vp), 1);
        vECDir = glm::vec4(0, 0, -1, 0);
    }
    else
    {
        vECOrg = glm::vec4(0, 0, 0, 1);
        vECDir = glm::vec4(glm::unProject(glm::vec3(m_MousePosX, vp[3] - m_MousePosY - 1.0f, 0.5), glm::mat4(1.f), matProj, vp), 0);
    }
    const auto matInv = glm::inverse(matView);
    m_MouseOrg = glm::dvec3(matInv * vECOrg);
    m_MouseDir = glm::normalize(glm::dvec3(matInv * vECDir));


    // Update Hit Test Buffer
    if (evt.fType == MAUIMouseEvent::kMove_EventType || evt.fType == MAUIMouseEvent::kWheel_EventType)
    {
        // NOTE : DO NOT UPDATE ON OTHER EVENTS (e.g. Popup focus will regenerate all hit test state)
        //mit::lib::MDebugProfiler _hitTestProfiler(L"Refresh Hit Test");
        //if(!IsGrabMouseEvent())
        RefreshHitTestBuffer(evt.fX, evt.fY);
    }

    // Last drawn is topmost, thus event goes inverse order

    hovered |= SendMouseHoverEventToWidget(evt);



    if ( IsGrabMouseEvent() )
    {
        std::list< std::weak_ptr< AUIWidget > > tmpList;
        GetWidgetSelection().GetCopy( tmpList );
        const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
        for ( auto itr : tmpList )
        {
            if ( auto pWidget = itr.lock() )
            {
                if ( pWidget->IsInstanced() == false )
                    continue;
                if ( widgettree.IsVisibleByParent( pWidget ) == false )
                    continue;
                if ( widgettree.IsFreezedByParent( pWidget ) )
                    continue;
                if ( widgettree.IsIgnoredByParent( pWidget ) )
                    continue;

                handled |= pWidget->OnMouseEvent( evt );
            }
        }
    }

    // Copy of hit test buffer. Hit test buffer may change during mouse event 
    auto tmpHitTestBuffer = m_HitTestBuffer;

    if (false == handled)
    {
        // Preview event
        for (auto itr = tmpHitTestBuffer.rbegin() ; itr != tmpHitTestBuffer.rend() ; ++itr)
        {
            auto target = (*itr).fInstance;
            if (auto pInstance = target.lock().get()) {
                auto pWidget = pInstance->GetWidget();
                AUIAssert(pInstance->IsHit());
                AUIAssert(pWidget);
                if (false == pWidget->HasPreviewMouseEventCallback())
                    continue;
                if (pWidget->IsMouseHover())
                    handled = pWidget->OnPreviewMouseEvent(evt);
                if ( handled )
                    break;
            }
        }
    }

    if ( false == handled )
    {
        // Hit test order
        for ( auto itr = tmpHitTestBuffer.begin() ; itr != tmpHitTestBuffer.end() ; ++itr )
        {
            auto target = (*itr).fInstance;
            if ( auto pInstance = target.lock().get() )
            {
                AUIAssert( pInstance->IsHit() );
                handled = SendMouseEventToWidget( pInstance, evt );
                if ( handled )
                {
                    if ( MAUIMouseEvent::kMove_EventType == evt.fType )
                    {
                        AUIAssert( pInstance->GetWidget() );
                        m_wpTooltipTarget = pInstance->GetWidget()->weak_from_this();
                    }
                    else
                    {
                        m_wpTooltipTarget.reset();
                    }
                    break;
                }
            }
        }
    }


    if ( hovered == false )
    {
        // Release focus
        switch ( evt.fType )
        {
        case MAUIMouseEvent::kLBtnDown_EventType:
        case MAUIMouseEvent::kMBtnDown_EventType:
        case MAUIMouseEvent::kRBtnDown_EventType:
            SetFocusTarget({});
            break;
        default:
            break;
        }
    }

    if (MAUIMouseEvent::kLeave_EventType == evt.fType && HasTooltipInstance())
    {
        this->OnHideTooltip();
    }


    m_bLastHandled = handled;
    m_bLastHovered = hovered;

    return handled || hovered;
}

bool AUIWidgetManager::SendMouseHoverEventToWidget( const MAUIMouseEvent& evt ) // 받은 Mouse Hover Event를 Widget에 전달
{
    bool hovered = false;
    auto aHoverInstance = m_HoverInstances;
    if (evt.fType == MAUIMouseEvent::kLeave_EventType)
    {
        // Leave all
        for (auto wpInstance : aHoverInstance)
        {
            auto pInstance = wpInstance.lock();
            if (!pInstance)
                continue;
            auto pWidget = pInstance->GetWidget();
            if (pWidget->IsMouseHover())
            {
                pWidget->MouseLeave();
            }
     //       else
        //        assert(0);
        }
        m_HoverInstances.clear();
        return hovered;
    }



    auto tmpHitTestBuffer = m_HitTestBuffer;
    m_HoverInstances.clear();
    for (auto itr = tmpHitTestBuffer.begin(); itr != tmpHitTestBuffer.end(); ++itr)
    {
        // Hover event
        auto wpInstance = (*itr).fInstance;
        auto pInstance = wpInstance.lock();
        if (!pInstance)
            continue;
        auto pWidget = pInstance->GetWidget();

        // Newly hovered
        if (pWidget->IsMouseHover() == false)
        {
            pWidget->MouseEnter();
        }
        // Hover Event
        pWidget->MouseHover();
        hovered |= true;
        m_HoverInstances.push_back(wpInstance);
    }

    for (auto wpInstance : aHoverInstance)
    {
        auto pInstance = wpInstance.lock();
        if (!pInstance)
            continue;
        if (pInstance->IsHit())
            continue;
        auto pWidget = pInstance->GetWidget();
        if (pWidget->IsMouseHover())
        {
            pWidget->MouseLeave();
        }
     //   else
      //      assert(0);
    }

    return hovered;
    //bool hovered = false;
    //decltype(m_Instances) currentInstances;
    //do
    //{
    //    std::lock_guard< std::recursive_mutex > guard(m_mtxInstances);
    //    currentInstances.reserve(m_Instances.size());
    //    currentInstances.assign(m_Instances.begin(), m_Instances.end());
    //} while (false);
    //const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    //for (auto itrInst = currentInstances.rbegin(); itrInst != currentInstances.rend(); ++itrInst)
    //{
    //    // Hover event
    //    auto pInstance = (*itrInst).get();
    //    if (pInstance == nullptr)
    //    {
    //        AUIAssertFailReason("Invalid instance");
    //        continue;
    //    }
    //    auto pWidget = pInstance->GetWidget();
    //    if (pWidget->IsInstanced() == false)
    //        continue;
    //    if (widgettree.IsVisibleByParent(pWidget) == false)
    //        continue;
    //    if (widgettree.IsFreezedByParent(pWidget))
    //        continue;
    //    if (widgettree.IsIgnoredByParent(pWidget))
    //        continue;
    //    // By hit
    //    if (pInstance->IsHit())
    //    {
    //        if (evt.fType == MAUIMouseEvent::kLeave_EventType)
    //        {
    //            // Leave all
    //            if (pWidget->IsMouseHover())
    //            {
    //                pWidget->MouseLeave();
    //            }
    //        }
    //        else
    //        {
    //            // Newly hovered
    //            if (pWidget->IsMouseHover() == false)
    //            {
    //                pWidget->MouseEnter();
    //            }
    //            // Hover Event
    //            pWidget->MouseHover();
    //            hovered |= true;
    //        }
    //    }
    //    else
    //    {
    //        // Leave all
    //        if (pWidget->IsMouseHover())
    //        {
    //            pWidget->MouseLeave();
    //        }
    //    }
    //}
    //return hovered;
}

bool AUIWidgetManager::SendMouseEventToWidget( AUIInstance* const pInstance, const MAUIMouseEvent& evt )
{
    if ( pInstance == nullptr )
    {
        AUIAssertFailReason("Invalid instance");
        return false;
    }

    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    auto pWidget = pInstance->GetWidget();
    if ( nullptr == pWidget )
        return false;

    if ( false == pWidget->IsInstanced() )
        return false;
    if ( false == widgettree.IsVisibleByParent( pWidget ) )
        return false;
    if ( widgettree.IsFreezedByParent( pWidget ) )
        return false;
    if ( widgettree.IsIgnoredByParent( pWidget ) )
        return false;

    bool handled = false;

    if ( pWidget->IsMouseHover() )
    {
        handled = pWidget->OnMouseEvent( evt );
    }

    switch ( evt.fType )
    {
    case MAUIMouseEvent::kLBtnDown_EventType:
    case MAUIMouseEvent::kMBtnDown_EventType:
    case MAUIMouseEvent::kRBtnDown_EventType:
        if ( pWidget->IsFocusable() && handled )
        {
            // Change focus
            if ( GetFocusedTarget().expired() )
            {
                SetFocusTarget( pWidget->shared_from_this() );
            }
            else
            {
                if ( pWidget != GetFocusedTarget().lock().get() )
                    SetFocusTarget( pWidget->shared_from_this() );
            }
            //handled = true;
        }
        break;
    default:
        break;
    }

    return handled;
}

bool AUIWidgetManager::SendKeyboardEvent( const AUIKeyboardEvent& evt ) // Keyboard Event를 받으면 Instance를 찾아서 Widget으로 전달
{
    if ( GetFocusedTarget().expired() == false )
    {
        if ( auto pFocusWidget = GetFocusedTarget().lock().get() )
        {
            auto found = m_mapWidget2Instance.find( pFocusWidget );
            if ( found == m_mapWidget2Instance.end() )
            {
                return false;
            }

            return SendKeyboardEventToWidget( found->second.get(), evt );
        }
    }

    return false;
}

void AUIWidgetManager::SendTickTimeEvent( const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick )
{
    if ( false == m_wpTooltipTarget.expired() )
    {
        if ( m_wpTooltipTimerTarget.lock() != m_wpTooltipTarget.lock() )
        {
            // New timer target
            m_wpTooltipTimerTarget = m_wpTooltipTarget;
            m_TooltipTimerStart = curTick;
            this->HideTooltip();
        }
        else
        {
            // Show Tooltip
            auto pTargetWidget = m_wpTooltipTimerTarget.lock();
            AUIAssert( pTargetWidget );
            if ( pTargetWidget->IsShowTooltip() )
            {
                const auto pTooltip = pTargetWidget->GetTooltip();
                const auto dt = curTick - m_TooltipTimerStart;
                if ( dt >= pTooltip->GetShowDuration() )
                {
                    this->ShowTooltip( pTooltip );
                }
            }
        }
    }

    decltype(m_Instances) currentInstances;
    do
    {
        std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );
        currentInstances.reserve( m_Instances.size() );
        currentInstances.assign( m_Instances.begin(), m_Instances.end() );
    } while ( false );

    // Last drawn is topmost, thus event goes inverse order
    for (auto itrInst = currentInstances.rbegin() ; itrInst != currentInstances.rend() ; ++itrInst)
    {
        auto pInstance = (*itrInst).get();
        SendTickTimeToWidget( pInstance, prevTick, curTick );
    }
}

bool AUIWidgetManager::SendKeyboardEventToWidget( AUIInstance* const pInstance, const AUIKeyboardEvent& evt ) // 받은 Keyboard Event를 Widget에 전달
{
    if ( pInstance == nullptr )
    {
        AUIAssertFailReason("Invalid instance");
        return false;
    }

    auto pWidget = pInstance->GetWidget();

    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    if ( widgettree.IsVisibleByParent( pWidget ) == false )
        return false;
    if ( widgettree.IsFreezedByParent( pWidget ) )
        return false;
    if ( widgettree.IsIgnoredByParent( pWidget ) )
        return false;

    bool handled = false;
    handled = pWidget->OnKeyboardEvent( evt );

    return handled;
}

void AUIWidgetManager::SendTickTimeToWidget( AUIInstance* const pInstance, const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick )
{
    if ( pInstance == nullptr )
    {
        AUIAssertFailReason("Invalid instance");
        return;
    }

    auto pWidget = pInstance->GetWidget();
    if ( pWidget->IsVisible() == false )
        return;


    pWidget->OnTickTimeEvent( prevTick, curTick );
}

bool AUIWidgetManager::SendSetCursorEvent( AUICursorIcon& cursoricon ) // Event에 따른 Cursor 아이콘 Control
{
    bool handled = false;

    if ( IsGrabMouseEvent() )
    {
        std::list< std::weak_ptr< AUIWidget > > tmpList;
        GetWidgetSelection().GetCopy( tmpList );
        for ( auto itr : tmpList )
        {
            if ( auto pWidget = itr.lock() )
            {
                if ( pWidget->IsVisible() == false )
                    continue;
                handled = pWidget->OnSetCursorEvent( cursoricon );
                if ( handled )
                    break;
            }
        }
    }
    else
    {
        // Hit test order
        for ( auto& itrHit : m_HitTestBuffer )
        {
            if ( auto pInstance = itrHit.fInstance.lock().get() )
            {
                AUIAssert( pInstance->IsHit() );
                handled = SendSetCursorEventToWidget( pInstance, cursoricon );
                if ( handled )
                    break;
            }
        }
    }

    return handled;
}

bool AUIWidgetManager::SendSetCursorEventToWidget( AUIInstance* const pInstance, AUICursorIcon& cursoricon ) // 받은 Cursor Event Widget에 전달
{
    if ( pInstance == nullptr )
    {
        AUIAssertFailReason("Invalid instance");
        return false;
    }

    auto pWidget = pInstance->GetWidget();
    if ( pWidget->IsVisible() == false )
        return false;

    bool handled = false;

    if ( pWidget->IsMouseHover() )
        handled = pWidget->OnSetCursorEvent( cursoricon );

    return handled;
}

void AUIWidgetManager::InvalidateCamera()
{
    for (auto i = 0; i < AUICoordSpaceNum; i++)
    {
        if (auto pSensorManager = m_aSensorManager[i].get())
            pSensorManager->_invliadate_camera();
    }
}

void AUIWidgetManager::SetFocusTarget( const std::weak_ptr< AUIWidget >& pWidget ) // Parameter에 들어온 Widget을 Focus하도록 변경
{
    if ( auto pPrevFocusedWidget = m_pFocusWidget.lock() )
        pPrevFocusedWidget->FocusOut();

    m_pFocusWidget = pWidget;

    if ( auto pNextFocusedWidget = pWidget.lock() )
        pNextFocusedWidget->FocusIn();
}

void AUIWidgetManager::InvalidateSensor(AUIWidget* pWidget)
{
    auto rootcoord = pWidget->GetRootTargetCoord();
     if(auto pSensorManager = GetSensorManager(rootcoord))
            pSensorManager->_invalidate_sensor(pWidget->shared_from_this());
}
void AUIWidgetManager::InvalidateUIState(AUIWidget* pWidget)
{
	auto rootcoord = pWidget->GetRootTargetCoord();
	if (auto pSensorManager = GetSensorManager(rootcoord))
		pSensorManager->_invalidate_buffer();
}
bool AUIWidgetManager::UpdateAllInstance()
{
    m_bDirty = false;

    OnPreUpdateAllInstance();

    auto visualHasChanged = false;

    // Update data
    //std::vector< std::shared_ptr< MAUIInstance > > currentInstances;
    //do 
    //{
    //    std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );
    //    currentInstances.reserve( m_Instances.size() );
    //    currentInstances.assign( m_Instances.begin(), m_Instances.end() );
    //} while ( false );
    const auto& currentInstances = m_Instances;
    for ( const auto& itrInst : currentInstances )
    {
        auto pWidget = itrInst->GetWidget();

//         if ( pWidget->IsVisible() == false )
//             continue;
//         if ( pWidget->IsIgnored() == true )
//             continue;

        // Pre Update
        pWidget->OnPreUpdate();

        if ( pWidget->IsRoot() )
        {
            if ( pWidget->IsNeedUpdateSize() )
                AUIWidget::CallMeasureAndUpdateSize( pWidget );
        }
        if ( pWidget->IsNeedUpdateChildPosition() )
            AUIWidget::CallOnUpdateChildPosition(pWidget);
        if (pWidget->m_bDefault2DSensor)
            pWidget->UpdateDefault2DSensorSize();

        if ( pWidget->IsDirty() )
        {
            itrInst->SetDirty();
            pWidget->m_bWasDirty = true;
        }
        visualHasChanged |= pWidget->Update();

        // Post Update
        pWidget->OnPostUpdate();
    }

    // Update instance
    for ( const auto& itrInst : currentInstances )
    {
        UpdateInstance(itrInst);
    }

    OnPostUpdateAllInstance();

    return visualHasChanged;
}

bool AUIWidgetManager::IsInvoked( const std::shared_ptr< AUIWidget >& pWidget ) const
{
    if ( pWidget == nullptr )
        return false;
    if ( pWidget->IsCreated() == false )
        return false;
    const auto found = std::find( m_InvokedWidgets.begin(), m_InvokedWidgets.end(), pWidget );
    if ( found == m_InvokedWidgets.end() )
        return false;
    return true;
}

bool AUIWidgetManager::Invoke( const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt )
{
    if ( IsInvoked( pWidget ) )
    {
        AUIAssertFailReason("Widget already invoked!");
        return false;
    }

    const auto ret = OnInvoke( pWidget, pParent, pos, opt );
    if ( ret )
        m_InvokedWidgets.emplace_back( pWidget );

    return ret;
}

bool AUIWidgetManager::Dismiss( const std::shared_ptr< AUIWidget >& pWidget )
{
    const auto found = std::find( m_InvokedWidgets.begin(), m_InvokedWidgets.end(), pWidget );
    if ( found == m_InvokedWidgets.end() )
    {
        AUIAssertFailReason("Not invoked from here!");
        return false;
    }

    // To prevent multiple Dismiss() call
    m_InvokedWidgets.erase( found );

    const auto ret = OnDismiss( pWidget );

    return ret;
}

bool AUIWidgetManager::OnInvoke( const std::shared_ptr< AUIWidget >& pWidget, const std::shared_ptr< AUIWidget >& pParent, const AUIScalar3& pos, const AUIPopupPos& opt )
{
    AUIAssertFailReason("Popup not supported!");
    return false;
}

bool AUIWidgetManager::OnDismiss( const std::shared_ptr< AUIWidget >& pWidget )
{
    AUIAssertFailReason("Popup not supported!");
    return false;
}

void AUIWidgetManager::UpdateInstance( AUIWidget* const pWidget ) // param Widget으로 Instance를 찾아 Update
{
    auto found = m_mapWidget2Instance.find( pWidget );
    if ( found == m_mapWidget2Instance.end() )
    {
        AUIAssertFail();
        return;
    }
    auto pInstance = found->second;
    UpdateInstance(pInstance);
}

void AUIWidgetManager::UpdateInstance(const std::shared_ptr<AUIInstance>& pInstance)
{
    AUIAssert(pInstance);
    pInstance->UpdateInstance();
    auto pWidget = pInstance->GetWidget();
    AUIAssert(pWidget->m_LifeState.GetCurInstance().lock() == pInstance);
    AUIAssert(pWidget->m_LifeState.GetCurWidgetManager() == this);
}

std::shared_ptr< AUIInstance > AUIWidgetManager::OnRegisterWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    return std::unique_ptr< AUIInstance >( new AUIInstance( this, pWidget ) );
}

AUIInstance* const AUIWidgetManager::FindInstance( AUIWidget* const pWidget )
{
    auto found = m_mapWidget2Instance.find( pWidget );
    if ( found == m_mapWidget2Instance.end() )
    {
        AUIAssertFail();
        return nullptr;
    }

    return found->second.get();
}

const AUIInstance* const AUIWidgetManager::FindInstance( AUIWidget* const pWidget ) const
{
    auto found = m_mapWidget2Instance.find( pWidget );
    if ( found == m_mapWidget2Instance.end() )
    {
        AUIAssertFail();
        return nullptr;
    }

    return found->second.get();
}

void AUIWidgetManager::RefreshHitTestBuffer( int x, int y )
{


    //std::unordered_map< AUIWidget*, bool > mapVisualHit;
    //std::vector<std::pair<AUIWidget*, bool>> arrVisualHit;
    //arrVisualHit.reserve(m_Instances.size());
    //auto funcFindVisualHit = [&arrVisualHit](AUIWidget* _widget) -> std::optional<bool> {
    //    const auto found = std::find_if(std::begin(arrVisualHit), std::end(arrVisualHit), [_widget](const std::pair<AUIWidget*, bool>& _data) -> bool {
    //        return _data.first == _widget;
    //    });
    //    if (std::end(arrVisualHit) == found)
    //        return {};
    //    return { found->second };
    //};

    std::vector<std::weak_ptr<AUIInstance>> aHitInstance;
    decltype(m_Instances) currentInstances;
    do
    {
        std::lock_guard< std::recursive_mutex > guard(m_mtxInstances);
        currentInstances.reserve(m_Instances.size());
        currentInstances.assign(m_Instances.begin(), m_Instances.end());
    } while (false);
    for (auto itr : currentInstances)
    {
        if (auto pInstance = itr.get())
            pInstance->SetNotHit();
    }
    for (auto i = 0; i < AUICoordSpaceNum; i++)
    {
        if (auto pSensorManager = m_aSensorManager[i].get())
        {
            if(!pSensorManager->CheckSensors())
                continue;
            aHitInstance = pSensorManager->HitInstances();
            break;
        }
    }



    std::unordered_set<AUIWidget*> setVisualHitTrue;
    std::unordered_set<AUIWidget*> setVisualHitFalse;
    setVisualHitTrue.reserve(m_Instances.size());
    setVisualHitFalse.reserve(m_Instances.size());


    //decltype(m_Instances) arrValidInstances;
    //std::vector<bool> arrHit;
    //arrValidInstances.reserve(m_Instances.size());
    //arrHit.resize(m_Instances.size());
    //const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    //auto inst_size = m_Instances.size();
    //constexpr int OpenMPThreshold = 1;




    //for (auto i = 0; i < inst_size; i++)
    //{
    //    auto& pInstance = m_Instances[i];
    //    AUIAssert(pInstance);
    //    auto pWidget = pInstance->GetWidget();
    //    AUIAssert(pWidget);

    //    // Prune invisible objects
    //    if (widgettree.IsVisibleByParent(pWidget) == false)
    //        arrHit[i] = false;
    //    else
    //        arrHit[i] = true;
    //}

    //for (auto i=0; i< inst_size;i++)
    //{
    //    auto& pInstance = m_Instances[i];
    //    AUIAssert(pInstance);
    //    if (arrHit[i] == false)
    //        continue;
    //    pInstance->UpdateHitData(x, y);
    //    arrHit[i] = pInstance->IsHit();
    //}

    decltype(aHitInstance) arrValidInstances;
    arrValidInstances.reserve(aHitInstance.size());
    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    auto inst_size = aHitInstance.size();
    constexpr int OpenMPThreshold = 1;


    for (auto i = 0; i < inst_size ; i++)
    {
        auto pInstance = aHitInstance[i].lock();
        AUIAssert(pInstance);
        auto pWidget = pInstance->GetWidget();
        AUIAssert(pWidget);

        if (pInstance->IsHit() == false)
            continue;

        // Non-Drawable based widget
        const auto forceInsert = (nullptr == pWidget->GetAsDrawable());

        if (pWidget->IsRoot())
        {
            //mapVisualHit[pWidget] = true;
            //arrVisualHit.emplace_back(pWidget, true);
            setVisualHitTrue.emplace(pWidget);
            arrValidInstances.emplace_back(pInstance);
        }
        else
        {
            auto pParentWidget = pWidget->GetParent();
            if (pParentWidget && pParentWidget->IsHitTestAffectToChild())
            {
                AUIAssert(pParentWidget);

                const auto foundTrue = setVisualHitTrue.find(pParentWidget);
                const auto foundFalse = setVisualHitFalse.find(pParentWidget);
                if (setVisualHitTrue.end() != foundTrue)
                {
                    setVisualHitTrue.emplace(pWidget);
                    arrValidInstances.emplace_back(pInstance);
                }
                else if (setVisualHitFalse.end() != foundFalse)
                {
                    setVisualHitFalse.emplace(pWidget);
                    if (forceInsert)
                        arrValidInstances.emplace_back(pInstance);
                }
                else
                {
                    // WTF
                    AUIDebugPrint(L"[WARNING] Out of order child widget instance\n");
                    setVisualHitFalse.emplace(pWidget);
                    if (forceInsert)
                        arrValidInstances.emplace_back(pInstance);
                }

            }
            else
            {
                setVisualHitTrue.emplace(pWidget);
                arrValidInstances.emplace_back(pInstance);
            }
        }
    }

    // Clear
    m_HitTestBuffer.clear();
    m_HitTestBuffer.reserve(arrValidInstances.size());

    std::optional<float> firstDistance;
    bool isSortingRequired = false;

    // Last drawn is topmost, thus event goes inverse order
    for (auto itrInst = arrValidInstances.rbegin() ; itrInst != arrValidInstances.rend() ; ++itrInst)
    {
        auto pInstance = (*itrInst).lock();
        AUIAssert(pInstance);
        AUIAssert(pInstance->IsHit());

        m_HitTestBuffer.emplace_back(pInstance->GetHitDistance(), pInstance);

        if (!firstDistance)
            firstDistance = pInstance->GetHitDistance();
        if (false == isSortingRequired)
            isSortingRequired = std::abs(*firstDistance - pInstance->GetHitDistance()) > std::numeric_limits<float>::epsilon();

    }

    if (isSortingRequired)
    {
        std::sort(std::begin(m_HitTestBuffer), std::end(m_HitTestBuffer), [](const HitBufferData& _left, const HitBufferData& _right) -> bool {
            return std::less<>()(_left.fDistance, _right.fDistance);
        });
    }

}

void AUIWidgetManager::RegisterWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    if ( AUIApplication::Instance().IsTraceWidgetLifecycle() )
    {
        AUIDebugPrint( "AUIWidgetManager(%p)::RegisterWidget : %s %p | parent : %s %p\n", this, typeid(*pWidget).name(), pWidget.get(), pWidget->GetParent() ? typeid(*pWidget->GetParent()).name() : "N/A", pWidget->GetParent() );
    }

    AUIAssert( pWidget->m_LifeState.IsPendingCreate() );


    //////////////////////////////////////////////////////////////////////////
    // Bug fix code for
    //  - Tab Widget : Add -> Create -> Sync -> Destroy -> Clear -> Add -> Sync
    // Maybe better way?
    if ( auto pParentWidget = pWidget->GetParent() )
    {

        std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );
        if ( m_mapWidget2Instance.end() == m_mapWidget2Instance.find( pParentWidget ) )
        {
            pWidget->m_LifeState.ResetCurInstance();

            pWidget->m_LifeState.SetCurWidgetManager( this );

            pWidget->m_LifeState.SetPendingCreate( false );
            pWidget->m_LifeState.SetPendingCreateWidgetManager( nullptr );

            pWidget->m_LifeState.SetPendingDestroy( false );
            pWidget->m_LifeState.SetPendingDestroyWidgetManager( nullptr );

            pWidget->m_LifeState.SetCreated( false );
            return;
        }
    }
    //////////////////////////////////////////////////////////////////////////

    OnPreRegisterWidget();

    auto pInstance = OnRegisterWidget( pWidget );
    if ( nullptr == pInstance )
    {
        AUIAssertFailReason("Failed to register widget");
        return;
    }

    pInstance->CreateInstance();

    // Create widget
    pWidget->m_LifeState.SetCurWidgetManager( this );
    pWidget->m_LifeState.SetCurInstance( pInstance );
    pWidget->m_LifeState.SetPendingCreate( false );
    pWidget->m_LifeState.SetPendingCreateWidgetManager( nullptr );
    pWidget->Create();


    do
    {
        std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );

        auto insertPos = m_Instances.end();
        if ( auto pParentWidget = pWidget->GetParent() )
        {
            auto foundParentInstance = m_mapWidget2Instance.find( pParentWidget );
            if ( m_mapWidget2Instance.end() != foundParentInstance )
            {
                insertPos = std::find( m_Instances.begin(), m_Instances.end(), foundParentInstance->second );
                ++insertPos;
            }
            else
            {
                if ( AUIApplication::Instance().IsTraceWidgetLifecycle() )
                {
                    AUIDebugPrint( "AUIWidgetManager(%p)::RegisterWidget - Failed to find parent instance : %s %p\n", this, typeid(*pParentWidget).name(), pParentWidget );
                }
            }
        }

        m_Instances.insert( insertPos, pInstance );
        m_mapWidget2Instance[pWidget.get()] = pInstance;
    } while ( false );      // For mutex guard
    AUIAssert( m_Instances.size() == m_mapWidget2Instance.size() );



    //////////////////////////////////////////////////////////////
    // Add To SensorManager
    //////////////////////////////////////////////////////////////
    auto rootc_info =  pWidget->GetRootCoordInfo();
    auto rootc_type = (size_t)rootc_info->GetTargetCoord();
    if (auto pSensorManager = m_aSensorManager[rootc_type].get())
        pSensorManager->_invalidate_buffer();



    OnPostRegisterWidget();

    pWidget->UpdateSize();
    pWidget->UpdateChildPosition();
    pWidget->Invalidate();
    pWidget->m_LifeState.SetCreated( true );
    pWidget->SetCreated( true );

    SetDirty();
}

void AUIWidgetManager::UnregisterWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }


    if ( AUIApplication::Instance().IsTraceWidgetLifecycle() )
    {
        AUIDebugPrint( "AUIWidgetManager(%p)::UnregisterWidget : %s %p | parent : %s %p\n", this, typeid(*pWidget).name(), pWidget.get(), pWidget->GetParent() ? typeid(*pWidget->GetParent()).name() : "N/A", pWidget->GetParent() );
    }

    AUIAssert( pWidget->m_LifeState.IsPendingDestory() );

    std::shared_ptr< AUIInstance > pInstance;
    do
    {
        std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );

        auto foundInstance = m_mapWidget2Instance.find( pWidget.get() );
        if ( foundInstance == m_mapWidget2Instance.end() )
        {
            break;
        }
        pInstance = foundInstance->second;

        m_mapWidget2Instance.erase( foundInstance );
    } while ( false );      // For mutex guard

    OnPreUnregisterWidget();

    //////////////////////////////////////////////////////////////
    // Remove From SensorManager
    //////////////////////////////////////////////////////////////
    auto rootc_info = pWidget->GetRootCoordInfo();
    auto rootc_type = (size_t)rootc_info->GetTargetCoord();
    if (auto pSensorManager = m_aSensorManager[rootc_type].get())
        m_aSensorManager[rootc_type]->_invalidate_buffer();

    pWidget->Destroy();
    pWidget->m_LifeState.SetCurWidgetManager( nullptr );

    do
    {
        std::lock_guard< std::recursive_mutex > guard( m_mtxInstances );
        auto itrInstance = std::find( m_Instances.begin(), m_Instances.end(), pInstance );
        if ( itrInstance == m_Instances.end() )
        {
            break;
        }

        pInstance->DestroyInstance();

        m_Instances.erase( itrInstance );
    } while ( false );      // For mutex guard

    AUIAssert( m_Instances.size() == m_mapWidget2Instance.size() );

    pWidget->m_LifeState.ResetCurInstance();
    pWidget->m_LifeState.SetPendingDestroy( false );
    pWidget->m_LifeState.SetPendingDestroyWidgetManager( nullptr );
    pWidget->m_LifeState.SetCreated( false );
    pWidget->SetCreated( false );

    OnPostUnregisterWidget();

    SetDirty();
}

void AUIWidgetManager::ShowTooltip( const std::shared_ptr< AUITooltip >& pTooltip )
{
    m_pTooltip = pTooltip;
    m_bShowTooltip = true;
    AUIApplication::Instance().PostLazyUpdate();
}

void AUIWidgetManager::HideTooltip()
{
    m_bShowTooltip = false;
    AUIApplication::Instance().PostLazyUpdate();
}

void AUIWidgetManager::OnShowTooltip( const std::shared_ptr< AUITooltip >& pTooltip, int x, int y )
{

}

void AUIWidgetManager::OnHideTooltip()
{

}

void AUIWidgetManager::LazyUpdateTooltip()
{
    if ( m_bShowTooltip )
    {
        if ( false == m_bHasTooltipInst )
        {
            this->OnShowTooltip( m_pTooltip, m_MousePosX + m_TooltipOffsetX, m_MousePosY + m_TooltipOffsetY );
            m_bHasTooltipInst = true;
        }
    }
    else
    {
        if ( m_bHasTooltipInst )
        {
            this->OnHideTooltip();
            m_bHasTooltipInst = false;
        }
    }
}

void AUIWidgetManager::SetGrabMouseEvent( bool state )
{
    m_bGrabMouseEvent = state;

    if ( auto pHandle = GetHandle() )
    {
        if ( m_bGrabMouseEvent )
            pHandle->CaptureMouseEvent();
        else
            pHandle->ReleaseMouseEvent();
    }
}

void AUIWidgetManager::GetInstances(std::vector<std::shared_ptr<AUIInstance>>& arrInstances) const
{
    arrInstances.clear();
    std::lock_guard<std::recursive_mutex> _guard(m_mtxInstances);
    arrInstances.reserve(m_Instances.size());
    arrInstances.assign(m_Instances.begin(), m_Instances.end());
}
