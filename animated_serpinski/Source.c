#include <glut.h>
#include <stdlib.h>

float scale = 2.0f;
float delta_scale = 0.03f;
int depth = 1;
int delta_depth = 1;
int i = 0;

void drawSubTriangle(int n, float x1, float y1, float x2, float y2, float x3, float y3);

void timer()
{
	scale += delta_scale;
	
	if (scale > 5)
		delta_scale = -delta_scale;
	if (scale < 2)
		delta_scale = -delta_scale;

	if (i++>5)
	{
		if (delta_depth > 0)
			depth++;
		else
			depth--;
		i = 0;
	}

	if (depth > 8)
		delta_depth = -1;
	if (depth < 2)
		delta_depth = 1;

	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawMainTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	glEnd();
}

void drawSubTriangle(int n, float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	glEnd();

	if (n < depth)
	{
		drawSubTriangle
			(
			n + 1,
			(x1 + x2) / 2 + (x2 - x3) / 2,
			(y1 + y2) / 2 + (y2 - y3) / 2,
			(x1 + x2) / 2 + (x1 - x3) / 2,
			(y1 + y2) / 2 + (y1 - y3) / 2,
			(x1 + x2) / 2,
			(y1 + y2) / 2
			);

		drawSubTriangle
			(
			n + 1,
			(x3 + x2) / 2 + (x2 - x1) / 2,
			(y3 + y2) / 2 + (y2 - y1) / 2,
			(x3 + x2) / 2 + (x3 - x1) / 2,
			(y3 + y2) / 2 + (y3 - y1) / 2,
			(x3 + x2) / 2,
			(y3 + y2) / 2
			);

		drawSubTriangle
			(
			n + 1,
			(x1 + x3) / 2 + (x3 - x2) / 2,
			(y1 + y3) / 2 + (y3 - y2) / 2,
			(x1 + x3) / 2 + (x1 - x2) / 2,
			(y1 + y3) / 2 + (y1 - y2) / 2,
			(x1 + x3) / 2,
			(y1 + y3) / 2
			);
	}
}



void renderScene(void) {

	float x1 = -1.0f;
	float y1 = -1.0f;
	float x2 = 1.0f;
	float y2 = -1.0f;
	float x3 = 0.0f;
	float y3 = 1.0f;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glScalef(scale, scale, scale);
	drawMainTriangle(x1, y1, x2, y2, x3, y3);

	glColor3f(0.5f, 1.0f, 0.2f);
	drawSubTriangle(1,
		(x1 + x2) / 2,
		(y1 + y2) / 2,
		(x1 + x3) / 2,
		(y1 + y3) / 2,
		(x2 + x3) / 2,
		(y2 + y3) / 2
		);

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

int main(int argc, char** argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 640);
	glutCreateWindow("Serpinski Triangle");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutTimerFunc(30, timer, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}