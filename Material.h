/*
Material.h 材质（读取 .mtl 的数据）
图形学自学任务
author：田昊

* 参考：晓峰哥 NB！
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
	// 存放材料名称
	char _newmtl[256];
	Color _ambientColor;
	Color _diffuseColor;

	// 光照纹理属性图地址
	char _mapKa[256];	// 环境光路径
	char _mapKd[256];	// 漫反射光路径

	// 纹理图
	BMPImage *_mapKaImage, *_mapKdImage;

	// 构造 + 析构
	Material();
	Material(std::string newmtl, Color _ambientColor, Color _diffuseColor);
	~Material();

	// 读取 .mtl 文件信息
	bool ReadInMTL(const char * path);
	// 显示 Material 信息
	void Info();
};

#endif // !__MATERIAL_H