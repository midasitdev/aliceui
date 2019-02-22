#include "pch.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"
#include "AUIWidgetRootInfo.h"
#include "AUIDebug.h"

AUIWidget* AUIWidgetTreeHelper::FindByRuntimeID( const AUIRuntimeID id ) const
{
    const auto foundWidget = m_mapRuntimeID2Widget.find(id);
    if (std::end(m_mapRuntimeID2Widget) == foundWidget)
        return nullptr;

    auto pWidget = foundWidget->second;
    if (nullptr == pWidget)
    {
        AUIAssertFailReason("Can't be null");
        return nullptr;
    }
    std::lock_guard< std::recursive_mutex > guard( m_mutexWidget );
    const auto found = m_mapWidgetRelation.find( pWidget );
    if (m_mapWidgetRelation.end() == found)
    {
        return nullptr;
    }
    return found->first;
}

const std::vector< std::shared_ptr< AUIWidget > > AUIWidgetTreeHelper::GetChildren( AUIWidget* pParent ) const
{
    if ( pParent == nullptr )
    {
        AUIAssertFailReason("Invalid parent widget");
        return std::vector< std::shared_ptr< AUIWidget > >();
    }
    AUIAssert( m_mapWidgetRelation.find( pParent ) != m_mapWidgetRelation.end() );

    const auto& parentInfo = m_mapWidgetRelation.find( pParent )->second;

    // Create copy
    std::vector< std::shared_ptr< AUIWidget > > arrChildren;
    arrChildren = parentInfo.fChildren;

    return arrChildren;
}

const std::vector<std::shared_ptr<AUIWidget>>& AUIWidgetTreeHelper::RefChildren(AUIWidget* pParent) const
{
    if (pParent == nullptr)
    {
        AUIAssertFailReason("Invalid parent widget");
        static std::vector<std::shared_ptr<AUIWidget>> sEmptyChildren;
        return sEmptyChildren;
    }
    AUIAssert(m_mapWidgetRelation.find(pParent) != m_mapWidgetRelation.end());
    const auto found = m_mapWidgetRelation.find(pParent);
    return found->second.fChildren;
}

size_t AUIWidgetTreeHelper::GetChildCount( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid parent widget");
        return 0;
    }
    AUIAssert( m_mapWidgetRelation.find( pWidget ) != m_mapWidgetRelation.end() );
    return m_mapWidgetRelation.find( pWidget )->second.fChildren.size();
}

void AUIWidgetTreeHelper::RegisterWidget( AUIWidget* pWidget )
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    std::lock_guard< std::recursive_mutex > guard( m_mutexWidget );
    m_mapWidgetRelation.emplace( pWidget, RelationData() );
    m_mapRuntimeID2Widget.emplace(pWidget->GetRuntimeID(), pWidget);
}

void AUIWidgetTreeHelper::UnregisterWidget( AUIWidget* pWidget )
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    std::lock_guard< std::recursive_mutex > guard( m_mutexWidget );
    m_mapRuntimeID2Widget.erase(pWidget->GetRuntimeID());
    m_mapWidgetRelation.erase( pWidget );
}

bool AUIWidgetTreeHelper::AddChild( AUIWidget* pParent, AUIWidget* pChild )
{
    if ( pParent == nullptr || pChild == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return false;
    }
    AUIAssert( m_mapWidgetRelation.find( pParent ) != m_mapWidgetRelation.end() );
    AUIAssert( m_mapWidgetRelation.find( pChild ) != m_mapWidgetRelation.end() );

    if (pChild->OnSetParent(pParent) == false)
    {
        AUIDebugPrint(L"[ERROR] Can't setup parent\n");
        return false;
    }

	if ( pChild->GetParent() )
	{
        AUIAssertFailReason("Already has parent");
		return false;
	}

    auto& parentInfo = m_mapWidgetRelation.find( pParent )->second;
    do 
    {
        std::lock_guard< std::mutex > guard( parentInfo.fChildrenMutex );
        const auto found = std::find( parentInfo.fChildren.begin(), parentInfo.fChildren.end(), pChild->shared_from_this() );
        if ( parentInfo.fChildren.end() != found )
        {
            AUIDebugPrint(L"[ERROR] Can't add child widget\n");
            return false;
        }
        parentInfo.fChildren.emplace_back( pChild->shared_from_this() );
    } while ( false );


    pChild->m_spRootInfo = pParent->m_spRootInfo;

    auto& childInfo = m_mapWidgetRelation.find( pChild )->second;
    childInfo.fParentWidget = pParent;


    if ( pParent->IsInstanced() )
    {
        pParent->GetWidgetManager()->CreateInstance( pChild->shared_from_this() );
    }
    else if ( pParent->IsPendingCreate() )
    {
        auto pCreateWM = pParent->m_LifeState.GetPendingCreateWidgetManager();
        if ( pCreateWM )
        {
            pCreateWM->CreateInstance( pChild->shared_from_this() );
        }
    }



    return true;
}

