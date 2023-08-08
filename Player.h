#pragma once
#include"mysdl.h"
#include"Cube.h"
#include"ObjLoader.h"
#include"camera.h"
#include"Enemy.h"
class Enemy;
class Player
{
public:
	float tall, fat;
	GLuint ID;
	ObjLoader* model;
	float yaw, pitch;
	Point3 eye, heart,origin;
	int HP = 100;
	void Set(Point3 ey,Point3 he,float tal,float fa);
	bool Collide_test(Cube *cube_list,int num,Point3 test_heart);//碰撞检测
	void Update_position(Point3 ey);
	Point3 test_Updata_position(Point3 ey);
	void Origin();
	void QuasiCenter(Camera cam,Point3 ey,float len,float r,float g,float b);//准心
	bool hit_target(Vector3 n,Enemy *enemy_list[],int num);  //方向向量
	void Draw();
	void Get_yp(float ya, float pi);
	void DrawHP();
	//Player();
};

