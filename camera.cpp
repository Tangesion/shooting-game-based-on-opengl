// Sandy Hill, November 19, 1999 for ECE660
// a Camera class ? partial implementation - for flying through 3D scenes.
//#include "stdafx.h"
#include "mysdl.h"
#include "camera.h"
#include <iostream>

//<<<<<<<<<<<<<<<<<<<<<<< default constructor >>>>>>>>>>>>>>>>>
Camera :: Camera(void)
{ // make default camera
  setDefaultCamera(); // good default values here
}

//<<<<<<<<<<<<<<<<<<<<<<< default constructor >>>>>>>>>>>>>>>>>
void Camera :: setDefaultCamera(void)
{ // make default camera
  setShape(45.0f, 640/(float)480, 0.1f, 200.0f); // good default values here
  set(Point3(5.0, 5.0, 5.0),  Point3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));
}

//<<<<<<<<<<<<<<<<<<<< set >>>>>>>>>>>>>>>>>>>
void Camera :: set(Point3 Eye, Point3 look, Vector3 up)
{ // make u, v, n vectors
    //Eye.y = -0.5; 
  uup = up;
  Eye.y = 0.5;
  eye.set(Eye);
  n.set(eye.x - look.x, eye.y - look.y,eye.z - look.z);
  u.set(up.cross(n));
  v.set(n.cross(u));
  u.normalize(); v.normalize(); n.normalize();
  setModelViewMatrix();
}

//<<<<<<<<<<<<<<<< setModelViewMatrix >>>>>>>>>>>>>>>>
void Camera :: setModelViewMatrix(void)
{ // load modelview matrix with existing camera values
  float m[16];
  Vector3 eVec(eye.x, eye.y, eye.z);
  m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eVec.dot(u);
  m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eVec.dot(v);
  m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -eVec.dot(n);
  m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0;
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(m);
}

//<<<<<<<<<<<<<<<<<<<<<<< setShape >>>>>>>>>>>>>>>>
void Camera :: setShape(float vAngle, float asp, float nr, float fr)
{ // load projection matrix and camera values
  viewAngle = vAngle;
  aspect = asp;
  nearDist = nr;
  farDist = fr;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(viewAngle, aspect, nearDist, farDist);
  glMatrixMode(GL_MODELVIEW); // set its mode back again
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< setAspect >>>>>>>>>>>>>>>>>>>>>>
void Camera:: setAspect(float asp)
{ aspect = asp;}

//<<<<<<<<<<<<<<<<<<<<<<< getShape >>>>>>>>>>>>>>>>
void Camera :: getShape(float& vAngle, float& asp, float& nr, float& fr)
{
  vAngle = viewAngle;
  asp = aspect;
  nr = nearDist;
  fr = farDist;
}

//<<<<<<<<<<<<<<<<<<<<<< slide >>>>>>>>>>>>>>>>>>>>>>..
void Camera :: slide(double du, double dv, double dn)
{ // slide both eye and lookAt by amount du * u + dv * v + dn * n;
  double delX = du*u.x + dv*v.x + dn*n.x;
  double delY = du*u.y + dv*v.y + dn*n.y;
  double delZ = du*u.z + dv*v.z + dn*n.z;
  eye.set(eye.x+delX, eye.y+delY/*-0.5*/, eye.z+delZ);
  //setModelViewMatrix();
}
Point3 Camera::test_slide(double du, double dv, double dn)
{
    Point3 test_eye;
    double delX = du * u.x + dv * v.x + dn * n.x;
    double delY = du * u.y + dv * v.y + dn * n.y;
    double delZ = du * u.z + dv * v.z + dn * n.z;
    test_eye.set(eye.x + delX, eye.y + delY/*-0.5*/, eye.z + delZ);
    return test_eye;
}
//<<<<<<<<<<<<<<<<<<<<<<<< rotAxes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Camera:: rotAxes(Vector3& a, Vector3& b, float angle)
{ // rotate orthogonal vectors a (like x axis) and b(like y axia) through angle degrees
  float ang = 3.14159265/180*angle;
  float C = cos(ang), S = sin(ang);
  Vector3 t(C * a.x + S * b.x, C * a.y + S * b.y, C * a.z + S * b.z); 
  b.set(-S * a.x + C * b.x, -S * a.y + C * b.y, -S * a.z + C * b.z); 
  a.set(t.x, t.y, t.z); // put tmp into a'
}

//<<<<<<<<<<<<<<<<<<<<<<<< roll >>>>>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: roll(float angle)
{
  rotAxes(u, v, angle);
  setModelViewMatrix();
};

//<<<<<<<<<<<<<<<<<<<<<<<< pitch >>>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: pitch(float angle)
{
  rotAxes(v, n, angle);
  setModelViewMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<<<< yawCameraLeft >>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: yaw(float angle)
{
  rotAxes(n, u, angle);
  setModelViewMatrix();
} 

void Camera::getAxes(Vector3 &u, Vector3 &v, Vector3 &n)
{
  u = this->u; v = this->v; n = this->n;
}

void Camera::setAxes(Vector3 &u, Vector3 &v, Vector3 &n)
{
  this->u = u; this->v = v; this->n = n;
  setModelViewMatrix();
}

void Camera::printPosition()
{
  cout << "eye: <" << eye.x << ", " << eye.y << ", " << eye.z << ">" << endl;
  cout << "lookAt: <" << eye.x-n.x << ", " << eye.y-n.y << ", "
       << eye.z-n.z << ">" << endl;
}
Point3 Camera::get_look()
{
    Point3 look;
    look.set(eye.x - n.x, eye.y - n.y, eye.z - n.z);
    return look;
}
void Camera::FPS_Dirction(float yaw_angle, float pitch_angle)
{
    float yaw_ang = 3.14159265 / 180 * yaw_angle;
    float pitch_ang= 3.14159265 / 180 * pitch_angle;
    float cos_yaw = cos(yaw_ang), sin_yaw = sin(yaw_ang);
    float cos_pitch = cos(pitch_ang), sin_pitch = sin(pitch_ang);
    Point3 dirct;
    dirct.x = eye.x+cos_pitch * sin_yaw;
    dirct.y = eye.y+sin_pitch;
    dirct.z = eye.z-cos_pitch * cos_yaw;
    eye.y = 0.5;
    set(eye, dirct, uup);
}