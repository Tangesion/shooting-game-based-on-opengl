#pragma once
#include"mysdl.h"
#define BITMAP_ID 0x4D42 
#pragma warning(disable:4996);
class CBMPLoader
{
public:
    CBMPLoader();
    ~CBMPLoader();

    bool LoadBitmap(char* filename); /**< װ��һ��bmp�ļ� */
    void FreeImage();                /**< �ͷ�ͼ������ */

    unsigned int ID;                 /**< ���������ID�� */
    int imageWidth;                  /**< ͼ���� */
    int imageHeight;                 /**< ͼ��߶� */
    unsigned char* image;            /**< ָ��ͼ�����ݵ�ָ�� */
 
};

