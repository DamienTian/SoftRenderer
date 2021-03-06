/*
Vertex.h 顶点
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

#ifndef __VERTEX_H
#define __VERTEX_H

#include <deque>

//#include "Vector.h"
#include "Color.h"

class Vertex
{
public:
	// 顶点的几何坐标
	Vector4 _position;
	// 记录该顶点的顶点法线
	Vector4 _vertexNormal;

	// NOTE：tangent

	// 顶点的纹理坐标 
	//	NOTE：UV 不止一套，在一个模型有多套纹理贴图时，UV 坐标需要有多套
	_FLOAT _u, _v;

	// 顶点颜色 
	Color _color;

	// QUESTION：在《Math of 3D game programming》中提到：
	//			“Vertices carry information such as lighting colors and texture...”
	//		所以我能否在 Vertex 中加入有关光照影响的参数？
	// ANSWER：目前改为在生成像素阶段处理光照

	// 构造 + 析构函数
	Vertex();
	Vertex(Vector4 position, Vector4 vertexNormal, _FLOAT u, _FLOAT v, Color color);
	Vertex(const Vertex& other);
	Vertex& operator = (const Vertex& other);
	~Vertex() {}

	// 顶点加减运算
	Vertex operator + (const Vertex& other) const;
	Vertex operator - (const Vertex& other) const;
	Vertex operator * (_FLOAT scale) const;

	// 初始化
	// 处理纹理坐标，对纹理坐标进行透视校正插值
	// 原理参考：任程 --- 透视校正插值（perspective correct interpolation）
	void Init();

	// 顶点信息
	void Info();
};

// 计算插值
Vertex Interpolate(Vertex& v1, Vertex& v2, _FLOAT t);

#endif // !__VERTEX_H



