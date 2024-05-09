#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<pair<float, float>> points(12);
int cc = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 1280, 0, 720);
    points[0].first = 525; points[0].second = 305;
    points[1].first = 525; points[1].second = 335;
    points[2].first = 625; points[2].second = 335;
    points[3].first = 625; points[3].second = 435;
    points[4].first = 655; points[4].second = 435;
    points[5].first = 655; points[5].second = 335;
    points[6].first = 755; points[6].second = 335;
    points[7].first = 755; points[7].second = 305;
    points[8].first = 655; points[8].second = 305;
    points[9].first = 655; points[9].second = 205;
    points[10].first = 625; points[10].second = 205;
    points[11].first = 625; points[11].second = 305;
}

void rotate()
{
    float angle = 45 * 3.14 / 180;
    float tx = 640;
    float ty = 320;
    float x, y;
    
    for(int i=0;i<12;i++)
    {
        x = points[i].first;
        y = points[i].second;
        
        points[i].first = (x-tx)*cos(angle) - (y-ty)*sin(angle) + tx;
        points[i].second = (x-tx)*sin(angle) + (y-ty)*cos(angle) + ty;
    }
}

void draw()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<12;i++)
        {
            glVertex2i(round(points[i].first), round(points[i].second));
        }
    glEnd();
    glFlush();
}

void display()
{
    draw();
    glutSwapBuffers();
}

struct pixel
{
    GLubyte r, g, b;
};

pixel fc, bc, c;

void boundaryFill(int x, int y)
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
    fc.r = 255;
    fc.g = 255;
    fc.b = 0;
    if((c.r != bc.r || c.g != bc.g || c.b != bc.b) && (c.r != fc.r || c.g != fc.g || c.b != fc.b))
    {
        glColor3ub(fc.r, fc.g, fc.b);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
        glFlush();
        
        boundaryFill(x+1, y);
        boundaryFill(x-1, y);
        boundaryFill(x, y+1);
        boundaryFill(x, y-1);
    }
}

void mouseClick(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(cc == 0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            rotate();
            draw();
            cc++;
        }
        else if(cc == 1)
        {
            boundaryFill(640, 320);
            cc++;
        }
        glutSwapBuffers();
    }
}

int main(int argc, char** argv)
{
    bc.r = bc.g = bc.b = 255;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(320, 180);
    glutCreateWindow("Rotation & Colour Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