bool AUIWidgetTreeHelper::AddChildAt( AUIWidget* pParent, size_t pos, AUIWidget* pChild )
{
    if ( kAUIChildPosEnd == pos )
        return AddChild( pParent, pChild );

    if ( pParent == nullptr || pChild == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return false;
    }
    AUIAssert( m_mapWidgetRelation.find( pParent ) != m_mapWidgetRelation.end() );
    AUIAssert( m_mapWidgetRelation.find( pChild ) != m_mapWidgetRelation.end() );

    if ( pChild->OnSetParent( pParent ) == false )
    {
        AUIDebugPrint(L"[ERROR] Can't setup parent\n");
        return false;
    }

    if ( pChild->GetParent() )
    {
        AUIAssertFailReason("Already has parent");
        return false;
    }

    auto& parentInfo = m_mapWidgetRelation.find( pParent )->second;
    do 
    {
        std::lock_guard< std::mutex > guard( parentInfo.fChildrenMutex );
        if ( parentInfo.fChildren.size() < pos )
        {
            AUIDebugPrint(L"[ERROR] Can't find parent info\n");
            return false;
        }
        else
        {
            // Check has child
            const auto found = std::find(parentInfo.fChildren.begin(), parentInfo.fChildren.end(), pChild->shared_from_this());
            if (parentInfo.fChildren.end() != found)
            {
                AUIDebugPrint(L"[ERROR] Can't find parent info\n");
                return false;
            }
            // Insert
            parentInfo.fChildren.emplace(parentInfo.fChildren.begin() + pos, pChild->shared_from_this());
        }
    } while ( false );


    pChild->m_spRootInfo = pParent->m_spRootInfo;

    auto& childInfo = m_mapWidgetRelation.find( pChild )->second;
    childInfo.fParentWidget = pParent;


    if ( pParent->IsInstanced() )
    {
        pParent->GetWidgetManager()->CreateInstance( pChild->shared_from_this() );
    }
    else if ( pParent->IsPendingCreate() )
    {
        auto pCreateWM = pParent->m_LifeState.GetPendingCreateWidgetManager();
        if ( pCreateWM )
        {
            pCreateWM->CreateInstance( pChild->shared_from_this() );
        }
    }



    return true;
}

bool AUIWidgetTreeHelper::DelChild( AUIWidget* pParent, AUIWidget* pChild )
{
    if ( pParent == nullptr || pChild == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return false;
    }
    AUIAssert( m_mapWidgetRelation.find( pParent ) != m_mapWidgetRelation.end() );
    AUIAssert( m_mapWidgetRelation.find( pChild ) != m_mapWidgetRelation.end() );


    auto& parentInfo = m_mapWidgetRelation.find( pParent )->second;
    do 
    {
        std::lock_guard< std::mutex > guard( parentInfo.fChildrenMutex );
        const auto found = std::find( parentInfo.fChildren.begin(), parentInfo.fChildren.end(), pChild->shared_from_this() );
        if (found == parentInfo.fChildren.end())
        {
            AUIDebugPrint(L"[ERROR] Can't find parent info\n");
            return false;
        }
        parentInfo.fChildren.erase( found );
    } while ( false );


    do
    {
        std::lock_guard< std::recursive_mutex > widgetGuard( m_mutexWidget );
        auto& childInfo = m_mapWidgetRelation.find( pChild )->second;
        if ( childInfo.fParentWidget != pParent )
        {
            AUIDebugPrint(L"[ERROR] Can't find parent info\n");
            return false;
        }
        pChild->m_spRootInfo = std::make_shared<AUIWidgetRootInfo>();
        childInfo.fParentWidget = nullptr;
    } while ( false );


    if ( pParent->IsInstanced() )
    {
        pParent->GetWidgetManager()->DestroyInstance( pChild->shared_from_this() );
    }
    else if ( pParent->IsPendingDestroy() )
    {
        auto pDestroyWM = pParent->m_LifeState.GetPendingDestroyWidgetManager();
        if ( pDestroyWM )
        {
            pDestroyWM->DestroyInstance( pChild->shared_from_this() );
        }
    }

    return true;
}

bool AUIWidgetTreeHelper::ClearChild( AUIWidget* pParent )
{
    if ( pParent == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return false;
    }
    const auto found = m_mapWidgetRelation.find( pParent );
    if ( found == m_mapWidgetRelation.end() )
    {
        // Empty
        return true;
    }
    auto& parentInfo = found->second;
    std::vector< std::shared_ptr< AUIWidget > > children;
    do 
    {
        std::lock_guard< std::mutex > guard( parentInfo.fChildrenMutex );
        children = std::move( parentInfo.fChildren );
        AUIAssert(0 == parentInfo.fChildren.size());
    } while ( false );

    for ( auto& child : children )
    {
        auto pChild = child.get();
        if (pChild == nullptr)
        {
            AUIDebugPrint(L"[ERROR] Invalid child\n");
            continue;
        }
        std::lock_guard< std::recursive_mutex > widgetGuard( m_mutexWidget );
        auto& childInfo = m_mapWidgetRelation.find( pChild )->second;
        if ( childInfo.fParentWidget != pParent )
        {
            AUIDebugPrint(L"[ERROR] Can't find parent info\n");
            continue;
        }

        pChild->m_spRootInfo = std::make_shared< AUIWidgetRootInfo >();
        childInfo.fParentWidget = nullptr;

        if ( pParent->IsInstanced() )
        {
            pParent->GetWidgetManager()->DestroyInstance( pChild->shared_from_this() );
        }
    }


    return true;
}

