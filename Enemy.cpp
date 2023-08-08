#include "Enemy.h"

void Enemy::Draw(Player &player)
{

	float pi = 3.14159265;
	float angle = 3.14159265 / 180 * yaw;
	float a = cos(angle);
	float b = cos(pi / 2 - angle);
	float c = cos(angle + pi / 2);
	if (HP == 0)
	{
		if (pitch >=90)
			pitch = 90;
		else
			pitch = pitch + 90.0/1000; //倒下的动作 1s中完成倒下动作
	}
	if (Ac&&HP>0)
	{
		//攻击1s
		if (pitch >-45&&down==1)
		{
			pitch = pitch - 45.0 / 500;
		}
		if(pitch<=-45)
		{
			down = 0;
			if (HP >= 0)
			{
				player.HP = player.HP - 5;
				printf("HP:%d\n", player.HP);
			}
			if (player.HP <= 0)
			{
				player.HP = 0;
				printf("YOU ARE DIE!\n");
			}
			
		}
		if (down == 0)
		{
			pitch = pitch + 45.0 / 500;
			if (pitch >= 0)
				down = 1;
		}
		//printf("HP:%d", HP);
		
	}
	
	float sita = 3.14159265 / 180 * pitch;
	float d = cos(sita);
	float e = cos(pi / 2 - sita);
	float f = cos(sita + pi / 2);
	glPushMatrix();
	//glRotatef(180, 1, 0, 0);
	
	
	glTranslatef(origin.x, origin.y, origin.z);
	glRotatef(yaw, 0, 1, 0);
	glRotatef(-pitch, 1, 0, 0);
	
		
	
	//上面
	
	glBegin(GL_QUADS);
	glVertex3f(length , height, 0);//右上顶点
	glVertex3f(0, height, 0);//左上顶点
	glVertex3f(0 , height, width);//左下顶点
	glVertex3f(length,  height, width );//右下顶点	


	
	//底面
	
	glVertex3f(length, 0, 0);//右上顶点
	glVertex3f(0, 0, 0);//左上顶点
	glVertex3f(0, 0, width);//左下顶点
	glVertex3f(length, 0, width);//右下顶点	

	//正面



	//后面

	

	glVertex3f(length, height, 0);//右上顶点
	glVertex3f(0, height, 0);//左上顶点
	glVertex3f(0, 0, 0);//左下顶点
	glVertex3f(length, 0, 0);//右下顶点	


	//左面



	glVertex3f(0, height, width);//右上顶点
	glVertex3f(0, height, 0);//左上顶点
	glVertex3f(0, 0, 0);//左下顶点
	glVertex3f(0, 0, width);//右下顶点	

	//右面


	glVertex3f(length, height, width);//右上顶点
	glVertex3f(length, height, 0);//左上顶点
	glVertex3f(length, 0, 0);//左下顶点
	glVertex3f(length, 0, width);//右下顶点	
	
	glEnd(); // 立方体绘制结束
	glPopMatrix();
	
	
	
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	glColor3f(1, 1, 1);
	glTranslatef(origin.x, origin.y, origin.z);
	glRotatef(yaw, 0, 1, 0);
	glRotatef(-pitch, 1, 0, 0);
	glBegin(GL_QUADS);
	
	/** 指定纹理坐标和顶点坐标 */
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(length,0,width);//右下顶点
	glTexCoord2f(1.0f, 1.0f); glVertex3f(length,height,width);//右上顶点
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,height,width);//左上顶点
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,width);//左下顶点
	glDisable(GL_TEXTURE_2D);
	
	glEnd();
	glPopMatrix();
	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);

}

void Enemy::FindPlayer(Player player)
{
	float angle;
	Vector3 n;
	Point3 move;
	if (HP > 0&&Ac==false)
	{
		n.set(player.eye.x - position.x, 0, player.eye.z - position.z);
		float pi = 3.14159265;
		angle = atan((player.eye.x - position.x) / (player.eye.z - position.z)) / (2 * pi) * 360;
		SetAngle(angle);  //朝向玩家
		position = origin;
		move.set(origin.x + n.x * v  , 0, origin.z + n.z * v );						//走向玩家
		SetPosition(move);
	}
	//printf("%f\n", angle);

}
Enemy::Enemy(Cube cub):Cube(cub)
{
	cube = cub;
	position = cube.origin;
}
void Enemy::set(Cube cub)
{
	cube = cub;
	position = cube.origin;
}
void Enemy::SetTime(int time)
{
	t = time;
}
bool Enemy::Init()
{
    char filename[128];                                         /**< 用来保存文件名 */
    const char* bmpName[] = { "Zomb" };
   
        sprintf(filename, "source/%s", bmpName[0]);
        strcat(filename, ".bmp");
        if (!m_texture.LoadBitmap(filename))                     /**< 载入位图文件 */
        {
            MessageBox(NULL, (LPCWSTR)"装载位图文件失败！", (LPCWSTR)"错误", MB_OK);    /**< 如果载入失败则弹出对话框 */
            exit(0);
        }
        glGenTextures(1, &m_texture.ID);                        /**< 生成一个纹理对象名称 */

        glBindTexture(GL_TEXTURE_2D, m_texture.ID);             /**< 创建纹理对象 */
        /** 控制滤波: */
        /*
            其中GL_TEXTURE_WRAP_S，GL_TEXTURE_WRAP_T通常可设置为GL_REPEAT或GL_CLAMP两种方式。
            当待填充的多边形大于纹理的时候，GL_REPEAT表示多余的部分用重复的方式填充；GL_CLAMP表示多余的部分用相连边缘的相邻像素填充。
            在实际绘制中，我们一般采用GL_CLAMP_EDGE来处理，这就消除了接缝处的细线，增强了天空盒的真实感。
        */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /** 创建纹理 */
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
            m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
            m_texture.image);
		//m_texture.FreeImage();
    return true;
}

void Enemy::Attack(Player player)
{
	float AXmax, AXmin, AYmax, AYmin, AZmax, AZmin; //敌人
	float BXmax, BXmin, BYmax, BYmin, BZmax, BZmin;//玩家
	BXmax = player.heart.x + player.fat / 2;
	BXmin = player.heart.x - player.fat / 2;
	BYmax = player.heart.y + player.tall / 2;
	BYmin = player.heart.y - player.tall / 2;
	BZmax = player.heart.z + player.fat / 2;
	BZmin = player.heart.z - player.fat / 2;
	AXmax = origin.x + length;
	AXmin = origin.x;
	AYmax = origin.y + height;
	AYmin = origin.y;
	AZmax = origin.z + width;
	AZmin = origin.z;
	//碰撞开始攻击
	if (BXmin <= AXmax && BXmax >= AXmin &&
		BYmin <= AYmax && BYmax >= AYmin &&
		BZmin <= AZmax && BZmax >= AZmin)
	{
		Ac = true;
		//printf("攻击！\n");
		
		
	}
	else
	{
		Ac = false;
	}

	
}