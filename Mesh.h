/*
Mesh.h 渲染结构
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
		OpenGL-tutorial --- OBJ
		R. Diane etc. --- MTL material format (Lightwave OBJ)
*/

//#pragma once
#ifndef __MESH_H
#define __MESH_H

#include <stdlib.h> // atof()

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

#include "Vertex.h"
#include "Bound.h"
#include "Transform.h"
#include "Material.h"

class Mesh
{
public:
	// 顶点缓冲与顶点数量
	Vertex * _verticesBuffer;
	_INT _verticesCount;

	// 顶点索引缓冲
	_INT * _indicesBuffer;
	_INT _indicesCount;

	// AABB 包围盒
	AABB * _bound;

	// 存储 .obj 中的信息
	std::string _mtlPath;

	// 构造 + 析构函数
	Mesh();
	Mesh(_INT verticesCount, _INT indexCount);
	Mesh(const Mesh& other);
	~Mesh();

	// 基于现在的 Mesh 更改包围盒大小
	void InitBound(Vector3 objectPosition = Vector3(0.0f, 0.0f, 0.0f));

	// 读取 .obj 文件模型
	bool ReadInOBJ(const char * path);

	// 打印 Mesh 信息
	void Info();
};


#endif // !__MESH_H