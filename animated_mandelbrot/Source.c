#include <stdlib.h>
#include <glut.h>

// Initial window sizes
int win_width = 900;
int win_height = 600;
// Initial c values
float color = 0.1;
int colorIsShrinking = 0;

// Show if animation or move timers work
int control_anim = 0; 
int control_move = 0;
// Show if parameters are changing
float delta_c = 0.2;
int delta_scale = 1;
int delta_move_x = 1;
int delta_move_y = 1;
// Parametrs
float scale = 0.3;
float move_x = -0.5;
float move_y = 0;
float angle = 0;

// Produces color animation

void anim_timer(void)
{

	if (color > 3.5)
		colorIsShrinking = 1;
	if (color < -0.5)
		colorIsShrinking = 0;

	if (colorIsShrinking)
		color -= delta_c;
	else
		color += delta_c;

	if (move_x > 1)
		delta_move_x = -1;
	if (move_x < -1)
		delta_move_x = 1;

	if (move_y > 0.5)
		delta_move_y = -1;
	if (move_y < -0.5)
		delta_move_y = 1;

	if (scale > 0.4)
		delta_scale = -1;
	if (scale < 0.2)
		delta_scale = 1;

	glutPostRedisplay();
	if (control_anim == 0)
	glutTimerFunc(60, anim_timer, 0);
}

// Computes new X

float compX(float move)
{
	if (delta_move_x > 0)
		move += 0.03;
	else
		move -= 0.03;

	return move;
}

// Computes new Y

float compY(float move)
{
	if (delta_move_y > 0)
		move += 0.03;
	else
		move -= 0.03;

	return move;
}

// Computes new Scale

float compScale(float scale)
{
	if (delta_scale > 0)
		scale += 0.005;
	else
		scale -= 0.005;

	return scale;
}

// Drawing function

void display(void)
{
	float pixRe, pixIm, zNewRe, zNewIm, zOldRe, zOldIm;
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

		zOldIm = zOldRe = 0;

		glColor3f(0, 0, 0);

		for (i = 0; i < maxIterations; i++)
		{
			zNewRe = zOldRe * zOldRe - zOldIm * zOldIm + pixRe;
			zNewIm = 2 * zOldRe * zOldIm + pixIm;

			if ((zNewRe * zNewRe + zNewIm * zNewIm) > 4)
			{
				glColor3f(1 * i / 255.0f + color, 0.2, ((i%4)/4.0)/color);
				break;
			}

			zOldRe = zNewRe;
			zOldIm = zNewIm;
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

	glutCreateWindow("Mandelbrot");

	//Register callback functions
	glutDisplayFunc(display);
	glutTimerFunc(45,anim_timer, 0);


	glutMainLoop();

	return 0;
}