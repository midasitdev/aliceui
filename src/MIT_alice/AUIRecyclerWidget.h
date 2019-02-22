#pragma once

#include "AUIRecyclerCommonDef.h"
#include "AUILayoutWidget.h"

class ALICEUI_API AUIRecyclerWidget : public AUILayoutWidget
{
    typedef AUILayoutWidget SuperClass;
    typedef AUIRecyclerAdapter Adapter;
    typedef AUIRecyclerLayoutManager LayoutManager;
public:
    AUIRecyclerWidget();
    virtual ~AUIRecyclerWidget();


    //////////////////////////////////////////////////////////////////////////
    // Adapter
public:
    void SetAdapter(std::shared_ptr< Adapter > pAdapter);
    std::shared_ptr< Adapter > GetAdapter() const {
        return m_pAdapter;
    }
private:
    std::shared_ptr< Adapter > m_pAdapter;


    //////////////////////////////////////////////////////////////////////////
    // LayoutManager
public:
    void SetLayoutManager(std::unique_ptr< LayoutManager > pLayoutManager);
    LayoutManager* GetLayoutManager() const { AUIAssert(m_pLayoutManager); return m_pLayoutManager.get(); }
private:
    std::unique_ptr< LayoutManager > m_pLayoutManager;


    //////////////////////////////////////////////////////////////////////////
    // Measure
protected:
    virtual void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    virtual void OnUpdateChildPosition();

    // NOTE : DO NOT CALL Directly!
//    //////////////////////////////////////////////////////////////////////////
//    // Public child interface
//public:
//    virtual void AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos ) override;
//    virtual void DelSubWidget( const std::shared_ptr< AUIWidget >& widget ) override;
//    virtual void PopSubWidget() override;
//    virtual void ClearSubWidget() override;
//    virtual std::shared_ptr< AUIWidget > FindSubWidget( size_t pos ) override;
//    virtual size_t SubWidgetCount() const override;

    //////////////////////////////////////////////////////////////////////////
    // Internal
protected:
    void SyncAdapter();
    const std::vector< std::shared_ptr< AUIRecyclerWidgetHolder > >& GetWidgetHolders() const {
        return m_WidgetHolders;
    }
private:
    void NotifyChange();
    void ItemChanged(size_t pos);
    void ItemInserted(size_t pos);
    void ItemMoved(size_t fromPos, size_t toPos);
    void ItemRemoved(size_t pos);
    void ItemRangeChanged(size_t startPos, size_t itemCount);
    void ItemRangeInserted(size_t startPos, size_t itemCount);
    void ItemRangeRemoved(size_t startPos, size_t itemCount);
    AUISlotPool m_spoolAdapter;
    std::vector<std::shared_ptr<AUIRecyclerWidgetHolder>> m_WidgetHolders;
};
