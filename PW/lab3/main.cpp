#include <windows.h>
#include <w32api/windowsx.h>


static TCHAR szAppName[] = TEXT ("Lab3") ;
WNDCLASS wndClass ;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void RegisterClass(HINSTANCE hInstance, WNDPROC WndProc);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    HWND hwnd ;
    MSG msg ;

    RegisterClass(hInstance, WndProc);
    hwnd = CreateWindow (
            szAppName, // window class name
            TEXT ("Lab 2 "), // window caption
            WS_OVERLAPPEDWINDOW, // window style
            CW_USEDEFAULT, // initial x position
            CW_USEDEFAULT, // initial y position
            800, // initial x size
            600, // initial y size
            NULL, // parent window handle
            NULL, // window menu handle
            hInstance, // program instance handle
            NULL) ; // creation parameters

    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;

    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

return msg.wParam ;
}

void RegisterClass(HINSTANCE hInstance, WNDPROC WndProc) {
    wndClass.style = CS_HREDRAW | CS_VREDRAW ;
    wndClass.lpfnWndProc = WndProc ;
    wndClass.cbClsExtra = 0 ;
    wndClass.cbWndExtra = 0 ;
    wndClass.hInstance = hInstance ;
    wndClass.hIcon = NULL ;
    wndClass.hCursor = NULL ;
    wndClass.hbrBackground = WHITE_BRUSH ;
    wndClass.lpszMenuName =NULL ;
    wndClass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndClass)) {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
    }
}
