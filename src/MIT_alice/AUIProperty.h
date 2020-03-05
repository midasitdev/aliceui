#pragma once


#include "AUIAPIDef.h"
#include "AUIScalar.h"
#include <array>
#include <cmath>


typedef size_t AUIRuntimeID;

enum class AUISizePolicy
{
    kContent = 0, // 내용물에 최적화
    kFixed,	// 자신의 Default Size에 고정
    kParent	//Parent의 크기에 맞춤
};

//////////////////////////////////////////////////////////////////////////
// Property
class ALICEUI_API AUIProperty final
{
public:
    AUIProperty() noexcept;
    ~AUIProperty() = default;
    AUIProperty(const AUIProperty&) noexcept = default;
    AUIProperty(AUIProperty&&) noexcept = default;
    AUIProperty& operator=(const AUIProperty&) noexcept = default;
    AUIProperty& operator=(AUIProperty&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////////
    // Range
public:
    void ResetRange() noexcept
    {
        m_RangeMin.setZero();
        m_RangeMax.setZero();
    }
    void SetRange(const AUIScalar2& minVal, const AUIScalar2& maxVal) noexcept
    {
        SetRangeMin(minVal);
        SetRangeMax(maxVal);
    }
    void SetRange(const SkScalar minX, const SkScalar minY, const SkScalar maxX, const SkScalar maxY) noexcept
    {
        SetRangeMin(minX, minY);
        SetRangeMax(maxX, maxY);
    }
    void SetRangeMin(const SkScalar x, const SkScalar y) noexcept
    {
        SetRangeMin(AUIScalar2(x, y));
    }
    void SetRangeMax(const SkScalar x, const SkScalar y) noexcept
    {
        SetRangeMax(AUIScalar2(x, y));
    }
    void SetRangeMin(const AUIScalar2& val) noexcept
    {
        m_RangeMin = val;
    }
    void SetRangeMax(const AUIScalar2& val) noexcept
    {
        m_RangeMax = val;
    }
    void SetSize(const SkScalar width, const SkScalar height) noexcept
    {
        SetSize(AUIScalar2(width, height));
    }
    void SetSize(const AUIScalar2& size) noexcept
    {
        m_RangeMax = m_RangeMin + size;
    }
    AUIScalar2 GetRangeMin() const noexcept {
        return m_RangeMin;
    }
    SkScalar GetRangeMinX() const noexcept {
        return m_RangeMin.fX;
    }
    SkScalar GetRangeMinY() const noexcept {
        return m_RangeMin.fY;
    }
    AUIScalar2 GetRangeMax() const noexcept {
        return m_RangeMax;
    }
    SkScalar GetRangeMaxX() const noexcept {
        return m_RangeMax.fX;
    }
    SkScalar GetRangeMaxY() const noexcept {
        return m_RangeMax.fY;
    }
    AUIScalar2 GetSize() const noexcept {
        return m_RangeMax - m_RangeMin;
    }
    SkScalar GetWidth() const noexcept {
        return m_RangeMax.fX - m_RangeMin.fX;
    }
    SkScalar GetHeight() const noexcept {
        return m_RangeMax.fY - m_RangeMin.fY;
    }
private:
    AUIScalar2 m_RangeMin;
    AUIScalar2 m_RangeMax;


    //////////////////////////////////////////////////////////////////////////
    // Size
public:
    void ResetMinimumSize() noexcept
    {
        m_MinimumSize.setZero();
    }
    void ResetMaximumSize() noexcept
    {
        m_MaximumSize.setMaximum();
    }
    void ResetDefaultSize() noexcept
    {
        m_DefaultSize.setZero();
    }
    void ResetMeasureSize() noexcept
    {
        m_MeasureSize.setZero();
    }
    void SetMinimumSize(const AUIScalar2& val) noexcept {
        m_MinimumSize = val;
    }
    void SetMaximumSize(const AUIScalar2& val) noexcept {
        m_MaximumSize = val;
    }
    void SetDefaultSize(const AUIScalar2& val) noexcept {
        m_DefaultSize = val;
    }
    void SetMeasureSize(const AUIScalar2& val) noexcept {
        m_MeasureSize = val;
    }
    AUIScalar2 GetMinimumSize() const noexcept {
        return m_MinimumSize;
    }
    SkScalar GetMinimumWidth() const noexcept {
        return m_MinimumSize.fX;
    }
    SkScalar GetMinimumHeight() const noexcept {
        return m_MinimumSize.fY;
    }
    AUIScalar2 GetMaximumSize() const noexcept {
        return m_MaximumSize;
    }
    SkScalar GetMaximumWidth() const noexcept {
        return m_MaximumSize.fX;
    }
    SkScalar GetMaximumHeight() const noexcept {
        return m_MaximumSize.fY;
    }
    AUIScalar2 GetDefaultSize() const noexcept {
        return m_DefaultSize;
    }
    SkScalar GetDefaultWidth() const noexcept {
        return m_DefaultSize.fX;
    }
    SkScalar GetDefaultHeight() const noexcept {
        return m_DefaultSize.fY;
    }
    AUIScalar2 GetMeasureSize() const noexcept {
        return m_MeasureSize;
    }
    SkScalar GetMeasureWidth() const noexcept {
        return m_MeasureSize.fX;
    }
    SkScalar GetMeasureHeight() const noexcept {
        return m_MeasureSize.fY;
    }
private:
    AUIScalar2 m_MinimumSize;
    AUIScalar2 m_MaximumSize;
    AUIScalar2 m_DefaultSize;
    AUIScalar2 m_MeasureSize;


    //////////////////////////////////////////////////////////////////////////
    // Size Policy
public:
    void SetSizePolicy(const AUISizePolicy width, const AUISizePolicy height) noexcept {
        m_WidthPolicy = width;
        m_HeightPolicy = height;
    }
    void SetSizePolicyWidth(const AUISizePolicy sp) noexcept {
        m_WidthPolicy = sp;
    }
    void SetSizePolicyHeight(const AUISizePolicy sp) noexcept {
        m_HeightPolicy = sp;
    }
    AUISizePolicy GetSizePolicyWidth() const noexcept {
        return m_WidthPolicy;
    }
    AUISizePolicy GetSizePolicyHeight() const noexcept {
        return m_HeightPolicy;
    }
private:
    AUISizePolicy m_WidthPolicy = AUISizePolicy::kContent;
    AUISizePolicy m_HeightPolicy = AUISizePolicy::kContent;


    //////////////////////////////////////////////////////////////////////////
    // Weight
public:
    void ResetWeight() noexcept
    {
        m_Weight = 1.0f;
    }
    void SetWeight(const SkScalar val) noexcept
    {
        m_Weight = val;
    }
    SkScalar GetWeight() const noexcept
    {
        return m_Weight;
    }
private:
    SkScalar m_Weight = 1.0f;


    //////////////////////////////////////////////////////////////////////////
    // Padding
public:
    void ResetPadding() noexcept
    {
        m_PaddingLeft = m_PaddingTop = m_PaddingRight = m_PaddingBottom = 0.0f;
    }
    void SetPadding(const SkScalar val) noexcept
    {
        SetPaddingLTRB(val, val, val, val);
    }
    void SetPaddingLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom) noexcept
    {
        m_PaddingLeft = left;
        m_PaddingTop = top;
        m_PaddingRight = right;
        m_PaddingBottom = bottom;
    }
    void SetPaddingLeft(const SkScalar val) noexcept
    {
        m_PaddingLeft = val;
    }
    void SetPaddingTop(const SkScalar val) noexcept
    {
        m_PaddingTop = val;
    }
    void SetPaddingRight(const SkScalar val) noexcept
    {
        m_PaddingRight = val;
    }
    void SetPaddingBottom(const SkScalar val) noexcept
    {
        m_PaddingBottom = val;
    }
    SkScalar GetPaddingLeft() const noexcept
    {
        return m_PaddingLeft;
    }
    SkScalar GetPaddingTop() const noexcept
    {
        return m_PaddingTop;
    }
    SkScalar GetPaddingRight() const noexcept
    {
        return m_PaddingRight;
    }
    SkScalar GetPaddingBottom() const noexcept
    {
        return m_PaddingBottom;
    }
private:
    SkScalar m_PaddingLeft = 0.0f;
    SkScalar m_PaddingTop = 0.0f;
    SkScalar m_PaddingRight = 0.0f;
    SkScalar m_PaddingBottom = 0.0f;

