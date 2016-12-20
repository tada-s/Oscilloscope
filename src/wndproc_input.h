#ifndef WNDPROC_INPUT_H_INCLUDED
    #define WNDPROC_INPUT_H_INCLUDED

    #include <windows.h>
    #include <stdio.h>

    LRESULT inputproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    typedef struct {
        int x, y;
        bool lButton, mButton, rButton;
    } inpMouse;

    extern inpMouse inputMouse;
    extern bool inputKeyboard[sizeof(WPARAM)];

#endif // WNDPROC_INPUT_H_INCLUDED
