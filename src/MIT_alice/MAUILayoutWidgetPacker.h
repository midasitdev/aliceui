#pragma once
#define MIDAS_SDK

#include "MAUIWidgetPacker.h"

#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class __MY_EXT_CLASS__ MAUILayoutWidgetPacker : public MAUIWidgetPacker
        {
            MRUNTIME_DECL_KINDOF( MAUILayoutWidgetPacker );
        private:
            MAUILayoutWidgetPacker();
        public:
            MAUILayoutWidgetPacker( const std::shared_ptr< MAUILayoutWidget >& pBase );
            virtual ~MAUILayoutWidgetPacker();
            static std::shared_ptr< MAUILayoutWidgetPacker > CreateLinear( bool horizontal = false );
            static std::shared_ptr< MAUILayoutWidgetPacker > CreateRelative();


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
