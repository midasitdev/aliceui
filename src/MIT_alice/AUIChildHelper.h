#pragma once


#include "AUIAPIDef.h"
#include <memory>

class AUIWidget;
class ALICEUI_API AUIChildHelper
{
public:
    AUIChildHelper();
    ~AUIChildHelper();

    //////////////////////////////////////////////////////////////////////////
    // Callback interface
public:
    class Callback
    {
    public:
        virtual void OnShowWidget(const std::shared_ptr< AUIWidget >& pChild) = 0;
        virtual void OnHideWidget(const std::shared_ptr< AUIWidget >& pChild) = 0;
        virtual void OnAddWidget(const std::shared_ptr< AUIWidget >& pChild, const size_t index) = 0;
        virtual void OnDelWidgetAt(const size_t index) = 0;
        virtual void OnDelAllWidgets() = 0;
        virtual void OnAttachToParent(const std::shared_ptr< AUIWidget >& pWidget, const size_t index) = 0;
        virtual void OnDetachFromParent(const size_t index) = 0;
        virtual size_t GetChildCount() const = 0;
        virtual std::shared_ptr< AUIWidget > OnGetChildAt(const size_t index) const = 0;
    };
private:
    Callback* m_pCallback;


    //////////////////////////////////////////////////////////////////////////
    // Internal
private:
    std::vector< std::shared_ptr< AUIWidget > > m_HiddenWidgets;
};
