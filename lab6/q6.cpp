#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include<cmath>

int ww = 600, wh = 600;

float targetColor[3];            // color at seed point
float fillColor[3] = {0.0, 1.0, 0.0}; // green

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
    const float epsilon = 0.01f; // tolerance for floating point comparison
    return (fabs(c1[0] - c2[0]) < epsilon &&
            fabs(c1[1] - c2[1]) < epsilon &&
            fabs(c1[2] - c2[2]) < epsilon);
}

// Flood fill using 8-connected neighbors
void floodFill8(int x, int y) {
    float currentColor[3];
    getPixel(x, y, currentColor);

    if (!isSameColor(currentColor, fillColor) && isSameColor(currentColor, targetColor)) {
        setPixel(x, y, fillColor);

        floodFill8(x + 1, y);
        floodFill8(x - 1, y);
        floodFill8(x, y + 1);
        floodFill8(x, y - 1);

        floodFill8(x + 1, y + 1);
        floodFill8(x - 1, y - 1);
        floodFill8(x - 1, y + 1);
        floodFill8(x + 1, y - 1);
    }
}

void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0); // red boundary
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(200, 200);
        glVertex2i(400, 200);
        glVertex2i(450, 350);
        glVertex2i(300, 450);
        glVertex2i(150, 350);
    glEnd();
}

void start() {
    usleep(2000000);
    // Get color at seed point (300,300)
    getPixel(300, 300, targetColor);
    floodFill8(300, 300);
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
    glutCreateWindow("Flood Fill");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
