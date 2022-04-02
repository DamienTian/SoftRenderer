/*
Scanline.h 扫描线
NOTE：由于扫描线对应屏幕上的光栅，所以数据类型都是整形的
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#pragma once
#ifndef __SCANLINE_H
#define __SCANLINE_H

#include "Pixel.h"

class Scanline
{
public:
	// 扫描的起点像素与步长
	Pixel _startPixel, _stepPixel;

	// 扫描线的起始坐标和扫描线的宽度
	_INT _x, _y, _width;

	// 构造 + 析构函数
	Scanline() {}
	Scanline(Vertex start, Vertex step, _INT x, _INT y, _INT width);
	Scanline(Pixel startPixel, Pixel stepPixel, _INT x, _INT y, _INT width);
	~Scanline() {}
};

#endif // !__SCANLINE_H



