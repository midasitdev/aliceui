//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef MITI18N_EXPORTS
#   error Do not include *Impl.h outside
#endif

//////////////////////////////////////////////////////////////////////////
// ICU Header
#include <unicode/unistr.h>
#include <unicode/ucnv.h>

namespace mit
{
    namespace i18n
    {
        const size_t MICUNullTerm = size_t( -1 );   // Null termination mark

        class MICUUtility final
        {
        public:
            MICUUtility() = default;
            ~MICUUtility() = default;


            //////////////////////////////////////////////////////////////////////////
            // String conversion
        public:
            static icu::UnicodeString CvtToUStr( const std::wstring& in );
            static icu::UnicodeString CvtToUStr( const std::string& in );
            static icu::UnicodeString CvtToUStr( const char* pIn, const size_t len = MICUNullTerm );
            static icu::UnicodeString CvtToUStr( const wchar_t* pIn, const size_t len = MICUNullTerm );
            static std::wstring CvtToWStr( const icu::UnicodeString& in );
            static std::wstring CvtToWStr( const std::string& in );
            static std::wstring CvtToWStr( const char* pIn );
            static std::string CvtToStr( const icu::UnicodeString& in );
            static std::string CvtToStr( const std::wstring& in );
            static std::string CvtToStr( const wchar_t* pIn );

            //////////////////////////////////////////////////////////////////////////
            // Basic type conversion
        public:
            static bool UBoolToBool(const UBool val) {
                return !!val;
            }
        };
    }
}
