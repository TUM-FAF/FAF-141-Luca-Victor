//
// Created by Vitiok on 5/8/2016.
//
#include <windows.h>

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;

    switch(message) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rc);
            DrawText (hdc, TEXT ("Hello World!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc (hWnd, message, wParam, lParam) ;
}
