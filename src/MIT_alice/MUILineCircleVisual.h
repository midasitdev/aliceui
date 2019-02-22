#pragma once
#define MIDAS_SDK
#include "MUILinesVisual.h"
#include "MUICircleDef.h"

#include "HeaderPre.h"
namespace mit
{
    namespace ui
    {
        class __MY_EXT_CLASS__ MUILineCircleVisual : public MUILinesVisual
        {
            MRUNTIME_DECL_KINDOF( MUILineCircleVisual );
        public:
            MUILineCircleVisual();
            virtual ~MUILineCircleVisual();


            //////////////////////////////////////////////////////////////////////////
            // Rendering data
        public:
            const std::vector< Circle >& GetCircles() const;
            float GetLineWidth() const;
            SkColor GetLineColor() const;
        };
    }
}
#include "HeaderPost.h"
