#include "stdafx.h"
#include "MICUTimeZone.h"
#include "MICUTimeZoneImpl.h"

using namespace mit::i18n;

MICUTimeZone::MICUTimeZone()
    : m_pImpl( new Impl() )
{

}

MICUTimeZone::MICUTimeZone( const MICUTimeZone& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

MICUTimeZone::MICUTimeZone( MICUTimeZone&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

MICUTimeZone::MICUTimeZone( const std::wstring& id )
    : m_pImpl( new Impl( id ) )
{

}

MICUTimeZone::~MICUTimeZone()
{

}

bool MICUTimeZone::IsEqual( const MICUTimeZone& timezone ) const
{
    return !!( *GetImpl()->GetTimeZone() == *timezone.GetImpl()->GetTimeZone() );
}

MICUTimeZone MICUTimeZone::GetUnknown()
{
    static std::once_flag sOnce;
    static MICUTimeZone sUnknownTimeZone;
    std::call_once( sOnce, [&]() {
        sUnknownTimeZone.GetImpl()->SetUnknown();
    } );
    return sUnknownTimeZone;
}
