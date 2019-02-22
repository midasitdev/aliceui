#pragma once

#include "AUIAPIDef.h"

class ALICEUI_API AUIStringUtil
{
public:
    static bool IsEqualIgnoreCase(const std::string& left, const std::string& right);
    static bool IsEqualIgnoreCase(const std::wstring& left, const std::wstring& right);

    static std::vector< std::wstring > SplitByNewline(const std::wstring& text);
    static std::vector<std::wstring> SplitByDelim(const std::wstring& text, const wchar_t delim);

    static size_t ToHashIgnoreCase(const std::string& text);
    static size_t ToHashIgnoreCase(const std::wstring& text);

    static std::string ToLowerCase(const std::string& text);
    static std::wstring ToLowerCase(const std::wstring& text);

    static std::string ToUpperCase(const std::string& text);
    static std::wstring ToUpperCase(const std::wstring& text);
};
