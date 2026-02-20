#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float rx, ry, xc = 0, yc = 0;

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
}

void renderEllipse(float rx, float ry, float xc, float yc) {
	float curX = 0, curY = ry;
	float p = ry * ry - rx * rx * ry + (1.0/4) * rx * rx;
	
	glBegin(GL_POINTS);
	while (2 * ry * ry * curX < 2 * rx * rx * curY) {
		plotSymmetric(curX, curY, xc, yc);
		
		curX = curX + 1;
		
		p = p + 2 * ry * ry * curX + ry * ry;
		
		if (p >= 0){ 
			p -= 2 * rx * rx * curY;
			curY = curY - 1;
		}
	}
	
	p = ry * ry * (curX + 1.0/2) * (curX + 1.0/2) + rx * rx * (curY - 1) * (curY - 1) - rx * rx * ry * ry;
	
	while (curY > 0) {
		plotSymmetric(curX, curY, xc, yc);
		curY = curY - 1;
		
		p = p - 2 * rx * rx * curY + rx * rx;
		if (p <= 0) {
			p += 2 * ry * ry * curX;
			curX = curX + 1;
		}
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	renderEllipse(rx, ry, xc, yc);
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter x-axis radius: ";
	cin >> rx;
	cout << "Enter y-axis radius: ";
	cin >> ry;
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
