#ifndef WNDPROC_H_INCLUDED
    #define WNDPROC_H_INCLUDED

    #include <windows.h>
    #include <stdio.h>

    #include "wndproc_input.h"

    LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif // WNDPROC_H_INCLUDED
