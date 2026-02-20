#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float r, xc = 0, yc = 0;

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

void plotPoint(int x, int y) {
	glVertex2i(x, y);
	cout << "(" << x << ", " << y << ")" << endl;
}

void plotSymmetric(float x, float y, float xc, float yc) {
	plotPoint(round(x+xc), round(y+yc));
	plotPoint(round(-x+xc), round(y+yc));
	plotPoint(round(x+xc), round(-y+yc));
	plotPoint(round(-x+xc), round(-y+yc));
	plotPoint(round(y+xc), round(x+yc));
	plotPoint(round(-y+xc), round(x+yc));
	plotPoint(round(y+xc), round(-x+yc));
	plotPoint(round(-y+xc), round(-x+yc));
}

void renderCircle(float radius, float xc, float yc) {
	float curX = 0, curY = radius;
	float p = (float)5/4 - radius;
	
	glBegin(GL_POINTS);
	while (curX <= curY) {
		plotSymmetric(curX, curY, xc, yc);
		curX = curX + 1;
		if (p >= 0) curY = curY - 1;
		if (p < 0)
			p = p + 1 + 2 * (curX + 1);
		else
			p = p + 1 + 2 * (curX + 1) - 2 * curY;
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	renderCircle(r, xc, yc);
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter the Radius: ";
	cin >> r;
	cout << "Enter Center Coords: ";
	cin >> xc >> yc;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Point Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