    //////////////////////////////////////////////////////////////////////////
    // Margin
public:
    void ResetMargin() noexcept
    {
        m_MarginLeft = m_MarginTop = m_MarginRight = m_MarginBottom = SkScalar(0);
    }
    void SetMargin(const SkScalar val) noexcept
    {
        SetMarginLTRB(val, val, val, val);
    }
    void SetMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom) noexcept
    {
        m_MarginLeft = left;
        m_MarginTop = top;
        m_MarginRight = right;
        m_MarginBottom = bottom;
    }
    void SetMarginLeft(const SkScalar val) noexcept
    {
        m_MarginLeft = val;
    }
    void SetMarginTop(const SkScalar val) noexcept
    {
        m_MarginTop = val;
    }
    void SetMarginRight(const SkScalar val) noexcept
    {
        m_MarginRight = val;
    }
    void SetMarginBottom(const SkScalar val) noexcept
    {
        m_MarginBottom = val;
    }
    SkScalar GetMarginLeft() const noexcept
    {
        return m_MarginLeft;
    }
    SkScalar GetMarginTop() const noexcept
    {
        return m_MarginTop;
    }
    SkScalar GetMarginRight() const noexcept
    {
        return m_MarginRight;
    }
    SkScalar GetMarginBottom() const noexcept
    {
        return m_MarginBottom;
    }
