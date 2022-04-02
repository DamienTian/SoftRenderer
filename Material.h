/*
Material.h ���ʣ���ȡ .mtl �����ݣ�
ͼ��ѧ��ѧ����
author�����

* �ο�������� NB��
*/

#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <stdlib.h> // atof()

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include <cassert>

#include "Color.h"
#include "Image.h"

class Material
{
public:
	// ��Ų�������
	char _newmtl[256];
	Color _ambientColor;
	Color _diffuseColor;

	// ������������ͼ��ַ
	char _mapKa[256];	// ������·��
	char _mapKd[256];	// �������·��

	// ����ͼ
	BMPImage *_mapKaImage, *_mapKdImage;

	// ���� + ����
	Material();
	Material(std::string newmtl, Color _ambientColor, Color _diffuseColor);
	~Material();

	// ��ȡ .mtl �ļ���Ϣ
	bool ReadInMTL(const char * path);
	// ��ʾ Material ��Ϣ
	void Info();
};

#endif // !__MATERIAL_H