#include <windows.h>

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);

#define ID_MYBUTTON 1
#define ID_ROMAN_MYBUTTON 2

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int ss) {
    /* создаем и регистрируем класс главного окна */
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = MainWinProc;
    wc.cbClsExtra = wc.cbWndExtra=0;
    wc.hInstance=hInst;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Main Window";
    if (!RegisterClass(&wc)) return FALSE;

    /* создаем главное окно и отображаем его */
    HWND hMainWnd = CreateWindow("Main Window","Okoshko",WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);
    if (!hMainWnd) return FALSE;
    ShowWindow(hMainWnd,ss);
    UpdateWindow(hMainWnd);


    MSG msg; /* цикл обработки событий */
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            /* при создании окна внедряем в него кнопочку */
            CreateWindow("button", "My button", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         50, 100, 100, 200, hw, (HMENU) ID_MYBUTTON, NULL, NULL);
            CreateWindow("button", "My Roman button", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                         160, 100, 150, 200, hw, (HMENU) ID_ROMAN_MYBUTTON, NULL, NULL);
            /* стиль WS_CHILD означает, что это дочернее окно и для него
             вместо дескриптора меню будет передан целочисленный идентификатор,
             который будет использоваться дочерним окном для оповещения
             родительского окна через WM_COMMAND */
            return 0;
        case WM_COMMAND:
            /* нажата наша кнопочка? */
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON))
                MessageBox(hw, "You pressed my button", "MessageBox", MB_OK | MB_ICONWARNING);
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_ROMAN_MYBUTTON))
                MessageBox(hw, "Roma is my button", "Roma Info", MB_OK | MB_ICONWARNING);

            return 0;
        case WM_DESTROY:
            /* пользователь закрыл окно, программа может завершаться */
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}