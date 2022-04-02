/*
Triangle.h
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#pragma once
#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include "Vertex.h"

class Triangle
{
public:
	// 三角形三顶点
	Vertex _v1, _v2, _v3;	// TODO：改成三个索引 int

	// 构造 + 析构函数
	Triangle() {}
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	
	~Triangle() {}

	bool IsTriangle() const;

	// 找三角形的中点（仅 _position ）
	static Vertex Centroid(Triangle triangle);
};

#endif // !__TRIANGLE_H
