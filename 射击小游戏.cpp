// 射击小游戏.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"mysdl.h"
#include"camera.h"
#include"Cube.h"
#include"Player.h"
#include"game.h"
#include"Enemy.h"
#include<SOIL/SOIL.h>
#include"CSkyBox.h"
#pragma comment(lib,"soil.lib")
using namespace std;
CSkyBox m_SkyBox;
Game game;
Camera cam;
Point3 p(0.5, 1, 0.5);
Point3 o(0, 0, 0);
Point3 pr(2, 0, 0);
Cube cube(o, 10, 10, 0.1, 0,0, 1, 1, 1);
Cube pazi(p, 0.25, 0.1, 0.5, 0,0, 0, 0, 1);
Cube pre(pr, 0.25, 0.1, 0.5, 0, 0,0, 0, 0);
int tim=0;
int Count = 0;
int num_enemy = 5;
//pazi.set(p, 0.25, 0.1, 0.5, 0, 0, 0, 1);
//cube.set(o, 10, 10, 0.1, 0, 1, 1, 1);
//pre.set(pr, 0.25, 0.1, 0.5, 0, 1, 0, 0);
//Cube enemy;
Cube me;
Player player;
Enemy * enemy_list[100];
Cube cube_list[100];
Point3 test_eye, test_heart;
Enemy enemy(pre);
Point3 x(0.6, 0.6, 5), y(0.6, 0.6, 0);
Vector3 z(0, 1, 0);
int num=2;
void Init()
{
	//glEnable(GL_TEXTURE_2D);
	/*cam.set(x, y, z);*/
	/** 初始化天空 */
	if (!m_SkyBox.Init())
	{
		MessageBox(NULL, (LPCWSTR)"初始化天空失败!", (LPCWSTR)"错误", MB_OK);
		exit(0);
	}
	/*enemy_list[0] = &enemy;
	enemy_list[0]->Init();*/
	game.SetRandEnemy(num_enemy, enemy_list);
	for (int i = 0; i < num_enemy; i++)
	{
		enemy_list[i]->Init();
		printf("%f %f %f\n",enemy_list[i]->origin.x, enemy_list[i]->origin.y, enemy_list[i]->origin.z);
		printf("%f %f %f\n", enemy.origin.x, enemy.origin.y, enemy.origin.z);
	}
	//enemy.Init();
	
}
void myKeyborad(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'p':
		break;
	case'w':
		//试探性移动
		
		test_eye = cam.test_slide(0, 0, -0.1);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(0, 0, -0.1);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("前方碰撞！\n");
		}
		
		break;
	case's':
		test_eye = cam.test_slide(0, 0, 0.1);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(0, 0, 0.1);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("后方碰撞！\n");
		}
		 break;
	case'd':
		test_eye = cam.test_slide(0.1, 0, 0);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(0.1, 0, 0);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("右方碰撞！\n");
		}
		break;
	case'a':
		test_eye = cam.test_slide(-0.1, 0, 0);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(-0.1, 0, 0);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("左方碰撞！\n");
		}
		break;
	case' ':
		test_eye = cam.test_slide(0, 0.1, 0);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(0, 0.1, 0);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("上方碰撞！\n");
		}
		break;
	case 'c':
		test_eye = cam.test_slide(0, -0.1, 0);
		test_heart = player.test_Updata_position(test_eye);
		if (!player.Collide_test(cube_list, num, test_heart))
		{
			cam.slide(0, -0.1, 0);
			player.Update_position(cam.eye);
		}
		else
		{
			printf("下方碰撞！\n");
		}
		break;

	default:
		break;
	}
	
	glutPostRedisplay();
}
bool firstmouse = true;
float pitch = 0, yaw = 0;
float last_x, last_y;
bool reset = false;
void myMousemotion(int x, int y)
{


	if (firstmouse || reset)
	{
		SetCursorPos(320, 240);
		last_x = x;
		last_y = y;
		firstmouse = false;
		reset = false;
	}
	//printf("%d,%d\n", x, y);
	float xoffset = last_x - x;
	float yoffset = last_y - y;
	last_x = x;
	last_y = y;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	//printf("%f,%f\n", xoffset, yoffset);
	yaw += xoffset;

	pitch += yoffset;
	//printf("pitch:%f  ,yaw:%f", pitch, yaw);
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = 89.0f;

	cam.FPS_Dirction(-yaw, pitch);
	player.Get_yp(yaw, pitch);
	glutPostRedisplay();
	if (x <= 5 || x >= 635 || y <= 5 || y >= 475)
	{
		SetCursorPos(320, 240);
		reset = true;
	}


}
void myMouseButton(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		Vector3 n;
		n.set(cam.get_look().x - cam.eye.x, cam.get_look().y - cam.eye.y, cam.get_look().z - cam.eye.z);
		player.hit_target(n, enemy_list, num_enemy);
	}
	
}
void myTimerfunc(int val)
{
	tim=tim+1;
	glutTimerFunc(10, myTimerfunc, 0);
}

void myDisplay(void)
{
	
	glViewport(0, 0, 640, 480);
	//glPushMatrix();
	glClearDepth(1);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/*| GL_STENCIL_BUFFER_BIT*/);
	glColor3f(1, 1, 1);
	glViewport(0, 0, 640, 480);
	cam.setShape(30.0f, 64.0f / 48.0f, 0.5f, 50.0f); 
	if(Count==0)
		cam.set(x, y, z);
	cam.setModelViewMatrix();
	Count++;
	//glutWireCube(1);
	//glutWireTeapot(1);
	//cam.printPosition();
	game.SetLight();
	game.moveLight(cam);
	
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);//6a
	m_SkyBox.CreateSkyBox(0, 0, 0, 1.0 / 2, 0.5 / 2, 1.0 / 2);
	//cube.Draw();
	pazi.Draw();
	
	//cout << enemy.Cube::height << endl;
	for (int i = 0; i < num_enemy; i++)
	{
		enemy_list[i]->FindPlayer(player);
		enemy_list[i]->SetTime(tim);
		enemy_list[i]->Attack(player);
		enemy_list[i]->Draw(player);
	}
	/*enemy.FindPlayer(player);
	enemy.SetTime(tim);
	enemy.Attack(player);
	enemy.Draw(player);*/
	player.Draw();
	player.DrawHP();
	//glutSwapBuffers();
	//glPopMatrix();

	player.QuasiCenter(cam, cam.get_look(), 10, 1, 0, 0);
	
	
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	//glDisable(GL_COLOR_MATERIAL);
}
ObjLoader playerObj;
void main(int argc, char** argv)
{
	playerObj.Init("AK47.obj");
	player.model = &playerObj;
	Point3 x(0.6, 0.6, 5), y(0.6, 0.6, 0),heart(0.6,0.3,3);
	/*Point3 x(500, 35, 400), y(501, 35, 400),heart(500,17,400);*/
	Vector3 z(0, 1, 0);
	player.Set(x, heart, 0.6, 2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("shooting game");
	//game.SetLight();
	Init();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glutKeyboardFunc(myKeyborad);
	glutPassiveMotionFunc(myMousemotion);
	glutMouseFunc(myMouseButton);
	glutDisplayFunc(myDisplay);
	//glutIdleFunc(myDisplay);
	glutTimerFunc(10, myTimerfunc, 1);
	/*glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glViewport(0, 0, 640, 480);
	
	cam.setShape(30.0f, 64.0f / 48.0f, 0.5f, 50.0f);*/
	
	glutMainLoop();
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
