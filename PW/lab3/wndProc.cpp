//
// Created by Vitiok on 5/8/2016.
//
#include <windows.h>
#include "resource.h"
#include "Line.h"
void setCurrentDrawing(Line *) ;
Line *currentLine = new Line();

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    POINT currentPosition;
    RECT rc;
    HPEN hNewPen;
    int weight;

    switch(message) {
        case WM_CREATE:
            RegisterHotKey(hWnd, IDHK_ABOUT, MOD_CONTROL, 0x41);
            RegisterHotKey(hWnd, IDHK_EXIT, MOD_CONTROL, 0x58);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rc);
            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
            switch(wParam) {
                case ID_DRAW_LINE:
                    hdc = GetDC(hWnd) ;
                    GetClientRect(hWnd, &rc) ;
                    Line *newLine;
                    newLine = new Line();
                    newLine->setIsDrawing(TRUE);
                    setCurrentDrawing(newLine);
                    InvalidateRect(hWnd, &rc, TRUE);
                    ReleaseDC(hWnd, hdc);
                    break;
                case ID_INCREASE_WEIGHT:
                    currentLine->modifyWeight(TRUE);
                    break;
                case ID_DECREASE_WEIGHT:
                    currentLine->modifyWeight(FALSE);
                    break;
            }
            break;
        case WM_LBUTTONDOWN:
            if (currentLine != NULL) {
                GetCursorPos(&currentPosition);
                ScreenToClient(hWnd, &currentPosition);
                TCHAR szBuffer1 [20] ;
                hdc = GetDC(hWnd);
                wsprintf (szBuffer1, TEXT ("x:%i y:%i"), currentPosition.x, currentPosition.y) ;
                TextOut(hdc, 200, 200, szBuffer1, 10) ;
                currentLine->setStart(currentPosition);
            }
            break;
        case WM_LBUTTONUP:
            if (currentLine->getIsDrawing() == TRUE) {
                GetCursorPos(&currentPosition);
                ScreenToClient(hWnd, &currentPosition);
                TCHAR szBuffer2 [20] ;
                hdc = GetDC(hWnd);
                wsprintf (szBuffer2, TEXT ("x:%i y:%i"), currentPosition.x, currentPosition.y) ;
                TextOut(hdc, 200, 240, szBuffer2, 10) ;
                currentLine->setEnd(currentPosition);
                currentLine->Draw(hdc) ;
                InvalidateRect(hWnd, &rc, TRUE);
            }
            break;
        case WM_HOTKEY:
            switch(wParam) {
                case IDHK_ABOUT:
                    MessageBox(hWnd, TEXT("Draw app. Use menu to draw something"), MB_OK, MB_ICONINFORMATION);
                    break;
                case IDHK_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc (hWnd, message, wParam, lParam) ;
}

void setCurrentDrawing(Line *newLine) {
    currentLine = newLine;
}