#include <GL/glut.h>
#include <math.h>

float cube[8][3] = {
    {-0.5,-0.5,0.5}, {0.5,-0.5,0.5}, {0.5,0.5,0.5}, {-0.5,0.5,0.5},
    {-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,0.5,-0.5}, {-0.5,0.5,-0.5}
};

void draw(float v[8][3]) {
    glBegin(GL_LINES);
    for(int i=0; i<4; i++) {
        glVertex3fv(v[i]); glVertex3fv(v[(i+1)%4]);
        glVertex3fv(v[i+4]); glVertex3fv(v[(i+1)%4+4]);
        glVertex3fv(v[i]); glVertex3fv(v[i+4]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3, 3, 5, 0, 0, 0, 0, 1, 0);

    glColor3f(0.5, 0.5, 0.5);
    draw(cube);

    float angle = 45.0 * 3.14159 / 180.0;
    float rotated[8][3];
    for(int i=0; i<8; i++) {
        rotated[i][0] = cube[i][0];
        rotated[i][1] = cube[i][1] * cos(angle) - cube[i][2] * sin(angle);
        rotated[i][2] = cube[i][1] * sin(angle) + cube[i][2] * cos(angle);
    }

    glColor3f(1.0, 0.5, 0.0);
    draw(rotated);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D X-Rotation");
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
