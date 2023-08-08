#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;

#include <windows.h>
#include <assert.h>
#include <math.h>
//#include <gl/Gl.h>
//#include <gl/Glu.h>
//#include <gl/glut.h>
#include<GL/glew.h>
#include<GL/glut.h>
//@@@@@@@@@@@@@@@@@@ Point3 class @@@@@@@@@@@@@@@@
class Point2 {
public:
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2& p) { x = p.x; y = p.y; }

	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }

};
class Point3 {
public:
	float x, y, z;
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
	void set(Point3& p) { x = p.x; y = p.y; z = p.z; }
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	Point3() { x = y = z = 0; }
	void build4tuple(float v[])
	{// load 4-tuple with this color: v[3] = 1 for homogeneous
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
	}
};
//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3 {
public:
	float x, y, z;
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
	void set(Vector3 v) { x = v.x; y = v.y; z = v.z; }
	void flip() { x = -x; y = -y; z = -z; } // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	void normalize();//adjust this vector to unit length
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
	Vector3() { x = y = z = 0; } //default constructor
	Vector3 cross(Vector3 b); //return this cross b
	float dot(Vector3 b); // return this dotted with b

	//  operators
	Vector3 operator + (const Vector3& rhs) const {

		return(Vector3(x + rhs.x, y + rhs.y, z + rhs.z));

	}

	Vector3 operator - (const Vector3& rhs) const {

		return(Vector3(x - rhs.x, y - rhs.y, z - rhs.z));

	}

	Vector3 operator / (double k) const {

		return(Vector3(x / k, y / k, z / k));

	}

	Vector3 operator * (const double k) const {

		// scalar multiply
		return(Vector3(x * k, y * k, z * k));

	}

	Vector3 operator *= (const double k) {

		x *= k;
		y *= k;
		z *= k;

		return(*this);

	}

	Vector3 operator += (const Vector3& rhs) {

		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return(*this);

	}

	float& operator [] (int n) {

		// access like an array
		switch (n) {

		case 0: return(x);
		case 1: return(y);
		case 2: return(z);
		default: /* bug out */;

		}
	}

	friend ostream& operator << (ostream& o, Vector3 v) {

		o << v.x << " " << v.y << " " << v.z << endl;
		return(o);


	}
};

// @@@@@@@@@@@@@@@@@@@@@ Color3 class @@@@@@@@@@@@@@@@
class Color3 { // holds an red,green,blue 3-tuple
public:
	float red, green, blue;
	Color3() { red = green = blue = 0; }
	Color3(float r, float g, float b) { red = r; green = g; blue = b; }
	Color3(Color3& c) { red = c.red; green = c.green; blue = c.blue; }
	void set(float r, float g, float b) { red = r; green = g; blue = b; }
	void set(Color3& c)
	{
		red = c.red; green = c.green; blue = c.blue;
	}
	void add(float r, float g, float b)
	{
		red += r; green += g; blue += b;
	}
	void add(Color3& src, Color3& refl);
	void add(Color3& colr);
	void build4tuple(float v[]);
};


//@@@@@@@@@@@@@@@@@@@@ light class @@@@@@@@@@@@@@@@@@@
class Light { // for a linked list of light sources?color and position
public:
	Point3 pos;
	Color3 color;
	Light* next;
	void setPosition(Point3 p) { pos.set(p); }
	void setColor(Color3 c) { color.set(c); }
	Light() { next = NULL; }
};