#include <GL/glut.h>
#include <iostream>
#include<unistd.h>
int ww = 600, wh = 600;

float boundaryColor[3] = {1.0, 0.0, 0.0}; // red
float fillColor[3] = {0.0, 1.0, 0.0};     // green

void getPixel(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setPixel(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

bool isSameColor(float c1[3], float c2[3]) {
    return (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]);
}

void boundaryFill8(int x, int y) {
    float currentColor[3];
    getPixel(x, y, currentColor);

    if (!isSameColor(currentColor, boundaryColor) &&
        !isSameColor(currentColor, fillColor)) {

        setPixel(x, y, fillColor);

        boundaryFill8(x+1, y);
        boundaryFill8(x-1, y);
        boundaryFill8(x, y+1);
        boundaryFill8(x, y-1);

        boundaryFill8(x+1, y+1);
        boundaryFill8(x-1, y-1);
        boundaryFill8(x-1, y+1);
        boundaryFill8(x+1, y-1);
    }
}

void drawPolygon() {
    glColor3fv(boundaryColor);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(200, 200);
        glVertex2i(400, 200);
        glVertex2i(450, 350);
        glVertex2i(300, 450);
        glVertex2i(150, 350);
    glEnd();
    // glLineWidth(3.0);
}
/*
void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        boundaryFill8(x, wh - y); // adjust y
    }
}
*/
void start(){
	usleep(2000000);
	boundaryFill8(300,300);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
    start();
    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, ww, 0, wh);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Boundary Fill");

    init();
    glutDisplayFunc(display);
    // glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
