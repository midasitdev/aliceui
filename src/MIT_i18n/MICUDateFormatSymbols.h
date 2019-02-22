#pragma once
#define MIDAS_SDK
#include "MICUCommonDef.h"

namespace mit::i18n
{
    class __MITI18N_API__ MICUDateFormatSymbols final
    {
    public:
        MICUDateFormatSymbols();
        MICUDateFormatSymbols(const MICULocale& locale);
        MICUDateFormatSymbols(const MICUCalendar& calendar);
        ~MICUDateFormatSymbols();

        //////////////////////////////////////////////////////////////////////////
        // Getters
    public:
        std::vector<std::wstring> GetEras() const;
        std::vector<std::wstring> GetEraNames() const;
        std::vector<std::wstring> GetNarrowEras() const;
        std::vector<std::wstring> GetMonths() const;
        std::vector<std::wstring> GetShortMonths() const;
        std::vector<std::wstring> GetWeekdays() const;
        std::vector<std::wstring> GetShortWeekdays() const;
        std::vector<std::wstring> GetQuarters() const;
        std::vector<std::wstring> GetAmPmStrings() const;

        //////////////////////////////////////////////////////////////////////////
        // Operation
    public:
        bool IsEqual(const MICUDateFormatSymbols& dfmtsym) const;
        bool operator==(const MICUDateFormatSymbols& dfmtsym) const {
            return IsEqual(dfmtsym);
        }
        bool operator!=(const MICUDateFormatSymbols& dfmtsym) const {
            return !IsEqual(dfmtsym);
        }
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    public:
        Impl * GetImpl() const { assert(m_pImpl); return m_pImpl.get(); }
    };
}
