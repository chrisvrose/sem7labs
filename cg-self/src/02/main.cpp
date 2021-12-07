#include <GL/glut.h>
#include <cmath>
#include <iostream>
int myinit()
{
    glClearColor(1, 0, 1, 1);

    glOrtho(0, 400, 0, 400, -10, 10);

    return 1;
}

void circleBresDraw(int h, int k, int x, int y, float color[3])
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

void circleBres(int h, int k, int r, float color[3])
{
    int x = 0, y = r, d = 3 - 2 * r;

    while (x < y) {
        circleBresDraw(h, k, x, y, color);
        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    circleBresDraw(h, k, x, y, color);
}
int cx = 0, cy = 0, r = 10;
float col[3]={1,0,1};
#define SCOL(x,r,g,b) {x[0]=r;x[1]=g;x[2]=b;}
void displayLoop()
{
    // glBegin(GL_TRIANGLE_FAN);
    glClear(GL_COLOR_BUFFER_BIT);

    // glVertex2d(0,0);
    // glVertex2d(.5,.5);
    // glVertex2d(1,0);
    // float a[] = { 1, 0, 1 };
    circleBres(cx, cy, r, col);
    // glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        cx = x;
        cy = 400 - y;

    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        r = (int)sqrt((x - cx) * (x - cx) + (400 - y - cy) * (400 - y - cy));

        std::cout << "Pos:" << cx << " " << cy << ' ' << r << std::endl;
        glutPostRedisplay();
    }
}
void keeb(u_char key, int x, int y)
{
    switch (key) {
    case 'w':
        cy++;
        break;
    case 'a':
        cx--;
        break;
    case 's':
        cy--;
        break;
    case 'd':
        cx++;
        break;
    case 'r':SCOL(col,1,0,0);break;
    case 'g':SCOL(col,0,1,0);break;
    case 'b':SCOL(col,0,0,1);break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(400, 400);
    uint wid = glutCreateWindow("Hi");

    myinit();
    glClearColor(0, 0, 0, 1);

    glutDisplayFunc(displayLoop);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keeb);
    glutMainLoop();

    return 0;
}