private:
    SkScalar m_MarginLeft = 0.0f;
    SkScalar m_MarginTop = 0.0f;
    SkScalar m_MarginRight = 0.0f;
    SkScalar m_MarginBottom = 0.0f;

    //////////////////////////////////////////////////////////////////////////
    // Align by parent option
public:
    enum ParentOption : unsigned int
    {
        kParentTop_ParentOpt = 0,
        kParentBottom_ParentOpt,
        kParentLeft_ParentOpt,
        kParentRight_ParentOpt,

        kParentCenterHorizontal_ParentOpt,
        kParentCenterVertical_ParentOpt,
        kParentCenter_ParentOpt,

        // Total
        kParentOptTotal_ParentOpt
    };
    void ResetParentOption() noexcept
    {
        std::fill(m_ParentOption.begin(), m_ParentOption.end(), false);
    }
    void SetParentTop(const bool val) noexcept
    {
        SetParentOption(kParentTop_ParentOpt, val);
    }
    bool GetParentTop() const noexcept
    {
        return GetParentOption(kParentTop_ParentOpt);
    }
    void SetParentBottom(const bool val) noexcept
    {
        SetParentOption(kParentBottom_ParentOpt, val);
    }
    bool GetParentBottom() const noexcept
    {
        return GetParentOption(kParentBottom_ParentOpt);
    }
    void SetParentLeft(const bool val) noexcept
    {
        SetParentOption(kParentLeft_ParentOpt, val);
    }
    bool GetParentLeft() const noexcept
    {
        return GetParentOption(kParentLeft_ParentOpt);
    }
    void SetParentRight(const bool val) noexcept
    {
        SetParentOption(kParentRight_ParentOpt, val);
    }
    bool GetParentRight() const noexcept
    {
        return GetParentOption(kParentRight_ParentOpt);
    }
    void SetParentCenterHorizontal(const bool val) noexcept
    {
        SetParentOption(kParentCenterHorizontal_ParentOpt, val);
    }
    bool GetParentCenterHorizontal() const noexcept
    {
        return GetParentOption(kParentCenterHorizontal_ParentOpt) || GetParentOption(kParentCenter_ParentOpt);
    }
    void SetParentCenterVertical(const bool val) noexcept
    {
        SetParentOption(kParentCenterVertical_ParentOpt, val);
    }
    bool GetParentCenterVertical() const noexcept
    {
        return GetParentOption(kParentCenterVertical_ParentOpt);
    }
    void SetParentCenter(const bool val) noexcept
    {
        SetParentOption(kParentCenter_ParentOpt, val);
    }
    bool GetParentCenter() const noexcept
    {
        return GetParentOption(kParentCenter_ParentOpt) || (GetParentOption(kParentCenterVertical_ParentOpt) && GetParentOption(kParentCenterHorizontal_ParentOpt));
    }
private:
    void SetParentOption(const ParentOption opt, const bool val) noexcept
    {
        m_ParentOption[opt] = val;
    }
    bool GetParentOption(const ParentOption opt) const noexcept
    {
        return m_ParentOption[opt];
    }
    std::array< bool, kParentOptTotal_ParentOpt > m_ParentOption = { false, };


    //////////////////////////////////////////////////////////////////////////
    // Align by target option
