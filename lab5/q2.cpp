#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float rx = 0, ry = 100, xc = 0, yc = 0;

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void plotPoint(int x, int y) {
	glVertex2i(x, y);
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

void drawPolygon(vector<vector<int>>&points) {
    // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    int arr[2];
    for (auto el: points) {
    	arr[0] = el[0], arr[1] = el[1];
        glVertex2iv(arr);
    }
    arr[0] = points[0][0], arr[1] = points[0][1];
    glVertex2iv(arr);

    glEnd();
    glFlush();
}



void renderCircle(float xc, float yc, float radius) {
	float curX = 0, curY = radius;
	float p = (float)5/4 - radius;
	glColor3f(1.0, 0.8, 0.0);
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

void renderHouse(int x, int y, int scale) {
	vector<int> xs, ys;
	
	//scale 50
	xs.push_back(x - 150 );
	xs.push_back(x - 100 );
	xs.push_back(x - 50 );
	xs.push_back(x);
	xs.push_back(x + 50 );
	xs.push_back(x + 100 );
	xs.push_back(x + 150 );
	
	ys.push_back(y);
	ys.push_back(y - 100 );
	ys.push_back(y - 150 );
	ys.push_back(y - 250 );
	
	vector<vector<int>> roof;
	roof.push_back({xs[3], ys[0]});
	roof.push_back({xs[0], ys[1]});
	roof.push_back({xs[6], ys[1]});
	drawPolygon(roof);
	
	vector<vector<int>> wall;
	wall.push_back({xs[1], ys[1]});
	wall.push_back({xs[5], ys[1]});
	wall.push_back({xs[5], ys[3]});
	wall.push_back({xs[1], ys[3]});
	drawPolygon(wall);
	
	vector<vector<int>> door;
	door.push_back({xs[2], ys[2]});
	door.push_back({xs[4], ys[2]});
	door.push_back({xs[4], ys[3]});
	door.push_back({xs[2], ys[3]});
	drawPolygon(door);
}

void renderFence(int startx, int endx, int y, int height, int width) {
	int margin = 10;
	for (int x=startx; x<=endx; x+=2*width) {
		 vector<vector<int>> points;
		 points.push_back({x, y});
		 points.push_back({x, y+height-5});
		 points.push_back({x+5, y+height});
		 points.push_back({x+width-5, y+height});
		 points.push_back({x+width, y+height-5});
		 points.push_back({x+width, y});
		 drawPolygon(points);
		 
		 points.clear();
		 points.push_back({x+width, y+height/2});
		 points.push_back({x+2*width, y+height/2});
		 points.push_back({x+2*width, y+height/2+margin});
		 points.push_back({x+width, y+height/2+margin});
		 drawPolygon(points);
		 
		 points.clear();
		 points.push_back({x+width, y+height/2+4*margin});
		 points.push_back({x+2*width, y+height/2+4*margin});
		 points.push_back({x+2*width, y+height/2+5*margin});
		 points.push_back({x+width, y+height/2+5*margin});
		 drawPolygon(points);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	//renderHouse(20, 200, 25);
	//renderHouse(-200, 200, 50);
	//renderHouse(150, 100, 60);
	
	renderHouse(300, 200, 25);
	renderHouse(-10, 150, 25);
	renderHouse(-300, 250, 25);
	
	renderCircle(250, 350, 50);
	renderFence(-500, 500, -350, 125, 20);
	glFlush();
}

int main(int argc, char** argv) {
	//cout << "Enter x-axis radius: ";
	//cin >> rx;
	//cout << "Enter y-axis radius: ";
	//cin >> ry;
	//cout << "Enter Center Coords: ";
	//cin >> xc >> yc;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Point Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
