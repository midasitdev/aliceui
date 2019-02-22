#pragma once
#define MIDAS_SDK

#include "MAUIWidgetPacker.h"


#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class __MY_EXT_CLASS__ MAUIExpandableWidgetPacker : public MAUIWidgetPacker
        {
            MRUNTIME_DECL_KINDOF( MAUIExpandableWidgetPacker );
        public:
            MAUIExpandableWidgetPacker();
            MAUIExpandableWidgetPacker( const std::shared_ptr< MAUIExpandableWidget >& pBase );
            virtual ~MAUIExpandableWidgetPacker();


            //////////////////////////////////////////////////////////////////////////
            // Content
        public:
            void SetTitle( const std::wstring& title );
        protected:
            virtual std::shared_ptr< MAUILayoutWidget > OnNewContent();
        private:
            std::shared_ptr< MAUILayoutWidget > m_pContent;


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
