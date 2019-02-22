#include "stdafx.h"
#include "MICUDateFormatSymbolsImpl.h"
#include "MICULocaleImpl.h"
#include "MICUCalendarImpl.h"

using namespace mit::i18n;

MICUDateFormatSymbols::Impl::Impl()
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(errCode));
    assert(U_SUCCESS(errCode));
    assert(m_pDateFormatSymbols);
}

MICUDateFormatSymbols::Impl::Impl(const MICULocale& locale)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(locale.GetImpl()->RefLocale(), errCode));
    assert(U_SUCCESS(errCode));
    assert(m_pDateFormatSymbols);
}

MICUDateFormatSymbols::Impl::Impl(const MICUCalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(calendar.GetImpl()->GetCalendar()->getType(), errCode));
    assert(U_SUCCESS(errCode));
    assert(m_pDateFormatSymbols);
}

MICUDateFormatSymbols::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICUDateFormatSymbols::Impl& MICUDateFormatSymbols::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICUDateFormatSymbols::Impl::CopyFrom(const Impl& other)
{
    *GetDFS() = *other.GetDFS();
}

bool MICUDateFormatSymbols::Impl::operator==(const Impl& other)
{
    return *GetDFS() == *other.GetDFS();
}
