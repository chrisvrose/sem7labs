#include <GL/glut.h>
#include <iostream>

void plotpixels(int h, int k, int x, int y, float color[3])
{
    glColor3fv(color);

    glBegin(GL_POINTS);

    glVertex2i(x + h, y + k);
    glVertex2i(-x + h, y + k);
    glVertex2i(-x + h, -y + k);
    glVertex2i(x + h, -y + k);

    glVertex2i(y + h, x + k);
    glVertex2i(-y + h, x + k);
    glVertex2i(-y + h, -x + k);
    glVertex2i(y + h, -x + k);

    glEnd();
}

void circleDraw(int h, int k, int r, float color[3])
{
    int x = 0, y = r, d = 3 - 2 * r;

    while (x < y) {
        plotpixels(h, k, x, y, color);
        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    plotpixels(h, k, x, y, color);
}

void cylinderDraw()
{
    int xc = 100, yc = 100, r = 50, i, n = 50;
    float color0[3] = { 1, 0, 0 };
    float color1[3] = { .6, 1, .6 };
    for (i = 0; i < n; i++) {
        if (i == 0 || i == n - 2) {
            circleDraw(xc, yc + i, r, color0);
        } else
            circleDraw(xc, yc + i, r, color1);
    }
}

void parallelepiped(int x1, int x2, int y1, int y2)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

void parallelepiped_draw()
{
    int x1 = 200, x2 = 300, y1 = 100, y2 = 175, i, n = 40;
    for (i = 0; i < n; i += 2)
        parallelepiped(x1 + i, x2 + i, y1 + i, y2 + i);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0-200, 400.0-200, 0.00-200, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void display0()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2i(0, 0);
    glColor3f(1, 1, 0);
    glVertex2i(100, 0);
    glColor3f(0, 1, 1);

    glVertex2i(100, 100);
    glColor3f(1, 0, 1);
    glVertex2i(0, 100);
    glEnd();

    glFlush();
}
void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2i(0, 0);
    glColor3f(1, 1, 0);
    glVertex2i(100, 0);
    glColor3f(0, 1, 1);

    glVertex2i(100, 100);
    glColor3f(1, 0, 1);
    glVertex2i(0, 100);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

uint w0, w1;
void idle1()
{
    glutSetWindow(w1);
    glMatrixMode(GL_MODELVIEW);
    glRotated(.1f, 0, 0, 1);
    glutPostRedisplay();
}

void mouse1(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutIdleFunc(idle1);
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glutIdleFunc(nullptr);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    w0 = glutCreateWindow("w0");
    init();
    glutDisplayFunc(display0);
    w1 = glutCreateWindow("w1");
    init();
    glutDisplayFunc(display1);
    glutMouseFunc(mouse1);
    glutIdleFunc(idle1);
    glutMainLoop();
    return 0;
}
