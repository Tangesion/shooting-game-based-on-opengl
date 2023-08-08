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
	//glBegin(GL_QUADS); // 开始绘制立方体
	//glColor3f(0.0f, 1.0f, 0.0f); // 颜色改为蓝色
	//glVertex3f(1.0f, 1.0f, -1.0f); // 四边形的右上顶点 (顶面)
	//glVertex3f(-1.0f, 1.0f, -1.0f); // 四边形的左上顶点 (顶面)
	//glVertex3f(-1.0f, 1.0f, 1.0f); // 四边形的左下顶点 (顶面)
	//glVertex3f(1.0f, 1.0f, 1.0f); // 四边形的右下顶点 (顶面)
	//顶面
	float pi = 3.14159265;
	float angle = 3.14159265 / 180 * yaw;
	float a = cos(angle);
	float b = cos(pi / 2 - angle);
	float c = cos(angle + pi / 2);
	glPushMatrix();
	
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//右上顶点
	glVertex3f(origin.x, origin.y + height, origin.z);//左上顶点
	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//左下顶点
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z +length*c+ width*a);//右下顶点	

	////底面
	//glColor3f(1.0f, 1.0f, 1.0f); // 颜色改成橙色
	//glBegin(GL_QUADS);
	//glVertex3f(1.0f, -1.0f, 1.0f); // 四边形的右上顶点(底面)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // 四边形的左上顶点(底面)
	//glVertex3f(-1.0f, -1.0f, -1.0f); // 四边形的左下顶点(底面)
	//glVertex3f(1.0f, -1.0f, -1.0f); // 四边形的右下顶点(底面)

	//底面
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//右上顶点
	glVertex3f(origin.x, origin.y, origin.z);//左上顶点
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//左下顶点
	glVertex3f(origin.x + length*a+width*b, origin.y, origin.z + length*c+width*a);//右下顶点


	//glColor3f(1.0f, 0.0f, 0.0f); // 颜色改成红色
	//glVertex3f(1.0f, 1.0f, 1.0f); // 四边形的右上顶点(前面)
	//glVertex3f(-1.0f, 1.0f, 1.0f); // 四边形的左上顶点(前面)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // 四边形的左下顶点(前面)
	//glVertex3f(1.0f, -1.0f, 1.0f); // 四边形的右下顶点(前面)

	//正面
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z + length*c+width*a);//右上顶点
	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//左上顶点
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//左下顶点
	glVertex3f(origin.x + length*a+width*b, origin.y, origin.z +length*c+ width*a);//右下顶点

	//后面

	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//右上顶点
	glVertex3f(origin.x, origin.y + height, origin.z);//左上顶点
	glVertex3f(origin.x, origin.y, origin.z);//左下顶点
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//右下顶点



	//glColor3f(1.0f, 1.0f, 0.0f); // 颜色改成黄色
	//glVertex3f(0.5f, -1.0f, -0.5f); // 四边形的右上顶点(后面)
	//glVertex3f(-0.5f, -1.0f, -0.5f); // 四边形的左上顶点(后面)
	//glVertex3f(-0.5f, 0.5f, -0.5f); // 四边形的左下顶点(后面)
	//glVertex3f(0.5f, 0.5f, -0.5f); // 四边形的右下顶点(后面)
	//
	//glColor3f(0.0f, 0.0f, 1.0f); // 颜色改成蓝色
	//glVertex3f(-1.0f, 1.0f, 1.0f); // 四边形的右上顶点(左面)
	//glVertex3f(-1.0f, 1.0f, -1.0f); // 四边形的左上顶点(左面
	//glVertex3f(-1.0f, -1.0f, -1.0f); // 四边形的左下顶点(左面)
	//glVertex3f(-1.0f, -1.0f, 1.0f); // 四边形的右下顶点(左面)
	
	//左面

	glVertex3f(origin.x+width*b, origin.y + height, origin.z + width*a);//右上顶点
	glVertex3f(origin.x, origin.y + height, origin.z);//左上顶点
	glVertex3f(origin.x, origin.y, origin.z);//左下顶点
	glVertex3f(origin.x+width*b, origin.y, origin.z + width*a);//右下顶点

	//右面
	glVertex3f(origin.x + length*a+width*b, origin.y + height, origin.z +length*c+ width*a);//右上顶点
	glVertex3f(origin.x + length*a, origin.y + height, origin.z+length*c);//左上顶点
	glVertex3f(origin.x + length*a, origin.y, origin.z+length*c);//左下顶点
	glVertex3f(origin.x + length * a + width * b, origin.y, origin.z + length*c+ width*a);//右下顶点
	//glColor3f(1.0f, 0.0f, 1.0f); // 颜色改成紫罗兰色
	//glVertex3f(1.0f, 1.0f, -1.0f); // 四边形的右上顶点(右面)
	//glVertex3f(1.0f, 1.0f, 1.0f); // 四边形的左上顶点(右面)
	//glVertex3f(1.0f, -1.0f, 1.0f); // 四边形的左下顶点(右面)
	//glVertex3f(1.0f, -1.0f, -1.0f); // 四边形的右下顶点(右面)
	glEnd(); // 立方体绘制结束
	/*glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);*/
	glPopMatrix();
}