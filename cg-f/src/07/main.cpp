#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> x;
vector<int> y;
vector<int> xint;

void edgeDetect(int x0,int y0,int x1,int y1,int sl){
	// must be y1>y0 - swap if not
	if(y0>y1) {
		swap(x0,x1);swap(y0,y1);
	}
	// sl is inbetween the line's y
	if(y0<=sl&&sl<=y1){
		// add it to the xints for that vector
		xint.push_back(x0+(sl-y0)*(x1-x0)/(y1-y0));
	}
}
void displayEdge(){
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<x.size();i++){
		glVertex2f(x[i],y[i]);
	}
	glEnd();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	displayEdge();
	//foreach scanline
	for(int sl=0;sl<500;sl++){
		// how many lines?
		int n = x.size();
		//start with xintercept list
		xint.clear();
		for(int i=0;i<n;i++){
			// find all intersecting edges for linepair
			edgeDetect(x[i],y[i],x[(i+1)%n],y[(i+1)%n],sl);
		}
		// number of y intercepts
		int m = xint.size();
		// sort them, from lowest to biggest
		sort(xint.begin(),xint.end());
		// Here's the thing, we want to draw for 0,1 , 2,3 , 4,5
		// so have i = half the index
		// then 2*i   -> first element -> 0,2,4,6
		// then 2*i+1 -> second element -> 1,3,5,7
		for(int i=0;i<m/2;i++){
			glBegin(GL_LINES);
				glVertex2i(xint[2*i],sl);
				glVertex2i(xint[2*i+1],sl);
			glEnd();
			glFlush();
			for(int i=0;i<1<<16;i++);
		}
	}
}

int main(int c, char**v){
	glutInit(&c,v);
	cout << "Enter #verts\n";
	int n;
	cin >> n;
	cout << "Enter verts\n";
	int temp;
	for (int i = 0; i < n; i++) {
		cin >> temp; x.push_back(temp);
		cin >> temp; y.push_back(temp);
	}

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("");

	glutDisplayFunc(display);
	glClearColor(0,0,0,1);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 499, 0, 499);
	glutMainLoop();
	return 0;
}