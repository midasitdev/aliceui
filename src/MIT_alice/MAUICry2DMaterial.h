#pragma once
#define MIDAS_SDK

#include "MAUICryCommonDef.h"
#include "../MIT_render/MMaterial.h"
#include "../MIT_render/MGlossyMaterial.h"

#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class __MY_EXT_CLASS__ MAUICry2DMaterial : public mit::render::MGlossyMaterial
        {
            MRUNTIME_DECL_KINDOF( MAUICry2DMaterial );
        public:
            MAUICry2DMaterial( mit::render::MMaterialGearBox* pGearBox );
            virtual ~MAUICry2DMaterial();
        };
    }
}
#include "HeaderPost.h"
