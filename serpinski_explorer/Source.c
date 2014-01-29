#include <glut.h>

float scale = 2.0f;
float transx = 0.0f;
float transy = 0.0f;
int depth = 7;

void drawSubTriangle(int n, float x1, float y1, float x2, float y2, float x3, float y3);

void drawMainTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	glEnd();
}

void drawSubTriangle(int n, float x1, float y1, float x2, float y2, float x3, float y3)
{
	glColor3f(0.0f, 0.0f, 1.0f);

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

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
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

void renderScene(void) {

	float x1 = -1.0f;
	float y1 = -1.0f;
	float x2 = 1.0f;
	float y2 = -1.0f;
	float x3 = 0.0f;
	float y3 = 1.0f;

	depth = 7 + (int)scale / 4;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
		
	glScalef(scale, scale, scale);
	glTranslatef(transx, transy, 0);
	drawMainTriangle(x1,y1,x2,y2,x3,y3);
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

void processSpecialKeys(unsigned char key, int x, int y) {
	int mod;
	mod = glutGetModifiers();

	switch (key)
	{
	case GLUT_KEY_UP:
		//moving up
		if (mod == GLUT_ACTIVE_ALT)
			transy -= 0.09f;
		else
			transy -= 0.03f;
		break;
	case GLUT_KEY_DOWN:
		//moving down
		if (mod == GLUT_ACTIVE_ALT)
			transy += 0.09f;
		else
			transy += 0.03f;
		break;
	case GLUT_KEY_LEFT:
		//moving left
		if (mod == GLUT_ACTIVE_ALT)
			transx += 0.09f;
		else
			transx += 0.03f;
		break;
	case GLUT_KEY_RIGHT:
		//moving right
		if (mod == GLUT_ACTIVE_ALT)
			transx -= 0.09f;
		else
			transx -= 0.03f;
		break;
	case GLUT_KEY_F1:
		//scaling up resulting image
		if (mod == GLUT_ACTIVE_ALT)
			scale += 0.09f;
		else
			scale += 0.03f;
		break;
	case GLUT_KEY_F2:
		//scaling down resulting image
		if (mod == GLUT_ACTIVE_ALT)
			scale -= 0.09f;
		else
			scale -= 0.03f;
		break;
	}
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
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;

}