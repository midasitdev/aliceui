#include "stdafx.h"
#include "MICULocaleImpl.h"

using namespace mit::i18n;

MICULocale::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

MICULocale::Impl& MICULocale::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void MICULocale::Impl::CopyFrom(const Impl& other)
{
    RefLocale() = other.RefLocale();
}
