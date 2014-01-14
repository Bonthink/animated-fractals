typedef struct
{
	float x;
	float y;
}vertex_t;

typedef struct
{
	vertex_t ver1;
	vertex_t ver2;
	vertex_t ver3;
}triangle_t;

triangle_t* triangle_create(void);

void triangle_initf(triangle_t* ptriangle,
	float v1x, float v1y, 
	float v2x, float v2y,
	float v3x, float v3y);

void triangle_initv(triangle_t* ptriangle,
	vertex_t ver1,
	vertex_t ver2,
	vertex_t ver3);

void triangle_delete(triangle_t* ptriangle);

vertex_t cal_middle_ver(vertex_t ver1, vertex_t ver2);