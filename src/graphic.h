#ifndef GRAPHIC_H_INCLUDED
    #define GRAPHIC_H_INCLUDED

    #include <windows.h>

    void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);
    void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC);

#endif // GRAPHIC_H_INCLUDED
