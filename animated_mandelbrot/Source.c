#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <malloc.h>
#include "ComplexNumbers.h"


int screen_width = 1000;
int screen_height = 700;
unsigned char* image;
float transx = 0.0;
float transy = 0.0;
float scale = 2.0;


void changeSize(int w, int h) {

	screen_width = w;
	screen_height = h;

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


unsigned char chooseColor(ComplexNumber c, unsigned char max_count)
{
	ComplexNumber z;
	unsigned char count = 0;
	float max_norm = 10;

	z.im = 0;
	z.re = 0;
	
	while (count++ < max_count)
	{
		z = complexSum(complexSquare(z), c);
		if (complexNorm(z) > max_norm)
			return count;
	}

	return 0;
}

void drawMandelbrot()
{
	ComplexNumber c;

	for (int y = 0; y < screen_height; y++)
	for (int x = 0; x < screen_width; x++)
	{
		c.re = transx - scale + (2 * scale * x) / screen_width;
		c.im = transy - scale + (2 * scale * y) / screen_height;
		image[3*y*screen_width+3*x+1] = 10000 * chooseColor(c, 64);
	}

}


void display()
{
	image = (unsigned char*)malloc(screen_width * screen_height * 3 * sizeof(unsigned char));

	drawMandelbrot();
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(screen_width, screen_height, GL_RGB, GL_UNSIGNED_BYTE, image);

	
	glutSwapBuffers();
	free(image);
}

void processSpecialKeys(int key, int x, int y) {
	int mod;
	mod = glutGetModifiers();

	switch (key)
	{
	case GLUT_KEY_UP:
		//moving up
		if (mod == GLUT_ACTIVE_ALT)
			transy += 0.09f;
		else
			transy += 0.03f;
		break;
	case GLUT_KEY_DOWN:
		//moving down
		if (mod == GLUT_ACTIVE_ALT)
			transy -= 0.09f;
		else
			transy -= 0.03f;
		break;
	case GLUT_KEY_LEFT:
		//moving left
		if (mod == GLUT_ACTIVE_ALT)
			transx -= 0.09f;
		else
			transx -= 0.03f;
		break;
	case GLUT_KEY_RIGHT:
		//moving right
		if (mod == GLUT_ACTIVE_ALT)
			transx += 0.09f;
		else
			transx += 0.03f;
		break;
	case GLUT_KEY_F1:
		//scaling up resulting image
		if (mod == GLUT_ACTIVE_ALT)
			scale -= 0.09f;
		else
			scale -= 0.03f;
		break;
	case GLUT_KEY_F2:
		//scaling down resulting image
		if (mod == GLUT_ACTIVE_ALT)
			scale += 0.09f;
		else
			scale += 0.03f;
		break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

int main(int argc, char *argv[])
{
	// Create OpenGL window
	glutInit(&argc, argv);
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Mandelbrot");

	// Specify callback function
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
	return 0;
}