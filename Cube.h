#pragma once
#include"mysdl.h"
class Cube
{
public:
	Point3 origin;
	float length, width, height;
	float r, g, b;
	float yaw;
	float pitch;
	Cube(Point3 o, float len, float wid, float hei,float ya,float pit, float R, float G, float B);
	Cube();
	void set(Point3 o, float len, float wid, float hei,float ya,float pit,float R, float G, float B);
	void Draw();
	void SetAngle(float angle);
	void SetPosition(Point3 position);
	
	
};

