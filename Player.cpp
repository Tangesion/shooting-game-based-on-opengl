#include "Player.h"
void Player::Set(Point3 ey,Point3 he,float tal,float fa)
{
	eye = ey;
	heart = he;
	tall = tal;
	fat = fa;
}

bool Player::Collide_test(Cube *cube_list,int num,Point3 test_heart)
{
	float AXmax, AXmin, AYmax, AYmin, AZmax, AZmin; //墙壁
	float BXmax, BXmin, BYmax, BYmin, BZmax, BZmin;//玩家
	/*BXmax = heart.x + fat/2;
	BXmin = heart.x - fat/2;
	BYmax = heart.y + tall/2;
	BYmin = heart.y - tall / 2;
	BZmax= heart.z + fat / 2;
	BZmin = heart.z - fat / 2;*/

	BXmax = test_heart.x + fat / 2;
	BXmin = test_heart.x - fat / 2;
	BYmax = test_heart.y + tall / 2;
	BYmin = test_heart.y - tall / 2;
	BZmax = test_heart.z + fat / 2;
	BZmin = test_heart.z - fat / 2;
	for (int i = 0; i < num; i++)
	{
		AXmax = cube_list[i].origin.x + cube_list[i].length;
		AXmin = cube_list[i].origin.x;
		AYmax = cube_list[i].origin.y + cube_list[i].height;
		AYmin = cube_list[i].origin.y;
		AZmax = cube_list[i].origin.z + cube_list[i].width;
		AZmin = cube_list[i].origin.z;
		if (BXmin <= AXmax && BXmax >= AXmin &&
			BYmin <= AYmax && BYmax >= AYmin &&
			BZmin <= AZmax && BZmax >= AZmin)
		{
			return true;
		}
	}
	
	return false;
}
void Player::Update_position(Point3 ey)
{
	eye = ey;
	eye.z = eye.z ;
	heart.set(ey.x, ey.y - tall / 2, ey.z);
}
Point3 Player::test_Updata_position(Point3 ey)
{
	Point3 test_heart;
	test_heart.set(ey.x, ey.y - tall / 2, ey.z );
	return test_heart;
}
void Player::Origin()
{
	origin.x = heart.x - fat / 2;
	origin.y = heart.y - tall / 2;
	origin.z = heart.z - fat / 2;
}

void Player::QuasiCenter(Camera cam,Point3 ey,float len, float r, float g, float b)
{
	
	//glMatrixMode(GL_PROJECTION);       //设置合适的矩阵一后面将解释
	//glLoadIdentity();
	//gluOrtho2D(0.0, 640.0, 0.0, 480.0);//
	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, 640, 480);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	/*glTranslated(ey.x, ey.y, ey.z);
	glRotatef(yaw, 0, 1, 0);
	glRotatef(pitch, 1, 0, 0);*/
	glTranslatef(320, 240,0);
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex2f(0,  len);
	glVertex2f(0,  -len);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f( -len, 0);
	glVertex2f( len, 0);
	glEnd();
	////glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	//glutSwapBuffers();
	//glFlush();
}
bool Player::hit_target(Vector3 n,Enemy *enemy_list[],int num)
{
	float t = 0;
	Point3 bullet;
	for (int i = 0; i < 10000; i++)
	{
		
		bullet.set(eye.x + n.x * t,eye.y+n.y*t,eye.z+n.z*t);
		for (int j = 0; j < num; j++)
		{
			if (bullet.x >= enemy_list[j]->origin.x && bullet.x <= enemy_list[j]->origin.x + enemy_list[j]->length &&
				bullet.y >= enemy_list[j]->origin.y && bullet.y <= enemy_list[j]->origin.y + enemy_list[j]->height &&
				bullet.z >= enemy_list[j]->origin.z && bullet.z <= enemy_list[j]->origin.z + enemy_list[j]->width)
			{	
				printf("命中！\n");
				enemy_list[j]->HP--;
				if (enemy_list[j]->HP <=0)
				{
					enemy_list[j]->HP = 0;
					printf("敌人阵亡\n");
				}
				
				return true;
			}
		}
		t = t + 0.01;
		
	}
}
void Player::Draw()
{
	//glPushMatrix();
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	//绘制玩家所需的变换，注意顺序
	glTranslatef(heart.x,heart.y,heart.z);//使模型位置和相机重合
	glRotatef(yaw, 0, 1, 0);//使模型偏航角和相机相同
	glRotatef(pitch, 1, 0, 0);//使模型俯仰角和相机相同
	glTranslatef(0.5, 0, -3);//适当移位模型
	glTranslatef(0, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(90, 0, 1, 0);
	//glPopMatrix();
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glBindTexture(GL_TEXTURE_2D, starFighter);
	
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, model->vArray);
	glNormalPointer(GL_FLOAT, 0, model->nArray);
	glTexCoordPointer(2, GL_FLOAT, 0, model->tArray);
	glDrawElements(GL_TRIANGLES, model->faceList.size() * 3, GL_UNSIGNED_INT, model->fArray);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void Player:: Get_yp(float ya, float pi)
{
	yaw = ya;
	pitch = pi;
}
void Player::DrawHP()
{
	glViewport(0, 0, 640, 480);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	float width = 20;
	float length = 440;
	float ori = 100;
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(ori, 0);
	glVertex2f(ori, width);
	glVertex2f(ori + length*HP/100.0, width);
	glVertex2f(ori + length*HP/100.0, 0);
	glEnd();
}