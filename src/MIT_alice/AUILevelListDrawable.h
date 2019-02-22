#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUILevelListDrawable : public AUIDrawable
{
public:
    AUILevelListDrawable();
    virtual ~AUILevelListDrawable();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;
    virtual bool IsRefreshDraw() const override {
        return m_bRefreshDraw;
    }
private:
    bool m_bRefreshDraw;


    //////////////////////////////////////////////////////////////////////////
    // Level Index
protected:
    virtual void OnChangeLevelIndex() override;


    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    void ClearLevel();
    void AddLevel(int low, int high, const std::shared_ptr< AUIDrawable >& pDrawable);
    void AddLevel(int val, const std::shared_ptr< AUIDrawable >& pDrawable) {
        AddLevel(val, val, pDrawable);
    }
protected:
    AUIDrawable* GetCurDrawable() const { return m_pCurDrawable.get(); }
private:
    std::shared_ptr< AUIDrawable > m_pCurDrawable;
    struct IndexData
    {
        int fLowBound;
        int fHighBound;
        std::shared_ptr< AUIDrawable > fDrawable;
        IndexData() : fLowBound(0), fHighBound(0) {}
        IndexData(int _low, int _high, const std::shared_ptr< AUIDrawable >& _pDrawable) : fLowBound(_low), fHighBound(_high), fDrawable(_pDrawable) {}
    };
    std::vector< IndexData > m_IndexData;
};
