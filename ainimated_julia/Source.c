#include <stdlib.h>
#include <glut.h>

int win_width = 800;
int win_height = 640;
float cRe = -1.2;
float cIm = 0.245f;
int flag = 0;
int control_timer = 0; // Indicates is the program interactive
int control_anim = 0;
int delta_scale = 0;
int delta_move_x = 0;
int delta_move_y = 0;
float scale = 1;
float move_x = 0;
float move_y = 0;

void timer(void)
{
	if (flag == 0)
		cRe += 0.01;
	else
		cRe -= 0.01;

	if (cRe > 1)
		flag = 1;
	if (cRe < -2)
		flag = 0;

	glutPostRedisplay();
	if (control_timer == 0)
	glutTimerFunc(60, timer, 0);
}

void anim_timer(void)
{
	glutPostRedisplay();

	if (control_anim == 1)
	glutTimerFunc(60, anim_timer, 1);
}

void pressSpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F3)
	{
		control_timer = (control_timer == 0) ? 1 : 0;
		if (control_timer == 0)
			glutTimerFunc(60, timer, 0);
	
		return;
	}

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

	control_anim = 1;
	glutTimerFunc(60, anim_timer, 1);
}

void releaseKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
	case GLUT_KEY_F2:
		delta_scale = 0.0f;
		break;
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: 
		delta_move_x = 0.0f;
		break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: 
		delta_move_y = 0.0;
		break;
	}

	control_anim = 0;
	glutPostRedisplay();
}

float compX(float move)
{
	if (delta_move_x > 0)
		move += 0.001;
	else
		move -= 0.001;

	return move;
}

float compY(float move)
{
	if (delta_move_y > 0)
		move += 0.001;
	else
		move -= 0.001;

	return move;
}

float compScale(float scale)
{
	if (delta_scale > 0)
		scale += 0.01;
	else
		scale -= 0.01;

	return scale;
}

void display(void)
{
	float pixRe, pixIm, zRe, zIm;
	int x, y, i;
	int maxIterations = 255;
	

	if (delta_move_x)
		move_x = compX(move_x);
	if (delta_move_y)
		move_y = compY(move_y);
	if (delta_scale)
		scale = compScale(scale);

	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(move_x, move_y, 0);
	glScalef(scale, scale, scale);

	glBegin(GL_POINTS);

	for (int x = 0; x < win_width; x++)
	for (int y = 0; y < win_height; y++)
	{
		pixRe = 1.5 * (x - win_width / 2) / (0.3*win_width);
		pixIm = (y - win_height / 2) / (0.3 * win_height);

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

		pixRe = 1.5 * (x - win_width / 2) / (scale * win_width)+move_x;
		pixIm = (y - win_height / 2) / (scale * win_height)+move_y;
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
	glutTimerFunc(45, timer, 0);
	glutSpecialFunc(pressSpecialKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	//glutIdleFunc(display);

	glutMainLoop();

	return 0;
}