bool AUIWidgetTreeHelper::ClearChildRecursive( AUIWidget* pWidget )
{
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widgets");
        return false;
    }

    const auto children = this->GetChildren( pWidget );
    for ( auto& child : children )
    {
        ClearChildRecursive( child.get() );
    }
    return this->ClearChild( pWidget );
}

bool AUIWidgetTreeHelper::IsChild(AUIWidget* pParent, AUIWidget* pChild) const
{
    return pParent == this->GetParent(pChild);
}

AUIWidget* AUIWidgetTreeHelper::GetParent( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return nullptr;
    }
    AUIAssert( m_mapWidgetRelation.find( pWidget ) != m_mapWidgetRelation.end() );

    const auto& widgetInfo = m_mapWidgetRelation.find( pWidget )->second;
    return const_cast< AUIWidget* >( widgetInfo.fParentWidget );
}

AUIWidget* AUIWidgetTreeHelper::GetRoot( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widgets");
        return nullptr;
    }
    auto pTmpWidget = pWidget;
    while ( pTmpWidget->GetParent() != nullptr )
    {
        pTmpWidget = pTmpWidget->GetParent();
    }
    return pTmpWidget;
}

bool AUIWidgetTreeHelper::IsVisibleByParent( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return false;
    }
    if ( pWidget->IsVisible() == false )
        return false;

    const auto found = m_CacheVisibleByParent.find(pWidget);
    if (m_CacheVisibleByParent.end() != found)
        return found->second;

    auto pTmpWidget = pWidget;
    while ( pTmpWidget->GetParent() != nullptr )
    {
        pTmpWidget = pTmpWidget->GetParent();
        if (pTmpWidget->IsVisible() == false)
        {
            m_CacheVisibleByParent.emplace(pWidget, false);
            return false;
        }
    }
    m_CacheVisibleByParent.emplace(pWidget, true);
    return true;
}

bool AUIWidgetTreeHelper::IsFreezedByParent( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return false;
    }
    if ( pWidget->IsFreezed() )
        return true;

    const auto found = m_CacheFreezedByParent.find(pWidget);
    if (m_CacheFreezedByParent.end() != found)
        return found->second;

    auto pTmpWidget = pWidget;
    while ( pTmpWidget->GetParent() != nullptr )
    {
        pTmpWidget = pTmpWidget->GetParent();
        if (pTmpWidget->IsFreezed())
        {
            m_CacheFreezedByParent.emplace(pWidget, true);
            return true;
        }
    }
    m_CacheFreezedByParent.emplace(pWidget, false);
    return false;
}

bool AUIWidgetTreeHelper::IsIgnoredByParent( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return false;
    }
    if ( pWidget->IsIgnored() )
        return true;

    const auto found = m_CacheIgnoredByParent.find(pWidget);
    if (m_CacheIgnoredByParent.end() != found)
        return found->second;

    auto pTmpWidget = pWidget;
    while ( pTmpWidget->GetParent() != nullptr )
    {
        pTmpWidget = pTmpWidget->GetParent();
        if (pTmpWidget->IsIgnored())
        {
            m_CacheIgnoredByParent.emplace(pWidget, true);
            return true;
        }
    }
    m_CacheIgnoredByParent.emplace(pWidget, false);
    return false;
}

bool AUIWidgetTreeHelper::IsDisabledByParent( AUIWidget* pWidget ) const
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return false;
    }
    if ( pWidget->IsDisabled() )
        return true;

    const auto found = m_CacheDisabledByParent.find(pWidget);
    if (m_CacheDisabledByParent.end() != found)
        return found->second;

    auto pTmpWidget = pWidget;
    while ( pTmpWidget->GetParent() != nullptr )
    {
        pTmpWidget = pTmpWidget->GetParent();
        if (pTmpWidget->IsDisabled())
        {
            m_CacheDisabledByParent.emplace(pWidget, true);
            return true;
        }
    }
    m_CacheDisabledByParent.emplace(pWidget, false);
    return false;
}

void AUIWidgetTreeHelper::NotifyUIStateChange(AUIWidget* pWidget)
{
    ClearStateCache();
}

void AUIWidgetTreeHelper::ClearStateCache()
{
    m_CacheVisibleByParent.clear();
    m_CacheFreezedByParent.clear();
    m_CacheIgnoredByParent.clear();
    m_CacheDisabledByParent.clear();
}
