#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;

//int cx = 300;
//int cy = 300;
//int r = 70;
bool flag = 1;

void DisplayPoint(int x, int y)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}    

void initialize(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
}

void octant(int xc, int yc, int x, int y)
{
    DisplayPoint(xc + x, yc + y);
    DisplayPoint(xc + y, yc + x);
    DisplayPoint(xc + y, yc - x);
    DisplayPoint(xc + x, yc - y);
    DisplayPoint(xc - x, yc - y);
    DisplayPoint(xc - y, yc - x);
    DisplayPoint(xc - y, yc + x);
    DisplayPoint(xc - x, yc + y);
}

void circleMP(int xc, int yc, int r)
{
    int p = 1 - r, x = 0, y = r;
    // loop til the x become y equal to radius (r,r)
    while (x < y)
    {
        octant(xc, yc, x, y);
        x++;
        if (p > 0)
        {
            // if p>0 decrement the y and 2(x-y)+1
            y--;
            p += 2 * (x - y) + 1;
        }
        else
        {
            // if p<=0 add 2x+1 to p
            p += 2 * x + 1;
        }
    }
}

// convert the rad to deg
double ang(int q)
{
    return (double)q * 3.142 / 180;
}

void drawcircles(int x, int y, int r)
{
    // circleMP(x,y,r);
    circleMP(x + 2 * r, y, 0.26 * r);
    circleMP(x - 2 * r, y, 0.26 * r);
    circleMP(x + 2 * r * cos(ang(90)), y + 2 * r * sin(ang(90)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(75)), y + 2 * r * sin(ang(75)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(45)), y + 2 * r * sin(ang(45)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(30)), y + 2 * r * sin(ang(30)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(15)), y + 2 * r * sin(ang(15)), 0.26 * r);

    circleMP(x - 2 * r * cos(ang(75)), y + 2 * r * sin(ang(75)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(30)), y + 2 * r * sin(ang(30)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(45)), y + 2 * r * sin(ang(45)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(15)), y + 2 * r * sin(ang(15)), 0.26 * r);

    circleMP(x - 2 * r * cos(ang(90)), y - 2 * r * sin(ang(90)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(75)), y - 2 * r * sin(ang(75)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(45)), y - 2 * r * sin(ang(45)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(30)), y - 2 * r * sin(ang(30)), 0.26 * r);
    circleMP(x - 2 * r * cos(ang(15)), y - 2 * r * sin(ang(15)), 0.26 * r);

    circleMP(x + 2 * r * cos(ang(75)), y - 2 * r * sin(ang(75)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(30)), y - 2 * r * sin(ang(30)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(45)), y - 2 * r * sin(ang(45)), 0.26 * r);
    circleMP(x + 2 * r * cos(ang(15)), y - 2 * r * sin(ang(15)), 0.26 * r);

    circleMP(x, y, 1.75 * r);
    circleMP(x, y, 1.6 * r);
}

void renderFunction(void)
{
    glColor3f(1, 1, 1);
    glPointSize(2);
    drawcircles(300, 300, 50);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Circle");
    initialize();
    glutDisplayFunc(renderFunction);
    glutAddMenuEntry("Draw", 1);
    glutAddMenuEntry("Clear", 2);
    glutAddMenuEntry("Color Fill", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
