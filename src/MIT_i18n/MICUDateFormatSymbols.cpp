#include "stdafx.h"
#include "MICUDateFormatSymbols.h"
#include "MICUDateFormatSymbolsImpl.h"

using namespace mit::i18n;

MICUDateFormatSymbols::MICUDateFormatSymbols()
    : m_pImpl(new Impl())
{

}

MICUDateFormatSymbols::MICUDateFormatSymbols(const MICULocale& locale)
    : m_pImpl(new Impl(locale))
{

}

MICUDateFormatSymbols::MICUDateFormatSymbols(const MICUCalendar& calendar)
    : m_pImpl(new Impl(calendar))
{

}

MICUDateFormatSymbols::~MICUDateFormatSymbols()
{

}

bool MICUDateFormatSymbols::IsEqual(const MICUDateFormatSymbols& dfmtsym) const
{
    return *GetImpl() == *dfmtsym.GetImpl();
}

std::vector<std::wstring> MICUDateFormatSymbols::GetEras() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getEras(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetEraNames() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getEraNames(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetNarrowEras() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getNarrowEras(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetMonths() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getMonths(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetShortMonths() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getShortMonths(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetWeekdays() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getWeekdays(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetShortWeekdays() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getShortWeekdays(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetQuarters() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getQuarters(cnt, icu::DateFormatSymbols::FORMAT, icu::DateFormatSymbols::ABBREVIATED);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> MICUDateFormatSymbols::GetAmPmStrings() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getAmPmStrings(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(MICUUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}
