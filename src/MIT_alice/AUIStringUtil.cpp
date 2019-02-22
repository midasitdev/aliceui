#include "pch.h"
#include "AUIStringUtil.h"

bool AUIStringUtil::IsEqualIgnoreCase(const std::string& left, const std::string& right)
{
    if (left.size() != right.size())
        return false;
    AUIAssert(left.size() == right.size());
    for (size_t idx = 0; idx < left.size(); ++idx)
    {
        if (::tolower(left.at(idx)) != ::tolower(right.at(idx)))
            return false;
    }
    return true;
}

bool AUIStringUtil::IsEqualIgnoreCase(const std::wstring& left, const std::wstring& right)
{
    if (left.size() != right.size())
        return false;
    AUIAssert(left.size() == right.size());
    for (size_t idx = 0; idx < left.size(); ++idx)
    {
        if (::towlower(left.at(idx)) != ::towlower(right.at(idx)))
            return false;
    }
    return true;
}

std::vector<std::wstring> AUIStringUtil::SplitByNewline(const std::wstring& text)
{
    std::vector< std::wstring > out;
    std::wistringstream iwss(text);
    std::wstring curline;
    while (std::getline(iwss, curline))
    {
        if (false == curline.empty())
        {
            std::wstring tmp;
            tmp.reserve(curline.size());
            for (const auto& c : curline)
            {
                if (L'\r' != c)
                    tmp.push_back(c);
            }
            out.emplace_back(tmp);
        }
    }
    return out;
}

std::vector<std::wstring> AUIStringUtil::SplitByDelim(const std::wstring& text, const wchar_t delim)
{
    std::vector< std::wstring > out;
    std::wistringstream iwss(text);
    std::wstring curline;
    while (std::getline(iwss, curline, delim))
    {
        if (false == curline.empty())
            out.emplace_back(curline);
    }
    return out;
}

size_t AUIStringUtil::ToHashIgnoreCase(const std::string& text)
{
    std::string lower;
    std::transform(text.begin(), text.end(), std::back_inserter(lower), ::tolower);
    return std::hash<std::string>()(lower);
}

size_t AUIStringUtil::ToHashIgnoreCase(const std::wstring& text)
{
    std::wstring lower;
    std::transform(text.begin(), text.end(), std::back_inserter(lower), ::towlower);
    return std::hash<std::wstring>()(lower);
}

std::string AUIStringUtil::ToLowerCase(const std::string& text)
{
    std::string lower;
    std::transform(text.begin(), text.end(), std::back_inserter(lower), ::tolower);
    return lower;
}

std::wstring AUIStringUtil::ToLowerCase(const std::wstring& text)
{
    std::wstring lower;
    std::transform(text.begin(), text.end(), std::back_inserter(lower), ::towlower);
    return lower;
}

std::string AUIStringUtil::ToUpperCase(const std::string& text)
{
    std::string upper;
    std::transform(text.begin(), text.end(), std::back_inserter(upper), ::toupper);
    return upper;
}

std::wstring AUIStringUtil::ToUpperCase(const std::wstring& text)
{
    std::wstring upper;
    std::transform(text.begin(), text.end(), std::back_inserter(upper), ::towupper);
    return upper;
}
