/**
 * two windows - one with  4 color rect and other with rotating rect 
 * */
#include <GL/glut.h>
#include <iostream>
uint id1,id2;
void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex2i(10,10);
    glColor3f(0,1,1);
    glVertex2i(10,100);
    glColor3f(1,0,1);
    glVertex2i(100,100);
    glColor3f(1,1,0);
    glVertex2i(100,10);
    glEnd();
    glFlush();
}

void idle2(){
    glutSetWindow(id2);

    glTranslatef(20,20,0);
    glRotatef(.10,0,0,1);
    glTranslatef(-20,-20,0);
    glutPostRedisplay();
}

int main(int c,char**v){
    glutInit(&c,v);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGB);
    id1=glutCreateWindow("1");
    glutDisplayFunc(draw);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,499,0,499);
    id2=glutCreateWindow("2");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,499,0,499);

    glutDisplayFunc(draw);
    glutIdleFunc(idle2);

    glutMainLoop();
}

