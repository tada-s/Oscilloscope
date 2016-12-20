#include "wndproc_input.h"

inpMouse inputMouse;
bool inputKeyboard[sizeof(WPARAM)];

void updateMouseCoord(POINTS p){
    inputMouse.x = p.x;
    inputMouse.y = p.y;
}

LRESULT inputproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
    // Mouse_Down
    case WM_LBUTTONDOWN:
        inputMouse.lButton = true;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    case WM_RBUTTONDOWN:
        inputMouse.rButton = true;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    case WM_MBUTTONDOWN:
        inputMouse.mButton = true;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    // Mouse_Up
    case WM_LBUTTONUP:
        inputMouse.lButton = false;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    case WM_RBUTTONUP:
        inputMouse.rButton = false;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    case WM_MBUTTONUP:
        inputMouse.mButton = false;
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    case WM_MOUSEMOVE:
        updateMouseCoord(MAKEPOINTS(lParam));
        return 0;
    // Key_Down
    case WM_KEYDOWN:
        inputKeyboard[wParam] = true;
        return 0;
    case WM_KEYUP:
        inputKeyboard[wParam] = false;
        return 0;
    default:
        return -1;
    }
}
