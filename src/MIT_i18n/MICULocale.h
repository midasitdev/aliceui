#pragma once
#define MIDAS_SDK
#include "MICUCommonDef.h"

namespace mit
{
    namespace i18n
    {
        class __MITI18N_API__ MICULocale final
        {
        public:
            MICULocale();
            MICULocale( const MICULocale& other );
            MICULocale( MICULocale&& other ) noexcept;
            ~MICULocale();


            //////////////////////////////////////////////////////////////////////////
            // Locale language/country setter
            //  - language : ISO-639 code (https://en.wikipedia.org/wiki/ISO_639)
            //  - country : ISO-3166 code (https://en.wikipedia.org/wiki/ISO_3166)
        public:
            static MICULocale Make(const std::wstring& language, const std::wstring& country = L"", const std::wstring& variant = L"", const std::wstring& keywordAndValues = L"") {
                MICULocale _locale;
                _locale.Set(language, country, variant, keywordAndValues);
                return _locale;
            }
            // Default
            void Set(const std::wstring& language, const std::wstring& country = L"", const std::wstring& variant = L"", const std::wstring& keywordAndValues = L"");
            void SetDefault();
            // Language
            void SetEnglish();
            void SetFrench();
            void SetGerman();
            void SetItalian();
            void SetJapanese();
            void SetKorean();
            void SetChinese();
            void SetSimplifiedChinese();
            void SetTraditionalChinese();
            // Country
            void SetFrance();
            void SetGermany();
            void SetItaly();
            void SetJapan();
            void SetKorea();
            void SetChina();
            void SetTaiwan();
            void SetUK();
            void SetUS();
            void SetCanada();
            void SetCanadaFrench();
            // Get
            std::wstring GetLanguage() const;
            std::wstring GetScript() const;
            std::wstring GetCountry() const;
            std::wstring GetVariant() const;
            bool IsScriptRightToLeft() const;


            //////////////////////////////////////////////////////////////////////////
            // Operation
        public:
            bool IsEqual( const MICULocale& locale ) const;
            bool operator==( const MICULocale& locale ) const {
                return IsEqual( locale );
            }
            bool operator!=( const MICULocale& locale ) const {
                return !IsEqual( locale );
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

