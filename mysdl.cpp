#include"mysdl.h"
double dot3(Vector3 a, Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
//
//<<<<<<<<<<<<<<<<<<<<<< checkOrthogVects >>>>>>>>>>>>>>>>
void checkOrthogVects(Vector3 a, Vector3 b, Vector3 c)
{ // check that system is orthonormal
	double aDotb = fabs(dot3(a, b));
	double aDotc = fabs(dot3(a, c));
	double bDotc = fabs(dot3(b, c));
	if (aDotb > 0.000001 || aDotc > 0.000001 || bDotc > 0.000001)
		cout << " Bad!! vectors NOT orthogonal!\n";
	double A = fabs(dot3(a, a) - 1.0);
	double B = fabs(dot3(b, b) - 1.0);
	double C = fabs(dot3(c, c) - 1.0);
#if 0
	if (A > 0.0000001)
		cout << "Bad!! first is not normalized!\n";
	if (B > 0.0000001)
		cout << "Bad!! second is not normalized!\n";
	if (C > 0.0000001)
		cout << "Bad!! third is not normalized!\n";
#endif
}

// Vector3 methods
Vector3 Vector3::cross(Vector3 b) //return this cross b
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b) // return this dotted with b
{
	return x * b.x + y * b.y + z * b.z;
}

void Vector3::normalize()//adjust this vector to unit length
{
	double sizeSq = x * x + y * y + z * z;
	if (sizeSq < 0.0000001)
	{
		cerr << "\nnormalize() sees vector (0,0,0)!";
		return; // does nothing to zero vectors;
	}
	float scaleFactor = 1.0 / (float)sqrt(sizeSq);
	x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
}

// Color3 methods
void Color3::add(Color3& src, Color3& refl)
{ // add the product of source color and reflection coefficient
	red += src.red * refl.red;
	green += src.green * refl.green;
	blue += src.blue * refl.blue;
}
void Color3::add(Color3& colr)
{ // add colr to this color
	red += colr.red; green += colr.green; blue += colr.blue;
}

void Color3::build4tuple(float v[])
{// load 4-tuple with this color: v[3] = 1 for homogeneous
	v[0] = red; v[1] = green; v[2] = blue; v[3] = 1.0f;
}
