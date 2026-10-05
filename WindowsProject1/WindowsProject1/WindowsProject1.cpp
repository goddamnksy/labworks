#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND g_hMain = NULL;
HWND g_hTemporary = NULL;
HWND g_hChild = NULL;

// TOPMOST state
bool g_bTopmost = false;

int WINAPI WinMain( 
    _In_ HINSTANCE hInstance, 
    _In_opt_ HINSTANCE, 
    _In_ LPSTR, 
    _In_ int nCmdShow
)
{
    LPCTSTR szClass = TEXT("a;eohgqeruiopugoqeig");

    WNDCLASS wc = { 0 };

    // Allow double-click messages
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = szClass;

    RegisterClass(&wc);

    // Main window

    g_hMain = ::CreateWindow(szClass, TEXT("Main window"), WS_OVERLAPPEDWINDOW, 100, 100, 400, 300, NULL, NULL, hInstance, NULL);

    if (g_hMain == NULL) {
        return -1;
    }

    // Temporary window

    g_hTemporary = ::CreateWindow(szClass, TEXT("Temporary window"), WS_POPUP | WS_CAPTION | WS_SYSMENU, 550, 100, 400, 300, NULL, NULL, hInstance, NULL);

    if (g_hTemporary == NULL) {
        return -1;
    }

    // Child window

    g_hChild = ::CreateWindow(szClass, TEXT("Child window"), WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 80, 150, 60, g_hMain, NULL, hInstance, NULL);

    if (g_hChild == NULL) {
        return -1;
    }

    // Show windows

    ShowWindow(g_hMain, nCmdShow);
    ShowWindow(g_hTemporary, nCmdShow);


    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return 0;
}


// Window procedure


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

        // Paint

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);

        if (hWnd == g_hMain || hWnd == g_hTemporary) {
            FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));
        }
        else if (hWnd == g_hChild) {
            FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));
            DrawText(hdc, TEXT("Child window"), -1, &clientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        EndPaint(hWnd, &ps);

        return 0;
    }

    // Left mouse button

    case WM_LBUTTONDOWN:
    {
        
        // Click in Main window
        

        if (hWnd == g_hMain) {

            HWND hOldParent = ::GetParent(g_hChild);

            if (hOldParent != g_hMain) {

                SetParent(g_hChild, g_hMain);
                SetWindowPos(g_hChild, NULL, 100, 80, 150, 60, SWP_NOZORDER | SWP_SHOWWINDOW);

                InvalidateRect(hOldParent, NULL, TRUE);
                UpdateWindow(hOldParent);

                InvalidateRect(g_hMain, NULL, TRUE);
                UpdateWindow(g_hMain);

                InvalidateRect(g_hChild, NULL, TRUE);
                UpdateWindow(g_hChild);
            }
        }

        
        // Click in Temporary window
        

        else if (hWnd == g_hTemporary) {

            HWND hOldParent = ::GetParent(g_hChild);

            if (hOldParent != g_hTemporary) {

                SetParent(g_hChild, g_hTemporary);
                SetWindowPos(g_hChild, NULL, 100, 80, 150, 60, SWP_NOZORDER | SWP_SHOWWINDOW);

                InvalidateRect(hOldParent, NULL, TRUE);
                UpdateWindow(hOldParent);

                InvalidateRect(g_hTemporary, NULL, TRUE);
                UpdateWindow(g_hTemporary);

                InvalidateRect(g_hChild, NULL, TRUE);
                UpdateWindow(g_hChild);
            }
        }

        return 0;
    }

    // Double left mouse button

    case WM_LBUTTONDBLCLK:
    {
        // Double-click works only in Temporary window
        if (hWnd == g_hTemporary) {

            g_bTopmost = !g_bTopmost;

            if (g_bTopmost) {

                SetWindowPos(g_hTemporary, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            }
            else {

                SetWindowPos(g_hTemporary, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            }
        }

        return 0;
    }

    // Window destruction

    case WM_DESTROY:
    {
        if (hWnd == g_hMain) {
            PostQuitMessage(0);
        }

        return 0;
    }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

