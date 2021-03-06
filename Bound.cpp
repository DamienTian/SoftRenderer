/*
Bound.cpp 包围盒
图形学自学任务
author：田昊

* 参考：腾讯游戏学院 Bounds 概述与 AABB 包围盒应用
*/

//#include "stdafx.h"
#include "Bound.h"

AABB::AABB() {
	_vMin = Vector4(0.0f, 0.0f, 0.0f, 1.0);
	_vMax = Vector4(0.0f, 0.0f, 0.0f, 1.0);
}

AABB::AABB(_FLOAT xMin, _FLOAT xMax,
		_FLOAT yMin, _FLOAT yMax,
		_FLOAT zMin, _FLOAT zMax) {
	if (xMin > xMax) { Swap(xMin, xMax); }
	if (yMin > yMax) { Swap(yMin, yMax); }
	if (zMin > zMax) { Swap(zMin, zMax); }

	_vMin = Vector4(xMin, yMin, zMin, 1.0f);
	_vMax = Vector4(xMax, yMax, zMax, 1.0f);
}

AABB::AABB(Vector4 vMin, Vector4 vMax) {
	_vMin = vMin;
	_vMax = vMax;
}