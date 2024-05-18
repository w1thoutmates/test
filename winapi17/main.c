#include <windows.h>

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK NonModalWinProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MultiplyWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);

#define ID_MULTIPLE_WINDOWS 1
#define ID_MESSAGE_BUTTON 2
#define ID_NON_MODAL_BUTTON 3
#define ID_NON_MODAL_OK 4
#define ID_MULTIPLY_OK 5

HWND hNonModalWnd = NULL;
HWND hStaticText = NULL;
HWND hMultiply = NULL;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss)
{
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = MainWinProc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MainWindow";
    if (!RegisterClass(&wc)) return FALSE;

    HWND hMainWnd = CreateWindow("MainWindow", "MAIN WINDOW", WS_OVERLAPPEDWINDOW,
                                 650, 200, 600, 600, NULL, NULL, hInst, NULL);
    if (!hMainWnd) return FALSE;
    ShowWindow(hMainWnd, ss);
    UpdateWindow(hMainWnd);

    WNDCLASS wcNonModal;
    wcNonModal.style = 0;
    wcNonModal.lpfnWndProc = NonModalWinProc;
    wcNonModal.cbClsExtra = wcNonModal.cbWndExtra = 0;
    wcNonModal.hInstance = hInst;
    wcNonModal.hIcon = NULL;
    wcNonModal.hCursor = NULL;
    wcNonModal.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcNonModal.lpszMenuName = NULL;
    wcNonModal.lpszClassName = "NonModalWindow";
    if (!RegisterClass(&wcNonModal)) return FALSE;

    WNDCLASS wcMulty;
    wcMulty.style = 0;
    wcMulty.lpfnWndProc = MultiplyWinProc;
    wcMulty.cbClsExtra = wcMulty.cbWndExtra = 0;
    wcMulty.hInstance = hInst;
    wcMulty.hIcon = NULL;
    wcMulty.hCursor = NULL;
    wcMulty.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcMulty.lpszMenuName = NULL;
    wcMulty.lpszClassName = "Multiply";
    if (!RegisterClass(&wcMulty)) return FALSE;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("button", "Multiply button", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                        5, 5, 110, 20, hw, (HMENU) ID_MULTIPLE_WINDOWS, NULL, NULL);
            CreateWindow("button", "Modal button", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         125, 5, 120, 20, hw, (HMENU) ID_MESSAGE_BUTTON, NULL, NULL);
            CreateWindow("button", "Non Modal button", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         250, 5, 140, 20, hw, (HMENU) ID_NON_MODAL_BUTTON, NULL, NULL);
            return 0;
        case WM_COMMAND:
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MULTIPLE_WINDOWS))
                for(int i = 0; i < 3; i++) {
                    HWND hMultiply = CreateWindow("Multiply", "Multiply Window", WS_BORDER,
                                                  100, 100 + (i * 200), 200, 150, hw, NULL, NULL, NULL);
                    ShowWindow(hMultiply, SW_SHOW);
                    UpdateWindow(hMultiply);
                }

            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MESSAGE_BUTTON))
                MessageBox(hw, "MessageBox", "Modal Window", MB_OK | MB_ICONWARNING);
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_NON_MODAL_BUTTON)) {

                hNonModalWnd = CreateWindow("NonModalWindow", "Non Modal Window", WS_BORDER,
                                                 840, 470, 185, 130, NULL, NULL, NULL, NULL);
                ShowWindow(hNonModalWnd, SW_SHOW);
                UpdateWindow(hNonModalWnd);
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}

LRESULT CALLBACK NonModalWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("button", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                        50, 50, 80, 20, hw, (HMENU) ID_NON_MODAL_OK, NULL, NULL);
            hStaticText = CreateWindowEx(0, "Static", "MessageBox", WS_CHILD | WS_VISIBLE | SS_LEFT,
                                         45, 10, 100, 20, hw, NULL, GetModuleHandle(NULL), NULL);
            return 0;
        case WM_COMMAND:
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_NON_MODAL_OK))
                DestroyWindow(hNonModalWnd);
        case WM_DESTROY:
            return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}
LRESULT CALLBACK MultiplyWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("button", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         50, 50, 80, 20, hw, (HMENU) ID_MULTIPLY_OK, NULL, NULL);
            hStaticText = CreateWindowEx(0, "Static", "MessageBox", WS_CHILD | WS_VISIBLE | SS_LEFT,
                                         45, 10, 100, 20, hw, NULL, GetModuleHandle(NULL), NULL);
            return 0;
        case WM_COMMAND:
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MULTIPLY_OK))
                DestroyWindow(hw);
        case WM_DESTROY:
            return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
    }