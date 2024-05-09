#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;

void initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 600, 0, 600);
    glClear(GL_COLOR_BUFFER_BIT);
}

void display(int x, int y){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

double ang(int a){
    return 3.14/180*a;
}
void octant(int xc,int yh,int x,int y){
    display(xc+x,yh+y);
    display(xc-x,yh+y);
    display(xc-x,yh-y);
    display(xc+x,yh-y);
    display(xc+y,yh+x);
    display(xc-y,yh+x);
    display(xc-y,yh-x);
    display(xc+y,yh-x);
}

void circleMP(int xc,int yc,int r){

    int x = 0;
    int y = r;
    
    int d = 3 - 2 * r;
    
    while(x<y){
       octant(xc,yc,x,y);
       if(d>=0){
           y--;
           d = d + 4 * (x-y) + 10;
       }
       else{
          d = d + 4 * x+ 6;
       }
       x++;
    }
    
}

void bangel(int x,int y,int r){
    
    circleMP(x + 1* r, y,  r);
    circleMP(x + 1* r*cos(90), y + 1 * r*sin(90),  r);
    circleMP(x - 1* r*cos(90), y - 1 * r*sin(90),  r);
    circleMP(x + 1* r*cos(90), y - 1 * r*sin(90),  r);
    circleMP(x - 1* r*cos(90), y + 1 * r*sin(90),  r);
    circleMP(x - 1 * r, y,  r);
    circleMP(x, y, r);
    circleMP(x, y, 2 * r);   
}

void display(){
    glColor3f(1, 1, 1);
    glPointSize(2);
    bangel(300,300,100);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Circle");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
