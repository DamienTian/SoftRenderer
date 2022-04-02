/*
Transform.cpp 坐标变换处理
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Transform.h"

Transform::Transform(Matrix4 worldTransform, Matrix4 viewTransform, Matrix4 perspectiveTransform, _INT width, _INT height) {
	_worldTransform = worldTransform;
	_viewTransform = viewTransform;
	_perspectiveTransform = perspectiveTransform;
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
	_width = width;
	_height = height;
}

Transform::Transform(const Transform& other) {
	_worldTransform = other._worldTransform;
	_viewTransform = other._viewTransform;
	_perspectiveTransform = other._perspectiveTransform;
	_width = other._width;
	_height = other._height;
}

void Transform::Init(_INT width, _INT height) {
	// 屏幕比例
	_FLOAT aspect = (_FLOAT)width / (_FLOAT)height;
	_width = width;
	_height = height;
	_worldTransform.SetIdentity();
	_viewTransform.SetIdentity();
	_perspectiveTransform.SetIdentity();
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}

void Transform::Init(Camera* camera, _INT width, _INT height, Matrix4 worldTransform) {
	_FLOAT aspect = (_FLOAT)width / (_FLOAT)height;
	_width = width;
	_height = height;
	_worldTransform = worldTransform;
	_viewTransform = camera->GetViewTransformMatrix();
	_perspectiveTransform = camera->GetPerspectiveTransformMatrix();
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}

// 转换到世界空间
Vector4 Transform::ToWorldSpace(const Vector4& v) {
	return v * _worldTransform;
}

// 转换到相机空间 
Vector4 Transform::ToViewSpace(const Vector4& v) {
	return v * _worldTransform * _viewTransform;
}

// 对向量进行几何变换
Vector4 Transform::ApplyTransform(const Vector4& v) const {
	return v * _transform;
}

// 检查需要裁剪的顶点
_INT Transform::CheckCVV(const Vector4& v) const {
	_FLOAT w = v._w;
	_INT check = 0;
	if (v._z < 0) { check |= 0x01; }
	if (v._z > w) { check |= 0x02; }
	if (v._x < -w) { check |= 0x04; }
	if (v._x > w) { check |= 0x08; }
	if (v._y < -w) { check |= 0x10; }
	if (v._y > w) { check |= 0x20; }
	return check;
}

Vector4 Transform::Homogenize(const Vector4& v) const {
 	_FLOAT inverse = 1.0f / v._w;
	return Vector4(
		(v._x * inverse + 1.0f) * _width * 0.5f,	// x
		(1.0f - v._y * inverse) * _height * 0.5f,	// y
		v._z * inverse,	// z
		1.0f	// w
	);
}

// 更新变换矩阵
void Transform::UpdateTransform() {
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}