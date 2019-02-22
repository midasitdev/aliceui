#pragma once

#define MIDAS_SDK
#include "MAUICommonDef.h"
namespace mit
{
    namespace alice
    {
        enum class MAUISimpleShapeType : unsigned int
        {
            ARROW = 0,
            RECT,
            TRIANGLE,
            ELLIPSOID,
        };
        struct MAUISimpleShape
        {
            MAUISimpleShapeType type;
            glm::vec3 origin;
            float defaultSize;
            SkColor color;
            MAUISimpleShape()
            {

            }
        };
    }
}