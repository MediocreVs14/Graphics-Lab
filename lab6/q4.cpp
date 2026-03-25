#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cmath>
#define PI 3.1415

using namespace std;

// Question : Draw Rect and Triangle and move triangle at top middle of rect

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // here (0,0) will be center of window
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
}


void drawShape(vector<float> coord){
	glBegin(GL_LINE_LOOP);
	
	for(int i = 0 ; i < coord.size() - 1 ; i += 2){
        	glVertex2f(coord[i], coord[i+1]);
        }
        
    	glEnd();
    
}

vector<float> translate(vector<float> coord, float x, float y){
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
	
	
	vector<float> rect = {0 , 0 , 6, 0, 6, 9, 0, 9};
	vector<float> tri = {0, 0 , 2, 0, 1, 1};
	
	//drawShape(rect);
	//drawShape(tri);
	
	rect = translate(rect, 5, 0);
	tri = translate(tri, 7, 9); // (2, 9) + (5, 0)
	
	drawShape(rect);
	drawShape(tri);
	
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
