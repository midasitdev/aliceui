#pragma once
#define MIDAS_SDK

#include "MICUCommonDef.h"

namespace mit
{
    namespace i18n
    {
        class __MITI18N_API__ MICUTimeZone final
        {
        public:
            MICUTimeZone();
            MICUTimeZone( const std::wstring& id );
            MICUTimeZone( const MICUTimeZone& other );
            MICUTimeZone( MICUTimeZone&& other ) noexcept;
            ~MICUTimeZone();

            //////////////////////////////////////////////////////////////////////////
            // Make
        public:
            static MICUTimeZone GetUnknown();


            //////////////////////////////////////////////////////////////////////////
            // Operation
        public:
            bool IsEqual( const MICUTimeZone& timezone ) const;
            bool operator==( const MICUTimeZone& timezone ) const {
                return IsEqual( timezone );
            }
            bool operator!=( const MICUTimeZone& timezone ) const {
                return !IsEqual( timezone );
            }

            //////////////////////////////////////////////////////////////////////////
            // Internal
        private:
            class Impl;
            std::unique_ptr< Impl > m_pImpl;
        public:
            Impl * GetImpl() const { assert( m_pImpl ); return m_pImpl.get(); }
        };
    }
}
