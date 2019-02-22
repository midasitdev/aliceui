#include "pch.h"
#include "AUIFloatStringFilter.h"

#include <regex>
#include <sstream>
#include <iomanip>
#include <exception>

static const unsigned int DefaultPrecision = 4;

AUIFloatStringFilter::AUIFloatStringFilter()
    : m_uiPrecision( DefaultPrecision )
    , m_eFormat( kDefault_Format )
{

}

AUIFloatStringFilter::AUIFloatStringFilter( Format format )
    : m_uiPrecision( DefaultPrecision )
    , m_eFormat( format )
{

}

AUIFloatStringFilter::AUIFloatStringFilter( unsigned int precision )
    : m_uiPrecision( precision )
    , m_eFormat( kDefault_Format )
{

}

AUIFloatStringFilter::AUIFloatStringFilter( Format format, unsigned int precision )
    : m_uiPrecision( precision )
    , m_eFormat( format )
{

}

AUIFloatStringFilter::~AUIFloatStringFilter()
{

}

std::wstring AUIFloatStringFilter::Filter( const std::wstring& strOrigin )
{
    return FilterFloat( strOrigin );
}

std::wstring AUIFloatStringFilter::FilterFloat( const std::wstring& strOrigin )
{
    static const std::wregex re( L"^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+|[.|eE])?" );
    std::wsmatch m;
    std::regex_search( strOrigin.begin(), strOrigin.end(), m, re );
    if ( m.size() == 0 )
    {
        if ( strOrigin.size() >= 1 )
        {
            if ( strOrigin[0] == '+' || strOrigin[0] == '-' )
            {
                return strOrigin.substr( 0, 1 );
            }
        }
        return std::wstring();
    }

    auto strNumber = std::wstring( m[0] );
    const auto firstDot = strNumber.find_first_of( L'.' );
    if ( firstDot != std::wstring::npos )
    {
        const auto lastDot = strNumber.find_last_of( L'.' );
        if ( firstDot != lastDot )
            strNumber.erase( lastDot, 1 );
    }

    // Precision
    const auto precisionDot = strNumber.find_first_of( L'.' );
    if ( precisionDot != std::wstring::npos )
    {
        const auto fractionCount = strNumber.size() - ( precisionDot + 1 );
        if ( fractionCount > m_uiPrecision )
        {
            const auto fractionDiff = (std::max)( std::wstring::size_type( 0 ), fractionCount - m_uiPrecision );
            for ( auto idx = 0 ; idx < fractionDiff ; ++idx )
            {
                strNumber.pop_back();
            }
        }

    }

    return strNumber;
}
