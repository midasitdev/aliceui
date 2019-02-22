#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    UErrorCode errCode(U_ZERO_ERROR);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        u_init(&errCode);
        assert(U_ZERO_ERROR == errCode);
        break;
    case DLL_PROCESS_DETACH:
        u_cleanup();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
