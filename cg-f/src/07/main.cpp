#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> x;
vector<int> y;
vector<int> xint;

void edgeDetect(int x0,int y0,int x1,int y1,int sl){
	if(y0>y1) {
		swap(x0,x1);swap(y0,y1);
	}
	if(y0==y1) return ;
	if(y0<=sl&&sl<=y1){
		xint.push_back(x0+(sl-y0)*(x1-x0)/(y1-y0));
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	for(int sl=0;sl<500;sl++){
		int n = x.size();
		xint.clear();
		for(int i=0;i<n;i++){
			edgeDetect(x[i],y[i],x[(i+1)%n],y[(i+1)%n],sl);
		}
		int m = xint.size();
		sort(xint.begin(),xint.end());
		for(int i=0;i<m/2;i++){
			glVertex2i(xint[2*i],sl);
			glVertex2i(xint[2*i+1],sl);
		}
	}
	glEnd();
	glFlush();
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