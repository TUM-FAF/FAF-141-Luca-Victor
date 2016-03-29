#include <windows.h>
#include "resource.h"


HWND hListBox, hAddButton, hRemoveButton, hClearButton;
HMENU hmenu;
HWND hnewItem;
HMENU hPopupMenu;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

void createWindows(HWND);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static TCHAR szAppName[] = TEXT ("HelloWin") ;
    HWND hwnd ;
    MSG msg ;
    WNDCLASS wndclass ;


    wndclass.style = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc = WndProc ;
    wndclass.cbClsExtra = 0 ;
    wndclass.cbWndExtra = 0 ;
    wndclass.hInstance = hInstance ;
    wndclass.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE(IDE_TARGET));
    wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_TARGET));
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName = NULL ;
    wndclass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndclass)) {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
        return 0 ;
    }

    hwnd = CreateWindow (szAppName, // window class name
                         TEXT ("Lab 2 "), // window caption
                         WS_OVERLAPPEDWINDOW, // window style
                         CW_USEDEFAULT, // initial x position
                         CW_USEDEFAULT, // initial y position
                         CW_USEDEFAULT, // initial x size
                         CW_USEDEFAULT, // initial y size
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
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc ;
    PAINTSTRUCT ps ;
    RECT rect ;
    UINT iTextLength;
    char* szText;
    POINT pt;
    int index;
    HINSTANCE hInstance;

    switch (message) {
        case WM_CREATE:
            hmenu = CreateMenu();
            AppendMenu(hmenu, MF_STRING, ID_ABOUT, "About");
            AppendMenu(hmenu, MF_STRING, ID_EXIT, "Exit");
            SetMenu(hwnd, hmenu);
            createWindows(hwnd);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)){
                case ID_ADD_BUTTON:
                    iTextLength = SendMessage(hnewItem, WM_GETTEXTLENGTH, 0, 0);
                    if (iTextLength != 0) {
                        szText = (char*)malloc(iTextLength+1);
                        SendMessage(hnewItem, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
                        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)szText);
                        SendMessage(hnewItem, WM_SETTEXT, 0, (LPARAM)"");
                        free(szText);
                    }
                    break;
                case ID_REMOVE_BUTTON:
                    index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    if (index != LB_ERR)
                        SendMessage(hListBox, LB_DELETESTRING, index, 0);
                    break;

                case ID_CLEAR_BUTTON:
                    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
                    break;
            }
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            EndPaint (hwnd, &ps) ;
            return 0 ;
        case WM_SETCURSOR:
            hInstance = GetModuleHandle(NULL);
            if (LOWORD(lParam) == HTCLIENT) {
                SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(IDC_TARGET)));
                return TRUE;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0) ;
            return 0 ;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void createWindows(HWND hwnd) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hListBox = CreateWindowExW(WS_EX_CLIENTEDGE
            , L"LISTBOX", NULL
            , WS_CHILD | WS_VISIBLE | LBS_NOTIFY
            , 7, 35, 200, 300
            , hwnd, NULL, hInstance, NULL);

    hnewItem = CreateWindow(
            TEXT("Edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            5, 5, 200, 20, hwnd,
            (HMENU)ID_NEW_ITEM,
            GetModuleHandle(NULL),
            NULL);

    hAddButton = CreateWindow(
            TEXT("Button"),
            TEXT("Add"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            210, 5, 78, 20, hwnd,
            (HMENU)ID_ADD_BUTTON,
            GetModuleHandle(NULL),
            NULL);

    hRemoveButton = CreateWindow(
            TEXT("Button"),
            TEXT("Remove"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            210, 35, 78, 20, hwnd,
            (HMENU)ID_REMOVE_BUTTON,
            GetModuleHandle(NULL),
            NULL);

    hClearButton = CreateWindow(
            TEXT("Button"),
            TEXT("Clear"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            210, 65, 78, 20, hwnd,
            (HMENU)ID_CLEAR_BUTTON,
            GetModuleHandle(NULL),
            NULL);
}