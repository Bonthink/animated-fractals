#include "triangles.h"
#include <malloc.h>

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

vertex_t cal_middle_ver(vertex_t ver1,vertex_t ver2)
{
	vertex_t ver;

	ver.x = (ver1.x + ver2.x) / 2.0f;
	ver.y = (ver1.y + ver2.y) / 2.0f;

	return ver;
}