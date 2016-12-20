#include "draw.h"

double la=.5, lb=.5;
double a=.5, b=.5;
double cursorX=.5, cursorY=.5;

double lineLife = 0;
double line_X = 0;
double line_Y = 0;



#define DRAW_SAMPLE 100
double p1x[DRAW_SAMPLE];
double p1y[DRAW_SAMPLE];
double p2x[DRAW_SAMPLE];
double p2y[DRAW_SAMPLE];
double p3x[DRAW_SAMPLE];
double p3y[DRAW_SAMPLE];
double p4x[DRAW_SAMPLE];
double p4y[DRAW_SAMPLE];
/*
float curveColorR = 0.8;
float curveColorG = 1;
float curveColorB = 1;
float backGroundColorR = 0.0;
float backGroundColorG = 0.2;
float backGroundColorB = 0.2;
*/

float curveColorR = 0;
float curveColorG = 1;
float curveColorB = 0;
float cursorCurveColorR = .2;
float cursorCurveColorG = .6;
float cursorCurveColorB = .2;
float backGroundColorR = 0.0;
float backGroundColorG = 0.1;
float backGroundColorB = 0.0;

/*
float curveColorR = 0;
float curveColorG = 0;
float curveColorB = 1;
float backGroundColorR = 0.0;
float backGroundColorG = 0.0;
float backGroundColorB = 0.0;
*/

void draw_init(){
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    double delta = 2*M_PI/DRAW_SAMPLE;

    for(int i = 0; i < DRAW_SAMPLE; i++){
        double t = (i)*delta-M_PI;
        //curve1
        p1x[i] = (sqrt(2) * cos(t) / (sin(t)*sin(t) + 1)) * 2 / 10;
        p1y[i] = (sqrt(2) * cos(t) * sin(t) / (sin(t)*sin(t) + 1)) * 2 / 10;
        //curve2
        p2x[i] = (2 * cos(t) + cos(2*t)) / 10;
        p2y[i] = (2 * sin(t) - sin(2*t)) / 10;
        //curve3
        p3x[i] = ((exp(cos(t)) - 2 * cos(4 * t)) * cos(t) ) / 10;
        p3y[i] = ( (exp(cos(t)) - 2 * cos(4 * t)) * sin(t) ) / 10;
        //curve4
        p4x[i] = ( cos(t) ) * 4 / 10;
        p4y[i] = ( sin(t) ) * 4 / 10;
    }



    glClear(GL_ACCUM_BUFFER_BIT);
}

void generateLine(double x, double y){
    line_X = x;
    line_Y = y;
    lineLife = 1;
}

void setCursor(double x, double y){
    cursorX = x; cursorY = y;
}

void drawCursor(double x, double y){
    glLineWidth(1.0);
    glColor4f(curveColorR,curveColorG,curveColorB,1);
    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(x,y-.075);
        glVertex2f(x,y);
        glVertex2f(x+.04,y-0.06);
        glVertex2f(x,y-.075);
        glVertex2f(x+.04,y-0.06);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2){
    glColor4f(curveColorR,curveColorG,curveColorB,1);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
}
/*
double px1(double t){ return (sqrt(2) * cos(t) / (sin(t)*sin(t) + 1)) * 2 / 10; }
double py1(double t){ return (sqrt(2) * cos(t) * sin(t) / (sin(t)*sin(t) + 1)) * 2 / 10; }

double px2(double t){ return (2 * cos(t) + cos(2*t)) / 10; }
double py2(double t){ return (2 * sin(t) - sin(2*t)) / 10; }

double px3(double t){ return ( (exp(cos(t)) - 2 * cos(4 * t)) * cos(t) ) / 10; }
double py3(double t){ return ( (exp(cos(t)) - 2 * cos(4 * t)) * sin(t) ) / 10; }

double px4(double t){ return ( cos(t) ) * 4 / 10; }
double py4(double t){ return ( sin(t) ) * 4 / 10; }
*/
double xx(int t){ return ( p1x[t] * (b-.5) + p2x[t] * (b+.5) )*(a-.5) + ( p3x[t] * (b-.5) + p4x[t] * (b+.5) )*(a+.5); }
double yy(int t){ return ( p1y[t] * (b-.5) + p2y[t] * (b+.5) )*(a-.5) + ( p3y[t] * (b-.5) + p4y[t] * (b+.5) )*(a+.5); }

