// sier
#include<GL/glut.h>
#include<stdio.h>
typedef float vec3[3];
#define MP(x,y) {((x)[0]+(y)[0])/2,((x)[1]+(y)[1])/2,((x)[2]+(y)[2])/2}
void drawtr(vec3 a,vec3 b,vec3 c,vec3 d, int k){
	
	if(k){
		vec3 ab = MP(a,b),ac=MP(a,c),ad=MP(a,d),
			bc=MP(b,c),bd=MP(b,d),
			cd=MP(c,d);
		drawtr(a,ab,ac,ad,k-1);
		drawtr(ab,b,bc,bd,k-1);
		drawtr(ac,bc,c,cd,k-1);
		drawtr(ad,bd,cd,d,k-1);
	}else{
		glBegin(GL_TRIANGLES);
		// i do a,b,c,d 4 copies, then just delete d in first, c in second, ...
		glColor3f(1,0,0);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);

		glColor3f(0,1,0);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(d);

		glColor3f(1,0,1);
		glVertex3fv(a);
		glVertex3fv(c);
		glVertex3fv(d);

		glColor3f(1,1,0);
		glVertex3fv(b);
		glVertex3fv(c);
		glVertex3fv(d);


		
		glEnd();
	}
}
int s;

void display(){
	vec3 a = {0,0,0},b={1,0,1},c={1,1,0},d={0,1,1};
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawtr(a,b,c,d,s);
	glFlush();
}

void idle(){
    glRotatef(.01,1,1,1);
	glutPostRedisplay();
}

void myinit(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
}

int main(int c, char** v) {
	glutInit(&c, v);
	printf("How many divs\n:");
	scanf("%d",&s);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutCreateWindow("-");
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
