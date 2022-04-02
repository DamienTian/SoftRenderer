/*
Bound.h ��Χ��
ͼ��ѧ��ѧ����
author�����

* �ο�����Ѷ��ϷѧԺ Bounds ������ AABB ��Χ��Ӧ��
*/

#ifndef __BOUND_H
#define __BOUND_H

//#pragma once
#include "Mathf.h"

class AABB {
public:
	// ��Χ�з�Χ����λ��
	Vector4 _vMin, _vMax;

	// �����๹�캯�� + ��������
	AABB();
	AABB(_FLOAT xMin, _FLOAT xMax,
		_FLOAT yMin, _FLOAT yMax,
		_FLOAT zMin, _FLOAT zMax);
	AABB(Vector4 vMin, Vector4 vMax);
	~AABB() {};
};

#endif // __BOUND_H