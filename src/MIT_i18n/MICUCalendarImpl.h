//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "MICUPrivateDef.h"
#include "MICULocaleImpl.h"
#include "MICUTimeZoneImpl.h"

namespace mit::i18n
{
    //////////////////////////////////////////////////////////////////////////
    // Check enum order
    static_assert(static_cast<int>(MICUDateFields::kFieldCount) == UCAL_FIELD_COUNT, "Check enum order");

    class MICUCalendar::Impl final
    {
    public:
        Impl();
        Impl(const Impl& other);
        Impl(const MICULocale& locale);
        Impl(const MICUTimeZone& timezone);
        Impl(const MICUTimeZone& timezone, const MICULocale& locale);
        ~Impl() = default;
        Impl& operator=(const Impl& other);
        void CopyFrom(const Impl& other);
    public:
        icu::Calendar* GetCalendar() const {
            assert(m_pCalendar);
            return m_pCalendar.get();
        }
    private:
        std::unique_ptr< icu::Calendar > m_pCalendar;
    };
}
