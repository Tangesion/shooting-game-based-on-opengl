#pragma once
#include"mysdl.h"
#include"Cube.h"
#include"Player.h"
#include"CBMPLoader.h"
class Player;
class Enemy:public Cube
{
public:
	Cube cube;
	Point3 position;
	float v=0.0002;
	float t = 0;
	int HP = 5;
	bool Ac = false;
	int down = 1;
	void Draw(Player &player);
	void FindPlayer(Player player);
	void SetTime(int time);
	void Attack(Player player);
	Enemy(Cube cub);
	void set(Cube cub);
	Enemy() {};
	bool Init();
	CBMPLoader m_texture;
};

