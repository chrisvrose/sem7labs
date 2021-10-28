#include<iostream>
#include<GL/glut.h>

typedef float vec2[2];

#define MP(x,y) { ((x)[0]+y[0])/2,((x)[1]+(y)[1])/2 }

// draw 3 points as a Triangle
void trdraw(vec2 a,vec2 b,vec2 c) {
	glBegin(GL_TRIANGLES);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);

	glEnd();
}

void trloop(vec2 a, vec2 b,vec2 c,int k) {
	if (k) {
		vec2 ab = MP(a, b);
		vec2 bc = MP(b, c);
		vec2 ca = MP(c,a);
		trloop(a, ab, ca,k-1);
		trloop(b, bc, ab, k - 1);
		trloop(c, ca, bc, k - 1);
	}
	else trdraw(a,b,c);
}


void displayLoop() {
	//glClearColor(0, 0, 0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.f, 1.f, 1.f, .25f);

	vec2 a = { 0,0 };
	vec2 b = { .5,0 };
	vec2 c = { .25,.25 };

	trloop(a, b, c, 3);



	glEnd();
	glFlush();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
	std::cout << "Hello world" << std::endl;
	glutInit(&argc, argv);
	//single buffer, 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("Send help");
	glutInitWindowSize(800, 600);
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(displayLoop);

	glEnable(GL_DEPTH_TEST);
	

	glClearColor(0, 0, 0, 1.f);
	glutMainLoop();

}