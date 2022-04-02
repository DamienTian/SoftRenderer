/*
Image.cpp 图片（用于读取纹理）
图形学自学任务
author：田昊

* 参考：足迹 -- BMP文件格式详解
Wiki
CSDN July_Qiao 读取 BMP 文件并显示出来
*/

#include "Image.h"

Image::Image(){}
Image::~Image(){}

BMPImage::BMPImage() {
	_pixelColorBuffer = nullptr;
	_pixelColorTable = nullptr; 
}

BMPImage::~BMPImage() {
	if (_pixelColorBuffer != nullptr) {
		delete[]_pixelColorBuffer;
		_pixelColorBuffer = nullptr;
	}
	if (_pixelColorTable != nullptr) {
		delete[]_pixelColorTable;
		_pixelColorTable = nullptr;
	}
}

BMPImage* BMPImage::ReadInBMP(const char * path) {
	using std::cout;
	using std::endl;
	using std::string;
	
	assert(!strcmp(&path[strlen(path) - 4], ".bmp"));

	BMPImage* result = new BMPImage();
	FILE * file = fopen(path, "rb");
	if (file == nullptr) {
		cout << ".bmp 文件打开失败" << endl;
		return nullptr;
	}

	// 跳过位图文件头结构 BITMAPFILEHEADER
	fseek(file, sizeof(BITMAPFILEHEADER), 0);

	// 定义位图信息头结构变量，读取位图信息存入内存
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, file);
	result->_width = infoHead.biWidth;
	result->_height = infoHead.biHeight;
	result->_bitCount = infoHead.biBitCount;

	// 若图像不是 24 位真彩图，则读取文件中的彩色表
	if (result->_bitCount == 8) {
		result->_pixelColorTable = new RGBQUAD[256];
		fread(result->_pixelColorTable, sizeof(RGBQUAD), 256, file);
	}

	// 每行的字节量，用于分配读取空间
	result->_lineByte = result->_width * result->_bitCount / 8;
	result->_pixelColorBuffer = new unsigned char[result->_lineByte * result->_height];

	// 读入 .bmp 像素颜色数据
	fread(result->_pixelColorBuffer, 1, result->_lineByte * result->_height, file);
	fclose(file);

	// 写入 2D color vector: _colorBuffer
	result->CreateTexture();
	return result;
}

void BMPImage::CreateTexture() {
	using std::vector;

	_INT _pixelNumber = 0;
	if (_bitCount == 24) {
		for (auto i = 0; i < _height; i++) {
			vector<Color> newLine;
			for (auto j = 0; j < _width; j++) {
				Color newPixelColor;
				for (int k = 0; k < 3; k++) {
					// 像素 R G B，分别对应不同的 k
					_INT pixelColorElement = *(_pixelColorBuffer + i * _lineByte + j * 3 + k);
					// NOTE：经实验，贴图中颜色顺序是反着来的 （B G R）
					switch (k) {
					case(0): { newPixelColor._b = pixelColorElement;	break; }
					case(1): { newPixelColor._g = pixelColorElement;	break; }
					case(2): { newPixelColor._r = pixelColorElement;	break; }
					default:	break;
					}
				}
				newLine.push_back(newPixelColor/** (1.0f / 255.0f)*/);
				_pixelNumber++;
			}
			_colorBuffer.push_back(newLine);
		}
	}
}


