#pragma once
#define MIDAS_SDK

#include "MICUCommonDef.h"
#include "MICULocale.h"

namespace mit
{
    namespace i18n
    {
        class __MITI18N_API__ MICUDateFormat final
        {
        public:
            MICUDateFormat();       // DateTime Type, Simple Style, Default Locale
            MICUDateFormat(const MICUDateFormat& other);
            ~MICUDateFormat();

            //////////////////////////////////////////////////////////////////////////
            // Style
        public:
            enum Type
            {
                kDefault_Type = 0,      // Locale will be ignored
                kDate_Type,
                kTime_Type,
                kDateTime_Type,
            };
            enum Style
            {
                // Basic styles
                kNone_Style = -1,
                kFull_Style = 0,
                kLong_Style = 1,
                kMedium_Style = 2,
                kShort_Style = 3,
                // Offset
                kDateOffset_Style = kShort_Style + 1,

                // Date-Time Style
                kDateTime_Style = 8,

                // Relative Styles
                kRelative_Style = ( 1 << 7 ),
                kFullRelative_Style = ( kFull_Style | kRelative_Style ),
                kLongRelative_Style = ( kLong_Style | kRelative_Style ),
                kMediumRelative_Style = ( kMedium_Style | kRelative_Style ),
                kShortRelative_Style = ( kShort_Style | kRelative_Style ),

                // Default Style
                kDefault_Style = kMedium_Style
            };

            //////////////////////////////////////////////////////////////////////////
            // Special Style
        public:
            MICUDateFormat( const Type type, const Style style, const MICULocale& locale = MICULocale() );
            MICUDateFormat( const Style styleDate, const Style styleTime, const MICULocale& locale = MICULocale() );


            //////////////////////////////////////////////////////////////////////////
            // Formatting
        public:
            std::wstring Fmt(const MICUDateUTC& date);
            std::wstring Fmt(const MICUCalendar& calendar);

            //////////////////////////////////////////////////////////////////////////
            // Parsing
        public:
            bool Parse( const std::wstring& str, MICUCalendar& calendar ) const;





            //////////////////////////////////////////////////////////////////////////
            // Operation
        public:
            bool IsEqual( const MICUDateFormat& dateformat ) const;
            bool operator==( const MICUDateFormat& dateformat ) const {
                return IsEqual( dateformat );
            }
            bool operator!=( const MICUDateFormat& dateformat ) const {
                return !IsEqual( dateformat );
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
