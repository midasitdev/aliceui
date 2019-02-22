#include "stdafx.h"
#include "MICUTimeZoneImpl.h"

using namespace mit::i18n;

MICUTimeZone::Impl::Impl()
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::createDefault());
}

MICUTimeZone::Impl::Impl(const std::wstring& id)
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::createTimeZone(MICUUtility::CvtToUStr(id)));
}

MICUTimeZone::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICUTimeZone::Impl& MICUTimeZone::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICUTimeZone::Impl::CopyFrom(const Impl& other)
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(other.GetTimeZone()->clone());
}

void MICUTimeZone::Impl::SetUnknown()
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::getUnknown().clone());
}
