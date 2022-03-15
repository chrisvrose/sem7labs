//CH
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include<vector>
using namespace std;
typedef int outcode;

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

const int RIGHT = 4;
const int LEFT = 8;
const int TOP = 1;
const int BOTTOM = 2;
vector<float>x0l,y0l,xnl,ynl;


outcode getoc(int x,int y){
    outcode oc=0;
    if(y>ymax) oc|=TOP;
    if(y<ymin) oc|=BOTTOM;
    if(x>xmax) oc|=RIGHT;
    if(x<xmin) oc|=LEFT;
    return oc;
}

void draw(){
    for(int i=0;i<x0l.size();i++){
        float x0=x0l[i],y0=y0l[i],xn=xnl[i],yn=ynl[i];
    }
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("clip");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}