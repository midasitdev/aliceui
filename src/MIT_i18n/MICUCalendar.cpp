#include "stdafx.h"
#include "MICUCalendar.h"
#include "MICUCalendarImpl.h"

using namespace mit::i18n;

namespace
{

    inline UCalendarDateFields CvtToUDateField( const MICUDateFields& field )
    {
        return static_cast<UCalendarDateFields>( field );
    }
}

MICUCalendar::MICUCalendar()
    : m_pImpl( new Impl() )
{

}

MICUCalendar::MICUCalendar( const MICUCalendar& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

MICUCalendar::MICUCalendar( MICUCalendar&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

MICUCalendar::MICUCalendar( const MICULocale& locale )
    : m_pImpl( new Impl( locale ) )
{

}

MICUCalendar::MICUCalendar( const MICUTimeZone& timezone )
    : m_pImpl( new Impl( timezone ) )
{

}

MICUCalendar::MICUCalendar( const MICUTimeZone& timezone, const MICULocale& locale )
    : m_pImpl( new Impl( timezone, locale ) )
{

}

MICUCalendar::~MICUCalendar()
{

}

void MICUCalendar::SetTime( const MICUDateUTC& date )
{
    UErrorCode err = U_ZERO_ERROR;
    GetImpl()->GetCalendar()->setTime( static_cast<UDate>( date ), err );
    assert( U_SUCCESS( err ) );
}

MICUDateUTC MICUCalendar::GetTime() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto time = GetImpl()->GetCalendar()->getTime( err );
    assert( U_SUCCESS( err ) );
    return static_cast<MICUDateUTC>( time );
}

bool MICUCalendar::IsInDaylightTime() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto isInDaylight = GetImpl()->GetCalendar()->inDaylightTime( err );
    assert( U_SUCCESS( err ) );
    return !!isInDaylight;
}

MICUDaysOfWeek MICUCalendar::GetFirstDaysOfWeek() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto firstDayOfWeek = GetImpl()->GetCalendar()->getFirstDayOfWeek( err );
    assert( U_SUCCESS( err ) );
    return static_cast<MICUDaysOfWeek>( firstDayOfWeek );
}

MICUDateUTC MICUCalendar::GetNow()
{
    return static_cast<MICUDateUTC>( icu::Calendar::getNow() );
}

int32_t MICUCalendar::Get( const MICUDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val = GetImpl()->GetCalendar()->get( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

void MICUCalendar::Set( const MICUDateFields field, const int32_t val )
{
    GetImpl()->GetCalendar()->set( CvtToUDateField( field ), val );
}

void MICUCalendar::Set( const int32_t year, const MICUMonths month, const int32_t date, const int32_t hour, const int32_t minute, const int32_t second )
{
    GetImpl()->GetCalendar()->set( year, static_cast< int32_t >( month ), date, hour, minute, second );
}

void MICUCalendar::Set(const int32_t year, const int32_t month, const int32_t day, const int32_t hour /*= 0*/, const int32_t minute /*= 0*/, const int32_t second /*= 0*/)
{
    this->Set(year, NumberToMonth(month), day, hour, minute, second);
}

void MICUCalendar::Clear()
{
    GetImpl()->GetCalendar()->clear();
}

void MICUCalendar::Clear( const MICUDateFields field )
{
    GetImpl()->GetCalendar()->clear( CvtToUDateField( field ) );
}

int32_t MICUCalendar::GetActualMaximum( const MICUDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val =  GetImpl()->GetCalendar()->getActualMaximum( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

int32_t MICUCalendar::GetActualMinimum( const MICUDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val = GetImpl()->GetCalendar()->getActualMinimum( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

MICUDateUTC MICUCalendar::ToUTC(const int32_t year, const MICUMonths month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second)
{
    MICUCalendar _calendar;
    _calendar.Set(year, month, day, hour, minute, second);
    return _calendar.GetTime();
}

MICUDateUTC MICUCalendar::ToUTC(const int32_t year, const int32_t month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second)
{
    return ToUTC(year, NumberToMonth(month), day, hour, minute, second);
}

std::optional<int32_t> MICUCalendar::GetFieldDifference(const MICUDateFields field, const MICUDateUTC time)
{
    UErrorCode errCode(U_ZERO_ERROR);
    const auto val = GetImpl()->GetCalendar()->fieldDifference(time, CvtToUDateField(field), errCode);
    if (U_SUCCESS(errCode))
        return { val };
    else
        return {};
}
