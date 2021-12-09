#include <GL/glut.h>
#include <iostream>

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
    glVertex2i(150, 0);
    glColor3f(0, 1, 1);

    glVertex2i(150, 100);
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
    glRotated(.04f, 0, 0, 1);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    w0 = glutCreateWindow("w0");
    init();
    glutDisplayFunc(display0);
    w1 = glutCreateWindow("w1");
    init();
    glutDisplayFunc(display0);
    glutMouseFunc(mouse1);
    glutIdleFunc(idle1);
    glutMainLoop();
    return 0;
}
