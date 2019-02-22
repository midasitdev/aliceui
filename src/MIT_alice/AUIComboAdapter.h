#pragma once


#include "AUIAPIDef.h"
#include <any>
#include <memory>
#include "AUISignal.h"


class AUIWidget;
class ALICEUI_API AUIComboAdapter
{
public:
    AUIComboAdapter() = default;
    ~AUIComboAdapter() = default;


    //////////////////////////////////////////////////////////////////////////
    // Default adapter interface
public:
    virtual bool IsAllItemsEnabled() const { return true; }
    virtual bool IsEnabled(const size_t pos) { return true; }
    virtual size_t GetCount() const { return 0; }
    virtual std::any GetItem(const size_t pos) const { return {}; }
    template< typename T > const T GetItemCast(const size_t pos) const { return std::any_cast<T>(GetItem(pos)); }
    virtual std::shared_ptr< AUIWidget > GetWidget(const size_t pos, const std::shared_ptr< AUIWidget >& pOldWidget, const std::shared_ptr< AUIWidget >& pParentWidget) = 0;
    virtual std::shared_ptr< AUIWidget > GetComboItemWidget(const size_t pos, const std::shared_ptr< AUIWidget >& pOldWidget, const std::shared_ptr< AUIWidget >& pParentWidget) { return GetWidget(pos, pOldWidget, pParentWidget); }


    //////////////////////////////////////////////////////////////////////////
    // Basic methods
public:
    bool IsEmpty() const { return GetCount() == 0; }
    bool IsValidPos(const size_t pos) const { return pos < GetCount(); }


    //////////////////////////////////////////////////////////////////////////
    // Signals
public:
    AUISignal<void(AUIComboAdapter*)> DataChangedSignal;
    AUISignal<void(AUIComboAdapter*, size_t)> ClickItemSignal;

};
