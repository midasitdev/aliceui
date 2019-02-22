#pragma once
#define MIDAS_SDK
#include "MICUCommonDef.h"

namespace mit
{
    namespace i18n
    {
        class __MITI18N_API__ MICUCalendar final
        {
        public:
            MICUCalendar();
            MICUCalendar( const MICUCalendar& other );
            MICUCalendar( MICUCalendar&& other ) noexcept;
            ~MICUCalendar();

            //////////////////////////////////////////////////////////////////////////
            // Make
        public:
            MICUCalendar( const MICULocale& locale );
            MICUCalendar( const MICUTimeZone& timezone );
            MICUCalendar( const MICUTimeZone& timezone, const MICULocale& locale );



            //////////////////////////////////////////////////////////////////////////
            // DateField Set / Get
        public:
            int32_t Get( const MICUDateFields field ) const {
                bool _succcess = false;
                return this->Get( field, _succcess );
            }
            int32_t Get( const MICUDateFields field, bool& success ) const;
			int32_t GetWeekOfMonth() const {
				return this->Get( MICUDateFields::kWeekOfMonth );
			}
            MICUDaysOfWeek GetDayOfWeek() const {
                return static_cast<MICUDaysOfWeek>( this->Get( MICUDateFields::kDayOfWeek ) );
            }
            MICUDaysOfWeek GetDayOfMonth() const {
                return static_cast<MICUDaysOfWeek>( this->Get( MICUDateFields::kDayOfMonth ) );
            }
            MICUMonths GetMonth() const {
                return static_cast<MICUMonths>( this->Get( MICUDateFields::kMonth ) );
            }
            int32_t GetYear() const {
                return this->Get( MICUDateFields::kYear );
            }
            int32_t GetDate() const {
                return this->Get(MICUDateFields::kDate);
            }
            int32_t GetActualMaximum( const MICUDateFields field, bool& success ) const;
            int32_t GetActualMaximum( const MICUDateFields field ) const {
                bool _success = false;
                return GetActualMaximum( field, _success );
            }
            int32_t GetActualMinimum( const MICUDateFields field, bool& success ) const;
            int32_t GetActualMinimum( const MICUDateFields field ) const {
                bool _success = false;
                return GetActualMinimum( field, _success );
            }
            void Set( const MICUDateFields field, const int32_t val );
            void Set(const int32_t year, const MICUMonths month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
            void Set(const int32_t year, const int32_t month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
            void Clear();
            void Clear( const MICUDateFields field );


            //////////////////////////////////////////////////////////////////////////
            // Difference
            std::optional<int32_t> GetFieldDifference(const MICUDateFields field, const MICUDateUTC time);


            //////////////////////////////////////////////////////////////////////////
            // Time
        public:
            void SetTime( const MICUDateUTC& date );
            MICUDateUTC GetTime() const;
            static MICUDateUTC ToUTC(const int32_t year, const int32_t month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
            static MICUDateUTC ToUTC(const int32_t year, const MICUMonths month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
            static MICUDateUTC GetNow();


            //////////////////////////////////////////////////////////////////////////
            // Extra Information
        public:
            bool IsInDaylightTime() const;
            MICUDaysOfWeek GetFirstDaysOfWeek() const;



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
