#include "pch.h"
#include <clocale>

extern "C" {
    static AFX_EXTENSION_MODULE sMIT_aliceDLL = { 0, };

    int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
        UNREFERENCED_PARAMETER(lpReserved);

        auto loc = std::setlocale(LC_ALL, "ko_KR");

        if (dwReason == DLL_PROCESS_ATTACH)
        {
            TRACE("[MIT_alice] Prepare initialization.\n");

            // Init MFC Extension
            if (!AfxInitExtensionModule(sMIT_aliceDLL, hInstance))
                return 0;

            // Register Extension DLL
            new CDynLinkLibrary(sMIT_aliceDLL);

            TRACE("[MIT_alice] Initialized.\n");
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
            TRACE("[MIT_alice] Finalizing.\n");

            // Terminate MFC Extension
            AfxTermExtensionModule(sMIT_aliceDLL);
        }
        return 1;
    }
}
