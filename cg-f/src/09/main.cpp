#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool cliptest(float p, float q, float* t1, float* t2) {
    if (p == 0){
        if (q < 0)
            return false;  // parallel and out of the window
        else
            return true;
    }
    float r = q / p;
    if (p < 0) {
        if (r > *t2)
            return false;
        if (r > *t1)
            *t1 = r;
    }
    if (p > 0) {
        if (r < *t1)
            return false;
        if (r < *t2)
            *t2 = r;
    }
    return true;
}
vector<float> x0l, xnl, y0l, ynl;
float xmin = 10, xmax = 110, ymin = 10, ymax = 110;
float xwmin = 200, xwmax = 400, ywmin = 200, ywmax = 400;

void clipdraw() {
    int n = x0l.size();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    for (int i = 0; i < n; i++) {
        float  x0= x0l[i], xn = xnl[i], y0 = y0l[i], yn = ynl[i];
        float dx = xn-x0,dy=yn-y0,t1=0,t2=1;
        //original
        glColor3f(0,1,1);//cyan
        glVertex2f(x0,y0);glVertex2f(xn,yn);

        if(
            cliptest(-dx,x0-xmin,&t1,&t2)&&//L
            cliptest(dx,xmax-x0,&t1,&t2)&&//R
            cliptest(-dy,y0-ymin,&t1,&t2)&&//B
            cliptest(dy,ymax-y0,&t1,&t2)  //T
            ){
                // always set 1 first - otherwise if we set x0 first we lose the old x0 val
                if(t2<1){
                    xn=x0+t2*dx;
                    yn=y0+t2*dy;
                }
                if(t1>0){
                    x0=x0+t1*dx;
                    y0=y0+t1*dy;
                }
                glColor3f(1,0,1);//magenta
                glVertex2f((x0-xmin)*(xwmax-xwmin)/(xmax-xmin)+xwmin,(y0-ymin)*(ywmax-ywmin)/(ymax-ymin)+ywmin);
                glVertex2f((xn-xmin)*(xwmax-xwmin)/(xmax-xmin)+xwmin,(yn-ymin)*(ywmax-ywmin)/(ymax-ymin)+ywmin);
            }

    }
    glEnd();

    //original
    glBegin(GL_LINE_LOOP);glColor3f(1,0,0);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();
    // viewport
    glBegin(GL_LINE_LOOP);glColor3f(1,1,0);//yellow
        glVertex2f(xwmin,ywmin);
        glVertex2f(xwmax,ywmin);
        glVertex2f(xwmax,ywmax);
        glVertex2f(xwmin,ywmax);
    glEnd();glFlush();
}

int main(int c,char**v){
    glutInit(&c,v);
	cout << "Enter #verts\n";
	int n;
	cin >> n;
	cout << "Enter lines\n";
	float temp;
	for (int i = 0; i < n; i++) {
        cout<<"x0";cin>>temp;x0l.push_back(temp);
        cout<<"y0";cin>>temp;y0l.push_back(temp);
        cout<<"xn";cin>>temp;xnl.push_back(temp);
        cout<<"yn";cin>>temp;ynl.push_back(temp);
	}

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("");

	glutDisplayFunc(clipdraw);
	glClearColor(0,0,0,1);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 499, 0, 499);
	glutMainLoop();
	return 0;
}
