/*
Triangle.h
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#pragma once
#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include "Vertex.h"

class Triangle
{
public:
	// ������������
	Vertex _v1, _v2, _v3;	// TODO���ĳ��������� int

	// ���� + ��������
	Triangle() {}
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	
	~Triangle() {}

	bool IsTriangle() const;

	// �������ε��е㣨�� _position ��
	static Vertex Centroid(Triangle triangle);
};

#endif // !__TRIANGLE_H
