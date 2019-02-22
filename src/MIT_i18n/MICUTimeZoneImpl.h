//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "MICUPrivateDef.h"

namespace mit
{
    namespace i18n
    {
        class MICUTimeZone::Impl final
        {
        public:
            Impl();
            Impl( const std::wstring& id );
            Impl( const Impl& other );
            ~Impl() = default;
            Impl& operator=( const Impl& other );
            void CopyFrom( const Impl& other );
        public:
            void SetUnknown();
            icu::TimeZone* GetTimeZone() const {
                assert( m_pTimeZone );
                return m_pTimeZone.get();
            }
        private:
            std::unique_ptr< icu::TimeZone > m_pTimeZone;
        };
    }
}
