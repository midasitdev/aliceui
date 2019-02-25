#include "stdafx.h"
#include "resource.h"

// STL
#include <chrono>
#include <thread>

// Alice UI
#include "../MIT_alice/AUIApplication.h"
#include "../MIT_alice/AUIRasterWidgetManager.h"
#include "../MIT_alice/AUISlotPool.h"
#include "../MIT_alice/AUILinearLayoutWidget.h"
#include "../MIT_alice/AUIEditWidget.h"

// Skia
#include <SkSurface.h>


constexpr int kMaxLoadStringLen = 100;

// Global window data
HINSTANCE gMainInstance = NULL;
WCHAR gWindowTitle[kMaxLoadStringLen] = { L'\0', };
WCHAR gWindowClass[kMaxLoadStringLen] = { L'\0', };

// AliceUI globals
std::atomic_bool gRunning = false;
std::future<int> gRunningTask;
std::unique_ptr<AUIRasterWidgetManager> gWidgetManager;
std::chrono::milliseconds gPrevTickTime{ 0 };
AUISlotPool gMainSPool;
sk_sp<SkSurface> gSurface;
std::shared_ptr<AUILinearLayoutWidget> gRootWidget;

// Basic WinAPI function header
ATOM MyRegisterClass(HINSTANCE hInstance);
bool InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Main entry point
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // AliceUI framework auto initialization
    AUIApplicationAutoInit appAutoInit;

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, gWindowTitle, kMaxLoadStringLen);
    LoadStringW(hInstance, IDC_HELLOWORLD, gWindowClass, kMaxLoadStringLen);
    MyRegisterClass(hInstance);

    if (false == InitInstance(hInstance, nCmdShow))
        return FALSE;

    const auto hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_HELLOWORLD));

    MSG msg{ 0, };
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    // Prepare termination
    gRunning = false;
    gRunningTask.wait();

    return static_cast<int>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{ 0, };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_HELLOWORLD));
    wcex.hCursor        = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HELLOWORLD);
    wcex.lpszClassName  = gWindowClass;
    wcex.hIconSm        = LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(IDI_HELLOWORLD_SMALL));
    return RegisterClassExW(&wcex);
}

bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   gMainInstance = hInstance;

   // Create widget manager
   gWidgetManager.reset(new AUIRasterWidgetManager());
   gPrevTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

   auto pLayout = std::make_shared<AUILinearLayoutWidget>();
   auto pEdit = std::make_shared<AUIEditWidget>(L"Hello, World!");
   pEdit->SetDefaultSize(200.0f, 30.0f);
   pLayout->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
   pLayout->AddSubWidget(pEdit);
   pLayout->UpdateChildPosition();
   pLayout->UpdateSize();
   gRootWidget = pLayout;

   HWND hWnd = CreateWindowExW(NULL, gWindowClass, gWindowTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
      return false;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   // Connect refresh signal
   gMainSPool.Connect(AUIApplication::Instance().RefreshSignal, [hWnd]() {
       InvalidateRect(hWnd, nullptr, TRUE);
   });

   // Invoke refresh thread
   gRunning = true;
   std::packaged_task<int()> task([] {
       while (gRunning) {
           std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 / 60 });
           AUIApplication::Instance().Refresh();
       }
       return 0;
   });
   gRunningTask = task.get_future();
   std::thread t(std::move(task));
   t.detach();

   gWidgetManager->CreateInstance(gRootWidget);

   return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(gMainInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT rect{ 0, };
            GetWindowRect(hWnd, &rect);
            const auto width = rect.right - rect.left;
            const auto height = rect.bottom - rect.top;

            if (gSurface && gWidgetManager)
            {
                AUIApplication::Instance().RunUpdateInstanceTask();
                AUIApplication::Instance().RunLazyUpdate();

                const auto curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                gWidgetManager->SendTickTimeEvent(gPrevTickTime, curTime);
                gPrevTickTime = curTime;
                gWidgetManager->UpdateAllInstance();
                gSurface->getCanvas()->clear(SK_ColorWHITE);
                gWidgetManager->Render(gSurface->getCanvas());

                auto pImage = gSurface->makeImageSnapshot();
                if (pImage)
                {
                    SkPixmap pixmap;
                    if (pImage->peekPixels(&pixmap))
                    {
                        BITMAPINFO bmi{ 0, };
                        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                        bmi.bmiHeader.biBitCount = 32;
                        bmi.bmiHeader.biCompression = BI_RGB;
                        bmi.bmiHeader.biPlanes = 1;
                        bmi.bmiHeader.biWidth = width;
                        bmi.bmiHeader.biHeight = -height;
                        bmi.bmiHeader.biSizeImage = width * height;

                        // Check
                        assert(width == pixmap.width());
                        assert(height == pixmap.height());
                        SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, pixmap.height(), pixmap.addr(), &bmi, DIB_RGB_COLORS);
                    }
                }
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
    {
        RECT rect{ 0, };
        GetWindowRect(hWnd, &rect);
        const auto width = rect.right - rect.left;
        const auto height = rect.bottom - rect.top;
        gSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(width, height, SkAlphaType::kOpaque_SkAlphaType));
        gRootWidget->SetDefaultSize(SkIntToScalar(width), SkIntToScalar(height));
        break;
    }
    case WM_SETCURSOR:
    {
        AUICursorIcon cursoricon;
        if (gWidgetManager)
        {
            return gWidgetManager->SendSetCursorEvent(cursoricon) ? TRUE : FALSE;
        }
        break;
    }
    case WM_ERASEBKGND:
        return TRUE;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kLBtnDown_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_LBUTTONUP:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kLBtnUp_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_LBUTTONDBLCLK:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kLBtnDblClk_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MBUTTONDOWN:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kMBtnDown_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MBUTTONUP:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kMBtnUp_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MBUTTONDBLCLK:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kMBtnDblClk_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_RBUTTONDOWN:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kRBtnDown_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_RBUTTONUP:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kRBtnUp_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_RBUTTONDBLCLK:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kRBtnDblClk_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MOUSEWHEEL:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kWheel_EventType,
                    static_cast<int>(GET_KEYSTATE_WPARAM(wParam)), POINT{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) },
                    GET_WHEEL_DELTA_WPARAM(wParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MOUSEMOVE:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kMove_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_MOUSELEAVE:
        if (gWidgetManager)
            return gWidgetManager->SendMouseEvent(
                MAUIMouseEvent(MAUIMouseEvent::kLeave_EventType,
                    static_cast<MAUIMouseEvent::EventFlag>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))
            ) ? TRUE : FALSE;
        break;
    case WM_KEYDOWN:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kKeyDown_EventType,
                    static_cast<unsigned int>(wParam), LOWORD(lParam), HIWORD(lParam))
            );
        break;
    case WM_KEYUP:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kKeyUp_EventType,
                    static_cast<unsigned int>(wParam), LOWORD(lParam), HIWORD(lParam))
            );
        break;
    case WM_CHAR:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kChar_EventType,
                    static_cast<unsigned int>(wParam), LOWORD(lParam), HIWORD(lParam))
            );
        break;
    case WM_IME_STARTCOMPOSITION:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kIMECompStart_EventType, wParam, lParam)
            );
        break;
    case WM_IME_COMPOSITION:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kIMEComp_EventType, wParam, lParam)
            );
        break;
    case WM_IME_ENDCOMPOSITION:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kIMECompEnd_EventType, wParam, lParam)
            );
        break;
    case WM_IME_CHAR:
        if (gWidgetManager)
            return gWidgetManager->SendKeyboardEvent(
                AUIKeyboardEvent(AUIKeyboardEvent::kIMEChar_EventType, wParam, lParam)
            );
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return static_cast<INT_PTR>(TRUE);
        }
        break;
    }
    return static_cast<INT_PTR>(FALSE);
}
