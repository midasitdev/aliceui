#pragma once

#include "AUIFloatStringFilter.h"
#include "AUIUnitString.h"

class ALICEUI_API AUIFloatUnitStringFilter : public AUIFloatStringFilter
{
public:
    AUIFloatUnitStringFilter();
    explicit AUIFloatUnitStringFilter(const AUIUnitType& type);

    virtual ~AUIFloatUnitStringFilter();


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    virtual std::wstring Filter(const std::wstring& strOrigin) override;


    //////////////////////////////////////////////////////////////////////////
    // Unit
public:
    void SetUnitType(const AUIUnitType& type) { m_UnitType = type; }
    AUIUnitType GetUnitType() const { return m_UnitType; }
private:
    AUIUnitType m_UnitType;
};
