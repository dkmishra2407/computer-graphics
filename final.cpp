#include <GL/glut.h>
#include <iostream>
using namespace std;
        
int u1, v1, u2, v2;
int flag = 0;
int xl = 50, xh = 200, yl = 50, yh = 200;

struct code {
    int r, l, t, b;
};

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 640, 0, 480);
}

code get_code(int u, int v) {
    code c = {0, 0, 0, 0};

    if (u < xl)
        c.l = 1;

    if (u > xh)
        c.r = 1;

    if (v < yl)
        c.b = 1;

    if (v > yh)
        c.t = 1;

    return c;
}

void dis(float x, float y) {
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x, y);
    glEnd();
}

void bres(float u1, float v1, float u2, float v2) {
    float dx, dy, x = u1, y = v1, xi, yi;
    int steps, i;

    dx = u2 - u1;
    dy = v2 - v1;

    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    xi = dx / (float)steps;
    yi = dy / (float)steps;

    glBegin(GL_POINTS);
    glVertex2f(x, y);

    for (i = 0; i < steps; i++) {
        x += xi;
        y += yi;
        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
}

void draw() {
    glColor3f(1.0, 0.0, 0.0);
    bres(50, 50, 200, 50);
    bres(50, 50, 50, 200);
    bres(200, 50, 200, 200);
    bres(50, 200, 200, 200);
}

void cohen() {
    code c1, c2, c;
    float m;
    int xi, yi, flag;

    m = (float)(v2 - v1) / (u2 - u1);

    c1 = get_code(u1, v1);
    c2 = get_code(u2, v2);

    while (1) {
        if (c1.t == 0 && c2.t == 0 && c1.b == 0 && c2.b == 0 && c1.r == 0 && c2.r == 0 && c1.l == 0 && c2.l == 0)
            break;

        else if (((c1.t && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l)) != 0) {
            u1 = v1 = u2 = v2 = 0;
            break;
        }

        else {
            if (c1.l == 1 || c2.l == 1) {
                xi = xl;
                yi = v1 + m * (xl - u1);

                if (c1.l == 1)
                    flag = 0;
                else
                    flag = 1;
            } else if (c1.r == 1 || c2.r == 1) {
                xi = xh;
                yi = v1 + m * (xh - u1);

                if (c1.r == 1)
                    flag = 0;
                else
                    flag = 1;
            } else if (c1.b == 1 || c2.b == 1) {
                xi = u1 + ((1.0 / m) * (yl - v1));
                yi = yl;

                if (c1.b == 1)
                    flag = 0;
                else
                    flag = 1;
            } else if (c1.t == 1 || c2.t == 1) {
                xi = u1 + ((1.0 / m) * (yh - v1));
                yi = yh;

                if (c1.t == 1)
                    flag = 0;
                else
                    flag = 1;
            }

            c = get_code(xi, yi);

            if (flag == 0) {
                u1 = xi;
                v1 = yi;
                c1 = c;
            } else if (flag == 1) {
                u2 = xi;
                v2 = yi;
                c2 = c;
            }
        }
    }

    draw();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(u1, v1);
    glVertex2f(u2, v2);
    glEnd();

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && flag == 0) {
        u1 = x;
        v1 = 480 - y;
        flag = 1;
    } else if (state == GLUT_DOWN && flag == 1) {
        u2 = x;
        v2 = 480 - y;
        flag = 2;
        bres(u1, v1, u2, v2);
       
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') {
        display();
        flag = 0;
    }
    if (key == 'c') {
        glClear(GL_COLOR_BUFFER_BIT);
        cohen();
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Staircase Pattern");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

	

