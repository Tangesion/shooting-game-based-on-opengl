#include"game.h"
void Game::SetLight()
{
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };  //镜面反射参数
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };  //漫反射参数
	GLfloat mat_shininess[] = { 0.0 };         //高光指数
	GLfloat light1_angle[] = { 15.0 };//LIGHT1扩散角度
	GLfloat light_position[] = { 0.0, 1.0, -1.0, 0.0 };//LIGHT0位置,最后一个值为0则为平行光
	GLfloat white_light[] = { 0.3, 0.3, 0.3, 1.0 };//LIGHT0参数，灯颜色(0.3,0.3,0.3), 第四位为开关
	GLfloat yellow_light[] = { 1,0.87,0.315,1.0 };//LIGHT1参数
	
	GLfloat Light_Model_Ambient[] = { 0.1, 0.1, 0.1, 1.0 }; //环境光参数
	glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
	glShadeModel(GL_SMOOTH);           //多变性填充模式
	//材质属性
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);*/
	//平行光LIGHT0设置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);  //镜面反射光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数 
	//锥状光源LIGHT1设置
	GLfloat lightKc = 1, lightKl = 0.0, lightKq = 0.0, lightExp = 2;//有关点光源扩散强度衰减的参数。
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
	//设置LIGHT0
	GLfloat light0_position[] = { 0.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//设置LIGHT1
	GLfloat light1_position[] = { 0,0,0,1 };
	GLfloat light1_direction[] = { 0,0,0 };
	light1_position[0] = camera.eye.x;//根据相机位置设置LIGHT1位置
	light1_position[1] = camera.eye.y;
	light1_position[2] = camera.eye.z;
	light1_direction[0] =camera.get_look().x- camera.eye.x;//根据相机朝向设置LIGHT1朝向
	light1_direction[1] = camera.get_look().y- camera.eye.y;
	light1_direction[2] = camera.get_look().z-camera.eye.z;
	//cout<<"方向" << light1_direction[0]<<","<<light1_direction[1]<<","<<light1_direction[2] << endl;
	//cout << "位置" << light1_position[0] << ","<<light1_position[1] << ","<<light1_position[2] << endl;
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
	GLfloat wall_vert[][3] = {//坐标数组，每三个数据为一组
		-50000,-50000,-50000,
		50000,-50000,-50000,
		50000,50000,-50000,
		-50000,50000,-50000,
	};
	GLubyte index_list[][4] = {//顶点列表，按该表顺序连接上面的各个坐标点
		0,1,2,3,
	};
	GLfloat tex_coor[][2] = {//对应每个坐标点的纹理坐标
		0,0,//第一个点对应图像左上角
		1,0,//第二个点对应图像左下角
		1,1,//第三个点对应图像右下角
		0,1,//第四个点对应图像右上角
		//以上对应关系可能有误，需要理解不同系统下图像坐标的表示方法
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
void Game::readTexture()//三-②读取纹理
{
	//注意文件路径，以可执行文件根目录开始或者写上绝对路径
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//设置纹理属性，当最后一项为GL_REPLACE时，贴图效果不受环境光影响
	//下面的代码通过传递不同面的贴图id实现绘画不同面的天空，注意不同系统下读取图片的方向
	//不一定相同，所以必要时需要查看实际结果对图形进行旋转才能得到合理的结果
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);//使天空盒和玩家距离适中相等，可以提高真实感
	Drawskybox(skyBoxFront);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxLeft);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxBack);
	glRotatef(90, 0, 1, 0);
	Drawskybox(skyBoxRight);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);//使天空盒和玩家距离适中相等，可以提高真实感
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