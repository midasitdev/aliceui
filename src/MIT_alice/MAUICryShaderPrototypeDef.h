//////////////////////////////////////////////////////////////////////////
// Use only in MIT_alice
#ifndef __PROJ_MIT_ALICE__
#   error       Only include in MIT_alice project's cpp file
#endif
//////////////////////////////////////////////////////////////////////////

#include "../MIT_render/MITRenderShaderPrototypeDef.h"
#include "MIT_aliceRes.h"

#define MAUI_MODULE_FILE_NAME       _T( "MIT_alice.dll" )

namespace mit
{
    namespace alice
    {
        const mit::render::MShaderType MAUICryReservedOffset = 100;
        const mit::render::MShaderType MAUICryReservedStart = mit::render::MITRS_RESERVED_MAX + MAUICryReservedOffset;
        const mit::render::MShaderType MAUICryReservedEnd = MAUICryReservedStart + MAUICryReservedOffset;
        enum MAUICryShaderType : mit::render::MShaderType
        {
            MAUICRYS_2D = MAUICryReservedStart,

            // End
            MAUICRYS_End
        };

        static_assert( MAUICRYS_End <= MAUICryReservedEnd, "Shader Prototype Limit!" );
    }
}