public:
    enum TargetOption : unsigned int
    {
        kAbove_TargetOpt = 0,
        kBelow_TargetOpt,
        kToLeftOf_TargetOpt,
        kToRightOf_TargetOpt,

        kAlignLeft_TargetOpt,
        kAlignTop_TargetOpt,
        kAlignRight_TargetOpt,
        kAlignBottom_TargetOpt,

        kAlignBaseline_TargetOpt,

        // Total
        kTargetOptTotal_TargetOpt
    };
    void ResetTargetOption() noexcept
    {
        std::fill(m_TargetOption.begin(), m_TargetOption.end(), 0);
    }
    void SetAbove(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAbove_TargetOpt, id);
    }
    const AUIRuntimeID GetAbove() const noexcept
    {
        return GetTargetOption(kAbove_TargetOpt);
    }
    void SetBelow(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kBelow_TargetOpt, id);
    }
    const AUIRuntimeID GetBelow() const noexcept
    {
        return GetTargetOption(kBelow_TargetOpt);
    }
    void SetToLeftOf(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kToLeftOf_TargetOpt, id);
    }
    const AUIRuntimeID GetToLeftOf() const noexcept
    {
        return GetTargetOption(kToLeftOf_TargetOpt);
    }
    void SetToRightOf(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kToRightOf_TargetOpt, id);
    }
    const AUIRuntimeID GetToRightOf() const noexcept
    {
        return GetTargetOption(kToRightOf_TargetOpt);
    }
    void SetAlignLeft(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAlignLeft_TargetOpt, id);
    }
    const AUIRuntimeID GetAlignLeft() const noexcept
    {
        return GetTargetOption(kAlignLeft_TargetOpt);
    }
    void SetAlignTop(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAlignTop_TargetOpt, id);
    }
    const AUIRuntimeID GetAlignTop() const noexcept
    {
        return GetTargetOption(kAlignTop_TargetOpt);
    }
    void SetAlignRight(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAlignRight_TargetOpt, id);
    }
    const AUIRuntimeID GetAlignRight() const noexcept
    {
        return GetTargetOption(kAlignRight_TargetOpt);
    }
    void SetAlignBottom(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAlignBottom_TargetOpt, id);
    }
    const AUIRuntimeID GetAlignBottom() const noexcept
    {
        return GetTargetOption(kAlignBottom_TargetOpt);
    }
    void SetAlignBaseline(const AUIRuntimeID id) noexcept
    {
        SetTargetOption(kAlignBaseline_TargetOpt, id);
    }
    const AUIRuntimeID GetAlignBaseline() const noexcept
    {
        return GetTargetOption(kAlignBaseline_TargetOpt);
    }
private:
    void SetTargetOption(const TargetOption opt, const AUIRuntimeID id) noexcept
    {
        m_TargetOption[opt] = id;
    }
    const AUIRuntimeID GetTargetOption(const TargetOption opt) const noexcept
    {
        return m_TargetOption[opt];
    }
    std::array< AUIRuntimeID, kTargetOptTotal_TargetOpt > m_TargetOption = { false, };

    //////////////////////////////////////////////////////////////////////////
    // Gravity
