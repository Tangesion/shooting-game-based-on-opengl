#pragma once
#include"CBMPLoader.h"
#include"mysdl.h"
#define GL_CLAMP_TO_EDGE    0x812F
class CSkyBox
{
public:
    /** ���캯�� */
    CSkyBox();
    ~CSkyBox();

    /** ��ʼ�� */
    bool Init();

    /** ��Ⱦ��� */
    void  CreateSkyBox(float x, float y, float z,
        float width, float height,
        float length);

private:

    CBMPLoader  m_texture[6];   /**< ��պ����� */
    const unsigned int MAP_WIDTH = 1024;
    const unsigned int CELL_WIDTH = 1;
    const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;
};

