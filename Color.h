/*
Color.h
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/
//#pragma once

#ifndef __COLOR_H
#define __COLOR_H

#include <iostream>
#include "Mathf.h"

//_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t);

class Color
{
public:
	// rgba
	_FLOAT _r, _g, _b, _a = 1.0f;

	// 构造 + 析构函数
	Color();
	Color(_FLOAT r, _FLOAT g, _FLOAT b);
	Color(_FLOAT r, _FLOAT g, _FLOAT b, _FLOAT a);
	Color(const Color& other);
	Color& operator = (const Color& other);
	~Color() {}

	// 颜色间计算
	Color operator + (const Color& c) const;
	Color operator + (_FLOAT offset) const;
	Color operator - (const Color& c) const;
	Color operator - (_FLOAT offset) const;
	Color operator * (const Color& c) const;
	Color operator * (_FLOAT offset) const;

	// 将颜色转换成一个 16 进制数字表示
	_INT ConvertToINT();

	// 传入数据流打印信息
	friend std::ostream& operator << (std::ostream& o, const Color& c);
};

// 计算颜色插值（实现颜色渐变）
Color Interpolate(Color& c1, Color& c2, _FLOAT t);

#endif // !__COLOR_H


