/*
Transform.h 坐标变换处理
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#pragma once
#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Camera.h"

class Transform
{
public:
	// 世界变换矩阵
	// Model Space -> World Space
	Matrix4 _worldTransform;

	// 视图变换矩阵（变换摄像机位置）
	// World Space -> Camera Space
	Matrix4 _viewTransform;

	// 透视变换矩阵（变换场景中的顶点到视锥的近裁剪平面上上）
	// Camera Space -> Clip Space
	Matrix4 _perspectiveTransform;

	// 经变换得来的最终变换矩阵
	// world * view * perspective
	Matrix4 _transform;

	// 屏幕大小
	_INT _width, _height;

	// 构造 + 析构函数
	Transform() {}
	Transform(Matrix4 worldTransform, Matrix4 viewTransform, Matrix4 perspectiveTransform, _INT width, _INT height);
	Transform(const Transform& other);
	~Transform() {}

	// 初始化
	void Init(_INT width, _INT height);
	void Init(Camera* camera, _INT width, _INT height, Matrix4 worldTransform);

	// 转换到世界空间
	Vector4 ToWorldSpace(const Vector4& v);
	// 转换到相机空间
	Vector4 ToViewSpace(const Vector4& v);

	// 对顶点进行变换
	Vector4 ApplyTransform(const Vector4& v) const;

	// Canonical view volumn
	// 检查需要裁剪的顶点 
	// 作用是在进行透视除法之前取消绘制部分顶点, 然后进行屏幕映射
	_INT CheckCVV(const Vector4& v) const;

	// 同质化
	// 将进行 CVV 检查后的的顶点进行透视除法
	Vector4 Homogenize(const Vector4& v) const;

	// 更新变换矩阵
	void UpdateTransform();
};

#endif // !__TRANSFORM_H