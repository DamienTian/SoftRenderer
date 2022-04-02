/*
Transform.h ����任����
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#pragma once
#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Camera.h"

class Transform
{
public:
	// ����任����
	// Model Space -> World Space
	Matrix4 _worldTransform;

	// ��ͼ�任���󣨱任�����λ�ã�
	// World Space -> Camera Space
	Matrix4 _viewTransform;

	// ͸�ӱ任���󣨱任�����еĶ��㵽��׶�Ľ��ü�ƽ�����ϣ�
	// Camera Space -> Clip Space
	Matrix4 _perspectiveTransform;

	// ���任���������ձ任����
	// world * view * perspective
	Matrix4 _transform;

	// ��Ļ��С
	_INT _width, _height;

	// ���� + ��������
	Transform() {}
	Transform(Matrix4 worldTransform, Matrix4 viewTransform, Matrix4 perspectiveTransform, _INT width, _INT height);
	Transform(const Transform& other);
	~Transform() {}

	// ��ʼ��
	void Init(_INT width, _INT height);
	void Init(Camera* camera, _INT width, _INT height, Matrix4 worldTransform);

	// ת��������ռ�
	Vector4 ToWorldSpace(const Vector4& v);
	// ת��������ռ�
	Vector4 ToViewSpace(const Vector4& v);

	// �Զ�����б任
	Vector4 ApplyTransform(const Vector4& v) const;

	// Canonical view volumn
	// �����Ҫ�ü��Ķ��� 
	// �������ڽ���͸�ӳ���֮ǰȡ�����Ʋ��ֶ���, Ȼ�������Ļӳ��
	_INT CheckCVV(const Vector4& v) const;

	// ͬ�ʻ�
	// ������ CVV ����ĵĶ������͸�ӳ���
	Vector4 Homogenize(const Vector4& v) const;

	// ���±任����
	void UpdateTransform();
};

#endif // !__TRANSFORM_H