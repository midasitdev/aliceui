#pragma once
#define MIDAS_SDK

#if defined( _WIN32 )
#   ifdef MITI18N_EXPORTS
#       define __MITI18N_API__    __declspec(dllexport)
#   else
#       define __MITI18N_API__    __declspec(dllimport)
#   endif
#else
#   ifdef MITI18N_EXPORTS
#       define __MITI18N_API__    
#   else
#       define __MITI18N_API__    
#   endif
#endif

namespace mit::i18n
{
    enum class MBiDi
    {
        LeftToRight,
        RightToLeft,
        Mixed,
        Neutral
    };
}


