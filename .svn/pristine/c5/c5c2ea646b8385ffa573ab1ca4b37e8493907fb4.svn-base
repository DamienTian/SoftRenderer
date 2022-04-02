/*
Object.h 渲染物体（GameObject）
图形学自学任务
author：田昊

* 参考：OpenGL-tutorial --- OBJ
		R. Diane etc. --- MTL material format (Lightwave OBJ)
*/

#ifndef __OBJECT_H
#define __OBJECT_H

#include <stdlib.h> // atof()
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

#include "Mesh.h"
#include "Material.h"
#include "Image.h"

// NOTE：在引擎中，一个渲染物体对应 Mesh 和 Material 不止一个
//		目前的 RenderObject 先做只有一个 Mesh 对应一个 Material 的情况。
class RenderObject
{
public:
	std::string _name;
	// 位置以及倾斜角
	Vector3 _position;
	_FLOAT _theta;

	Mesh * _mesh;
	Material * _material;

	// 顶点索引顺序（是否是逆时针，默认不是）
	bool _isCounterClockwise = false;

	// 构造 + 析构
	RenderObject();
	RenderObject(std::string name, Vector3 position, _FLOAT alpha);
	~RenderObject();

	// 改变物体名称，位置，倾斜角与顶点绕序
	void SetName(std::string name);
	void SetPosition(Vector3 position);
	void SetAlpha(_FLOAT theta);

	// 写入一个 Mesh
	bool SetMesh(const Mesh& other);
	// 写入一个 Material
	bool SetMaterial(const Material& material);

	// 赋值函数
	
	
};

#endif // !__OBJECT_H

