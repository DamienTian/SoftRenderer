/*
Mesh.h ��Ⱦ�ṹ
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
		OpenGL-tutorial --- OBJ
		R. Diane etc. --- MTL material format (Lightwave OBJ)
*/

//#pragma once
#ifndef __MESH_H
#define __MESH_H

#include <stdlib.h> // atof()

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

#include "Vertex.h"
#include "Bound.h"
#include "Transform.h"
#include "Material.h"

class Mesh
{
public:
	// ���㻺���붥������
	Vertex * _verticesBuffer;
	_INT _verticesCount;

	// ������������
	_INT * _indicesBuffer;
	_INT _indicesCount;

	// AABB ��Χ��
	AABB * _bound;

	// �洢 .obj �е���Ϣ
	std::string _mtlPath;

	// ���� + ��������
	Mesh();
	Mesh(_INT verticesCount, _INT indexCount);
	Mesh(const Mesh& other);
	~Mesh();

	// �������ڵ� Mesh ���İ�Χ�д�С
	void InitBound(Vector3 objectPosition = Vector3(0.0f, 0.0f, 0.0f));

	// ��ȡ .obj �ļ�ģ��
	bool ReadInOBJ(const char * path);

	// ��ӡ Mesh ��Ϣ
	void Info();
};


#endif // !__MESH_H