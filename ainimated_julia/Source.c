#include <stdlib.h>
#include <glut.h>
#include <string.h>

// Initial window sizes
int win_width = 900;
int win_height = 600;
// Initial c values
float cRe = - 1.9;
float cIm = 0.245f;
int cReIsShrinking = 0;
// Show if animation or move timers work
int control_anim = 0; 
int control_move = 0;
// Show if parameters are changing
float delta_c = 0.005;
int delta_scale = 0;
int delta_move_x = 0;
int delta_move_y = 0;
// Parametrs
float scale = 0.3;
float move_x = 0;
float move_y = 0;

// Produces animation

void anim_timer(void)
{
	if (cReIsShrinking == 0)
		cRe += delta_c;
	else
		cRe -= delta_c;

	if (cRe > 1)
		cReIsShrinking = 1;
	if (cRe < -2)
		cReIsShrinking = 0;

	glutPostRedisplay();
	if (control_anim == 0)
	glutTimerFunc(60, anim_timer, 0);
}

// Produces moving and scaling

void move_timer(void)
{
	glutPostRedisplay();

	if (control_move == 1)
	glutTimerFunc(60, move_timer, 1);
}

// Handles keyboard calls

void pressSpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F3)
	{
		control_anim = (control_anim == 0) ? 1 : 0;
		if (control_anim == 0)
			glutTimerFunc(60,anim_timer, 0);
	
		return;
	}

	if (key == GLUT_KEY_F4)
		delta_c -= 0.001;

	if (key == GLUT_KEY_F5)
		delta_c += 0.001;

	if (control_anim == 0)
		return;

	switch (key)
	{
	case GLUT_KEY_F1:
		delta_scale = 1;
		break;
	case GLUT_KEY_F2:
		delta_scale = -1;
		break;
	case GLUT_KEY_LEFT:
		delta_move_x = -1;
		break;
	case GLUT_KEY_RIGHT:
		delta_move_x = 1;
		break;
	case GLUT_KEY_UP:
		delta_move_y = 1;
		break;
	case GLUT_KEY_DOWN:
		delta_move_y = -1;
		break;
	}

	control_move = 1;
	glutTimerFunc(60, move_timer, 1);
}

// Also handles keyboard calls

void releaseKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
	case GLUT_KEY_F2:
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: 
		delta_move_x = 0.0f;
		delta_scale = 0.0f;
		delta_move_y = 0.0;
		break;
	}

	control_move = 0;
	glutTimerFunc(60, move_timer, 1);
}

// Computes new X

float compX(float move)
{
	if (delta_move_x > 0)
		move += 0.01;
	else
		move -= 0.01;

	return move;
}

// Computes new Y

float compY(float move)
{
	if (delta_move_y > 0)
		move += 0.01;
	else
		move -= 0.01;

	return move;
}

// Computes new Scale

float compScale(float scale)
{
	if (delta_scale > 0)
		scale += 0.01;
	else
		scale -= 0.01;

	return scale;
}

// Drawing function

void display(void)
{
	float pixRe, pixIm, zRe, zIm;
	int x, y, i;
	int maxIterations = 255;
	
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	win_height = glutGet(GLUT_WINDOW_HEIGHT);

	if (delta_move_x)
		move_x = compX(move_x);
	if (delta_move_y)
		move_y = compY(move_y);
	if (delta_scale)
		scale = compScale(scale);

	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POINTS);

	for (int x = 0; x < win_width; x++)
	for (int y = 0; y < win_height; y++)
	{
		pixRe = (x - win_width / 2) / (scale* win_width)+move_x;
		pixIm = (y - win_height / 2) / (scale * win_height)+move_y;

		glColor3f(0, 0, 0);

		for (i = 0; i < maxIterations; i++)
		{
			zRe = pixRe * pixRe - pixIm * pixIm + cRe;
			zIm = 2 * pixRe * pixIm + cIm;

			if ((zRe * zRe + zIm * zIm) > 4)
			{
				glColor3f(10 * i / 255.0f, 0.2, 0.5);
				break;
			}

			//These are not already the pixel coordinates!
			pixRe = zRe;
			pixIm = zIm;
		}

		pixRe = (x - win_width / 2) / (0.5 * win_width);
		pixIm = (y - win_height / 2) / (0.5 * win_height);
		glVertex2f(pixRe, pixIm);
	}

	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//Initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(win_width, win_height);
	glDisable(GL_TEXTURE_2D);

	glutCreateWindow("Julias");

	//Register callback functions
	glutDisplayFunc(display);
	glutTimerFunc(45,anim_timer, 0);
	glutSpecialFunc(pressSpecialKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	glutMainLoop();

	return 0;
}