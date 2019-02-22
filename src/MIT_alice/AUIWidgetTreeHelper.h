#pragma once

#include "AUICommonDef.h"


class AUIWidget;

class ALICEUI_API AUIWidgetTreeHelper final
{
    friend class AUIWidget;
    friend class AUIApplication;
public:
    AUIWidgetTreeHelper() = default;
    ~AUIWidgetTreeHelper() = default;


    //////////////////////////////////////////////////////////////////////////
    // Find
public:
    AUIWidget* FindByRuntimeID(const AUIRuntimeID id) const;


    //////////////////////////////////////////////////////////////////////////
    // Child
public:
    AUIWidget* GetParent(AUIWidget* pWidget) const;
    AUIWidget* GetRoot(AUIWidget* pWidget) const;
    size_t GetChildCount(AUIWidget* pWidget) const;
    const std::vector<std::shared_ptr<AUIWidget>> GetChildren(AUIWidget* pParent) const;
    const std::vector<std::shared_ptr<AUIWidget>>& RefChildren(AUIWidget* pParent) const;
    bool IsVisibleByParent(AUIWidget* pWidget) const;
    bool IsVisibleByParent(const std::shared_ptr< AUIWidget >& pWidget) const { return IsVisibleByParent(pWidget.get()); }
    bool IsFreezedByParent(AUIWidget* pWidget) const;
    bool IsFreezedByParent(const std::shared_ptr< AUIWidget >& pWidget) const { return IsFreezedByParent(pWidget.get()); }
    bool IsIgnoredByParent(AUIWidget* pWidget) const;
    bool IsIgnoredByParent(const std::shared_ptr< AUIWidget >& pWidget) const { return IsIgnoredByParent(pWidget.get()); }
    bool IsDisabledByParent(AUIWidget* pWidget) const;
    bool IsDisabledByParent(const std::shared_ptr< AUIWidget >& pWidget) const { return IsDisabledByParent(pWidget.get()); }
    void NotifyUIStateChange(AUIWidget* pWidget);
    bool IsChild(AUIWidget* pParent, AUIWidget* pChild) const;
private:
    bool AddChild(AUIWidget* pParent, AUIWidget* pChild);
    bool AddChildAt(AUIWidget* pParent, size_t pos, AUIWidget* pChild);
    bool DelChild(AUIWidget* pParent, AUIWidget* pChild);
    bool ClearChild(AUIWidget* pParent);
    bool ClearChildRecursive(AUIWidget* pWidget);
    friend class AUIInnerGroupWidget;
    void ClearStateCache();
    mutable std::unordered_map<AUIWidget*, bool> m_CacheVisibleByParent;
    mutable std::unordered_map<AUIWidget*, bool> m_CacheFreezedByParent;
    mutable std::unordered_map<AUIWidget*, bool> m_CacheIgnoredByParent;
    mutable std::unordered_map<AUIWidget*, bool> m_CacheDisabledByParent;

    //////////////////////////////////////////////////////////////////////////
    // Relation Data
private:
    void RegisterWidget(AUIWidget* pWidget);
    void UnregisterWidget(AUIWidget* pWidget);
private:
    struct RelationData
    {
        const AUIWidget* fParentWidget = nullptr;
        std::mutex fChildrenMutex;
        std::vector< std::shared_ptr< AUIWidget > > fChildren;

        RelationData() noexcept = default;

        RelationData(RelationData&& org) noexcept = default;
        RelationData& operator=(RelationData&&) noexcept = default;

        RelationData(const RelationData& other) {
            *this = other;
        }
        RelationData& operator=(const RelationData& other) {
            fParentWidget = other.fParentWidget;
            fChildren = other.fChildren;
            return *this;
        }
    };
    mutable std::recursive_mutex m_mutexWidget;
    std::unordered_map< AUIWidget*, RelationData > m_mapWidgetRelation;
    std::unordered_map<AUIRuntimeID, AUIWidget*> m_mapRuntimeID2Widget;
};
