#include<GL/glut.h>

typedef float vec3[3];
// why write it 10x times
#define MP(p,q) {(p[0]+q[0])/2.f,(p[1]+q[1])/2.f,(p[2]+q[2])/2.f}

void myinit() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, 1, .1, 12);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -3);
}

void drawtr(vec3 a, vec3 b, vec3 c, vec3 d) {
  // each triangle is built by not having 1 point, eg. face abc without d, do for each
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3fv(a);//d
	glVertex3fv(b);
	glVertex3fv(c);
	
	glColor3f(1, 1, 0);
	glVertex3fv(b);//a
	glVertex3fv(c);
	glVertex3fv(d);

	glColor3f(1, 0, 1);
	glVertex3fv(a);//b
	glVertex3fv(c);
	glVertex3fv(d);

	glColor3f(0, 1, 1);
	glVertex3fv(a);//c
	glVertex3fv(b);
	glVertex3fv(d);

	glEnd();
	
}


void drawsier(vec3 a, vec3 b, vec3 c, vec3 d, unsigned int k) {
	if (k>0) {
		vec3 ab = MP(a, b);
		vec3 ac = MP(a, c);
		vec3 ad = MP(a, d);
		vec3 bc = MP(b, c);
		vec3 bd = MP(b, d);
		vec3 cd = MP(c, d);
    // the a/b/c/d remains in the same position, put the other midpoints based on the other letter
		drawsier(a, ab, ac, ad, k - 1);
		drawsier( ab,b, bc, bd, k - 1);
		drawsier( ac, bc,c, cd, k - 1);
		drawsier( ad, bd, cd,d, k - 1);
	}
	else {
		drawtr(a, b, c, d);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec3 a = { 0,0,0 };
	vec3 b = { 01,01,0 };
	vec3 c = { 01,0,01 };
	vec3 d = { 0,01,01 };
	
	drawsier(a,b,c,d,4);
	glFlush();
}


int main(int c, char** v) {
	glutInit(&c, v);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(400,400);
	glutCreateWindow("-");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
