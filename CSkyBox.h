#pragma once
#include"CBMPLoader.h"
#include"mysdl.h"
#define GL_CLAMP_TO_EDGE    0x812F
class CSkyBox
{
public:
    /** 构造函数 */
    CSkyBox();
    ~CSkyBox();

    /** 初始化 */
    bool Init();

    /** 渲染天空 */
    void  CreateSkyBox(float x, float y, float z,
        float width, float height,
        float length);

private:

    CBMPLoader  m_texture[6];   /**< 天空盒纹理 */
    const unsigned int MAP_WIDTH = 1024;
    const unsigned int CELL_WIDTH = 1;
    const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;
};

