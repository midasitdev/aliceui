#pragma once
#define MIDAS_SDK
#include "MAUILinearLayoutWidget.h"

#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class __MY_EXT_CLASS__ MAUIUniversalWidget : public MAUILinearLayoutWidget
        {
            typedef MAUILinearLayoutWidget _SuperWidget;
            MRUNTIME_DECL_KINDOF( MAUIUniversalWidget );
        public:
            MAUIUniversalWidget();
            virtual ~MAUIUniversalWidget();

            //////////////////////////////////////////////////////////////////////////
            // ID 2 Widget
        public:
        private:
            std::unordered_multimap< std::wstring, std::weak_ptr< MAUIWidget > > m_mapID2Widget;
            friend class MAUIWidgetBuilder;
        };
    }
}
#include "HeaderPost.h"
