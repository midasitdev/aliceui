#include "stdafx.h"
#include "MICUCalendarImpl.h"

using namespace mit::i18n;

MICUCalendar::Impl::Impl()
{
    UErrorCode err(U_ZERO_ERROR);
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(icu::Locale::getDefault(), err));
    assert(U_SUCCESS(err));
}

MICUCalendar::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICUCalendar::Impl::Impl(const MICULocale& locale)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(locale.GetImpl()->RefLocale(), err));
    assert(U_SUCCESS(err));
}

MICUCalendar::Impl::Impl(const MICUTimeZone& timezone)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(*timezone.GetImpl()->GetTimeZone(), err));
    assert(U_SUCCESS(err));
}

MICUCalendar::Impl::Impl(const MICUTimeZone& timezone, const MICULocale& locale)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(*timezone.GetImpl()->GetTimeZone(), locale.GetImpl()->RefLocale(), err));
    assert(U_SUCCESS(err));
}

MICUCalendar::Impl& MICUCalendar::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICUCalendar::Impl::CopyFrom(const Impl& other)
{
    m_pCalendar = std::unique_ptr< icu::Calendar >(GetCalendar()->clone());
    assert(m_pCalendar);
}
