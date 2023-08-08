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
			pitch = pitch + 90.0/1000; //���µĶ��� 1s����ɵ��¶���
	}
	if (Ac&&HP>0)
	{
		//����1s
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
	
		
	
	//����
	
	glBegin(GL_QUADS);
	glVertex3f(length , height, 0);//���϶���
	glVertex3f(0, height, 0);//���϶���
	glVertex3f(0 , height, width);//���¶���
	glVertex3f(length,  height, width );//���¶���	


	
	//����
	
	glVertex3f(length, 0, 0);//���϶���
	glVertex3f(0, 0, 0);//���϶���
	glVertex3f(0, 0, width);//���¶���
	glVertex3f(length, 0, width);//���¶���	

	//����



	//����

	

	glVertex3f(length, height, 0);//���϶���
	glVertex3f(0, height, 0);//���϶���
	glVertex3f(0, 0, 0);//���¶���
	glVertex3f(length, 0, 0);//���¶���	


	//����



	glVertex3f(0, height, width);//���϶���
	glVertex3f(0, height, 0);//���϶���
	glVertex3f(0, 0, 0);//���¶���
	glVertex3f(0, 0, width);//���¶���	

	//����


	glVertex3f(length, height, width);//���϶���
	glVertex3f(length, height, 0);//���϶���
	glVertex3f(length, 0, 0);//���¶���
	glVertex3f(length, 0, width);//���¶���	
	
	glEnd(); // ��������ƽ���
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
	
	/** ָ����������Ͷ������� */
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(length,0,width);//���¶���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(length,height,width);//���϶���
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,height,width);//���϶���
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,width);//���¶���
	glDisable(GL_TEXTURE_2D);
	
	glEnd();
	glPopMatrix();
	if (lp)                         /** �ָ�����״̬ */
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
		SetAngle(angle);  //�������
		position = origin;
		move.set(origin.x + n.x * v  , 0, origin.z + n.z * v );						//�������
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
    char filename[128];                                         /**< ���������ļ��� */
    const char* bmpName[] = { "Zomb" };
   
        sprintf(filename, "source/%s", bmpName[0]);
        strcat(filename, ".bmp");
        if (!m_texture.LoadBitmap(filename))                     /**< ����λͼ�ļ� */
        {
            MessageBox(NULL, (LPCWSTR)"װ��λͼ�ļ�ʧ�ܣ�", (LPCWSTR)"����", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
            exit(0);
        }
        glGenTextures(1, &m_texture.ID);                        /**< ����һ������������� */

        glBindTexture(GL_TEXTURE_2D, m_texture.ID);             /**< ����������� */
        /** �����˲�: */
        /*
            ����GL_TEXTURE_WRAP_S��GL_TEXTURE_WRAP_Tͨ��������ΪGL_REPEAT��GL_CLAMP���ַ�ʽ��
            �������Ķ���δ��������ʱ��GL_REPEAT��ʾ����Ĳ������ظ��ķ�ʽ��䣻GL_CLAMP��ʾ����Ĳ�����������Ե������������䡣
            ��ʵ�ʻ����У�����һ�����GL_CLAMP_EDGE��������������˽ӷ촦��ϸ�ߣ���ǿ����պе���ʵ�С�
        */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /** �������� */
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
            m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
            m_texture.image);
		//m_texture.FreeImage();
    return true;
}

void Enemy::Attack(Player player)
{
	float AXmax, AXmin, AYmax, AYmin, AZmax, AZmin; //����
	float BXmax, BXmin, BYmax, BYmin, BZmax, BZmin;//���
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
	//��ײ��ʼ����
	if (BXmin <= AXmax && BXmax >= AXmin &&
		BYmin <= AYmax && BYmax >= AYmin &&
		BZmin <= AZmax && BZmax >= AZmin)
	{
		Ac = true;
		//printf("������\n");
		
		
	}
	else
	{
		Ac = false;
	}

	
}