#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

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
	glPointSize(5.0);
	int radius = 50;
	
	int x = -100, y = 100;
	
	glColor3f(0.0, 0.47, 0.816);
	renderCircle(radius, x, y);
	glColor3f(0.0, 0.0, 0.0);
	renderCircle(radius, x + radius * 2 + radius/4, y);
	glColor3f(0.94, 0.16, 0.18);
	renderCircle(radius, x + radius * 4 + radius/2, y);
	glColor3f(1.0, 0.69, 0.08);
	renderCircle(radius, x + radius + radius/8, y - (radius + radius/4));
	glColor3f(0.0, 0.65, 0.32);
	renderCircle(radius, x + radius * 3 + 3 * radius / 8, y - (radius + radius/4));
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Point Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
