#pragma once
#define MIDAS_SDK

#include "MAUIWidgetPacker.h"

#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class MAUITab;
        class __MY_EXT_CLASS__ MAUITabWidgetPacker : public MAUIWidgetPacker
        {
            MRUNTIME_DECL_KINDOF( MAUITabWidgetPacker );
        public:
            MAUITabWidgetPacker();
            MAUITabWidgetPacker( const std::shared_ptr< MAUITabWidget >& pBase );
            virtual ~MAUITabWidgetPacker();


            //////////////////////////////////////////////////////////////////////////
            // Tab
        public:
            void SetTabName( const std::wstring& name ) { m_TabName = name; }
            void SetTabIcon( const std::shared_ptr< const SkBitmap >& pIcon ) { m_pIcon = pIcon; }
        protected:
            virtual std::shared_ptr< MAUITab > OnNewTab( const std::shared_ptr< MAUIWidget >& pContent );
        private:
            std::vector< std::shared_ptr< MAUITab > > m_TabData; 
            std::wstring m_TabName;
            std::shared_ptr< const SkBitmap > m_pIcon;

            //////////////////////////////////////////////////////////////////////////
            // Interface
        private:
            virtual bool OnStart() override;
            virtual bool OnEnd() override;
            virtual bool OnInsert( const std::shared_ptr< MAUIWidget >& pWidget ) override;
            virtual bool OnSetProperty( const MAUIProperty& prop ) override;
        };
    }
}
#include "HeaderPost.h"
