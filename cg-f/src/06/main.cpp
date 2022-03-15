// 3d sphere
// glColor3f is optional
#include<iostream>
#include "GL/glut.h"
#include<math.h>

typedef float vec3[3];
// sphere radius
#define SPR 75
// degrees to pi conversion factor
#define DPI (3.1415/180.f)
// coordinates function macro
#define SPHERE_GA(p1,p2) {SPR*sin(DPI*(p1))*cos(DPI*(p2)),SPR*cos(DPI*(p1))*cos(DPI*(p2)),SPR*sin(DPI*(p2))}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for(int p=-80;p<80;p+=10){
		glBegin(GL_QUAD_STRIP);
		for(int t=-180;t<=180;t+=10){
			vec3 p1 = SPHERE_GA(t,p),p2=SPHERE_GA(t,p+10);
			glColor3f(1,0,0);glVertex3fv(p1);
			glColor3f(0,1,0);glVertex3fv(p2);
		}
		glEnd();
	}


	vec3 nc = SPHERE_GA(0,90),sc=SPHERE_GA(0,-90);

	//nc
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,0,0);
	glVertex3fv(nc);

	glColor3f(1,1,0);
	for(int t=-180;t<=180;t+=10){
		vec3 p1 = SPHERE_GA(t,80);
		glVertex3fv(p1);
	}

	glEnd();

	//sc	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,0,0);
	glVertex3fv(sc);

	glColor3f(1,1,0);
	for(int t=-180;t<=180;t+=10){
		vec3 p1 = SPHERE_GA(t,-80);
		glVertex3fv(p1);
	}

	glEnd();glFlush();
}

void idle(){
	glRotatef(.01,1,1,1);
	glutPostRedisplay();
}

void myinit(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90,1,.1,150);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,-110);

	
}

int main(int c, char** v) {
	glutInit(&c, v);

	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutCreateWindow("-");
	myinit();
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}