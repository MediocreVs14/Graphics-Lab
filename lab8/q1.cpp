#include <GL/glut.h>

using namespace std;

//Write an OpenGL program to perform 3D Translation of a Cube and display both the original and translated cube.

float vertices[8][3] = {
    {-0.5,-0.5,0.5}, {0.5,-0.5,0.5}, {0.5,0.5,0.5}, {-0.5,0.5,0.5},
    {-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,0.5,-0.5}, {-0.5,0.5,-0.5}
};


void drawCube(float v[8][3]) {
    glBegin(GL_LINES);

    // Front face
    glVertex3fv(v[0]); glVertex3fv(v[1]);
    glVertex3fv(v[1]); glVertex3fv(v[2]);
    glVertex3fv(v[2]); glVertex3fv(v[3]);
    glVertex3fv(v[3]); glVertex3fv(v[0]);

    // Back face
    glVertex3fv(v[4]); glVertex3fv(v[5]);
    glVertex3fv(v[5]); glVertex3fv(v[6]);
    glVertex3fv(v[6]); glVertex3fv(v[7]);
    glVertex3fv(v[7]); glVertex3fv(v[4]);

    // Connect edges
    glVertex3fv(v[0]); glVertex3fv(v[4]);
    glVertex3fv(v[1]); glVertex3fv(v[5]);
    glVertex3fv(v[2]); glVertex3fv(v[6]);
    glVertex3fv(v[3]); glVertex3fv(v[7]);

    glEnd();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);

	glMatrixMode(GL_MODELVIEW);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(2, 2, 5, 0, 0, 0, 0, 1, 0);

    glColor3f(1.0, 0.0, 0.0); 
    drawCube(vertices);

    float tx = 1.2, ty = 0.5, tz = -1.0;
    float translated[8][3];

    for(int i = 0; i < 8; i++) {
        translated[i][0] = vertices[i][0] + tx;
        translated[i][1] = vertices[i][1] + ty;
        translated[i][2] = vertices[i][2] + tz;
    }

    glColor3f(0.0, 1.0, 0.0); 
    drawCube(translated);

    glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Cube Translation");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
