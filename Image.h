/*
Image.h 图片（用于读取纹理）
图形学自学任务
author：田昊

* 参考：足迹 -- BMP文件格式详解
Wiki
CSDN July_Qiao 读取 BMP 文件并显示出来
*/

#ifndef __IMAGE_H
#define __IMAGE_H

//#pragma once
// #pragma comment(lib, "...")：将 ... 连入库
#pragma comment(lib, "gdi32.lib")	// gdi32.lib Win 图形界面相关程序
#pragma comment(lib, "user32.lib")	// user32.lib Win 图形界面相关程序

#include "targetver.h"

// Windows 头文件: 
#include <windows.h>

// C++ 头文件
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <cassert>

// 外部程序：读取 .bmp 文件
//#include "bitmap_image.hpp"
#include "Mathf.h"
#include "Color.h"

class Image
{
public:
	Image();
	~Image();
};

class BMPImage {
public:
	// 图像宽高
	_INT _width, _height;
	// 每个像素的位数（24 位为真彩图）
	_INT _bitCount;
	// 每行图片信息的字节大小
	_INT _lineByte;
	// 储存图像像素缓冲（以数组形式）
	unsigned char * _pixelColorBuffer;
	// 颜色表储存（当此图不是 24 位真彩色图时）
	RGBQUAD* _pixelColorTable;
	// 先将读过的 .bmp 中的数据存入一个 color 2D array 中
	std::vector<std::vector<Color>> _colorBuffer;

	BMPImage();
	//BMPImage(_INT width, _INT height);
	~BMPImage();

	// 读入 .bmp 文件并存储
	static BMPImage* ReadInBMP(const char* path);
	// 输出贴图
	void CreateTexture();
};


#endif // !__IMAGE_H