#pragma once


#include "AUIAPIDef.h"
#include <unordered_map>
#include <memory>

namespace mit
{
    namespace alice
    {
        class MAUITemplate;
        class MAUITemplateProcessor;
        class ALICEUI_API MAUITemplatePool : public std::enable_shared_from_this< MAUITemplatePool >
        {
        public:
            MAUITemplatePool();
            ~MAUITemplatePool();

            //////////////////////////////////////////////////////////////////////////
            // Pool
        public:
            void Clear();
            bool Insert( const std::wstring& tag, const std::shared_ptr< MAUITemplate >& pTemplate );
            bool Remove( const std::wstring& tag );
            MAUITemplate* GetTemplate( const std::wstring& tag ) const;
            std::vector< std::wstring > GetTags() const;
            bool Has( const std::wstring& tag ) const { return m_mapTag2Template.end() != m_mapTag2Template.find( tag ); }
        private:
            std::unordered_map< std::wstring, std::shared_ptr< MAUITemplate > > m_mapTag2Template;
        };
    }
}

