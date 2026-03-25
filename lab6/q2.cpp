#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cmath>
#define PI 3.1415

using namespace std;

// Question : Rotation around origin then a fixed point

//glBegin(GL_POINTS);
// draw the pixel using glVertex2i(x, y)
// glEnd();

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0); // here (0,0) will be center of window
}


void drawTriangle(vector<float> &coord){
	float x1 = coord[0], y1 = coord[1];
	float x2 = coord[2], y2 = coord[3];
	float x3 = coord[4], y3 = coord[5];
	
	glBegin(GL_LINE_LOOP);
	
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        
    	glEnd();
    
}

pair<float, float> doRotateCalc(float x1, float y1, float a){
	float A = (PI / 180) * a;
	
	float x, y;
	x = x1 * cos(A) - y1 * sin(A);
	y = x1 * sin(A) + y1 * cos(A);
	
	x1 = x;
	y1 = y;
	
	return {x1, y1};
}	

vector<float> rotate(vector<float> coord, float a){
	for(int i = 0 ; i < coord.size()-1 ; i += 2){
		float x = coord[i], y = coord[i+1];
		pair<float, float> temp = doRotateCalc(x, y, a); 
		coord[i] = temp.first;
		coord[i+1] = temp.second;
		
	}
	
	return coord;
}

vector<float> translation(vector<float> coord, float x, float y){
	for(int i = 0 ; i < coord.size() ; i++){
		if(i % 2 == 0) coord[i] += x;
		else coord[i] += y;
	}
	
	return coord;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	
	// to draw a triangle
	
	vector<float> coord(6);
	cout << "Enter the coord of triangle : ";
	for(auto &x : coord) cin >> x;
	
	drawTriangle(coord);
	coord = rotate(coord, 30);
	drawTriangle(coord);
	
	
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
