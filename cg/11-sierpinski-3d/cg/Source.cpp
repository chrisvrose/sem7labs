#include<iostream>
#include<GL/glut.h>


typedef float vec3[3];

#define MP(x,y) { ( (x)[0]+(y)[0] )/2.f,((x)[1]+(y)[1])/2.f,((x)[2]+(y)[2])/2.f }
#define DIV(x,y) {(x)[0]/(y),(x)[1]/(y),(x)[2]/(y)}
#define FPSTIME(x) (1000/(x))
// draw 3 points as a Triangle

void tr3draw(vec3 a, vec3 b, vec3 c , vec3 d) {
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0);
	glVertex3fv(a); glVertex3fv(b); glVertex3fv(c);

	glColor3f(0, 1, 0);
	glVertex3fv(a); glVertex3fv(b); glVertex3fv(d);

	glColor3f(0, 0, 1);
	glVertex3fv(a); glVertex3fv(c); glVertex3fv(d);

	glColor3f(0.5f, 0.5f, .5f);
	glVertex3fv(b); glVertex3fv(c); glVertex3fv(d);


	glEnd();
}

void tr3loop(vec3 a, vec3 b, vec3 c, vec3 d,int k) {
	if (k) {
		//vec3
		vec3 ab = MP(a, b);
		vec3 ac = MP(a, c);
		vec3 ad = MP(a, d);
		vec3 bc = MP(b, c);
		vec3 bd = MP(b, d);
		vec3 cd = MP(c, d);


		tr3loop(a,ab,ac,ad, k - 1);
		tr3loop(b,bc,bd,ab, k - 1);
		tr3loop(c,ac,bc,cd, k - 1);
		tr3loop(d, ad, bd, cd, k - 1);
	}
	else tr3draw(a, b, c, d);
}


void displayLoop() {
	//glClearColor(0, 0, 0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glColor3f(1.f, 0.f, 1.f);

	/*glBegin(GL_TRIANGLES);
	glVertex3f(0, 0,0.f);
	glVertex3f(100.00, 0,0.f);
	glVertex3f(100,300,0);
	glEnd();*/

	vec3 a = { .0,.0,0.0f };
	vec3 b = { 1,1,0 };
	vec3 c = { 1,0,1};
	vec3 d = { 0,1,1};

	tr3loop(a, b, c,d, 4);



	//glEnd();
	glFlush();
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR){
		// Process/log the error.
		std::cout << "Error:" << err << std::endl;
	}
}

void mousefn(int button,int state,int x,int y) {
	if (state == GLUT_DOWN) {
		std::cout << "Called";
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glFrustum(0-1, 1, 0-1, 1, -1, 1);

}

void timerFn(int) {
	glRotatef(1, 0, 1, 0);
	//glRotated(3, 1, 0, 0);
	glutPostRedisplay();
	glutTimerFunc(FPSTIME(60), timerFn, 0);

}

int main(int argc, char** argv) {
	std::cout << "Hello world" << std::endl;
	glutInit(&argc, argv);
	//single buffer, 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Send help");

	
	glutMouseFunc(mousefn);
	//glutReshapeFunc(reshape);
	glutTimerFunc(FPSTIME(60), timerFn, 0);
	glutDisplayFunc(displayLoop);

	glEnable(GL_DEPTH_TEST);
	

	
	glClearColor(0,0,0, 1);
	//glClearDepth(2.f);

	//glLoadIdentity();
	// 
	//glOrtho(-400,400,-300,300,-50,50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0-2, 2.0, 0.0-2, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

	
	//glOrtho(0, 500.0, 0, 500.0, 0, 10.0f);

	//glClearColor(0, 0, 0, 1.f);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Process/log the error.
		std::cout << "Error:" << err << std::endl;
	}
	glutMainLoop();

}