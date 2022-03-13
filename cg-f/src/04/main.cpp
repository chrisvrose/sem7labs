// extrusion
#include <GL/glut.h>
#include <iostream>

uint id1,id2;
void pts(int h,int k,int x,int y){
    glVertex2i(h+x,k+y);
    glVertex2i(h+x,k-y);
    glVertex2i(h-x,k-y);
    glVertex2i(h-x,k+y);

    glVertex2i(h+y,k+x);
    glVertex2i(h-y,k+x);
    glVertex2i(h-y,k-x);
    glVertex2i(h+y,k-x);
}
void circ(int x0,int y0,int r){
    int x=0,y=r,p=3-4*r;
    glBegin(GL_POINTS);
    pts(x0,y0,x,y);

    while(y>=x){
        if(p<0){p+=4*x+6;x++;}
        else{p+=4*(x-y)+10;x++,y--;}
        pts(x0,y0,x,y);
    }

    glEnd();
    glFlush();
}

void ppd(int x0,int y0,int x1,int y1){
    glBegin(GL_LINE_LOOP);
    glVertex2i(x0,y0);
    glVertex2i(x0,y1);
    glVertex2i(x1,y1);
    glVertex2i(x1,y0);
    glEnd();glFlush();
}

void drawcirc(){

    for(int i=0;i<50;i+=5){
        circ(250,250-i,10);
    }
    glutSwapBuffers();
}

void drawppd(){
    for(int i=0;i<50;i+=5){
        ppd(250+i,250-i,350+i,350-i);
    }
    glutSwapBuffers();
}

int main(int c,char**v){
    glutInit(&c,v);
    glutInitWindowSize(500,500);

    glutInitDisplayMode(GLUT_DOUBLE);

    id1=glutCreateWindow("-");
    glMatrixMode(GL_PROJECTION);gluOrtho2D(0,499,0,499);glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(drawcirc);

    id2=glutCreateWindow("-");
    glMatrixMode(GL_PROJECTION);gluOrtho2D(0,499,0,499);glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(drawppd);

    glutMainLoop();
}