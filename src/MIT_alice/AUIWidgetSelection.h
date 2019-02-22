#pragma once

#include "AUICommonDef.h"

class AUIWidget;

class ALICEUI_API AUIWidgetSelection final
{
public:
    using widget_ref_type = std::weak_ptr<AUIWidget>;
    using list_type = std::list<widget_ref_type>;
    using const_iterator = list_type::const_iterator;

    AUIWidgetSelection() = default;
    ~AUIWidgetSelection() = default;


    //////////////////////////////////////////////////////////////////////////
    // Selection state
public:
    bool IsEmpty() const { return m_listSelWidgets.empty(); }
    void PushBack(const widget_ref_type pWidget) { m_listSelWidgets.push_back(pWidget); }
    void PushFront(const widget_ref_type pWidget) { m_listSelWidgets.push_front(pWidget); }
    void PopBack() { m_listSelWidgets.pop_back(); }
    void PopFront() { m_listSelWidgets.pop_front(); }
    void Clear() { m_listSelWidgets.clear(); }
    const_iterator Begin() { return m_listSelWidgets.cbegin(); }
    const_iterator End() { return m_listSelWidgets.cend(); }
    void Insert(const_iterator pos, const widget_ref_type pWidget);
    void Remove(const widget_ref_type pWidget);
    void Erase(const_iterator pos) { m_listSelWidgets.erase(pos); }
    bool Exist(const widget_ref_type pWidget);
    void GetCopy(list_type& lst) const;
private:
    list_type m_listSelWidgets;
};
