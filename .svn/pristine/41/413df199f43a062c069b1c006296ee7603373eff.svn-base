/*
Triangle.cpp
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) : _v1(v1), _v2(v2), _v3(v3) {}

bool Triangle::IsTriangle() const {
	if (_v1._position._x == _v2._position._x &&
		_v1._position._x == _v3._position._x) {
		return false;
	}
	if (_v1._position._y == _v2._position._y &&
		_v1._position._y == _v3._position._y) {
		return false;
	}
	return true;
}

Vertex Triangle::Centroid(Triangle triangle) {
	return (triangle._v1 + triangle._v2 + triangle._v3) * (1 / 3);
}