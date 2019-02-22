#pragma once


#include "AUILayoutBase.h"

class ALICEUI_API AUIGridLayout : public AUILayoutBase
{
public:
    AUIGridLayout() noexcept = default;
    ~AUIGridLayout() noexcept override = default;

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Grid Information
public:
    struct DivisionInfo
    {
        // Size Info
        SkScalar fDefaultSize = 10.0f;
        AUISizePolicy fSizePolicy = AUISizePolicy::kFixed;   // NOTE: Parent not supported
        // Padding Margin
        SkRect fMargin = SkRect::MakeEmpty();
        SkRect fPadding = SkRect::MakeEmpty();
        // Sub Division Count
        size_t fSubDivisionCount = 1;
        // Subdivision Items
        std::vector<std::shared_ptr<AUIWidget>> fWidgets;
    };
    void SetDivisionCount(const size_t count) {
        m_DivisionInfos.resize(count);
    }
    void SetDivisionInfo(const size_t idx, const DivisionInfo& info) {
        AUIAssert(idx < m_DivisionInfos.size());
        m_DivisionInfos[idx] = info;
    }
    const DivisionInfo& GetDivisionInfo(const size_t idx) const {
        AUIAssert(idx < m_DivisionInfos.size());
        return m_DivisionInfos[idx];
    }
    DivisionInfo& GetDivisionInfo(const size_t idx) {
        AUIAssert(idx < m_DivisionInfos.size());
        return m_DivisionInfos[idx];
    }
    const std::vector<DivisionInfo>& GetAllDivisionInfo() const {
        return m_DivisionInfos;
    }
    std::vector<DivisionInfo>& GetAllDivisionInfo() {
        return m_DivisionInfos;
    }
    bool IsHorizontal() const {
        return m_bHorizontal;
    }
    void SetHorizontal(bool horizontal) {
        AUIAssert(!"TODO");  // Not yet
        m_bHorizontal = horizontal;
    }
private:
    std::vector<DivisionInfo> m_DivisionInfos;
    bool m_bHorizontal = false;
};

