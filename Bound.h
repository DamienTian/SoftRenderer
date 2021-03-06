/*
Bound.h 包围盒
图形学自学任务
author：田昊

* 参考：腾讯游戏学院 Bounds 概述与 AABB 包围盒应用
*/

#ifndef __BOUND_H
#define __BOUND_H

//#pragma once
#include "Mathf.h"

class AABB {
public:
	// 包围盒范围顶点位置
	Vector4 _vMin, _vMax;

	// 派生类构造函数 + 析构函数
	AABB();
	AABB(_FLOAT xMin, _FLOAT xMax,
		_FLOAT yMin, _FLOAT yMax,
		_FLOAT zMin, _FLOAT zMax);
	AABB(Vector4 vMin, Vector4 vMax);
	~AABB() {};
};

#endif // __BOUND_H
