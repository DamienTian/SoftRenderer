/*
Trapezoid.h 多边形（梯形）
NOTE：记录了由扫描线扫描过后的集合梯形
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Trapezoid.h"

Trapezoid::Trapezoid(_FLOAT top, _FLOAT bottom, Line left, Line right) :
	_top(top), _bottom(bottom), _left(left), _right(right){}

// NOTE：具体划分方法见 BlauHimmel 实现和 2020/9/10 笔记
_INT Trapezoid::GetTrapezoids(const Triangle& triangle, Trapezoid* trapezoid) {
	if (trapezoid == nullptr) {
		return 0;
	}
	if (!triangle.IsTriangle()) {
		return 0;
	}
	// 将三个三角形顶点根据 y 轴值排序 （v1.y < v2.y < v3.y，y 越大越靠下）
	Vertex v1 = triangle._v1;
	Vertex v2 = triangle._v2;
	Vertex v3 = triangle._v3;
	if (v1._position._y > v2._position._y) {
		Swap(v1, v2);
	}
	if (v1._position._y > v3._position._y) {
		Swap(v1, v3);
	}
	if (v2._position._y > v3._position._y) {
		Swap(v2, v3);
	}

	// 若三点在一条 Y 轴上，不进行绘制
	if (v1._position._y == v2._position._y && v1._position._y == v3._position._y) { return 0; }
	// 若三点在一条 X 轴上，不进行绘制
	if (v1._position._x == v2._position._x && v1._position._x == v3._position._x) { return 0; }

	// 两种理想情况：当三角形的其中一条边与 x 轴平行的情况
	// 倒三角
	if (v1._position._y == v2._position._y) {
		if (v1._position._x > v2._position._x) {
			Swap(v1, v2);
		}
		// 划分多边形
		trapezoid[0]._top = v1._position._y;
		trapezoid[0]._bottom = v3._position._y;
		trapezoid[0]._left._end1 = v1;
		trapezoid[0]._left._end2 = v3;
		trapezoid[0]._right._end1 = v2;
		trapezoid[0]._right._end2 = v3;
		return (trapezoid[0]._top < trapezoid[0]._bottom) ? 1 : 0;
	}
	// 正三角
	if (v2._position._y == v3._position._y) {
		if (v2._position._x > v3._position._x) {
			Swap(v2, v3);
		}
		// 划分多边形
		trapezoid[0]._top = v1._position._y;
		trapezoid[0]._bottom = v3._position._y;
		trapezoid[0]._left._end1 = v1;
		trapezoid[0]._left._end2 = v2;
		trapezoid[0]._right._end1 = v1;
		trapezoid[0]._right._end2 = v3;
		return (trapezoid[0]._top < trapezoid[0]._bottom) ? 1 : 0;
	}

	// 不理想情况，需要划分为一个以上的三角形
	// 先根据 y 坐标分出两个多边形的顶和底
	trapezoid[0]._top = v1._position._y;
	trapezoid[0]._bottom = v2._position._y;
	trapezoid[1]._top = v2._position._y;
	trapezoid[1]._bottom = v3._position._y;

	// 计算 v2 在 v1v3 哪一侧（方法见帖子讲解）
	_FLOAT px, pk, sk;
	pk = (v3._position._y - v1._position._y) / (v2._position._y - v1._position._y);
	px = (v2._position._x - v1._position._x) * pk + v1._position._x;
	sk = (v3._position._y - v1._position._y) / (v3._position._x - v1._position._x);
	sk = (v3._position - v1._position).Len();
	// 当 v2 在 v1v3 左侧时
	if (px <= v3._position._x) {
		trapezoid[0]._left._end1 = v1;
		trapezoid[0]._left._end2 = v2;	
		trapezoid[0]._right._end1 = v1;
		trapezoid[0]._right._end2 = v3;
		trapezoid[1]._left._end1 = v2;
		trapezoid[1]._left._end2 = v3;
		trapezoid[1]._right._end1 = v1;
		trapezoid[1]._right._end2 = v3;
	}
	// 当 v2 在 v1v3 右侧时
	else {
		trapezoid[0]._left._end1 = v1;
		trapezoid[0]._left._end2 = v3;
		trapezoid[0]._right._end1 = v1;
		trapezoid[0]._right._end2 = v2;
		trapezoid[1]._left._end1 = v1;
		trapezoid[1]._left._end2 = v3;
		trapezoid[1]._right._end1 = v2;
		trapezoid[1]._right._end2 = v3;
	}
	return 2;
}

void Trapezoid::GetEndPoint(_FLOAT y) {
	// 算出 y 行与两条三角形边的交点的插值系数，利用该插值计算接下来的顶点
	//	原理：因为三点构成的平面(三角形)上的点一定在平面上，且三边上的点可以根据线性插值得出（因为在一条线上）
	//		  所以针对 y 的线性插值也可以用来求其他元素的线性插值（包括深度，纹理等）
	_FLOAT tLeft = (y - _left._end1._position._y) /
		(_left._end2._position._y - _left._end1._position._y);
	_FLOAT tRight = (y - _right._end1._position._y) /
		(_right._end2._position._y - _right._end1._position._y);
	// 线性插值算出扫描线的左边终点
	_left._v = Interpolate(_left._end1, _left._end2, tLeft);
	// 线性插值算出扫描线的右边终点
	_right._v = Interpolate(_right._end1, _right._end2, tRight);
}

Scanline Trapezoid::InitScanline(_INT y) {
	// TODO：在这里将顶点转换为像素
	_FLOAT width = _right._v._position._x - _left._v._position._x;
	Scanline scanline;

	// 扫描线起始点坐标
	scanline._x = (_INT)(_left._v._position._x);
	scanline._y = y;
	// 扫描线步长
	scanline._startPixel = Pixel(_left._v);
	
	// 扫描线宽度
	scanline._width = (_INT)(_right._v._position._x) - (_INT)(_left._v._position._x);
	if (_left._v._position._x >= _right._v._position._x) {
		scanline._width = 0;
	}

	// 扫描线像素步长（本质上就是除法：求出每一步需要变化的量）
	scanline._stepPixel = CalculateScanlineStepPixel(_left._v, _right._v, width);
	return scanline;
}

// 计算扫描线像素移动步长
Pixel Trapezoid::CalculateScanlineStepPixel(const Vertex& left, const Vertex& right, _FLOAT width) {
	Pixel stepPixel;
	_FLOAT inverse = 1.0f / width;
	stepPixel._position._x = (right._position._x - left._position._x) * inverse;
	stepPixel._position._y = (right._position._y - left._position._y) * inverse;
	
	stepPixel._normal._x = (right._vertexNormal._x - left._vertexNormal._x) * inverse;
	stepPixel._normal._y = (right._vertexNormal._y - left._vertexNormal._y) * inverse;
	stepPixel._normal._z = (right._vertexNormal._z - left._vertexNormal._z) * inverse;

	//stepPixel._textureCoord = Vector2((right._u - left._u) * inverse, (right._v - left._v) * inverse);
	stepPixel._textureCoord._x = (right._u - left._u) * inverse;
	stepPixel._textureCoord._y = (right._v - left._v) * inverse;

	stepPixel._color._r = (right._color._r - left._color._r) * inverse;
	stepPixel._color._g = (right._color._g - left._color._g) * inverse;
	stepPixel._color._b = (right._color._b - left._color._b) * inverse;

	stepPixel._depth = (right._position._w - left._position._w) * inverse;

	return stepPixel;
}