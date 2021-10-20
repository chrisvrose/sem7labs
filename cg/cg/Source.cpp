#include<iostream>
#include<GL/glut.h>


void displayLoop() {
	glClearColor(0, 0, 0, 1.f);
	glBegin(GL_TRIANGLES);
	glColor4f(1.f, 1.f, 1.f, .25f);
	glVertex2f(0.f, 0.f);
	glVertex2f(0.f, 1.f);
	glVertex2f(0.8f, .8f);

	glEnd();
	glFlush();

}

int main(int argc, char** argv) {
	std::cout << "Hello world" << std::endl;
	glutInit(&argc, argv);
	glutCreateWindow("Send help");
	glutInitWindowSize(800, 600);
	glutDisplayFunc(displayLoop);

	glutMainLoop();

}