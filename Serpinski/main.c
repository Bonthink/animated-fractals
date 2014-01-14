#include <glut.h>  
#include <malloc.h>
#include "triangles.h"
#include <stdlib.h>

#define FRACTN 6

void Initialize()
{
	glClearColor(1.0, 0.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


void Draw()
{
	int i;
	triangle_t** lastouttriangles;
	triangle_t** lastintriangles;
	int currentotrianglesnumber = 0;
	int currentitrianglesnumber = 0;

	triangle_t* pmaintriangle = triangle_create();
	triangle_initf(pmaintriangle, 0.25f, 0.25f, 0.75f, 0.25f, 0.50f, 0.75f);

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(pmaintriangle->ver1.x, pmaintriangle->ver1.y, 0);
	glVertex3f(pmaintriangle->ver2.x, pmaintriangle->ver2.y, 0);
	glVertex3f(pmaintriangle->ver3.x, pmaintriangle->ver3.y, 0);
	glEnd();

	lastouttriangles = (triangle_t**)malloc(sizeof(triangle_t*));
	lastouttriangles[0] = pmaintriangle;
	currentotrianglesnumber += 1;

	lastintriangles = (triangle_t**)malloc(sizeof(triangle_t*));
	lastintriangles[0] = NULL;
	draw_inner_triangle(lastouttriangles, &lastintriangles, currentitrianglesnumber);
	currentitrianglesnumber += 1;
	
	for (i = 0; i < FRACTN; i++)
	{
		calc_outtriangles(&lastouttriangles,lastintriangles,currentotrianglesnumber); //calculate the yellow triangles
		currentotrianglesnumber *= 3;
		draw_inner_triangle(lastouttriangles, &lastintriangles, currentitrianglesnumber); //calculate and draw blue triangles 
		currentitrianglesnumber *= 3;
	}

	for (i = 0; i < currentotrianglesnumber; i++)
	{
		free(lastintriangles[i]);
		free(lastouttriangles[i]);
	}

	free(lastintriangles);
	free(lastouttriangles);

	glFlush();							//Finish OpenGL funtions
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);		
	glutInitWindowPosition(100, 100);	
	glutCreateWindow("Polygon");		
	Initialize();			
	glutDisplayFunc(Draw);				//Register DisplayFunction
	
	glutMainLoop();

	return 0;
}