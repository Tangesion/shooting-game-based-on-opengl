#include"game.h"
void Game::SetLight()
{
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };  //���淴�����
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };  //���������
	GLfloat mat_shininess[] = { 0.0 };         //�߹�ָ��
	GLfloat light1_angle[] = { 15.0 };//LIGHT1��ɢ�Ƕ�
	GLfloat light_position[] = { 0.0, 1.0, -1.0, 0.0 };//LIGHT0λ��,���һ��ֵΪ0��Ϊƽ�й�
	GLfloat white_light[] = { 0.3, 0.3, 0.3, 1.0 };//LIGHT0����������ɫ(0.3,0.3,0.3), ����λΪ����
	GLfloat yellow_light[] = { 1,0.87,0.315,1.0 };//LIGHT1����
	
	GLfloat Light_Model_Ambient[] = { 0.1, 0.1, 0.1, 1.0 }; //���������
	glClearColor(0.0, 0.0, 0.0, 0.0);  //����ɫ
	glShadeModel(GL_SMOOTH);           //��������ģʽ
	//��������
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);*/
	//ƽ�й�LIGHT0����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);  //���淴���
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //��������� 
	//׶״��ԴLIGHT1����
	GLfloat lightKc = 1, lightKl = 0.0, lightKq = 0.0, lightExp = 2;//�йص��Դ��ɢǿ��˥���Ĳ�����
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, &lightKc);
	glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &lightKl);
	glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &lightKq);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_angle);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, &lightExp);
}
void Game:: moveLight(Camera camera)
{
	glPushMatrix();
	//����LIGHT0
	GLfloat light0_position[] = { 0.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//����LIGHT1
	GLfloat light1_position[] = { 0,0,0,1 };
	GLfloat light1_direction[] = { 0,0,0 };
	light1_position[0] = camera.eye.x;//�������λ������LIGHT1λ��
	light1_position[1] = camera.eye.y;
	light1_position[2] = camera.eye.z;
	light1_direction[0] =camera.get_look().x- camera.eye.x;//���������������LIGHT1����
	light1_direction[1] = camera.get_look().y- camera.eye.y;
	light1_direction[2] = camera.get_look().z-camera.eye.z;
	//cout<<"����" << light1_direction[0]<<","<<light1_direction[1]<<","<<light1_direction[2] << endl;
	//cout << "λ��" << light1_position[0] << ","<<light1_position[1] << ","<<light1_position[2] << endl;
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glPopMatrix();

}
void Game::axis(float length)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();
	glTranslated(0, 0, length - 0.2);
	glutWireCone(0.1, 1, 12, 9);
	glPopMatrix();
}
void Game::DrawAxis(float length)
{
	axis(0.5);    //x-axis
	glPushMatrix();
	glRotated(90, 0, 1.0, 0);
	axis(0.5);    //y-axis
	glRotated(-90, 1, 0, 0);
	axis(0.5);    //z-axis
	glPopMatrix();
}

void Game::Drawskybox(GLuint textureID)
{
	GLfloat wall_vert[][3] = {//�������飬ÿ��������Ϊһ��
		-50000,-50000,-50000,
		50000,-50000,-50000,
		50000,50000,-50000,
		-50000,50000,-50000,
	};
	GLubyte index_list[][4] = {//�����б����ñ�˳����������ĸ��������
		0,1,2,3,
	};
	GLfloat tex_coor[][2] = {//��Ӧÿ����������������
		0,0,//��һ�����Ӧͼ�����Ͻ�
		1,0,//�ڶ������Ӧͼ�����½�
		1,1,//���������Ӧͼ�����½�
		0,1,//���ĸ����Ӧͼ�����Ͻ�
		//���϶�Ӧ��ϵ����������Ҫ��ⲻͬϵͳ��ͼ������ı�ʾ����
	};
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, wall_vert);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coor);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, index_list);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}
void Game::readTexture()//��-�ڶ�ȡ����
{
	//ע���ļ�·�����Կ�ִ���ļ���Ŀ¼��ʼ����д�Ͼ���·��
	skyBoxFront = loadBMP_custom("source\\front.bmp");
	skyBoxBack = loadBMP_custom("source\\back.bmp");
	skyBoxLeft = loadBMP_custom("source\\left.bmp");
	skyBoxRight = loadBMP_custom("source\\right.bmp");
	skyBoxTop = loadBMP_custom("source\\top.bmp");
}

GLuint Game::loadBMP_custom(const char* imagepath)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char* data;
	FILE* file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }
	//else { printf("open successfully!\n"); }
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
	data = new unsigned char[imageSize];
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
	//Everything is in memory now, the file can be closed
	fclose(file);
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return textureID;
}
void Game::DrawScene(Camera cam)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//�����������ԣ������һ��ΪGL_REPLACEʱ����ͼЧ�����ܻ�����Ӱ��
	//����Ĵ���ͨ�����ݲ�ͬ�����ͼidʵ�ֻ滭��ͬ�����գ�ע�ⲻͬϵͳ�¶�ȡͼƬ�ķ���
	//��һ����ͬ�����Ա�Ҫʱ��Ҫ�鿴ʵ�ʽ����ͼ�ν�����ת���ܵõ�����Ľ��
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);//ʹ��պк���Ҿ���������ȣ����������ʵ��
	Drawskybox(skyBoxFront);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxLeft);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxBack);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxRight);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);//ʹ��պк���Ҿ���������ȣ����������ʵ��
	//glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	Drawskybox(skyBoxTop);
	glPopMatrix();
}

void Game::SetRandEnemy(int num, Enemy* enemy_list[])
{
	Point3 rand_position;
	unsigned seed;
	seed = time(0);
	srand(seed);
	static Enemy enemy[50];
	for (int i = 0; i < num; i++)
	{
		rand_position.x = rand() % (256 / 8);
		rand_position.z = rand() % (256 / 8);
		rand_position.y = 0;
		printf("%f %f %f\n", rand_position.x, rand_position.y, rand_position.z);
		Cube cube(rand_position, 0.25, 0.1, 0.5, 0, 0, 0, 0, 0);
		Enemy pr(cube);
		enemy[i]=pr;
		enemy_list[i] = &enemy[i];

	}
}