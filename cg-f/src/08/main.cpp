// CH
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
typedef int outcode;

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

const int RIGHT = 4;
const int LEFT = 8;
const int TOP = 1;
const int BOTTOM = 2;
vector<float> x0l, y0l, xnl, ynl;

outcode getoc(int x, int y) {
    outcode oc = 0;
    if (y > ymax)
        oc |= TOP;
    if (y < ymin)
        oc |= BOTTOM;
    if (x > xmax)
        oc |= RIGHT;
    if (x < xmin)
        oc |= LEFT;
    return oc;
}

void draw() {
    glBegin(GL_LINES);
    for (int i = 0; i < x0l.size(); i++) {
        float x0 = x0l[i], y0 = y0l[i], xn = xnl[i], yn = ynl[i];
        outcode o1 = getoc(x0, y0), o2 = getoc(xn, yn);
        bool accept = false, done = false;
        do {
            if (!(o1 | o2)) {
                accept = done = true;
            } else if (o1 & o2) {
                done = true;
            } else {
                outcode o = o1 ? o1 : o2;
                float x, y;
                if (o & TOP) {
                    x = x0 + (ymax - y0) * (xn - x0) / (yn - y0);
                    y = ymax;
                }
                if (o & BOTTOM) {
                    y = ymin;
                    x = x0 + (ymin - y0) * (xn - x0) / (yn - y0);
                }
                if (o & LEFT) {
                    x = xmin;
                    y = y0 + (xmin - x0) * (yn - y0) / (xn - x0);
                }
                if (o & RIGHT) {
                    x = xmax;
                    y = y0 + (xmax - x0) * (yn - y0) / (xn - x0);
                }
                if (o == o1) {
                    x0 = x, y0 = y;o1 = getoc(x0,y0);
                } else if (o == o2) {
                    xn = x, yn = y;o2 = getoc(xn,yn);
                }
            }
        } while (!done);
        if (accept) {
            // cout<<"Accept"<<x0<<' '<<y0<<';'<<(x0 - xmin) * (xvmax - xvmin) / (xmax - xmin) + xvmin << ' '<<(y0 - ymin) * (yvmax - yvmin) / (ymax - ymin) + yvmin <<'\n';
            // cout<<"Accept2"<<xn<<' '<<yn;
            // fflush(NULL);
            glVertex2f((x0 - xmin) * (xvmax - xvmin) / (xmax - xmin) + xvmin,
                       (y0 - ymin) * (yvmax - yvmin) / (ymax - ymin) + yvmin);
            glVertex2f((xn - xmin) * (xvmax - xvmin) / (xmax - xmin) + xvmin,
                       (yn - ymin) * (yvmax - yvmin) / (ymax - ymin) + yvmin);
        }
    }
    glEnd();
}
void myinit() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 499, 0, 499);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    

    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin, yvmin);
    glVertex2f(xvmin, yvmax);
    glVertex2f(xvmax, yvmax);
    glVertex2f(xvmax, yvmin);
    glEnd();

    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    for (int i = 0; i < x0l.size(); i++) {
        glVertex2f(x0l[i], y0l[i]);
        glVertex2f(xnl[i], ynl[i]);
    }
    glEnd();
    glColor3f(0, 0, 1);
    draw();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    cout << "Enter #verts\n";
    int n;
    cin >> n;
    cout << "Enter lines\n";
    float temp;
    for (int i = 0; i < n; i++) {
        cout << "x0";
        cin >> temp;
        x0l.push_back(temp);
        cout << "y0";
        cin >> temp;
        y0l.push_back(temp);
        cout << "xn";
        cin >> temp;
        xnl.push_back(temp);
        cout << "yn";
        cin >> temp;
        ynl.push_back(temp);
    }
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("clip");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}