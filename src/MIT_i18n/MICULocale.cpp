#include "stdafx.h"
#include "MICULocale.h"
#include "MICULocaleImpl.h"

using namespace mit::i18n;

MICULocale::MICULocale()
    : m_pImpl( new Impl() )
{
    this->SetDefault();
}

MICULocale::MICULocale( const MICULocale& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

MICULocale::MICULocale( MICULocale&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

MICULocale::~MICULocale()
{

}


void MICULocale::Set( const std::wstring& language, const std::wstring& country /*= L""*/, const std::wstring& variant /*= L""*/, const std::wstring& keywordAndValues /*= L"" */ )
{
    const auto utf8language = MICUUtility::CvtToStr( language );
    const auto utf8country = MICUUtility::CvtToStr( country );
    const auto utf8variant = MICUUtility::CvtToStr( variant );
    const auto utf8keywordAndValues = MICUUtility::CvtToStr( keywordAndValues );

    GetImpl()->RefLocale() = icu::Locale( utf8language.c_str(), utf8country.c_str(), utf8variant.c_str(), utf8keywordAndValues.c_str() );
}

void MICULocale::SetDefault()
{
    GetImpl()->RefLocale() = icu::Locale::getDefault();
}

void MICULocale::SetEnglish()
{
    GetImpl()->RefLocale() = icu::Locale::getEnglish();
}

void MICULocale::SetFrench()
{
    GetImpl()->RefLocale() = icu::Locale::getFrench();

}

void MICULocale::SetGerman()
{
    GetImpl()->RefLocale() = icu::Locale::getGerman();

}

void MICULocale::SetItalian()
{
    GetImpl()->RefLocale() = icu::Locale::getItalian();

}

void MICULocale::SetJapanese()
{
    GetImpl()->RefLocale() = icu::Locale::getJapanese();

}

void MICULocale::SetKorean()
{
    GetImpl()->RefLocale() = icu::Locale::getKorean();

}

void MICULocale::SetChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getChinese();

}

void MICULocale::SetSimplifiedChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getSimplifiedChinese();

}

void MICULocale::SetTraditionalChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getTraditionalChinese();

}

void MICULocale::SetFrance()
{
    GetImpl()->RefLocale() = icu::Locale::getFrance();

}

void MICULocale::SetGermany()
{
    GetImpl()->RefLocale() = icu::Locale::getGermany();

}

void MICULocale::SetItaly()
{
    GetImpl()->RefLocale() = icu::Locale::getItaly();

}

void MICULocale::SetJapan()
{
    GetImpl()->RefLocale() = icu::Locale::getJapan();

}

void MICULocale::SetKorea()
{
    GetImpl()->RefLocale() = icu::Locale::getKorea();

}

void MICULocale::SetChina()
{
    GetImpl()->RefLocale() = icu::Locale::getChina();

}

void MICULocale::SetTaiwan()
{
    GetImpl()->RefLocale() = icu::Locale::getTaiwan();

}

void MICULocale::SetUK()
{
    GetImpl()->RefLocale() = icu::Locale::getUK();

}

void MICULocale::SetUS()
{
    GetImpl()->RefLocale() = icu::Locale::getUS();

}

void MICULocale::SetCanada()
{
    GetImpl()->RefLocale() = icu::Locale::getCanada();

}

void MICULocale::SetCanadaFrench()
{
    GetImpl()->RefLocale() = icu::Locale::getCanadaFrench();

}

std::wstring MICULocale::GetLanguage() const
{
    return MICUUtility::CvtToWStr( GetImpl()->RefLocale().getLanguage() );
}

std::wstring MICULocale::GetScript() const
{
    return MICUUtility::CvtToWStr( GetImpl()->RefLocale().getScript() );
}

std::wstring MICULocale::GetCountry() const
{

    return MICUUtility::CvtToWStr( GetImpl()->RefLocale().getCountry() );
}

std::wstring MICULocale::GetVariant() const
{

    return MICUUtility::CvtToWStr( GetImpl()->RefLocale().getVariant() );
}

bool MICULocale::IsScriptRightToLeft() const
{
    return !!GetImpl()->RefLocale().isRightToLeft();
}

bool MICULocale::IsEqual( const MICULocale& locale ) const
{
    return !!( GetImpl()->RefLocale() == locale.GetImpl()->RefLocale() );
}
