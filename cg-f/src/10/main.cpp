// sutherland hodgeman
//  #include<iostream>
#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef struct {float x;float y;} vec2;
vector<vec2> poly;
vector<vec2> clipper_ends;

int ymin, ymax, xmin, xmax;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499, 0.0, 499);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawPoly(vector<vec2> poly) {
    glBegin(GL_POLYGON);
    for (auto v : poly) {
        glVertex2f(v.x,v.y);
    }
    glEnd();
}

void clip(vector<vec2> mypoly) {
    vector<vec2> newpoints;
    int n = mypoly.size();
    
    //Top
    for (int i = 0; i < n; i++) {
        int inext = (i + 1) % n;

        vec2& current = mypoly[i];
        vec2& next = mypoly[inext];
        bool isFirstInside = current.y<=ymax,isSecondIn= next.y<=ymax;

        if(isFirstInside&&isSecondIn){ //in->in
            newpoints.push_back(next);
        }else if(!isFirstInside && isSecondIn){ // out->in
            // this inpoint is done the same way as cohen sutherland clips a line
            vec2 inpoint = {current.x+(ymax-current.y)*(next.x-current.x)/(next.y-current.y),ymax};  // x0=x0+ ymax-y0 * x1-x0
            newpoints.push_back(inpoint);
            
            newpoints.push_back(next);
        }else if(isFirstInside && !isSecondIn){ // in->out
            vec2 inpoint = {current.x+(ymax-current.y)*(next.x-current.x)/(next.y-current.y),ymax};  // x0=x0+ ymax-y1 * x1-x0
            newpoints.push_back(inpoint);
        }
    }
    swap(newpoints,mypoly);newpoints.clear();//"move" mypoly = newpoints, clear newpoints


    //bottom 
    n = mypoly.size();
    for(int i=0;i<n;i++){
        vec2 current = mypoly[i];
        vec2 next = mypoly[(i+1)%n];

        bool isFirstInside = current.y>=ymin,isSecondIn = next.y>=ymin;

        if(isFirstInside&&isSecondIn){ //in->in
            newpoints.push_back(next);
        }else if(!isFirstInside && isSecondIn){ // out->in
            vec2 inpoint = {current.x+(ymin-current.y)*(next.x-current.x)/(next.y-current.y),ymin};  // x0=x0+ ymax-y0 * x1-x0
            newpoints.push_back(inpoint);
            
            newpoints.push_back(next);
        }else if(isFirstInside && !isSecondIn){ // in->out
            vec2 inpoint = {current.x+(ymin-current.y)*(next.x-current.x)/(next.y-current.y),ymin};  // x0=x0+ ymax-y1 * x1-x0
            newpoints.push_back(inpoint);
        }else{
            cout<<"Completely out";
        }
    }
    swap(newpoints,mypoly);newpoints.clear();//"move" mypoly = newpoints, clear newpoints

    //r
    n = mypoly.size();

    for(int i=0;i<n;i++){
        vec2 current = mypoly[i];
        vec2 next = mypoly[(i+1)%n];

        bool isFirstInside = current.x<=xmax,isSecondIn = next.x<=xmax;

        if(isFirstInside&&isSecondIn){ //in->in
            newpoints.push_back(next);
        }else if(!isFirstInside && isSecondIn){ // out->in
            vec2 inpoint = {xmax,current.y+(xmax-current.x)*(next.y-current.y)/(next.x-current.x)};
            newpoints.push_back(inpoint);
            
            newpoints.push_back(next);
        }else if(isFirstInside && !isSecondIn){ // in->out
            vec2 inpoint = {xmax,current.y+(xmax-current.x)*(next.y-current.y)/(next.x-current.x)};
            newpoints.push_back(inpoint);
        }
    }
    swap(newpoints,mypoly);newpoints.clear();//"move" mypoly = newpoints, clear newpoints
    //l
    n = mypoly.size();
    for(int i=0;i<n;i++){
        vec2 current = mypoly[i];
        vec2 next = mypoly[(i+1)%n];

        bool isFirstInside = current.x>=xmin,isSecondIn = next.x>=xmin;

        if(isFirstInside&&isSecondIn){ //in->in
            newpoints.push_back(next);
        }else if(!isFirstInside && isSecondIn){ // out->in
            vec2 inpoint = {xmin,current.y+(xmin-current.x)*(next.y-current.y)/(next.x-current.x)};
            newpoints.push_back(inpoint);
            
            newpoints.push_back(next);
        }else if(isFirstInside && !isSecondIn){ // in->out
            vec2 inpoint = {xmin,current.y+(xmin-current.x)*(next.y-current.y)/(next.x-current.x)};  // x0=x0+ ymax-y1 * x1-x0
            newpoints.push_back(inpoint);
        }
    }
    swap(newpoints,mypoly);newpoints.clear();//"move" mypoly = newpoints, clear newpoints


    glColor3f(1,1,0);
    drawPoly(mypoly);
    cout<<"Left with "<<mypoly.size();
}
// Implements Sutherlandï¿½Hodgman algorithm
void display() {
    init();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    drawPoly(poly);  // original in green
    // i and k are two consecutive indexes
    int cs = clipper_ends.size();

    // We pass the current array of vertices, it's size
    // and the end points of the selected clipper line
    clip(poly);
    // clip(old_poly_points, poly_size, clipper_points[i][0],
    //      clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);

    glColor3f(0.0f, 0.0f, 1.0f);
    // drawPoly(old_poly_points, poly_size);
    glFlush();
}

// Driver code
int main(int argc, char* argv[]) {
    int n;
    cout << "Enter no. of vertices: \n";
    cin >> n;
    int t1, t2;
    // org_poly_size = poly_size;
    for (int i = 0; i < n; i++) {
        cout << "Polygon Vertex:\n";
        // scanf("%d%d", &old_poly_points[i][0], &old_poly_points[i][1]);
        cin >> t1 >> t2;
        vec2 p = {t1, t2};
        poly.push_back(p);
        // org_poly_points[i][0] = old_poly_points[i][0];
        // org_poly_points[i][1] = old_poly_points[i][1];
    }

    cout << "ymin,ymax,xmin,xmax";
    cin >> ymin >> ymax >> xmin >> xmax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Clipping!");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}