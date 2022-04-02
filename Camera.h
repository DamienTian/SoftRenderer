/*
Camera.h
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/
//#pragma once
#ifndef __CAMERA_H
#define __CAMERA_H

//#include "Vector.h"
//#include "Matrix.h"
#include <Windows.h>;
#include "Mathf.h"

class Camera {
public:
	// 相机位置
	Vector3 _position;
	// 相机的镜头朝向，垂直朝向，水平（右侧）朝向（左手定则）
	Vector3 _direction, _up, _right;

	// 屏幕宽高比
	_FLOAT _aspect;
	// 视锥体视角（影响视窗宽度）
	_FLOAT _angle;
	// 近，远裁剪平面到摄像机的距离
	_FLOAT _near, _far;

	// 构造 + 析构函数
	Camera() {}
	Camera(Vector3 position, Vector3 direction, Vector3 up,
		_FLOAT aspect, _FLOAT angle, _FLOAT nearDis, _FLOAT farDis);
	Camera(Camera& other);
	~Camera() {}

	// 构造视图变换矩阵
	Matrix4 GetViewTransformMatrix();
	static Matrix4 GetViewTransformMatrix(Vector4 position, Vector4 direction, Vector4 up);

	// 构造透视变换矩阵
	Matrix4 GetPerspectiveTransformMatrix();
	static Matrix4 GetPerspectiveTransformMatrix(_FLOAT aspect, _FLOAT angle, _FLOAT nearDis, _FLOAT farDis);
};
#endif // !__CAMERA_H



