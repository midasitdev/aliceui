#pragma once

#include "AUIRecyclerCommonDef.h"
#include "AUISignal.h"


class AUIWidget;

class ALICEUI_API AUIRecyclerAdapter : public std::enable_shared_from_this< AUIRecyclerAdapter >
{
public:
    AUIRecyclerAdapter();
    virtual ~AUIRecyclerAdapter();



    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_assert(std::is_base_of<AUIRecyclerAdapter, _Derived>::value, "Must be derived from AUIRecyclerAdapter");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIRecyclerAdapter*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIRecyclerAdapter*>(this));
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
    // Interface
protected:
    virtual size_t OnGetItemCount() const = 0;
    virtual void OnBindWidgetHolder(const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder, const size_t pos) = 0;
    virtual std::shared_ptr< AUIRecyclerWidgetHolder > OnCreateWidgetHolder(AUIWidget* pParent, const size_t widgetType) = 0;

    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    virtual size_t GetItemWidgetType(const size_t pos) const;
    size_t GetItemCount() const;
    void BindWidgetHolder(const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder, const size_t pos);
    std::shared_ptr< AUIRecyclerWidgetHolder > CreateWidgetHolder(AUIWidget* pParent, const size_t widgetType);

    //////////////////////////////////////////////////////////////////////////
    // Management
public:
    void AttachedToRecycler(const std::shared_ptr< AUIRecyclerWidget >& pRecycler, const size_t pos);
    void DetachedFromRecycler(const std::shared_ptr< AUIRecyclerWidget >& pRecycler);
    void FailedToRecycler(const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder);
    void WidgetRecycled(const std::shared_ptr< AUIRecyclerWidgetHolder >& pHolder);



    //////////////////////////////////////////////////////////////////////////
    // Notification
public:
    void NotifyDataChanged() {
        signalDataChanged.Send();
    }
    void NotifyItemChanged(const size_t pos) {
        signalItemChanged.Send(pos);
    }
    void NotifyItemInserted(const size_t pos) {
        signalItemInserted.Send(pos);
    }
    void NotifyItemMoved(const size_t fromPos, const size_t toPos) {
        signalItemMoved.Send(fromPos, toPos);
    }
    void NotifyItemRemoved(const size_t pos) {
        signalItemRemoved.Send(pos);
    }
    void NotifyItemRangeChanged(const size_t startPos, const size_t itemCount) {
        signalRangeChanged.Send(startPos, itemCount);
    }
    void NotifyItemRangeInserted(const size_t startPos, const size_t itemCount) {
        signalRangeInserted.Send(startPos, itemCount);
    }
    void NotifyItemRangeRemoved(const size_t startPos, const size_t itemCount) {
        signalRangeRemoved.Send(startPos, itemCount);
    }
    AUISignal<void(void)> signalDataChanged;
    AUISignal<void(size_t)> signalItemChanged;
    AUISignal<void(size_t)> signalItemInserted;
    AUISignal<void(size_t, size_t)> signalItemMoved;
    AUISignal<void(size_t)> signalItemRemoved;
    AUISignal<void(size_t, size_t)> signalRangeChanged;
    AUISignal<void(size_t, size_t)> signalRangeInserted;
    AUISignal<void(size_t, size_t)> signalRangeRemoved;
};
