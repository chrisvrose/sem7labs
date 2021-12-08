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
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}
void display(bool);
void display0() { display(false); }
void display1() { display(true); }

void display(bool isWin1)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    if (isWin1)
        cylinderDraw();
    else
        parallelepiped_draw();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    uint w0 = glutCreateWindow("Cylinder,parallelePiped Disp by Extruding Circle &Quadrilaterl ");
    init();
    glutDisplayFunc(display0);
    uint w1 = glutCreateWindow("Cylinder,parallelePiped Disp by Extruding Circle &Quadrilaterl ");
    init();
    glutDisplayFunc(display1);
    glutMainLoop();
    return 0;
}
