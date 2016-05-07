//
// Created by Vitiok on 5/7/2016.
//

#ifndef LAB2_REGISTERCLASS_H
#define LAB2_REGISTERCLASS_H

#include <windows.h>
#include "resource.h"

static TCHAR szAppName[] = TEXT ("BESTAPP") ;
WNDCLASS wndClass ;

void RegisterClass(HINSTANCE hInstance, WNDPROC WndProc) {
    wndClass.style = CS_HREDRAW | CS_VREDRAW ;
    wndClass.lpfnWndProc = WndProc ;
    wndClass.cbClsExtra = 0 ;
    wndClass.cbWndExtra = 0 ;
    wndClass.hInstance = hInstance ;
    wndClass.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE(IDE_TARGET)) ;
    wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_TARGET)) ;
    wndClass.hbrBackground = CreateSolidBrush (RGB(0, 0, 0)) ;
    wndClass.lpszMenuName = MAKEINTRESOURCE(IDC_APPMENU) ;
    wndClass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndClass)) {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
    }
}
#endif //LAB2_REGISTERCLASS_H
