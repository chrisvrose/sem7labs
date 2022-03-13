// draw a circle using bres
#include<GL/glut.h>
#include<cmath>
void draw(){}



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
int sx,sy;
void mouse(int b,int s,int x,int y){
    if(b==0){
        if(s==GLUT_DOWN){
            sx=x,sy=500-y;
        }
        else{
            int r = (int)sqrt((x-sx)*(x-sx)+(500-y-sy)*(500-y-sy));
            circ(sx,sy,r);
            glutPostRedisplay();
        }
    }
}
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(500,500);
    glutCreateWindow("");

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,499,0,499);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
}