#pragma once
#include"mysdl.h"
#define BITMAP_ID 0x4D42 
#pragma warning(disable:4996);
class CBMPLoader
{
public:
    CBMPLoader();
    ~CBMPLoader();

    bool LoadBitmap(char* filename); /**< 装载一个bmp文件 */
    void FreeImage();                /**< 释放图像数据 */

    unsigned int ID;                 /**< 生成纹理的ID号 */
    int imageWidth;                  /**< 图像宽度 */
    int imageHeight;                 /**< 图像高度 */
    unsigned char* image;            /**< 指向图像数据的指针 */
 
};

