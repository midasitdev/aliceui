#include "pch.h"
#include "AUIFloatUnitStringFilter.h"

AUIFloatUnitStringFilter::AUIFloatUnitStringFilter()
    : m_UnitType( AUIUnitType::kMeter )
{

}

AUIFloatUnitStringFilter::AUIFloatUnitStringFilter(const AUIUnitType& type)
	: m_UnitType(type)
{
}

AUIFloatUnitStringFilter::~AUIFloatUnitStringFilter()
{

}

std::wstring AUIFloatUnitStringFilter::Filter( const std::wstring& strOrigin )
{
    const auto strUnit = AUIUnitString::ToString( GetUnitType() );

    auto strTarget = strOrigin;
    const auto strFloat = this->FilterFloat( strTarget );
    return strFloat + L" " + strUnit;
}
