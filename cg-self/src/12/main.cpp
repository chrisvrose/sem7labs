#include<GL/glut.h>

float vertices[8][3] = {
    {0,0,0},
    {250,0,0},
    {250,250,0},
    {0,250,0},
    {0,250,250},
    {250,250,250},
    {250,0,250},
    {0,0,250}
};

inline void drawCube(){


    glColor3f(1,1,1);

    glBegin(GL_QUADS);
    for(int i=0;i<4;i++)
    glVertex3fv(vertices[i]);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[7]);
    glEnd();

    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[1]);
    glEnd();


    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[2]);
    glEnd();


    glColor3f(0,1,1);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[1]);
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glEnd();

    glFlush();

}

void disp(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    drawCube();

    glFlush();
    glutSwapBuffers();
}

void idle(){
    glRotated(.1,1,0,0);
    glRotated(.2,0,1,0);
    glRotated(.3,0,0,1);
    glutPostRedisplay();
}

void myinit(){
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,.1,2000.f);
    glMatrixMode(GL_MODELVIEW);

    glTranslated(-100,0,-800);

}
// attach this to explore
void keeb(unsigned char k, int x,int y){

    glMatrixMode(GL_MODELVIEW);

    
    switch(k){
        case 'r':
            glLoadIdentity();
            glTranslated(-100,0,-800);
            break;
        case ' ':
            glTranslated(0,-10,0);
            break;
        case 'x':
            glTranslated(0,10,0);
            break;
        case 'w':
            glTranslated(0,0,10);
            break;

        case 's':
            glTranslated(0,0,-10);
            break;

        case 'a':
            // glTranslated(0,0,10);
            glRotatef(10,0,1,0);
            break;
        case 'd':
            glRotatef(-10,0,1,0);

            // glTranslated(0,0,10);
            break;
    }
    glutPostRedisplay();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(500,500);

    glutCreateWindow("No");
    glutDisplayFunc(disp);
    glutKeyboardFunc(keeb);
    glutIdleFunc(idle);
    myinit();

    glutMainLoop();
    return 0;
}