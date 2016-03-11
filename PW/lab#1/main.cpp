#include <windows.h>

#define COLOR_BUTTON           100
#define TEXT_COLOR_BUTTON      101
#define TEXT_BUTTON            102
#define RECTANGLE_BUTTON       103
#define MOOD_BUTTON            104

const char ClassName[] = "MyClass";
UINT Bkcounter = 0;
UINT Text_bk_color = 0;
HBRUSH myBrush;
PMINMAXINFO MinMaxInfo;
UINT button_width = 78;
UINT button_height = 32;
BOOL bRectangle, bgoodMood, bText;

void createButtons(HWND, UINT, UINT);
void drawFace(HDC, HPEN, HPEN, COLORREF);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    MSG Msg;        // message strucure
    HWND hwnd;      // handle window
    WNDCLASSEX wc;  // window structure

    wc.lpszMenuName  = NULL;                            // window have no menu
    wc.hInstance     = hInstance;                       // A handle to the instance that contains the window procedure for the class
    wc.lpszClassName = ClassName;                       // lpszClassName is a string, it specifies the window class name
    wc.cbSize        = sizeof(WNDCLASSEX);              // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX).
    wc.cbClsExtra    = 0;                               // Extra bytes to allocate following the window-class structure.
    wc.style         = CS_HREDRAW | CS_VREDRAW ;        // window style. Can be any combination of the Class Styles
    wc.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(77, 136, 255));// A handle to the class background brush. Add 1 always.
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);     // A handle to the class cursor.
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // A handle to the class icon. This member must be a handle to an icon resource.
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // A handle to a small icon that is associated with the window class
    wc.lpfnWndProc   = WndProc;                         // A pointer to the window procedure. You must use the CallWindowProc.

    if(!RegisterClassEx(&wc)) { // handle registration of window class
        MessageBox(NULL, "Window Registration Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            ClassName,
            "My First Window",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 750, 500,
            NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)    {
        MessageBox(NULL, "Window Creation Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); // Sets the specified window's show state
    UpdateWindow(hwnd); //updates the client area by sending WM_PAINT message

    while(GetMessage(&Msg, NULL, 0, 0))    {
        TranslateMessage(&Msg); //passes the msg structure back to Windows for some keyboard translation
        DispatchMessage(&Msg); // passes the msg structure back to Windows
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { //window procedure is always defined so
    HDC hDc;
    RECT rect;
    SIZE size;
    PAINTSTRUCT ps;
    COLORREF face_color = RGB(224, 81, 81);
    COLORREF BkButton = RGB(224, 81, 81);
    COLORREF BkColors[] = {RGB(117, 163, 209), RGB(255, 212, 82)};
    COLORREF TextColors[] = {RGB(0, 0, 0), RGB(255, 255, 255)};
    HPEN myPen, hOldPen, hFacePen;
    LPDRAWITEMSTRUCT pdis = (DRAWITEMSTRUCT*)lParam;
    char text[] = "You clicked me!";
    char new_text[] = "Never too late!";
    char szBtnText1[] = "Text";
    char szBtnText2[] = "Rectagle";
    HFONT fontOutputText;

    switch(iMsg)    {
        case WM_CREATE:
            createButtons(hwnd, button_width, button_height);
            break;

        case WM_GETMINMAXINFO:
            MinMaxInfo = (PMINMAXINFO)lParam;
            MinMaxInfo->ptMinTrackSize.x = 300;
            MinMaxInfo->ptMinTrackSize.y = 350;
            MinMaxInfo->ptMaxTrackSize.x = 900;
            MinMaxInfo->ptMaxTrackSize.y = 600;
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case COLOR_BUTTON:
                    Bkcounter++;
                    Bkcounter = Bkcounter % ARRAYSIZE(BkColors);
                    myBrush = CreateSolidBrush(BkColors[Bkcounter]);
                    break;
                case TEXT_COLOR_BUTTON:
                    Text_bk_color++;
                    Text_bk_color = Text_bk_color % ARRAYSIZE(TextColors);
                    break;
                case TEXT_BUTTON:
                    bText = !bText;
                    break;
                case RECTANGLE_BUTTON:
                    bRectangle = !bRectangle;
                    break;
                case MOOD_BUTTON:
                    bgoodMood = !bgoodMood;
                    break;
            }

            hDc = (HDC) GetDC(hwnd);
            InvalidateRect (hwnd, NULL, TRUE);
            ReleaseDC(hwnd, hDc);
            break;

        case WM_CLOSE:
            if (MessageBox(NULL, "Are you sure you want to quit?",
                           "Confirmation", MB_ICONQUESTION | MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
            break;

        case WM_DRAWITEM:
            if ((UINT)wParam == TEXT_BUTTON) {
                GetTextExtentPoint32(pdis->hDC, szBtnText1, (int) strlen(szBtnText1), &size);
                SetTextColor(pdis->hDC, RGB(51, 51, 51));
                SetBkColor(pdis->hDC, BkButton);

                ExtTextOut(
                    pdis->hDC,
                    ((pdis->rcItem.right - pdis->rcItem.left) - size.cx) / 2,
                    ((pdis->rcItem.bottom - pdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &pdis->rcItem,
                    szBtnText1,
                    strlen(szBtnText1),
                    NULL);

            } else if((UINT)wParam == RECTANGLE_BUTTON)  {
                GetTextExtentPoint32(pdis->hDC, szBtnText2, (int) strlen(szBtnText2), &size);
                SetTextColor(pdis->hDC, RGB(51, 51, 51));
                SetBkColor(pdis->hDC, BkButton);

                ExtTextOut(
                        pdis->hDC,
                        ((pdis->rcItem.right - pdis->rcItem.left) - size.cx) / 2,
                        ((pdis->rcItem.bottom - pdis->rcItem.top) - size.cy) / 2,
                        ETO_OPAQUE | ETO_CLIPPED,
                        &pdis->rcItem,
                        szBtnText2,
                        strlen(szBtnText2),
                        NULL);
            }
            DrawEdge(
                    pdis->hDC,
                    &pdis->rcItem,
                    (pdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_BUMP ),
                    BF_RECT);
            return TRUE;
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT:
            myBrush = CreateSolidBrush(BkColors[Bkcounter]);
            hDc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            FillRect(hDc, &rect,  myBrush);
            SetBkColor(hDc, BkColors[Bkcounter]);
            SetTextColor(hDc, TextColors[Text_bk_color]);
            DrawText (hDc, TEXT ("Done with Pride and Prejudice by Victor"),
                      -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
            if (bRectangle) {
                COLORREF rectangleColor = RGB(217, 65, 30);
                myPen = CreatePen(PS_SOLID, 2, rectangleColor);
                hOldPen = (HPEN)SelectObject(hDc, myPen);
                Rectangle(hDc, 130, 60, 255, 100);
                rect.left = 131;
                rect.top = 61;
                rect.right = 253;
                rect.bottom = 98;
                FillRect(hDc, &rect,  myBrush);
                SelectObject(hDc, hOldPen);
                DeleteObject(myPen);
            }
            if (bText) {
                TextOut(hDc, 140, 70, text, ARRAYSIZE(text));
            }
            fontOutputText = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
            SelectObject(hDc, fontOutputText);
            TextOut(hDc, 140, 140, new_text, ARRAYSIZE(new_text));
            drawFace(hDc, hFacePen, hOldPen, face_color);
            EndPaint (hwnd, &ps);
            return 0 ;

        default:
            return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }

    return 0;
};

void createButtons(HWND hwnd, UINT width, UINT height) {
    CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Text Color",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE,  // Styles
            20,         // x position
            20,         // y position
            width,        // Button width
            height,        // Button height
            hwnd,     // Parent window
            (HMENU)TEXT_COLOR_BUTTON,
            NULL,
            NULL);

    CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Color",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE,  // Styles
            20,         // x position
            60,         // y position
            width,        // Button width
            height,        // Button height
            hwnd,     // Parent window
            (HMENU)COLOR_BUTTON,
            NULL,
            NULL);

    CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Click ME",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_OWNERDRAW,  // Styles
            20,         // x position
            100,         // y position
            width,        // Button width
            height,        // Button height
            hwnd,     // Parent window
            (HMENU)TEXT_BUTTON,
            NULL,
            NULL);

    CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Rectangle",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_OWNERDRAW, // Styles
            20,         // x position
            140,         // y position
            width,        // Button width
            height,        // Button height
            hwnd,     // Parent window
            (HMENU)RECTANGLE_BUTTON,
            NULL,
            NULL);

    CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Mood",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE,  // Styles
            110,         // x position
            20,         // y position
            width,        // Button width
            height,        // Button height
            hwnd,     // Parent window
            (HMENU)MOOD_BUTTON,
            NULL,
            NULL);

}

void drawFace(HDC hdc, HPEN hFacePen,HPEN hOldPen, COLORREF face_color) {
    hFacePen = CreatePen(PS_SOLID, 3, face_color);
    hOldPen = (HPEN) SelectObject(hdc, hFacePen);
    Arc(hdc, 50, 200, 150, 300, 0, 0, 0, 0);
    Arc(hdc, 80, 230, 90, 240, 0, 0, 0, 0);
    Arc(hdc, 110, 230, 120, 240, 0, 0, 0, 0);
    if(bgoodMood) {
        Arc(hdc, 65, 215, 135, 285, 65, 260, 135, 260);
    } else {
        Arc(hdc, 65, 260, 135, 330, 135, 270, 65, 270);
    };
    SelectObject(hdc, hOldPen);
    DeleteObject(hFacePen);
}