#include "pch.h"
#include "AUIIntegerStringFilter.h"

AUIIntegerStringFilter::AUIIntegerStringFilter()
{

}

AUIIntegerStringFilter::~AUIIntegerStringFilter()
{

}

std::wstring AUIIntegerStringFilter::Filter( const std::wstring& strOrigin )
{
    return this->FilterInteger( strOrigin );
}

std::wstring AUIIntegerStringFilter::FilterInteger( const std::wstring& strOrigin )
{

    std::wstring out;

    // Sign
    std::wstring prefix;
    if ( strOrigin.size() > 0 )
    {
        const auto firstChar = strOrigin[0];
        if ( firstChar == L'+' || firstChar == L'-' )
            prefix = firstChar;
    }

    try
    {
        out = std::to_wstring( std::stoi( strOrigin ) );
    }
    catch (std::exception&)
    {

    }

    if ( out.size() == 0 )
        out = prefix;

    return out;
}
