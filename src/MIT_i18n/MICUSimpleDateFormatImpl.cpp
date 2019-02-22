#include "stdafx.h"
#include "MICUSimpleDateFormatImpl.h"

using namespace mit::i18n;

MICUSimpleDateFormat::Impl::Impl(const std::wstring& pattern)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormat = std::unique_ptr<icu::SimpleDateFormat>(new icu::SimpleDateFormat(MICUUtility::CvtToUStr(pattern), errCode));
    assert(U_SUCCESS(errCode));
    assert(m_pDateFormat);
}

MICUSimpleDateFormat::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICUSimpleDateFormat::Impl& MICUSimpleDateFormat::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICUSimpleDateFormat::Impl::CopyFrom(const Impl& other)
{
    assert(m_pDateFormat);
    *GetDF() = *other.GetDF();
}