public:
    enum GravityOption : unsigned int
    {
        // Center
        kGravityCenter_GravityOpt = 0,
        kGravityCenterHorizontal_GravityOpt,
        kGravityCenterVertical_GravityOpt,

        // Position
        kGravityLeft_GravityOpt,
        kGravityTop_GravityOpt,
        kGravityRight_GravityOpt,
        kGravityBottom_GravityOpt,

        // Num
        kGravityOptTotal_GravityOpt
    };
    void ResetLayoutGravityOption() noexcept
    {
        std::fill(m_LayoutGravityOption.begin(), m_LayoutGravityOption.end(), false);
    }
    void SetLayoutGravityCenter(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityCenter_GravityOpt, val);
    }
    void SetLayoutGravityCenterHorizontal(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityCenterHorizontal_GravityOpt, val);
    }
    void SetLayoutGravityCenterVertical(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityCenterVertical_GravityOpt, val);
    }
    void SetLayoutGravityLeft(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityLeft_GravityOpt, val);
    }
    void SetLayoutGravityTop(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityTop_GravityOpt, val);
    }
    void SetLayoutGravityRight(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityRight_GravityOpt, val);
    }
    void SetLayoutGravityBottom(bool val) noexcept
    {
        SetLayoutGravityOption(kGravityBottom_GravityOpt, val);
    }
    bool GetLayoutGravityCenter() const noexcept
    {
        return GetLayoutGravityOption(kGravityCenter_GravityOpt) || (GetLayoutGravityOption(kGravityCenterVertical_GravityOpt) && GetLayoutGravityOption(kGravityCenterHorizontal_GravityOpt));
    }
    bool GetLayoutGravityCenterHorizontal() const noexcept
    {
        return GetLayoutGravityOption(kGravityCenterVertical_GravityOpt);
    }
    bool GetLayoutGravityCenterVertical() const noexcept
    {
        return GetLayoutGravityOption(kGravityCenterHorizontal_GravityOpt);
    }
    bool GetLayoutGravityLeft() const noexcept
    {
        return GetLayoutGravityOption(kGravityLeft_GravityOpt);
    }
    bool GetLayoutGravityTop() const noexcept
    {
        return GetLayoutGravityOption(kGravityTop_GravityOpt);
    }
    bool GetLayoutGravityRight() const noexcept
    {
        return GetLayoutGravityOption(kGravityRight_GravityOpt);
    }
    bool GetLayoutGravityBottom() const noexcept
    {
        return GetLayoutGravityOption(kGravityBottom_GravityOpt);
    }
    void ResetGravityOption()
    {
        std::fill(m_GravityOption.begin(), m_GravityOption.end(), false);
    }
    void SetGravityCenter(bool val) noexcept
    {
        SetGravityOption(kGravityCenter_GravityOpt, val);
    }
    void SetGravityCenterHorizontal(bool val) noexcept
    {
        SetGravityOption(kGravityCenterHorizontal_GravityOpt, val);
    }
    void SetGravityCenterVertical(bool val) noexcept
    {
        SetGravityOption(kGravityCenterVertical_GravityOpt, val);
    }
    void SetGravityLeft(bool val) noexcept
    {
        SetGravityOption(kGravityLeft_GravityOpt, val);
    }
    void SetGravityTop(bool val) noexcept
    {
        SetGravityOption(kGravityTop_GravityOpt, val);
    }
    void SetGravityRight(bool val) noexcept
    {
        SetGravityOption(kGravityRight_GravityOpt, val);
    }
    void SetGravityBottom(bool val) noexcept
    {
        SetGravityOption(kGravityBottom_GravityOpt, val);
    }
    bool GetGravityCenter() const noexcept
    {
        return GetGravityOption(kGravityCenter_GravityOpt) || (GetGravityOption(kGravityCenterVertical_GravityOpt) && GetGravityOption(kGravityCenterHorizontal_GravityOpt));
    }
    bool GetGravityCenterHorizontal() const noexcept
    {
        return GetGravityOption(kGravityCenterVertical_GravityOpt);
    }
    bool GetGravityCenterVertical() const noexcept
    {
        return GetGravityOption(kGravityCenterHorizontal_GravityOpt);
    }
    bool GetGravityLeft() const noexcept
    {
        return GetGravityOption(kGravityLeft_GravityOpt);
    }
    bool GetGravityTop() const noexcept
    {
        return GetGravityOption(kGravityTop_GravityOpt);
    }
    bool GetGravityRight() const noexcept
    {
        return GetGravityOption(kGravityRight_GravityOpt);
    }
    bool GetGravityBottom() const noexcept
    {
        return GetGravityOption(kGravityBottom_GravityOpt);
    }
private:
    void SetLayoutGravityOption(const GravityOption opt, bool val) noexcept
    {
        m_LayoutGravityOption[opt] = val;
    }
    bool GetLayoutGravityOption(const GravityOption opt) const noexcept
    {
        return m_LayoutGravityOption[opt];
    }
    void SetGravityOption(const GravityOption opt, bool val) noexcept
    {
        m_GravityOption[opt] = val;
    }
    bool GetGravityOption(const GravityOption opt) const noexcept
    {
        return m_GravityOption[opt];
    }
    std::array< bool, kGravityOptTotal_GravityOpt > m_LayoutGravityOption = { false, };
    std::array< bool, kGravityOptTotal_GravityOpt > m_GravityOption = { false, };
};
