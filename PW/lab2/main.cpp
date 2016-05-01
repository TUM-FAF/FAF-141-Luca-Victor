#include <windows.h>
#include "resource.h"


HWND hListBox, hAddButton, hRemoveButton, hClearButton;
HMENU hmenu;
HWND hnewItem;
HMENU hPopupMenu;
static HWND hScrollBars[3], hLabel[3], hValue[3];
static COLORREF crPrim[3] = { RGB (255, 0, 0), RGB (0, 255, 0), RGB (0, 0, 255) } ;
static HBRUSH hBrush[3], hBrushStatic ;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

void createWindows(HWND);
static TCHAR szAppName[] = TEXT ("HelloWin") ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
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
    wndclass.hbrBackground = CreateSolidBrush (RGB(0, 0, 0)) ;
    wndclass.lpszMenuName = MAKEINTRESOURCE(IDC_APPMENU) ;
    wndclass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndclass)) {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
        return 0 ;
    }

    hwnd = CreateWindow (
            szAppName, // window class name
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
    static HMENU hMenu ;
    HDC hdc ;
    PAINTSTRUCT ps ;
    RECT rect ;
    UINT iTextLength;
    char* szText;
    POINT pt;
    int index, iCurrentIdBar;
    HINSTANCE hInstance;
    static int color[3];


    switch (message) {
        case WM_CREATE:
            hMenu = LoadMenu (hInstance, szAppName) ;
            hMenu = GetSubMenu (hMenu, 0) ;
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
        case WM_HSCROLL:
            iCurrentIdBar = GetWindowLong ((HWND) lParam, GWL_ID) ;
            switch (LOWORD (wParam)) {
                case SB_LINELEFT:
                    if (color[iCurrentIdBar] > 5)
                        color[iCurrentIdBar] -= 5;
                    break;
                case SB_LINERIGHT:
                    if (color[iCurrentIdBar] < 250)
                        color[iCurrentIdBar] += 5;
                    break;
                case SB_THUMBTRACK :
                    color[iCurrentIdBar] = HIWORD (wParam) ;
                    break ;
                default :
                    break ;
            }
            SetScrollPos (hScrollBars[iCurrentIdBar], SB_CTL, color[iCurrentIdBar], TRUE) ;
            hBrushStatic = CreateSolidBrush(RGB(color[0], color[1], color[2]));
            TCHAR szBuffer [40] ;
            hdc = GetDC(hwnd);
            wsprintf (szBuffer, TEXT ("%i"), color[iCurrentIdBar]) ;
            SetWindowText (hValue[iCurrentIdBar], szBuffer) ;
            DeleteObject((HBRUSH)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) hBrushStatic));
            InvalidateRect (hwnd, &rect, TRUE) ;
            ReleaseDC(hwnd, hdc);
            break;
        case WM_KEYDOWN:
            iCurrentIdBar = GetWindowLong ((HWND) lParam, GWL_ID) ;
            switch(wParam) {
                case VK_UP :
                    SendMessage(hScrollBars[iCurrentIdBar], WM_HSCROLL, SB_LINELEFT, 0);
                break;
                case VK_DOWN :
                    SendMessage(hScrollBars[iCurrentIdBar], WM_HSCROLL, SB_LINERIGHT, 0);
                break;
            }
            return 0;
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect(hwnd, &rect);

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
            DeleteObject (hBrushStatic) ;
            PostQuitMessage (0) ;
            return 0 ;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void createWindows(HWND hwnd) {
    static TCHAR * szColorLabel[] = {(TCHAR *)("Red"), (TCHAR *)("Green"), (TCHAR *)("Blue")} ;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hListBox = CreateWindowExW(WS_EX_CLIENTEDGE
            , L"LISTBOX", NULL
            , WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL
            , 7, 35, 200, 200
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

    for (int i = 0; i < 3; i++) {
        hScrollBars[i] = CreateWindow (
                TEXT ("scrollbar"), NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                5, 250 + i*60, 150, 10, hwnd,
                (HMENU) i,
                hInstance,
                NULL) ;

        SetScrollRange (hScrollBars[i], SB_CTL, 0, 255, FALSE) ;
        SetScrollPos (hScrollBars[i], SB_CTL, 0, FALSE) ;

        hLabel [i] = CreateWindow (
                TEXT ("static"), szColorLabel[i],
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                155, 242 + i*60, 50, 20,
                hwnd, (HMENU) (i + 3),
                hInstance, NULL);

        hValue [i] = CreateWindow (
                TEXT ("static"), TEXT ("0"),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                80, 262 + i*60, 40, 20,
                hwnd, (HMENU) (i + 6),
                hInstance, NULL) ;
        hBrush[i] = CreateSolidBrush (crPrim[i]) ;

    }
    hBrushStatic = CreateSolidBrush (GetSysColor (COLOR_BTNHIGHLIGHT)) ;
}