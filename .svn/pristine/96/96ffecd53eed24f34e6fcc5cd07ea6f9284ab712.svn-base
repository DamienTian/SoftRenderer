/*
Pixel.cpp	像素（用于扫描线内部）
图形学自学任务
author：田昊

* 参考：晓峰哥 NB！
*/

#include "Pixel.h"

Pixel::Pixel(){}

Pixel::Pixel(Vector2 position, Vector3 normal, Vector2 textureCoord, Color color, _FLOAT depth) {
	_position = position;
	_normal = normal;
	_textureCoord = textureCoord;
	_color = color;
	_depth = depth;
}

Pixel::Pixel(Vector4 position, Vector4 normal, _FLOAT u, _FLOAT v, Color color) {
	_position = Vector2(position._x, position._y);
	_normal = Vector3(normal._x, position._y, position._z);
	_textureCoord = Vector2(u, v);
	_color = color;
	_depth = position._w;
}

Pixel::Pixel(Vertex v) {
	_position = Vector2(v._position._x, v._position._y);
	_normal = Vector3(v._vertexNormal._x, v._vertexNormal._y, v._vertexNormal._z);
	_textureCoord = Vector2(v._u, v._v);
	_color = v._color;
	_depth = v._position._w;
}

Pixel::~Pixel(){}

Pixel Pixel::operator + (const Pixel& other) const {
	Pixel result = Pixel(
		_position + other._position,
		_normal + other._normal,
		_textureCoord + other._textureCoord,
		_color + other._color,
		_depth + other._depth
	);
	return result;
}

Pixel Pixel::operator - (const Pixel& other) const {
	Pixel result = Pixel(
		_position - other._position,
		_normal - other._normal,
		_textureCoord - other._textureCoord,
		_color - other._color,
		_depth - other._depth
	);
	return result;
}

Pixel Pixel::operator * (_FLOAT scale) const {
	Pixel result = Pixel(
		_position * scale,
		_normal * scale,
		_textureCoord * scale,
		_color * scale,
		_depth * scale
	);
	return result;
}

Pixel Interpolate(Pixel& p1, Pixel& p2, _FLOAT t) {
	Pixel result = Pixel(
		Interpolate(p1._position, p2._position, t),
		Interpolate(p1._normal, p2._normal, t),
		Interpolate(p1._textureCoord, p2._textureCoord, t),
		Interpolate(p1._color, p2._color, t),
		Interpolate(p1._depth, p2._depth, t)
	);

	return result;
}