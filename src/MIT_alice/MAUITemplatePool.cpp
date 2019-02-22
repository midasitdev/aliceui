#include "pch.h"
#include "MAUITemplatePool.h"

using namespace mit::alice;

MAUITemplatePool::MAUITemplatePool()
{

}

MAUITemplatePool::~MAUITemplatePool()
{

}

void MAUITemplatePool::Clear()
{
    m_mapTag2Template.clear();
}

bool MAUITemplatePool::Insert( const std::wstring& tag, const std::shared_ptr< MAUITemplate >& pTemplate )
{
    if ( nullptr == pTemplate )
    {
        AUIAssertFailReason("Invalid template");
        return false;
    }

    const auto found = m_mapTag2Template.find( tag );
    if ( m_mapTag2Template.end() != found )
    {
		//register 되어 있더라도, 새로 생성만 하지 않으면 문제 없음. skwoo
        return false;
    }

    m_mapTag2Template[tag] = pTemplate;

    return true;
}

bool MAUITemplatePool::Remove( const std::wstring& tag )
{
    const auto found = m_mapTag2Template.find( tag );
    if ( m_mapTag2Template.end() == found )
    {
        AUIAssertFailReason("Template not registered");
        return false;
    }

    m_mapTag2Template.erase( found );

    return true;
}

MAUITemplate* MAUITemplatePool::GetTemplate( const std::wstring& tag ) const
{
    const auto found = m_mapTag2Template.find( tag );
    if ( m_mapTag2Template.end() == found )
        return nullptr;
    return found->second.get();
}

std::vector< std::wstring > MAUITemplatePool::GetTags() const
{
    std::vector< std::wstring > arrTags;
    for ( auto itr : m_mapTag2Template )
    {
        arrTags.emplace_back( itr.first );
    }
    return arrTags;
}
