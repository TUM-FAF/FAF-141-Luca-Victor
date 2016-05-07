#include <windows.h>
#include <w32api/windowsx.h>
#include "resource.h"
#include "registerClass.h"


HWND hListBox, hAddButton, hRemoveButton, hClearButton, hNewItem, hRenameItem;
HMENU hPopUpMenu;
static HWND hScrollBars[3], hLabel[3], hValue[3];
static COLORREF crPrim[3] = { RGB (255, 0, 0), RGB (0, 255, 0), RGB (0, 0, 255) } ;
static HBRUSH hBrush[3], hBrushStatic ;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

BOOL CALLBACK RenameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void createWindows(HWND);
void SetRandomColor(HWND, int*, RECT);
static TCHAR szRenameWindow[] = TEXT("Rename");

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
             CW_USEDEFAULT, // initial x size
             CW_USEDEFAULT, // initial y size
             NULL, // parent window handle
             NULL, // window menu handle
             hInstance, // program instance handle
             NULL) ; // creation parameters

    RegisterHotKey(hwnd, HK_CTRL_X, MOD_CONTROL, 0x58);
    RegisterHotKey(hwnd, HK_CRTL_SPACE, MOD_CONTROL, VK_SPACE);

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
    static HMENU hMenu ;
    RECT rect ;
    UINT iTextLength;
    char* szText;
    static POINT pt;
    int index, i = 0;
    HINSTANCE hInstance = nullptr;
    static int color[3];

    switch (message) {
        case WM_CREATE:
            hInstance = (HINSTANCE) ((LPCREATESTRUCT) lParam)->hInstance ;
            hMenu = LoadMenu (hInstance, szAppName) ;
            hMenu = GetSubMenu (hMenu, 0) ;
            createWindows(hwnd);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)){
                case ID_ADD_BUTTON:
                    iTextLength = (UINT) SendMessage(hNewItem, WM_GETTEXTLENGTH, 0, 0);
                    if (iTextLength != 0) {
                        szText = (char*)malloc(iTextLength+1);
                        SendMessage(hNewItem, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
                        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)szText);
                        SendMessage(hNewItem, WM_SETTEXT, 0, (LPARAM)"");
                        free(szText);
                    }
                    break;
                case ID_REMOVE_BUTTON:
                    index = (int) SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    if (index != LB_ERR)
                        SendMessage(hListBox, LB_DELETESTRING, index, 0);
                    break;
                case ID_CLEAR_BUTTON:
                    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
                    break;
                case IDM_ABOUT:
                    MessageBox(hwnd, TEXT("This is the coolest and best app in the world!"), MB_OK, MB_ICONEXCLAMATION) ;
                    break;
                case IDM_RESIZE:
                    SendMessage(hListBox,  LB_SETITEMDATA, 0, (LPARAM) TEXT("Jora"));

                    SetWindowPos(hwnd, HWND_TOP, 200, 200, 400, 500, SWP_NOOWNERZORDER);
                    break;
                case IDM_EXIT:
                    PostQuitMessage (0) ;
                    break;
                case IDM_DELETE:
                    index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    SendMessage(hListBox, LB_DELETESTRING, index, 0);
                    break;
                case IDM_RENAME:
                    if (DialogBox (hInstance, MAKEINTRESOURCE(IDR_ABOUTBOX), hwnd, (DLGPROC)RenameDlgProc)){
                        InvalidateRect(hwnd, NULL, TRUE);
                    }
                    break;
            }
        case WM_CONTEXTMENU:
            if((HWND)wParam == hListBox) {
                hPopUpMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_POPUPMENU));
                hPopUpMenu = GetSubMenu(hPopUpMenu, 0);
                ClientToScreen(hwnd, (LPPOINT) &pt);
                pt.x = GET_X_LPARAM(lParam);
                pt.y = GET_Y_LPARAM(lParam);
                TrackPopupMenu (hPopUpMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
                DestroyMenu(hPopUpMenu);
            }
            break;
        case WM_HSCROLL:
            i = GetWindowLong ((HWND) lParam, GWL_ID) ;
            switch (LOWORD (wParam)) {
                case SB_LINELEFT:
                    if (color[i] > 5)
                        color[i] -= 5;
                    break;
                case SB_LINERIGHT:
                    if (color[i] < 250)
                        color[i] += 5;
                    break;
                case SB_THUMBTRACK :
                    color[i] = HIWORD (wParam) ;
                    break ;
                default :
                    break ;
            }
            SetScrollPos (hScrollBars[i], SB_CTL, color[i], TRUE) ;
            hBrushStatic = CreateSolidBrush(RGB(color[0], color[1], color[2]));
            TCHAR szBuffer [40] ;
            wsprintf (szBuffer, TEXT ("%i"), color[i]) ;
            SetWindowText (hValue[i], szBuffer) ;
            DeleteObject((HBRUSH)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) hBrushStatic));
            InvalidateRect (hwnd, &rect, TRUE) ;
            break;
        case WM_KEYDOWN:
            i = GetWindowLong ((HWND) lParam, GWL_ID) ;
            switch(wParam) {
                case VK_UP :
                    SendMessage(hScrollBars[i], WM_HSCROLL, SB_LINELEFT, 0);
                    break;
                case VK_DOWN :
                    SendMessage(hScrollBars[i], WM_HSCROLL, SB_LINERIGHT, 0);
                    break;
            }
            return 0;
        case WM_HOTKEY:
            switch(wParam) {
                case HK_CTRL_X:
                    PostQuitMessage (0) ;
                    break;
                case HK_CRTL_SPACE:
                    SetRandomColor(hwnd, color, rect);
                    break;
            }
            break;
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

