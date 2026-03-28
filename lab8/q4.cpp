#include <GL/glut.h>

const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;
const int x_min = -50, x_max = 50, y_min = -50, y_max = 50;

int computeCode(double x, double y) {
    int code = INSIDE;
    if (x < x_min) code |= LEFT;
    else if (x > x_max) code |= RIGHT;
    if (y < y_min) code |= BOTTOM;
    else if (y > y_max) code |= TOP;
    return code;
}

void cohenSutherland(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;
    while (1) {
        if (!(code1 | code2))     { accept = 1; break; }
        else if (code1 & code2) { break; }
        else {
            int code_out;
            double x, y;
            if (code1 != 0) code_out = code1;
            else code_out = code2;
            if (code_out & TOP) { x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1); y = y_max; }
            else if (code_out & BOTTOM) { x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1); y = y_min; }
            else if (code_out & RIGHT) { y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1); x = x_max; }
            else if (code_out & LEFT) { y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1); x = x_min; }
            if (code_out == code1) { x1 = x; y1 = y; code1 = computeCode(x1, y1); }
            else { x2 = x; y2 = y; code2 = computeCode(x2, y2); }
        }
    }
    if (accept) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1); glVertex2d(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min); glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max); glVertex2f(x_min, y_max);
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(-80, -20); glVertex2d(70, 80);
    glEnd();
    cohenSutherland(-80, -20, 70, 80);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cohen-Sutherland");
    gluOrtho2D(-100, 100, -100, 100);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