void draw(){


    glClearColor(backGroundColorR, backGroundColorG, backGroundColorB, 255);
    glClear(GL_COLOR_BUFFER_BIT);

    //glAccum(GL_RETURN, .3);


    double beta = .1;




    // Surface
    for(int t = 0; t < DRAW_SAMPLE; t++){
        glBegin(GL_QUADS);
            //l1

            glColor4f(curveColorR, curveColorG, curveColorB, .08);
            a = la;
            b = lb;
            glVertex2f(xx(t),yy(t));
            glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
            glColor4f(curveColorR, curveColorG, curveColorB, 0);
            a = cursorX+beta;
            b = cursorY+beta;
            glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
            glVertex2f(xx(t),yy(t));

            //l2
            glColor4f(curveColorR, curveColorG, curveColorB, .08);
            a = la;
            b = lb;
            glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
            glVertex2f(xx(t),yy(t));
            glColor4f(curveColorR, curveColorG, curveColorB, 0);
            a = (la - cursorX)*.5+la-beta;
            b = (lb - cursorY)*.5+lb-beta;
            glVertex2f(xx(t),yy(t));
            glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
        glEnd();
    }

    //cursor

    if(lineLife > 0){
        // LifeCurve

        glLineWidth(2.0);
        glColor4f(cursorCurveColorR, cursorCurveColorG, cursorCurveColorB, lineLife);
        for(int t = 0; t < DRAW_SAMPLE; t ++){
            glBegin(GL_LINES);
        a = line_X;
        b = line_Y;
                glVertex2f(xx(t),yy(t));
                glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
            glEnd();
        }

        line_X += 0.005;
        line_Y += 0.005;

        lineLife -= 0.02;
    }

    // Curve
    a = cursorX;
    b = cursorY;

    glLineWidth(2.0);
    glColor4f(curveColorR, curveColorG, curveColorB, 255);
    for(int t = 0; t < DRAW_SAMPLE; t ++){
        glBegin(GL_LINES);
            a = la;
            b = lb;
            glVertex2f(xx(t),yy(t));
            glVertex2f(xx((t+1)%DRAW_SAMPLE),yy((t+1)%DRAW_SAMPLE));
        glEnd();
    }

/*
    glLineWidth(8.0);
    glColor4ub(0, 255, 0, 10);
    for(double t = -M_PI; t < M_PI; t += delta){
        glBegin(GL_LINES);
            a = la;
            b = lb;
            glVertex2f(xx(t),yy(t));
            glVertex2f(xx(t+delta),yy(t+delta));
        glEnd();
    }*/


    // V(n+1) = ( V(n) - V(n-1) ) * k + V(n-1)
    la = (cursorX - la)/8 + la;
    lb = (cursorY - lb)/8 + lb;

    //Osciloscope grid
    glLineWidth(1.7);
    glColor4ub(0, 0, 0, 100);
    glBegin(GL_LINES);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(0,-1);
        glVertex2f(0,1);
    glEnd();
    glLineWidth(0.7);
    for(double i = -1; i < 1; i+= .05){
        glBegin(GL_LINES);
            glVertex2f(-0.01,i);
            glVertex2f(0.01,i);
            glVertex2f(i,-0.01);
            glVertex2f(i,0.01);
        glEnd();
    }
    for(double i = -1; i < 1; i+= .25){
        glBegin(GL_LINES);
            glVertex2f(-1,i);
            glVertex2f(1,i);
            glVertex2f(i,-1);
            glVertex2f(i,1);
        glEnd();
    }

/*
    glClear(GL_ACCUM_BUFFER_BIT);
    glAccum(GL_ACCUM, 1.0);
    glAccum(GL_RETURN,1.0);*/

}
