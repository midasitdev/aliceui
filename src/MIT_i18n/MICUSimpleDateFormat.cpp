#include "stdafx.h"
#include "MICUSimpleDateFormat.h"
#include "MICUSimpleDateFormatImpl.h"
#include "MICUCalendarImpl.h"

using namespace mit::i18n;

MICUSimpleDateFormat::MICUSimpleDateFormat(const std::wstring& pattern)
    : m_pImpl(new MICUSimpleDateFormat::Impl(pattern))
{

}

MICUSimpleDateFormat::~MICUSimpleDateFormat()
{

}

std::wstring MICUSimpleDateFormat::Fmt(const MICUDateUTC& date)
{
    icu::UnicodeString ustr;
    GetImpl()->GetDF()->format(static_cast<UDate>(date), ustr);
    return MICUUtility::CvtToWStr(ustr);
}

std::wstring MICUSimpleDateFormat::Fmt(const MICUCalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    return this->Fmt(calendar.GetImpl()->GetCalendar()->getTime(errCode));
}

bool MICUSimpleDateFormat::Parse(const std::wstring& str, MICUCalendar& calendar) const
{
    icu::ParsePosition pos(0);
    GetImpl()->GetDF()->parse(MICUUtility::CvtToUStr(str), *calendar.GetImpl()->GetCalendar(), pos);
    return icu::ParsePosition(0) != pos;
}

bool MICUSimpleDateFormat::IsEqual(const MICUSimpleDateFormat& dateformat) const
{
    return MICUUtility::UBoolToBool(*GetImpl()->GetDF() == *dateformat.GetImpl()->GetDF());
}
