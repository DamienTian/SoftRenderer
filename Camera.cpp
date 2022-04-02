/*
Camera.cpp
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 direction, Vector3 up, _FLOAT aspect, _FLOAT angle, _FLOAT nearDis, _FLOAT farDis) {
	_position = position;
	_direction = direction.Normalize();
	_up = up.Normalize();
	_right = _up.Cross(_direction).Normalize();
	_aspect = aspect;
	_angle = angle;
	_near = nearDis;
	_far = farDis;
}

Camera::Camera(Camera& other) {
	_position = other._position;
	_direction = other._direction.Normalize();
	_up = other._up.Normalize();
	_right = _up.Cross(_direction).Normalize();
	_aspect = other._aspect;
	_angle = other._angle;
	_near = other._near;
	_far = other._far;
}

// 构造视图变换矩阵
Matrix4 Camera::GetViewTransformMatrix() {
	Matrix4 viewTransform = Matrix4();

	viewTransform(0, 0) = _right._x;
	viewTransform(1, 0) = _right._y;
	viewTransform(2, 0) = _right._z;
	viewTransform(3, 0) = -_position.Dot(_right);

	viewTransform(0, 1) = _up._x;
	viewTransform(1, 1) = _up._y;
	viewTransform(2, 1) = _up._z;
	viewTransform(3, 1) = -_position.Dot(_up);

	viewTransform(0, 2) = _direction._x;
	viewTransform(1, 2) = _direction._y;
	viewTransform(2, 2) = _direction._z;
	viewTransform(3, 2) = -_position.Dot(_direction);

	viewTransform(0, 3) = 0.0f;
	viewTransform(1, 3) = 0.0f;
	viewTransform(2, 3) = 0.0f;
	viewTransform(3, 3) = 1.0f;

	return viewTransform;
}

Matrix4 Camera::GetViewTransformMatrix(Vector4 position, Vector4 direction, Vector4 up) {
	direction = direction.Normalize();
	up = up.Normalize();
	Vector4 horizontal = up.Cross(direction).Normalize();

	Matrix4 viewTransform = Matrix4();

	viewTransform(0, 0) = horizontal._x;
	viewTransform(1, 0) = horizontal._y;
	viewTransform(2, 0) = horizontal._z;
	viewTransform(3, 0) = -position.Dot(horizontal);

	viewTransform(0, 1) = up._x;
	viewTransform(1, 1) = up._y;
	viewTransform(2, 1) = up._z;
	viewTransform(3, 1) = -position.Dot(up);

	viewTransform(0, 2) = direction._x;
	viewTransform(1, 2) = direction._y;
	viewTransform(2, 2) = direction._z;
	viewTransform(3, 2) = -position.Dot(direction);

	viewTransform(0, 3) = 0.0f;
	viewTransform(1, 3) = 0.0f;
	viewTransform(2, 3) = 0.0f;
	viewTransform(3, 3) = 1.0f;

	return viewTransform;
}

Matrix4 Camera::GetPerspectiveTransformMatrix() {
	Matrix4 perspectiveTransform = Matrix4();
	perspectiveTransform.SetZero();
	float cotHalfAngle = 1.0f / tanf(_angle * 0.5f);

	perspectiveTransform(0, 0) = cotHalfAngle / _aspect;
	perspectiveTransform(1, 1) = cotHalfAngle;
	perspectiveTransform(2, 2) = _far / (_far - _near);
	perspectiveTransform(2, 3) = 1.0f;
	perspectiveTransform(3, 2) = _far * _near / (_near - _far);

	return perspectiveTransform;
}

Matrix4 Camera::GetPerspectiveTransformMatrix(_FLOAT aspect, _FLOAT angle, _FLOAT nearDis, _FLOAT farDis) {
	Matrix4 perspectiveTransform = Matrix4();
	perspectiveTransform.SetZero();
	float cotHalfAngle = 1.0f / tanf(angle * 0.5f);

	perspectiveTransform(0, 0) = cotHalfAngle / aspect;
	perspectiveTransform(1, 1) = cotHalfAngle;
	perspectiveTransform(2, 2) = farDis / (farDis - nearDis);
	perspectiveTransform(2, 3) = 1.0f;
	perspectiveTransform(3, 2) = farDis * nearDis / (nearDis - farDis);

	return perspectiveTransform;
}