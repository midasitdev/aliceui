#pragma once

#include "AUIRecyclerCommonDef.h"

class AUIWidget;
class AUIRecyclerWidget;

class ALICEUI_API AUIRecyclerLayoutManager
{
public:
    AUIRecyclerLayoutManager();
    virtual ~AUIRecyclerLayoutManager();

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) = 0;
    virtual void OnUpdateChildPosition() = 0;


    //////////////////////////////////////////////////////////////////////////
    // Setup
public:
    void SetRecyclerWidget(AUIRecyclerWidget* pRecyclerWidget) {
        m_pRecyclerWidget = pRecyclerWidget;
    }

    AUIRecyclerWidget* GetRecyclerWidget() const { AUIAssert(m_pRecyclerWidget); return m_pRecyclerWidget; }
private:
    AUIRecyclerWidget* m_pRecyclerWidget;



    //////////////////////////////////////////////////////////////////////////
    // Sub Widgets
public:
    void AddWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void AddWidget(const std::shared_ptr< AUIWidget >& pWidget, const size_t index);
    void DelWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void AttachWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void AttachWidget(const std::shared_ptr< AUIWidget >& pWidget, const size_t index);
    void DetachWidget(const std::shared_ptr< AUIWidget >& pWidget);
    void ClearWidget();
protected:
    virtual void OnAddWidget(const std::shared_ptr< AUIWidget >& pWidget, const size_t index);
    virtual void OnDelWidget(const std::shared_ptr< AUIWidget >& pWidget);
    virtual void OnAttachWidget(const std::shared_ptr< AUIWidget >& pWidget, const size_t index);
    virtual void OnDetachWidget(const std::shared_ptr< AUIWidget >& pWidget);
    virtual void OnClearWidget();

    //////////////////////////////////////////////////////////////////////////
    // Layout Operation
public:
    void MeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);
    void UpdateChildPosition();
};
