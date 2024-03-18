//TO-DO: CREATE THE PENTAGON FOR CASE 3


#include <GL\glut.h>

int points = 12000;
int id = 5;
float r = 0.33333333333;
int potitionX, potitionY;
int lastPX = 0, lastPY = 0;

//random number generator between 0.0-1.0
double randomNumber() {
	return (double)rand() / (double)RAND_MAX;
}

//fractal creator
void hexagon() {
	typedef GLfloat point2[2];
	point2 vertices[6] = {
	{500.0, 375.0},       // Vertex 1
	{750.0, 250.0},       // Vertex 2
	{1000.0, 375.0},      // Vertex 3
	{1000.0, 625.0},      // Vertex 4
	{750.0, 750.0},       // Vertex 5
	{500.0, 625.0}        // Vertex 6
	};

	int i, j;
	point2 q = { 620.0, 300.0 };
	glClear(GL_COLOR_BUFFER_BIT);


	for (i = 0; i < points; i++) {
		j = rand() % 6;

		q[0] = (q[0] + vertices[j][0]) * r;
		q[1] = (q[1] + vertices[j][1]) * r;

		glBegin(GL_POINTS);
		glVertex2fv(q);
		glEnd();
	}

	glFlush();
}

void pentagon() {
	typedef GLfloat point2[2];
	point2 vertices[5] = {
		{500.0, 375.0},       // Vertex 1
		{650.0, 250.0},       // Vertex 2
		{850.0, 250.0},       // Vertex 3
		{1000.0, 375.0},      // Vertex 4
		{750.0, 600.0}        // Vertex 5
	};

	int i, j;
	point2 q = { 500.0, 800.0 };
	glClear(GL_COLOR_BUFFER_BIT);

	for (i = 0; i < points; i++) {
		j = rand() % 5; // Choose from 5 vertices

		q[0] = (q[0] + vertices[j][0]) * r;
		q[1] = (q[1] + vertices[j][1]) * r;

		glBegin(GL_POINTS);
		glVertex2fv(q);
		glEnd();
	}

	glFlush();
}

//show the menu
void menu(int id) {
	switch (id) {
	case 1:
		// 15000 points, random color
		glColor3f(randomNumber(), randomNumber(), randomNumber());
		points = 15000;
		break;
	case 2:
		// r=1/3, hexagon
		r = 0.33333333333;
		break;
	case 3:
		// r=3/8, TO-DO:Pentagon
		r = 0.375;
		break;
	case 4:
		// quit
		exit(0);
	case 5:
		points = 12000;
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
	glClearColor(1.0, 1.0, 1.0, 0.0); // white backr
	glColor3f(0.0, 0.0, 0.0); // black hexagon at init/on

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 700.0, 0.0, 700.0);
	glMatrixMode(GL_MODELVIEW);

}

void display(void) {

	if (id==5 || id==2){
		hexagon();
	}

	if (id == 3) {
		
		pentagon(); // Display pentagon
	}

	glutSwapBuffers();
}

void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(700, 700);

	glutInitWindowPosition(800, 200);

	glutCreateWindow("Graphics 1st Project - Fractals");

	glutDisplayFunc(display);

	glutCreateMenu(menu);

	glutMouseFunc(LeftClick);
	glutMotionFunc(RightDrag);

	glutAddMenuEntry("15000 points, random color", 1);
	glutAddMenuEntry("Hexagon, r=1/3", 2);
	glutAddMenuEntry("Pentagon, r=3/8", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myinit();

	glutMainLoop();

}
