#include <glut.h>   //����������� ���������� glut.h
#include "triangles.h"

void Initialize()
{
	//������� ������� (���������) ����
	glClearColor(1.0, 0.0, 1.0, 1.0);

	//���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void Draw()
{
	int i, j;
	//������� ����� glClear(GL_COLOR_BUFFER_BIT);

	triangle_t* pmaintriangle = triangle_create();
	triangle_initf(pmaintriangle, 0.25f, 0.25f, 0.75f, 0.25f, 0.50f, 0.75f);

	glColor3f(1.0, 1.0, 0.0); //�������� ����� ����
	glBegin(GL_TRIANGLES);
	glVertex3f(pmaintriangle->ver1.x, pmaintriangle->ver1.y, 0);
	glVertex3f(pmaintriangle->ver2.x, pmaintriangle->ver2.y, 0);
	glVertex3f(pmaintriangle->ver3.x, pmaintriangle->ver3.y, 0);
	glEnd();

	triangle_t* ptriangle1 = triangle_create();
	triangle_initv(ptriangle1, cal_middle_ver(pmaintriangle->ver1, pmaintriangle->ver2),
		cal_middle_ver(pmaintriangle->ver2, pmaintriangle->ver3),
		cal_middle_ver(pmaintriangle->ver3, pmaintriangle->ver1));

	glColor3f(0.0, 0.0, 1.0); //�������� ����� ����
	glBegin(GL_TRIANGLES);
	glVertex3f(ptriangle1->ver1.x, ptriangle1->ver1.y, 0);
	glVertex3f(ptriangle1->ver2.x, ptriangle1->ver2.y, 0);
	glVertex3f(ptriangle1->ver3.x, ptriangle1->ver3.y, 0);
	glEnd();

	triangle_delete(pmaintriangle);
	triangle_delete(ptriangle1);

	glFlush();
}

//����� � ������� ����
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);		//��������� ������ ����
	glutInitWindowPosition(100, 100);	//������� ����
	glutCreateWindow("Polygon");		//��� ����
	Initialize();						
	glutDisplayFunc(Draw);				//����������� ������� ���������
	glutMainLoop();

	return 0;
}