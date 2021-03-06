/*
Pixel.h	像素（用于扫描线）
图形学自学任务
author：田昊

* 参考：晓峰哥 NB！
*/

#ifndef __PIXEL_H
#define __PIXEL_H

#include "Mathf.h"
#include "Color.h"
#include "Vertex.h"

class Pixel
{
public:
	// 位置（置于平面中）
	Vector2 _position;
	// 像素法向量
	Vector3 _normal;
	// 纹理坐标
	//	NOTE：这是一个 Vector2, 其中 x 是 u, y 是 v
	Vector2 _textureCoord;
	// 像素颜色
	Color _color;
	// 像素深度信息
	_FLOAT _depth;

	// 构造 + 析构函数
	Pixel();
	Pixel(Vector2 position, Vector3 normal, Vector2 textureCoord, Color color, _FLOAT depth);
	Pixel(Vector4 position, Vector4 normal, _FLOAT u, _FLOAT v, Color color);
	Pixel(Vertex v);
	~Pixel();

	// 像素加减运算
	Pixel operator + (const Pixel& other) const;
	Pixel operator - (const Pixel& other) const;
	Pixel operator * (_FLOAT scale) const;
};

// 计算插值
Pixel Interpolate(Pixel& p1, Pixel& p2, _FLOAT t);

#endif // !__PIXEL_H