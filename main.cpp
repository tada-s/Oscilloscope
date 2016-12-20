#include "main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    bool flagMLoop;

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    HDC hDC;
    HGLRC hRC;

    //Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_OWNDC;;
    wc.lpfnWndProc   = wndproc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "windowClass1";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        wc.lpszClassName,
        "OpenGL",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL,
        hInstance,
        NULL);

    if(hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    EnableOpenGL(hwnd,&hDC,&hRC);

    draw_init();

    flagMLoop = true;
    int lx=0, ly=0;
    while(flagMLoop){
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT){
                flagMLoop = false;
            }else{
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }else{
            if(inputKeyboard['A']) printf("A!\n");
            if(inputKeyboard['Q']) DestroyWindow(hwnd);
            float mx= inputMouse.x / ( (float)(SCREEN_WIDTH) / 2 ) - 1, my = -(inputMouse.y / ( (float)(SCREEN_HEIGHT) / 2 ) - 1);
            draw();
            //drawCursor(mx,my);
            if(inputMouse.lButton){
                generateLine(mx, my);
                drawLine(
                    lx / ( (float)(SCREEN_WIDTH) / 2 ) - 1,
                    -(ly / ( (float)(SCREEN_HEIGHT) / 2 ) - 1),
                    mx,
                    my
                     );
            };
            setCursor(mx,my);

            SwapBuffers(hDC);

            lx = inputMouse.x;
            ly = inputMouse.y;
            Sleep(10);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    return msg.wParam;
}






