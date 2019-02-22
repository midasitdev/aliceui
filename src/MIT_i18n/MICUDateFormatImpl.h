//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "MICUPrivateDef.h"

namespace mit::i18n
{
    //////////////////////////////////////////////////////////////////////////
    // Check enum order
    static_assert(static_cast<int>(MICUDateFormat::kNone_Style) == icu::DateFormat::kNone, "Check enum order");
    static_assert(static_cast<int>(MICUDateFormat::kShortRelative_Style) == icu::DateFormat::kShortRelative, "Check enum order");
    static_assert(static_cast<int>(MICUDateFormat::kDefault_Style) == icu::DateFormat::kDefault, "Check enum order");

    class MICUDateFormat::Impl final
    {
    public:
        Impl();
        Impl(const Impl& other);
        Impl(const MICUDateFormat::Type type, const MICUDateFormat::Style style, const icu::Locale& locale);
        Impl(const MICUDateFormat::Style styleDate, const MICUDateFormat::Style styleTime, const icu::Locale& locale);
        ~Impl() = default;
        Impl& operator=(const Impl& other);
        void CopyFrom(const Impl& other);
    public:
        icu::DateFormat* GetDF() const {
            assert(m_pDateFormat);
            return m_pDateFormat.get();
        }
    private:
        std::unique_ptr< icu::DateFormat > m_pDateFormat;
    };
}
