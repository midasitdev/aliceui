//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "MICUPrivateDef.h"

namespace mit::i18n
{
    class MICULocale::Impl final
    {
    public:
        Impl() = default;
        Impl(const Impl& other);
        ~Impl() = default;
        Impl& operator=(const Impl& other);
        void CopyFrom(const Impl& other);
    public:
        const icu::Locale& RefLocale() const {
            return m_Locale;
        }
        icu::Locale& RefLocale() {
            return m_Locale;
        }
    private:
        icu::Locale m_Locale;
    };

}
