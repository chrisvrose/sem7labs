//draw line using bres line drawing
#include <GL/glut.h>
#include <iostream>



void myinit(){
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0,499,0,499);
    glMatrixMode(GL_MODELVIEW);
}

void bresenham(int x0,int y0,int Dx,int Dy,int dx,int dy,int xn,int yn,bool flip){

    int x=x0,y=y0,p=2*Dy-Dx,ge=2*Dy,gne=2*(Dy-Dx);

    glBegin(GL_POINTS);

    !flip?glVertex2i(x,y):glVertex2i(y,x);

    for(int i=0;i<Dx;i++){
        if(p<0){p+=ge;x+=dx;}else{
            p+=gne;x+=dx;y+=dy;
        }
        !flip?glVertex2i(x,y):glVertex2i(y,x);
    }

    glEnd();glFlush();
}

void draw(){}
int sx,sy,ex,ey;
void mouse(int b,int s, int x,int y){
    if(b==GLUT_LEFT_BUTTON){
        if(s==GLUT_DOWN){
            sx=x,sy=500-y;
        }else{
            ex=x,ey=500-y;

            int Dx=abs(ex-sx),Dy=abs(ey-sy),dx=(ex>sx?1:-1),dy=(ey>sy?1:-1);

            if(Dy==0||Dy<Dx) bresenham(sx,sy,Dx,Dy,dx,dy,ex,ey,false);
            else bresenham(sy,sx,Dy,Dx,dy,dx,ey,ex,true);

            glutPostRedisplay();
        }
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(500, 500);
    uint wid = glutCreateWindow("Hi");

    myinit();

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
