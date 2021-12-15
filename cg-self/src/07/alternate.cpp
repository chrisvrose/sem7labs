#include<GL/glut.h>
#include<cmath>
#include<iostream>
#include<vector>
#include<algorithm>
typedef double vec2[2];
using namespace std;
int h=50,k=50,r=40;
std::vector<int> x;
std::vector<int> y;
std::vector<int> xint;


void edgeDetect(int x1,int y1, int x2, int y2,int scanline) {
	if (y1 > y2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y1<scanline && y2>scanline) {
		//intersect
		// scanline-y1th proportion of the (x2-x1)
		xint.push_back(x1+(scanline-y1)*(x2-x1)/(y2-y1));
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	int n = x.size();
	for (int i = 0; i < 500; i++) {
		xint.clear();
		for (int j = 0; j < n; j++) {
			edgeDetect(x[j], y[j], x[(j + 1) % n], y[(j + 1) % n], i);
		}

		std::sort(xint.begin(), xint.end());
		int m = xint.size();
		if(m>=2)
		for (int k = 0; k < m; k += 2) {
			cout << "Drawing " << xint[k] << ' ' << xint[k + 1]<<'\n';
			glBegin(GL_LINES);
			glVertex2i(xint[k], i);
			glVertex2i(xint[k+1], i);
			glEnd();
		}
	}
	glFlush();
}


int main(int ac, char** av) {
	glutInit(&ac, av);
	
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
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glutMainLoop();
	return 0;
}
