//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "MICUPrivateDef.h"

namespace mit::i18n
{
    class MICUSimpleDateFormat::Impl final
    {
    public:
        Impl(const std::wstring& pattern);
        ~Impl() = default;

        // Copy
    public:
        Impl(const Impl& other);
        Impl& operator=(const Impl& other);
        void CopyFrom(const Impl& other);

        // Formatter
    public:
        icu::SimpleDateFormat* GetDF() const {
            assert(m_pDateFormat);
            return m_pDateFormat.get();
        }
    private:
        std::unique_ptr<icu::SimpleDateFormat> m_pDateFormat;
    };
}
