#include "stdafx.h"
#include "MICUDateFormat.h"
#include "MICUDateFormatImpl.h"
#include "MICULocaleImpl.h"
#include "MICUCalendarImpl.h"

using namespace mit::i18n;

MICUDateFormat::MICUDateFormat()
    : m_pImpl( new Impl() )
{

}

MICUDateFormat::MICUDateFormat( const MICUDateFormat& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

MICUDateFormat::MICUDateFormat( const Type type, const Style style , const MICULocale& locale )
    : m_pImpl( new Impl( type, style, locale.GetImpl()->RefLocale() ) )
{

}

MICUDateFormat::MICUDateFormat( const Style styleDate , const Style styleTime , const MICULocale& locale )
    : m_pImpl( new Impl( styleDate, styleTime, locale.GetImpl()->RefLocale() ) )
{

}

MICUDateFormat::~MICUDateFormat()
{

}

bool MICUDateFormat::IsEqual( const MICUDateFormat& dateformat ) const
{
    return MICUUtility::UBoolToBool( *GetImpl()->GetDF() == *dateformat.GetImpl()->GetDF() );
}

std::wstring MICUDateFormat::Fmt( const MICUDateUTC& date )
{
    icu::UnicodeString ustr;
    GetImpl()->GetDF()->format(static_cast<UDate>(date), ustr);
    return MICUUtility::CvtToWStr( ustr );
}

std::wstring MICUDateFormat::Fmt(const MICUCalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    return this->Fmt(calendar.GetImpl()->GetCalendar()->getTime(errCode));
}

bool MICUDateFormat::Parse( const std::wstring& str, MICUCalendar& calendar ) const
{
    icu::ParsePosition pos(0);
    GetImpl()->GetDF()->parse( MICUUtility::CvtToUStr( str ), *calendar.GetImpl()->GetCalendar(), pos );
    return icu::ParsePosition(0) != pos;
}
