#include <GL/glut.h>

// Program to perform 3D Scaling of a Pyramid and display both the original and scaled object.

float pyr[5][3] = {{0,1,0}, {-1,-1,1}, {1,-1,1}, {1,-1,-1}, {-1,-1,-1}};
//float pyr[5][3] = {{0,-1,0}, {1,1,-1}, {-1,1,-1}, {-1,1,1}, {1,1,1}}; // will result in an upside down pyramid

void drawPyramid(float v[5][3]) {
    glBegin(GL_LINE_LOOP);
    // base of pyramid
    glVertex3fv(v[1]); glVertex3fv(v[2]); glVertex3fv(v[3]); glVertex3fv(v[4]);
    glEnd();
    glBegin(GL_LINES);
    // connecting base with top with single lines
    for(int i=1; i<5; i++) { glVertex3fv(v[0]); glVertex3fv(v[i]); }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0);
    gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0);

    glColor3f(1.0, 1.0, 1.0);
    drawPyramid(pyr);

    float sx = 1.5, sy = 1.5, sz = 1.5;
    float scaled[5][3];
    for(int i=0; i<5; i++) {
        scaled[i][0] = pyr[i][0] * sx;
        scaled[i][1] = pyr[i][1] * sy;
        scaled[i][2] = pyr[i][2] * sz;
    }

    glColor3f(1.0, 0.0, 1.0);
    drawPyramid(scaled);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Scaling");
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

