#include "triangles.h"
#include <malloc.h>
#include <glut.h>
#include <stdlib.h>

triangle_t* triangle_create()
{
	triangle_t* ptriangle = (triangle_t*)malloc(sizeof(triangle_t));
	return ptriangle;
}

void triangle_initf(triangle_t* ptriangle,
	float v1x, float v1y,
	float v2x, float v2y,
	float v3x, float v3y)
{
	ptriangle->ver1.x = v1x;
	ptriangle->ver1.y = v1y;
	ptriangle->ver2.x = v2x;
	ptriangle->ver2.y = v2y;
	ptriangle->ver3.x = v3x;
	ptriangle->ver3.y = v3y;
}

void triangle_initv(triangle_t* ptriangle,
	vertex_t ver1,
	vertex_t ver2,
	vertex_t ver3)
{
	ptriangle->ver1 = ver1;
	ptriangle->ver2 = ver2;
	ptriangle->ver3 = ver3;
}

void triangle_delete(triangle_t* ptriangle)
{
	free(ptriangle);
}

vertex_t calc_middle_ver(vertex_t ver1,vertex_t ver2)
{
	vertex_t ver;

	ver.x = (ver1.x + ver2.x) / 2.0f;
	ver.y = (ver1.y + ver2.y) / 2.0f;

	return ver;
}

float calc_middlef(float arg1, float arg2)
{
	float arg = (arg1 + arg2) / 2.0;
	return arg;
}

void draw_inner_triangle(triangle_t** lastouttriangles, triangle_t*** plastintriangles, int currentitrianglesnumber)
{
	int i;
	triangle_t** nlit;

	if (currentitrianglesnumber == 0)
		nlit = (triangle_t**)malloc(sizeof(triangle_t*));
	else
		nlit = (triangle_t**)malloc(3 * currentitrianglesnumber*sizeof(triangle_t*));

	if (currentitrianglesnumber == 0)
	{
		triangle_t* ptriangle = triangle_create();
		triangle_initv(ptriangle,
			calc_middle_ver(lastouttriangles[0]->ver1, lastouttriangles[0]->ver2),
			calc_middle_ver(lastouttriangles[0]->ver2, lastouttriangles[0]->ver3),
			calc_middle_ver(lastouttriangles[0]->ver3, lastouttriangles[0]->ver1));

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(ptriangle->ver1.x, ptriangle->ver1.y, 0);
		glVertex3f(ptriangle->ver2.x, ptriangle->ver2.y, 0);
		glVertex3f(ptriangle->ver3.x, ptriangle->ver3.y, 0);
		glEnd();

		nlit[0] = ptriangle;
	}
	else
		for (i = 0; i<(3*currentitrianglesnumber); i++)
		{
			triangle_t* ptriangle = triangle_create();
			triangle_initv(ptriangle, 
				calc_middle_ver(lastouttriangles[i]->ver1, lastouttriangles[i]->ver2),
				calc_middle_ver(lastouttriangles[i]->ver2, lastouttriangles[i]->ver3),
				calc_middle_ver(lastouttriangles[i]->ver3, lastouttriangles[i]->ver1));
	
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_TRIANGLES);
			glVertex3f(ptriangle->ver1.x, ptriangle->ver1.y, 0);
			glVertex3f(ptriangle->ver2.x, ptriangle->ver2.y, 0);
			glVertex3f(ptriangle->ver3.x, ptriangle->ver3.y, 0);
			glEnd();
	
			nlit[i] = ptriangle;
		}

	for (i = 0; i < (currentitrianglesnumber); i++)
	{
		free((*plastintriangles)[i]);
	}

	if (currentitrianglesnumber!=0)
		*plastintriangles = (triangle_t**)realloc(*plastintriangles, 3*currentitrianglesnumber*sizeof(triangle_t*));
	*plastintriangles = nlit;
	nlit = NULL;
	free(nlit);
}

void calc_outtriangles(triangle_t*** plastouttriangles, triangle_t** lastintriangles, int currenttrianglesnumber)
{
	int i;
	triangle_t** nlot;

	nlot = (triangle_t**)malloc(3 * currenttrianglesnumber*sizeof(triangle_t*));

	for (i = 0; i < currenttrianglesnumber; i++)
	{
		triangle_t* ptriangle1 = triangle_create();
		triangle_initf(ptriangle1,
			(*plastouttriangles)[i]->ver1.x, (*plastouttriangles)[i]->ver1.y,
			lastintriangles[i]->ver1.x, lastintriangles[i]->ver1.y,
			lastintriangles[i]->ver3.x, lastintriangles[i]->ver3.y);
		nlot[3 * i + 0] = ptriangle1;

		triangle_t* ptriangle2 = triangle_create();
		triangle_initf(ptriangle2,
			lastintriangles[i]->ver1.x, lastintriangles[i]->ver1.y,
			(*plastouttriangles)[i]->ver2.x, (*plastouttriangles)[i]->ver2.y,
			lastintriangles[i]->ver2.x, lastintriangles[i]->ver2.y);
		nlot[3 * i + 1] = ptriangle2;

		triangle_t* ptriangle3 = triangle_create();
		triangle_initf(ptriangle3,
			lastintriangles[i]->ver3.x, lastintriangles[i]->ver3.y,
			lastintriangles[i]->ver2.x, lastintriangles[i]->ver2.y,
			(*plastouttriangles)[i]->ver3.x, (*plastouttriangles)[i]->ver3.y);
		nlot[3 * i + 2] = ptriangle3;
	}

	for (i = 0; i < currenttrianglesnumber; i++)
	{
		free((*plastouttriangles)[i]);
	}

	*plastouttriangles = (triangle_t**)realloc(*plastouttriangles,3 * currenttrianglesnumber*sizeof(triangle_t*));
	*plastouttriangles = nlot;
	nlot = NULL;
	free(nlot);
}