#pragma once

// Skia linkage configuration
#if defined(ALICEUI_SKIA_STATIC_LINKAGE)
#   if defined(SKIA_DLL)
#       undef SKIA_DLL
#   endif
#else
#   ifndef SKIA_DLL
#       define SKIA_DLL
#   endif
#endif

// Don't use min/max macro
#if defined(min)
#   undef min
#endif
#if defined(max)
#   undef max
#endif
