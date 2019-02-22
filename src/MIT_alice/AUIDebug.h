#pragma once

#include "AUIAPIDef.h"

ALICEUI_API void AUIDebugPrintImpl(const char* filename, int line, const char* fmt, ...);
ALICEUI_API void AUIDebugPrintImpl(const char* filename, int line, const wchar_t* fmt, ...);

#ifndef AUIDebugPrint
#   ifdef _DEBUG
#       define AUIDebugPrint(...) AUIDebugPrintImpl(__FILE__, __LINE__, __VA_ARGS__)
#   else
#       define AUIDebugPrint(...) do {} while(false)
#   endif
#endif

#ifndef AUIAssert
#   include <cassert>
#   define AUIAssert(cond) assert(cond)
#endif

#define AUIAssertFail()                 AUIAssert(false)
#define AUIAssertFailReason(reason)     AUIAssert(false && reason)

#define AUIDebugPrintAssertFail(...)    AUIDebugPrint(__VA_ARGS__); AUIAssertFail()

