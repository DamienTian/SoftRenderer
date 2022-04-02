/*
Trapezoid.h 多边形（梯形）
NOTE：基于Gouraud 着色算法，记录了由扫描线扫描过后的多边形
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/
//#pragma once

#ifndef __TRAPEZOID_H
#define __TRAPEZOID_H

#include "Line.h"
#include "Triangle.h"
#include "Scanline.h"

class Trapezoid
{
public:
	// 扫描梯形的顶和底
	// _top：开始扫描的 Y 坐标
	// _bottom：结束扫描的 Y 坐标
	_FLOAT _top, _bottom;

	// 扫描线集合梯形的两边
	Line _left, _right;

	// 构造 + 析构函数
	Trapezoid() {}
	Trapezoid(_FLOAT top, _FLOAT bottom, Line left, Line right);
	~Trapezoid() {}

	// 以下三种方法是基于 Gouraud 着色算法的三角形划分 和 扫描线生成算法
	// ==========================================================================
	// 生成划分三角形的扫描线集合，划分出一个以上的待扫描渲染的三角形
	// 返还三种情况：
	//	return 0 = 无法划分出三角形
	//  return 1 = 划分出一个三角形（大部分情况下是三角形本体）
	//	return 2 = 划分出两个三角形
	static _INT GetTrapezoids(const Triangle& triangle, Trapezoid* trapezoid);

	// 获取每一条扫描线的起点与终点
	// y 是每一行像素，最大为 height - 1
	void GetEndPoint(_FLOAT y);

	// 生成扫描线对象（根据提供的扫描线 Y 轴）
	Scanline InitScanline(_INT y);

	// 计算扫描线步长（像素）
	Pixel CalculateScanlineStepPixel(const Vertex& left, const Vertex& right, _FLOAT width);
	// ==========================================================================
};

#endif // !__TRAPEZOID_H
