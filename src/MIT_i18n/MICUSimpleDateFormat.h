#pragma once
#define MIDAS_SDK
#include "MICUCommonDef.h"

namespace mit::i18n
{
    class __MITI18N_API__ MICUSimpleDateFormat final
    {
    public:
        MICUSimpleDateFormat(const std::wstring& pattern);
        ~MICUSimpleDateFormat();

        //////////////////////////////////////////////////////////////////////////
        // Formatting : http://www.unicode.org/reports/tr35/tr35-dates.html#Date_Field_Symbol_Table
    public:
        std::wstring Fmt(const MICUDateUTC& date);
        std::wstring Fmt(const MICUCalendar& calendar);

        //////////////////////////////////////////////////////////////////////////
        // Parsing
    public:
        bool Parse(const std::wstring& str, MICUCalendar& calendar) const;

        //////////////////////////////////////////////////////////////////////////
        // Operation
    public:
        bool IsEqual(const MICUSimpleDateFormat& dateformat) const;
        bool operator==(const MICUSimpleDateFormat& dateformat) const {
            return IsEqual(dateformat);
        }
        bool operator!=(const MICUSimpleDateFormat& dateformat) const {
            return !IsEqual(dateformat);
        }

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    public:
        Impl * GetImpl() const {
            assert(m_pImpl);
            return m_pImpl.get();
        }
    };
}
