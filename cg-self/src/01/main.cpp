#include <GL/glut.h>
#include <iostream>

void draw_line(int x1, int x2, int y1, int y2, float color[3])
{
    int dx, dy, i, e, incx, incy, inc1, inc2, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < y1)
        incy = -1;
    x = x1;
    y = y1;
    glColor3fv(color);
    glBegin(GL_POINTS);
    if (dx == 0) {
        if (dy == 0) {
            glVertex2d(x1, y1);
        } else if (y1 > y2) {
            for (int i = y2; i <= y1; i++) {
                glVertex2i(x1, i);
            }
        } else {
            // y2>y1
            for (int i = y1; i <= y2; i++) {
                glVertex2i(x1, i);
            }
        }
    } else if (dy == 0) {
        if (x1 > x2) {
            for (int i = x2; i <= x1; i++) {
                glVertex2i(i, y1);
            }
        } else {
            // y2>y1
            for (int i = x1; i <= x2; i++) {
                glVertex2i(i, y1);
            }
        }
    } else if (dx > dy) {
        glVertex2i(x, y);
        e = 2 * dy - dy;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else {
                e += inc2;
            }
            x += incx;
            glVertex2i(x, y);
        }
    } else {

        glVertex2i(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
            glVertex2i(x, y);
        }
    }

    glEnd();
    glFlush();
}

// int x1,x2,y1,y2;
float color[3] = { 1, 1, 1 };

void displayLoop()
{
    // glClear(GL_COLOR_BUFFER_BIT);
    // draw_line(x1,x2,y1,y2,color);
}

void myinit()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 400, 0, 400, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    return;
}
int x1c, x2c, y1c, y2c;
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1c = x;
        y1c = 400 - y;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x2c = x;
        y2c = 400 - y;
        draw_line(x1c, x2c, y1c, y2c, color);
        printf("(%d,%d)->(%d,%d)\n",x1c,y1c,x2c,y2c);
    }
    glutPostRedisplay();
}
void keeb(u_char key, int x, int y)
{
    if (key == 'c') {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glutPostRedisplay();
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(400, 400);
    uint wid = glutCreateWindow("Hi");

    myinit();

    // std::cout<<"P1(x,y)?"<<std::endl;
    // std::cin>>x1>>y1;
    // std::cout<<"P2(x,y)?"<<std::endl;
    // std::cin>>x2>>y2;

    glutDisplayFunc(displayLoop);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keeb);
    glutMainLoop();
    return 0;
}