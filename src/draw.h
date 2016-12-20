#ifndef DRAW_H_INCLUDED
    #define DRAW_H_INCLUDED

    #define _USE_MATH_DEFINES

    #include <gl/gl.h>
    #include <math.h>
    #include <stdlib.h>
    #define M_PI (acos(-1))
    void drawCursor(double x, double y);
    void setCursor(double aa, double bb);
    void drawLine(float x1, float y1, float x2, float y2);
    void draw();
    void generateLine(double x, double y);
    void draw_init();
#endif // DRAW_H_INCLUDED
