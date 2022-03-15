//house ref and scaling
#include <GL/glut.h>
#include <math.h>
#include <iostream>
typedef float vec2[2];

float m,c,t,xr,yr;

vec2 house[11] = {
    {100,100},
    {140,100},
    {140,150},
    {160,150},
    {160,100},
    {200,100},
    {200,200},
    {220,200},
    {150,300},
    {80,200},
    {100,200},
};

void drawhouse(){
    glBegin(GL_LINE_LOOP);
    for(auto v:house){glVertex2fv(v);}
    glEnd();
}

void drawusual(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);drawhouse();glFlush();
    
}

void drawrefl(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);drawhouse();


    float r = atan(m)*180/3.1415f;
    glPushMatrix();
    glTranslatef(0,c,0);
    glRotatef(r,0,0,1);
    glScalef(1,-1,1);
    glRotatef(-r,0,0,1);
    glTranslatef(0,-c,0);

    drawhouse();
    glPopMatrix();


    glFlush();
}

void drawrot(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);drawhouse();glFlush();

    glPushMatrix();
    glTranslatef(xr,yr,0);
    glRotatef(t,0,0,1);
    glTranslatef(-xr,-yr,0);
    drawhouse();
    glPopMatrix();

    glFlush();
}
void keeb (unsigned char button,  int x, int y){
    if(button=='r'){
        drawrot();
    }else if(button=='f'){
        drawrefl();
    }else{
        glutPostRedisplay();
    }
}

int main(int c,char**v){
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Clipping!");
    glutDisplayFunc(drawusual);
    glutKeyboardFunc(keeb);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,499,0,499);
    glMatrixMode(GL_MODELVIEW);
    std::cout<<"m,c";std::cin>>m>>c;
    std::cout<<"t,xr,yr";std::cin>>t>>xr>>yr;

    glutMainLoop();
}



