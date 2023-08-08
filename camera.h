#pragma once

//#ifndef _HlCamera
//#define _HlCamera
#include "mysdl.h" // needed for Vector3 definitions

//##################### class CAMERA ######################
class Camera{
 private:
  

 public:
	 Point3 eye;
	 Vector3 u, v, n, uup;
	 float aspect, nearDist, farDist, viewAngle;
	 void setModelViewMatrix();
	  Camera(void);
	  void roll(float angle);
	  void pitch(float angle);
	  void yaw(float angle);
	  void slide(double du, double dv, double dn);
	  void set(Point3 Eye, Point3 look, Vector3 up);
	  void setShape(float viewAngle, float aspect, float Near, float Far);
	  void setAspect(float asp);
	  void getShape(float& viewAngle, float& aspect, float& Near, float& Far);
	  void rotAxes(Vector3& a, Vector3& b, float angle);
	  void setDefaultCamera();
	  void getAxes(Vector3 &u, Vector3 &v, Vector3 &n);
	  void setAxes(Vector3 &u, Vector3 &v, Vector3 &n);
	  void printPosition();
	  void FPS_Dirction(float yaw_angle,float pitch_angle);
	  Point3 test_slide(double du, double dv, double dn);
	  Point3 get_look();
};
//#endif

