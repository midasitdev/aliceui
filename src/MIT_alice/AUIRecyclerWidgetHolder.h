#pragma once

#include "AUIRecyclerCommonDef.h"

class AUIWidget;
class ALICEUI_API AUIRecyclerWidgetHolder : public std::enable_shared_from_this< AUIRecyclerWidgetHolder >
{
public:
    AUIRecyclerWidgetHolder(const std::shared_ptr< AUIWidget >& pItemWidget);
    virtual ~AUIRecyclerWidgetHolder();


    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_AUIAssert(std::is_base_of<AUIRecyclerWidgetHolder, _Derived>::value, "Must be derived from AUIRecyclerWidgetHolder");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIRecyclerWidgetHolder*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIRecyclerWidgetHolder*>(this));
    }
    template<typename _Derived>
    std::shared_ptr<_Derived> CastShared() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return std::static_pointer_cast<_Derived>(shared_from_this());
    }
    template<typename _Derived>
    std::shared_ptr<_Derived> DynCastShared() const {
        return std::dynamic_pointer_cast<_Derived>(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    // Methods
public:
    std::shared_ptr< AUIWidget > GetItemWidget() const {
        return m_pItemWidget;
    }
    size_t GetAdapterPosition() const {
        return m_AdapterPosition;
    }
    size_t GetItemId() const {
        return m_ItemId;
    }
    void SetItemWidgetType(const size_t& type) {
        m_ItemWidgetType = type;
    }
    size_t GetItemWidgetType() const {
        return m_ItemWidgetType;
    }
    size_t GetLayoutPosition() const {
        return m_LayoutPosition;
    }
    size_t GetOldPosition() const {
        return m_OldPosition;
    }
    bool IsRecyclable() const {
        return m_bRecyclable;
    }
    void SetRecyclable(bool val) {
        m_bRecyclable = val;
    }

    //////////////////////////////////////////////////////////////////////////
    // Widget
private:
    std::shared_ptr< AUIWidget > m_pItemWidget;
    bool m_bRecyclable;
    size_t m_AdapterPosition;
    size_t m_ItemId;
    size_t m_ItemWidgetType;
    size_t m_LayoutPosition;
    size_t m_OldPosition;
};
