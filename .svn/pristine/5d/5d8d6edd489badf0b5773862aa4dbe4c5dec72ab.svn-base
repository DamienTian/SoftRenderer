/*
Color.cpp
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Color.h"

Color::Color() {
	_r = 1.0f;	_g = 1.0f;	_b = 1.0f;
}

Color::Color(_FLOAT r, _FLOAT g, _FLOAT b) {
	_r = Range(r, COLOR_MIN, COLOR_MAX);
	_g = Range(g, COLOR_MIN, COLOR_MAX);
	_b = Range(b, COLOR_MIN, COLOR_MAX);
}

Color::Color(_FLOAT r, _FLOAT g, _FLOAT b, _FLOAT a) {
	_r = Range(r, COLOR_MIN, COLOR_MAX);
	_g = Range(g, COLOR_MIN, COLOR_MAX);
	_b = Range(b, COLOR_MIN, COLOR_MAX);
	_a = Range(a, COLOR_MIN, COLOR_MAX);
}

Color::Color(const Color& other) {
	_r = other._r;
	_g = other._g;
	_b = other._b;
}

Color& Color::operator = (const Color& other) {
	if (&other != this) {
		_r = other._r;
		_g = other._g;
		_b = other._b;
	}
	return *this;
}

// 颜色间计算
Color Color::operator + (const Color& c) const {
	return Color(_r + c._r, _g + c._g, _b + c._b);
}

Color Color::operator + (_FLOAT offset) const {
	return Color(_r + offset, _g + offset, _b + offset);
}

Color Color::operator - (const Color& c) const {
	return Color(_r - c._r, _g - c._g, _b - c._b);
}

Color Color::operator - (_FLOAT offset) const {
	return Color(_r - offset, _g - offset, _b - offset);
}

Color Color::operator * (const Color& c) const {
	return Color(_r * c._r, _g * c._g, _b * c._b);
}

Color Color::operator * (_FLOAT offset) const {
	return Color(_r * offset, _g * offset, _b * offset);
}

_INT Color::ConvertToINT() {
	return ((_INT)_r  << 16) | ((_INT)_g << 8) | (_INT)_b;
}

// 计算颜色插值（实现颜色渐变填充）
Color Interpolate(Color& c1, Color& c2, _FLOAT t) {
	return Color(
		Interpolate(c1._r, c2._r, t),
		Interpolate(c1._g, c2._g, t),
		Interpolate(c1._b, c2._b, t)
	);
}

// 传入数据流打印信息
std::ostream & operator << (std::ostream& o, const Color& c) {
	o << "红 = "<<  c._r << ", 绿 = " << c._g << ", 蓝 = " << c._b;
	return o;
}