/*
Image.h ͼƬ�����ڶ�ȡ����
ͼ��ѧ��ѧ����
author�����

* �ο����㼣 -- BMP�ļ���ʽ���
Wiki
CSDN July_Qiao ��ȡ BMP �ļ�����ʾ����
*/

#ifndef __IMAGE_H
#define __IMAGE_H

//#pragma once
// #pragma comment(lib, "...")���� ... �����
#pragma comment(lib, "gdi32.lib")	// gdi32.lib Win ͼ�ν�����س���
#pragma comment(lib, "user32.lib")	// user32.lib Win ͼ�ν�����س���

#include "targetver.h"

// Windows ͷ�ļ�: 
#include <windows.h>

// C++ ͷ�ļ�
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <cassert>

// �ⲿ���򣺶�ȡ .bmp �ļ�
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
	// ͼ����
	_INT _width, _height;
	// ÿ�����ص�λ����24 λΪ���ͼ��
	_INT _bitCount;
	// ÿ��ͼƬ��Ϣ���ֽڴ�С
	_INT _lineByte;
	// ����ͼ�����ػ��壨��������ʽ��
	unsigned char * _pixelColorBuffer;
	// ��ɫ���棨����ͼ���� 24 λ���ɫͼʱ��
	RGBQUAD* _pixelColorTable;
	// �Ƚ������� .bmp �е����ݴ���һ�� color 2D array ��
	std::vector<std::vector<Color>> _colorBuffer;

	BMPImage();
	//BMPImage(_INT width, _INT height);
	~BMPImage();

	// ���� .bmp �ļ����洢
	static BMPImage* ReadInBMP(const char* path);
	// �����ͼ
	void CreateTexture();
};


#endif // !__IMAGE_H