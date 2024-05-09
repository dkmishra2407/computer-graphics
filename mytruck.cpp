#include<iostream>
#include<cmath> // Include cmath for abs() and round()
#include<GL/gl.h>
#include<GL/glut.h>

void display(int x,int y){
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void init(){
    gluOrtho2D(0,1000,0,600);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void dda(int x1,int y1,int x2,int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;
    if(std::abs(dx) > std::abs(dy)){ // Use std::abs() from cmath
        steps = std::abs(dx);
    }
    else{
        steps = std::abs(dy);
    }

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;
    float x = x1;
    float y = y1;
    display(x, y);
    for(int i = 0; i < steps; i++){
        x += xinc;
        y += yinc;
        display(std::round(x), std::round(y)); // Use std::round() from cmath
    }
}

void octant(int xc,int yc,int x,int y){
     display(xc+x,yc+y);
     display(xc+y,yc+x);
     display(xc-x,yc+y);
     display(xc-y,yc+x);
     display(xc-x,yc-y);
     display(xc-y,yc-x);
     display(xc+x,yc-y);
     display(xc+y,yc-x);
}

double ang(int q)
{
    return (double)q * 3.142 / 180;
}     

void circleMP(int xc,int yc,int r){
    int x = 0;
    int y = r;
    
    int d = 3 - 2 * r;
    
    do{
       octant(xc,yc,x,y);
        if(d>=0){
            d = d + 4 * (x-y) + 10;
            y--;
        }
        else{
            d = d + 4 * x + 6;
        }
        x++;
    }while(x<y);
}

void bangel(int x,int y,int r){

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

void draw(){
    glBegin(GL_POINTS);
    dda(100,100,500,100);
    dda(500,100,500,500);
    dda(500,500,100,500);
    dda(100,500,100,100);
    circleMP(200,50,50);
    circleMP(400,50,50);
    circleMP(200,50,30);
    circleMP(400,50,30);
    dda(535,100,535,500);
    dda(535,100,900,100);
    circleMP(650,50,50);
    circleMP(650,50,30);
    circleMP(820,50,50);
    circleMP(820,50,30);
    dda(535,500,635,500);
    dda(635,500,635,400);
    dda(635,400,770,400);
    dda(770,400,900,250);
    dda(900,250,900,100);
    dda(635,350,635,250);
    dda(635,250,750,250);
    dda(750,250,750,350);
    dda(750,350,635,350);
    glEnd();
    glFlush();
}

int main(int argc,char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Circle Drawing");
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(0,0);
    init();
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}

