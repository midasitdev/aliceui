#include "stdafx.h"
#include "MICUDateFormatImpl.h"

using namespace mit::i18n;

MICUDateFormat::Impl::Impl()
{
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createInstance());
    assert(m_pDateFormat);
}

MICUDateFormat::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICUDateFormat::Impl::Impl(const MICUDateFormat::Type type, const MICUDateFormat::Style style, const icu::Locale& locale)
{
    const auto icuStyle = static_cast<icu::DateFormat::EStyle>(style);
    switch (type)
    {
    case MICUDateFormat::Type::kDate_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateInstance(icuStyle, locale));
        break;
    case MICUDateFormat::Type::kTime_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createTimeInstance(icuStyle, locale));
        break;
    case MICUDateFormat::Type::kDateTime_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateTimeInstance(icuStyle, icuStyle, locale));
        break;
    default:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createInstance());
        break;
    }
    assert(m_pDateFormat);
}

MICUDateFormat::Impl::Impl(const MICUDateFormat::Style styleDate, const MICUDateFormat::Style styleTime, const icu::Locale& locale)
{
    const auto icuStyleDate = static_cast<icu::DateFormat::EStyle>(styleDate);
    const auto icuStyleTime = static_cast<icu::DateFormat::EStyle>(styleTime);
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateTimeInstance(icuStyleDate, icuStyleTime, locale));
    assert(m_pDateFormat);
}

MICUDateFormat::Impl& MICUDateFormat::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICUDateFormat::Impl::CopyFrom(const Impl& other)
{
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(static_cast<icu::DateFormat*>(other.GetDF()->clone()));
    assert(m_pDateFormat);
}