BOOL CALLBACK RenameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEditControl;
    int index, iTextLength;
    TCHAR *szText;

    switch(message) {
        case WM_INITDIALOG:
            hEditControl = GetDlgItem(hDlg, ID_EDIT) ;
            SetFocus(hEditControl) ;
            return FALSE ;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case ID_DIALOG_RENAME:
                    iTextLength = (UINT) SendMessage(hEditControl, WM_GETTEXTLENGTH, 0, 0) ;
                    szText = (char*)malloc(iTextLength+1);
                    SendMessage(hEditControl, WM_GETTEXT, (WPARAM) (iTextLength + 1), (LPARAM)szText) ;
                    index = (int) SendMessage(hListBox, LB_GETCURSEL, 0, 0) ;
                    SendMessage(hListBox, LB_DELETESTRING, 0, 0);
                    SendMessage(hListBox, LB_INSERTSTRING, index, (LPARAM) szText);
                    SendMessage(hEditControl, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    EndDialog (hDlg, TRUE) ;
                    return TRUE;
            }
    }
    return FALSE; ;
}


void createWindows(HWND hwnd) {
    static TCHAR * szColorLabel[] = {(TCHAR *)("Red"), (TCHAR *)("Green"), (TCHAR *)("Blue")} ;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hListBox = CreateWindowExW(WS_EX_CLIENTEDGE,
           L"LISTBOX", NULL,
           WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | LBS_HASSTRINGS,
           7, 35, 200, 200,
           hwnd, (HMENU)IDC_LIST_BOX, hInstance, NULL);

    hNewItem = CreateWindow(
            TEXT("Edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            5, 5, 200, 20, hwnd,
            (HMENU)ID_NEW_ITEM,
            GetModuleHandle(NULL),
            NULL);

    SetFocus(hNewItem);

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

    CreateWindow(
            TEXT("SCROLLBasc"),
            (LPCTSTR) NULL,
            WS_CHILD | WS_BORDER| WS_VISIBLE,
            100, 100, 400, 400,
            hwnd,
            (HMENU)(ID_CHILD_WINDOW),
            hInstance,
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
}

void SetRandomColor(HWND hwnd, int *color, RECT rect) {
    TCHAR szBuffer [40] ;
    for (int i = 0; i < 3; ++i) {
        color[i] = rand() % 255;
        SetScrollPos (hScrollBars[i], SB_CTL, color[i], TRUE) ;
        wsprintf (szBuffer, TEXT ("%i"), color[i]) ;
        SetWindowText (hValue[i], szBuffer) ;
    }
    hBrushStatic = CreateSolidBrush(RGB(color[0], color[1], color[2])) ;
    DeleteObject((HBRUSH)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) hBrushStatic)) ;
    InvalidateRect (hwnd, &rect, TRUE) ;
}
