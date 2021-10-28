#include<iostream>
#include<GL/glut.h>


void displayLoop() {
	//glClearColor(0, 0, 0, 1.f);
	glColor4f(1.f, 1.f, 1.f, .25f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.f, 0.f);
	glVertex2f(0.f, 1.f);
	glVertex2f(0.8f, .8f);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0, 0, 0, 1.f);
	glutMainLoop();

}