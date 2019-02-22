#pragma once

#include "AUIDrawable.h"

#include <vector>

class ALICEUI_API AUILayerDrawable : public AUIDrawable
{
public:
    AUILayerDrawable();
    virtual ~AUILayerDrawable();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* canvas) override;
    bool IsRefreshDraw() const override;
private:
    bool m_bRefreshDraw;

    //////////////////////////////////////////////////////////////////////////
    // UI State
protected:
    void OnChangeDrawUIState() override;


    //////////////////////////////////////////////////////////////////////////
    // Level Index
protected:
    void OnChangeLevelIndex() override;

    //////////////////////////////////////////////////////////////////////////
    // Bound
protected:
    void OnSetDrawBound() override;
    void OnSetDrawPadding() override;


    //////////////////////////////////////////////////////////////////////////
    // Layers
public:
    bool IsLayerEmpty() const { return m_Layers.empty(); }
    size_t GetLayerCount() const { return m_Layers.size(); }
    void InsertLayer(const std::shared_ptr< AUIDrawable >& pLayer);
    void InsertLayer(size_t pos, const std::shared_ptr< AUIDrawable >& pLayer);
    void SetLayer(size_t pos, const std::shared_ptr< AUIDrawable >& pLayer);
    void EraseLayer(const std::shared_ptr< AUIDrawable >& pLayer);
    void EraseLayer(size_t pos);
    long long GetLayerPos(const std::shared_ptr< AUIDrawable >& pLayer);
    void ClearLayer();
    std::shared_ptr< AUIDrawable > GetLayerAt(const size_t pos) const {
        if (m_Layers.size() < pos)
            return nullptr;
        return m_Layers[pos];
    }
private:
    std::vector< std::shared_ptr< AUIDrawable > > m_Layers;
};

