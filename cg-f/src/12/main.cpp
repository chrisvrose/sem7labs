#include <GL/glut.h>
/** Vertices of a coob */
float vertices[8][3] = {-1,   -1,   -1,

                        1, -1,   -1,

                        1, 1, -1,

                        -1,   1, -1,

                        -1,   1, 1,

                        1, 1, 1,

                        1, -1,   1,

                        -1,   -1,   1};
/** Colors of each vertex of a coob */
float colors[8][3] = {0, 0, 0,

                        1, 0, 0,

                        1, 1, 0,

                        0, 1, 0,

                        0, 1, 1,

                        1, 1, 1,

                        1, 0, 1,

                        0, 0, 1};

// use GLubyte **OR** unsigned char
GLubyte elementindices[] = {
    0,1,2,3,

    0,3,4,7,

    0,7,6,1,

    3,4,5,2,

    2,5,6,1,

    7,4,5,6
};

inline void drawCube() {
    /*
     * This will draw with the help of the bound vertex and color (and normal) pointers.
     * Pass a index list and it makes a drawcall with that-th element
     * 
     * Eg. {1,3} will issue a draw for the 2nd and 4th draw call 
     * Args:
     * 1. Type of draw calls
     * 
     * 2. Number of draw calls present in the index list
     * 3. What is the data type of the index list elements (ubyte array here)
     * 4. index list
     */
    glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,elementindices);
}

void disp() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCube();

    glFlush();
    glutSwapBuffers();
}

void idle() {
    // bruh just rotate
    glRotated(.1, 1, 0, 0);
    glRotated(.2, 0, 1, 0);
    glRotated(.3, 0, 0, 1);
    glutPostRedisplay();
}

inline void myinit() {
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // perspective op
    // just pass fov, aspect ratio (just keep it 1 if square), and near and far
    gluPerspective(80, 1, .1, 15.f);




    glMatrixMode(GL_MODELVIEW);
    // move the cube a bit away
    glTranslated(0, 0, -6);
}
void res(int w, int h){
    glViewport(0,0,w,h);
    
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);

    glutCreateWindow("No");
    glutDisplayFunc(disp);
    
    glutIdleFunc(idle);
    glutReshapeFunc(res);
    // we can use vertex and color arrays and pass them to opengl
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    /*
     * Explaining this - We are passing a set of triplets to OpenGL 
     * 1. Size of the ntuple - 3 -> x, y and z coordinate
     * 2. Datatype
     * 3. Stride - The gap between two successive elements - *3* elements(floats), or *0* for OpenGL to autodetect it
     *  (Stride is important if your array contains other data that you're passing at once)
     * 4. The actual data
     */
    glVertexPointer(3,GL_FLOAT,3*sizeof(float),vertices);
    glColorPointer(3,GL_FLOAT,3*sizeof(float),colors);

    myinit();

    glutMainLoop();
    return 0;
}