#include <iostream>
#include <GL/glut.h>
using namespace std;

void init ()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // Set display-window color to white
    glMatrixMode(GL_PROJECTION);            // Set projection parameters
    gluOrtho2D(-360, 360, -270, 270);       // To define coordinate reference (LRBT) frame within the display window
}

void displayPoint (float x, float y)
{
    glColor3f(0, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void ddaLine (float x1, float y1, float x2, float y2)
{
    float step;

    float dx = x2 - x1;
    float dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    float xinc = dx / (float)step;
    float yinc = dy / (float)step;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++)
    {
        displayPoint(x, y);
        x = x + xinc;
        y = y + yinc;
    }
}

void ddaDashDotLine (float x1, float y1, float x2, float y2)
{
    float step;

    float dx = x2 - x1;
    float dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    float xinc = dx / (float)step;
    float yinc = dy / (float)step;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++)
    {
        // In a group of 15 pixels, 8 will form a line (dash), 1 will form a dot,
        // remaining 6 are off and hence provide space between dash and dot.
        // Here, i%15 == 1, 2, 3, 12, 13, 14 are off pixels adjecent to i%15 == 0 pixel.
        if (i%15 == 4 || i%15 == 5 || i%15 == 6 || i%15 == 7 || i%15 == 8 || i%15 == 9 || i%15 == 10 || i%15 == 11)
            displayPoint(x, y);
        else if (i%15 == 0)
            displayPoint(x, y);
        x = x + xinc;
        y = y + yinc;
    }
}

void ddaDashLine (float x1, float y1, float x2, float y2)
{
    float step;

    float dx = x2 - x1;
    float dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    float xinc = dx / (float)step;
    float yinc = dy / (float)step;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++)
    {
        // Here, we only need line (dash) and spaces.
        // Therefore in a group of 11 pixels, i%11 == 0, 1, 2 are three off pixels
        // and the remaining form a straigh line (dash).
        if (i%11 == 3 || i%11 == 4 || i%11 == 5 || i%11 == 6 || i%11 == 7 || i%11 == 8 || i%11 == 9 || i%11 == 10)
            displayPoint(x, y);
        x = x + xinc;
        y = y + yinc;
    }
}

float x01, y01, x02, y02;
int choice;
void drawing ()
{
    glClear(GL_COLOR_BUFFER_BIT);           // Clear display window
   
    // Dividing the screen in four quadrants by drawning
    // two intersecting axes
    glColor3f(0.0, 1.0, 0.0);               // Coloring the axes Green
    glBegin(GL_LINES);
        glVertex2f(-360, 0);
        glVertex2f(360, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0, 270);
        glVertex2f(0, -270);
    glEnd();
   
    switch (choice)
    {
        case 1:
            ddaDashDotLine(x01, y01, x02, y02);
            break;
        case 2:
            ddaDashLine(x01, y01, x02, y02);
            break;
        default:
            break;
    }

    glFlush();                                      // Process all OpenGL routines as quickly as possible (To put changed pixel in frame buffer)
}

int main (int argc, char **argv)                    // argc -> argument counter, argv -> argument vector
{
    // Choosing Dash-Dot-Dash or Dash Line
    cout << "Dash-Dot-Dash / Dash Line using DDA" << endl;
    cout << "Enter 1 for Dash-Dot-Dash Line";
    cout << "\nEnter 2 for Dash Line" << endl;
    cin >> choice;

    // Coordinate inputs
    cout << "\nEnter the float coordinates of the points P1 and P2" << endl;
    cout << "Note that the x values range from -360 to 360 and y values from -270 to 270" << endl;
    cout << "(x, y) for P1: ";
    cin >> x01 >> y01;
    cout << "(x, y) for P2: ";
    cin >> x02 >> y02;

    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);    // Set display mode
    glutInitWindowPosition(50, 100);                // Set top-left display-window position
    glutInitWindowSize(720, 540);                   // Set display-window width and height
    glutCreateWindow("CGL QB Q3");                  // Create display window
   
    init();                                         // Execute initialization procedure
    glutDisplayFunc(drawing);                       // Send graphics to display window
    glutMainLoop();

    return 0;
}

	

