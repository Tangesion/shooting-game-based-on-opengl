#pragma once

#include"mysdl.h"
#include"camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Enemy.h"
#pragma warning(disable:4996);
class Game
{
public:
	void InitGame();
	void SetLight();
	void moveLight(Camera camera);
	void axis(float length);
	void DrawAxis(float length);
	void Drawskybox(GLuint textureID);
	GLuint skyBoxFront, skyBoxLeft, skyBoxRight, skyBoxBack, skyBoxTop;
	void readTexture();
	GLuint loadBMP_custom(const char* imagepath);
	void DrawScene(Camera cam);
	void SetRandEnemy(int num, Enemy* enemy_list[]);

};