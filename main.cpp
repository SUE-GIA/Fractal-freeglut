//Stefanos Panagiotis Giannakos 3568
//Added a refresh update function for the random colors

#include <GL\glut.h>
#include <stdlib.h>
#include <time.h>

int points = 12000;
int id = 5;
float r = 0.33333333333;
int potitionX, potitionY;
int lastPX = 0, lastPY = 0;
int activeMenuItem = 0; 
int pauseRefresh = 0; // Flag that controls the refresh update

//random number generator between 0.0-1.0
double randomNumber() {
    return (double)rand() / (double)RAND_MAX;
}

//fractal creator
void drawShape(GLfloat vertices[][2], int numVertices) {
    typedef GLfloat point2[2];

    int i, j;
    point2 q = { 300.0, 500.0 };

    for (i = 0; i < points; i++) {
        j = rand() % numVertices;

        q[0] = (q[0] + vertices[j][0]) * r;
        q[1] = (q[1] + vertices[j][1]) * r;

        if (points == 15000) {
            // Set random color for each point only when "15000 points, random color" is active
            glColor3f(randomNumber(), randomNumber(), randomNumber());
        }
        else {
            glColor3f(0.0, 0.0, 0.0);
        }
        

        glBegin(GL_POINTS);
        glVertex2fv(q);
        glEnd();
    }

    glFlush();
}

// Continuous update function
void update(int value) {
    if (!pauseRefresh) {
        glutPostRedisplay(); // Redraw the scene
    }
    glutTimerFunc(1000 / 60, update, 0); // Update 60 frames per
}

//show the menu
void menu(int choice) {
    switch (choice) {
    case 1:
        points = 15000;
        activeMenuItem = 1;
        pauseRefresh = 0; // Unpause the refresh update
        glutTimerFunc(0, update, 0);
        break;
    case 2:
        r = 0.33333333333;
        id = 2;
        activeMenuItem = 0; 
        break;
    case 3:
        r = 0.375;
        id = 3;
        activeMenuItem = 0; 
        break;
    case 4:
        exit(0);
    case 5:
        points = 12000;
        activeMenuItem = 0; 
        pauseRefresh = 1; // Pause the refresh update
        break;
    }

    glutPostRedisplay();
}

// left click for menu
void LeftClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        potitionX = x - lastPX;
        potitionY = y + lastPY;
    }
    else {
        lastPX = x - potitionX;
        lastPY = potitionY - y;
    }
}

void RightDrag(int x, int y) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(potitionX - x, potitionX - x + 700, -(potitionY - y), -(potitionY - y) + 700);

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}


void myinit(void) {

    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 0.0); // white background
    glColor3f(0.0, 0.0, 0.0); // black hexagon at init/on

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 700.0, 0.0, 700.0);
    glMatrixMode(GL_MODELVIEW);

    // Seed the random number generator
    srand(time(NULL));
}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    if (id == 2 || id == 5) {
        GLfloat hexagonVertices[][2] = {
            {450.0, 575.0},   // Vertex 1
            {700.0, 450.0},   // Vertex 2
            {950.0, 575.0},   // Vertex 3
            {950.0, 825.0},   // Vertex 4
            {700.0, 950.0},   // Vertex 5
            {450.0, 825.0}    // Vertex 6
        };

        drawShape(hexagonVertices, 6);
    }
    else if (id == 3) {
        GLfloat pentagonVertices[][2] = {
            {430.0,350.0},
            {730.0,350.0},
            {825.0,650.0},
            {580.0,830.0},
            {335.0,650.0}
        };
        drawShape(pentagonVertices, 5);
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(700, 700);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Graphics 1st Project - Fractals");

    glutDisplayFunc(display);

    glutCreateMenu(menu);

    glutMouseFunc(LeftClick);
    glutMotionFunc(RightDrag);

    glutAddMenuEntry("15000 points, random color", 1);
    glutAddMenuEntry("Hexagon, r=1/3", 2);
    glutAddMenuEntry("Pentagon, r=3/8", 3);
    glutAddMenuEntry("Quit", 4);
    glutAddMenuEntry("Original 12000 points, black", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myinit();

     
    

    glutMainLoop();

    return 0;
}
