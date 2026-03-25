#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cmath>
#define PI 3.1415

using namespace std;

// Question : Reflection along x axis then y axis

//glBegin(GL_POINTS);
// draw the pixel using glVertex2i(x, y)
// glEnd();

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0); // here (0,0) will be center of window
}


void drawLine(vector<float> &coord){
	float x1 = coord[0], y1 = coord[1];
	float x2 = coord[2], y2 = coord[3];
	
	glBegin(GL_LINES);
	
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        
    	glEnd();
    
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	
	// to draw a line
	float x1, y1, x2, y2;
	cout << "Enter the terminal coordinates of the line : ";
	cin >> x1 >> y1 >> x2 >> y2;
	vector<float> coord = {x1, y1, x2, y2};
	
	drawLine(coord);
	
	// reflect along x
	coord[0] *= -1;
	coord[2] *= -1;
	
	drawLine(coord);
	
	// reflect along y
	coord[1] *= -1;
	coord[3] *= -1;
	
	drawLine(coord);
	
	
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
