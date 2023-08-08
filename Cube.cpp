#include "Cube.h"
Cube::Cube(Point3 o, float len, float wid, float hei,float ya,float pit, float R, float G, float B)
{
	origin = o;
	length = len;
	width = wid;
	height = hei;
	yaw = ya;
	pitch = pit;
	r = R;
	g = G;
	b = B;
}
Cube::Cube()
{
	Point3 p(0, 0, 0);
	origin = p;
	length = 1;
	width = 1;
	height = 1;
	yaw = 0;
	pitch = 0;
	r = 1;
	g = 1;
	b = 1;
}

void Cube::set(Point3 o, float len, float wid, float hei,float ya,float pit, float R, float G, float B)
{
	origin = o;
	length = len;
	width = wid;
	height = hei;
	yaw = ya;
	pitch = pit;
	r = R;
	g = G;
	b = B;
}
void Cube::SetAngle(float angle)
{
	yaw = angle;
}
void Cube::SetPosition(Point3 position)
{
	origin = position;
}
void Cube::Draw()
{
	//glBegin(GL_QUADS); // ��ʼ����������
	//glColor3f(0.0f, 1.0f, 0.0f); // ��ɫ��Ϊ��ɫ
	//glVertex3f(1.0f, 1.0f, -1.0f); // �ı��ε����϶��� (����)
	//glVertex3f(-1.0f, 1.0f, -1.0f); // �ı��ε����϶��� (����)
	//glVertex3f(-1.0f, 1.0f, 1.0f); // �ı��ε����¶��� (����)
	//glVertex3f(1.0f, 1.0f, 1.0f); // �ı��ε����¶��� (����)
	//����
	float pi = 3.14159265;
	float angle = 3.14159265 / 180 * yaw;
	float a = cos(angle);
	float b = cos(pi / 2 - angle);
	float c = cos(angle + pi / 2);
	glPushMatrix();
	
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//���϶���
	glVertex3f(origin.x, origin.y + height, origin.z);//���϶���
	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//���¶���
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z +length*c+ width*a);//���¶���	

	////����
	//glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ�ĳɳ�ɫ
	//glBegin(GL_QUADS);
	//glVertex3f(1.0f, -1.0f, 1.0f); // �ı��ε����϶���(����)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // �ı��ε����϶���(����)
	//glVertex3f(-1.0f, -1.0f, -1.0f); // �ı��ε����¶���(����)
	//glVertex3f(1.0f, -1.0f, -1.0f); // �ı��ε����¶���(����)

	//����
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//���϶���
	glVertex3f(origin.x, origin.y, origin.z);//���϶���
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//���¶���
	glVertex3f(origin.x + length*a+width*b, origin.y, origin.z + length*c+width*a);//���¶���


	//glColor3f(1.0f, 0.0f, 0.0f); // ��ɫ�ĳɺ�ɫ
	//glVertex3f(1.0f, 1.0f, 1.0f); // �ı��ε����϶���(ǰ��)
	//glVertex3f(-1.0f, 1.0f, 1.0f); // �ı��ε����϶���(ǰ��)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // �ı��ε����¶���(ǰ��)
	//glVertex3f(1.0f, -1.0f, 1.0f); // �ı��ε����¶���(ǰ��)

	//����
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z + length*c+width*a);//���϶���
	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//���϶���
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//���¶���
	glVertex3f(origin.x + length*a+width*b, origin.y, origin.z +length*c+ width*a);//���¶���

	//����

	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//���϶���
	glVertex3f(origin.x, origin.y + height, origin.z);//���϶���
	glVertex3f(origin.x, origin.y, origin.z);//���¶���
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//���¶���



	//glColor3f(1.0f, 1.0f, 0.0f); // ��ɫ�ĳɻ�ɫ
	//glVertex3f(0.5f, -1.0f, -0.5f); // �ı��ε����϶���(����)
	//glVertex3f(-0.5f, -1.0f, -0.5f); // �ı��ε����϶���(����)
	//glVertex3f(-0.5f, 0.5f, -0.5f); // �ı��ε����¶���(����)
	//glVertex3f(0.5f, 0.5f, -0.5f); // �ı��ε����¶���(����)
	//
	//glColor3f(0.0f, 0.0f, 1.0f); // ��ɫ�ĳ���ɫ
	//glVertex3f(-1.0f, 1.0f, 1.0f); // �ı��ε����϶���(����)
	//glVertex3f(-1.0f, 1.0f, -1.0f); // �ı��ε����϶���(����
	//glVertex3f(-1.0f, -1.0f, -1.0f); // �ı��ε����¶���(����)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // �ı��ε����¶���(����)
	
	//����

	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//���϶���
	glVertex3f(origin.x, origin.y + height, origin.z);//���϶���
	glVertex3f(origin.x, origin.y, origin.z);//���¶���
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//���¶���

	//����
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z +length*c+ width*a);//���϶���
	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//���϶���
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//���¶���
	glVertex3f(origin.x + length * a + width * b, origin.y, origin.z + length*c+ width*a);//���¶���
	//glColor3f(1.0f, 0.0f, 1.0f); // ��ɫ�ĳ�������ɫ
	//glVertex3f(1.0f, 1.0f, -1.0f); // �ı��ε����϶���(����)
	//glVertex3f(1.0f, 1.0f, 1.0f); // �ı��ε����϶���(����)
	//glVertex3f(1.0f, -1.0f, 1.0f); // �ı��ε����¶���(����)
	//glVertex3f(1.0f, -1.0f, -1.0f); // �ı��ε����¶���(����)
	glEnd(); // ��������ƽ���
	/*glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);*/
	glPopMatrix();
}