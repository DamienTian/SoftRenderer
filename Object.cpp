/*
Object.h 渲染物体（GameObject）
图形学自学任务
author：田昊

* 参考：OpenGL-tutorial --- OBJ
R. Diane etc. --- MTL material format (Lightwave OBJ)
*/

#include "Object.h"

RenderObject::RenderObject()
{
	_name = "GameObject";
	// NOTE：在这里的内存也要被清空，否则会报错 “未加载 wntdll.pdb”
	_mesh = new Mesh();
	_material = new Material();
}

RenderObject::RenderObject(std::string name, Vector3 position, _FLOAT alpha)
{
	_name = name;
	_position = position;
	_theta = alpha;
	// NOTE：在这里的内存也要被清空，否则会报错 “未加载 wntdll.pdb”
	_mesh = new Mesh();
	_material = new Material();
}

RenderObject::~RenderObject()
{
	if (_mesh != nullptr) {
		delete _mesh;
		_mesh = nullptr;
	}
	if (_material != nullptr) {
		delete _material;
		_material = nullptr;
	}
}

void RenderObject::SetName(std::string name) {
	_name = name;
}

void RenderObject::SetPosition(Vector3 position) {
	_position = position;
}

void RenderObject::SetAlpha(_FLOAT theta) {
	_theta = theta;
}

bool RenderObject::SetMesh(const Mesh& other) {
	_mesh->_verticesCount = other._verticesCount;
	if (_mesh->_verticesCount > 0) {
		// 清空之前的顶点缓存
		if (_mesh->_verticesBuffer != nullptr) {
			delete[]_mesh->_verticesBuffer;
			_mesh->_verticesBuffer = nullptr;
		}
		_mesh->_verticesBuffer = new Vertex[_mesh->_verticesCount];
		for (int i = 0; i < _mesh->_verticesCount; ++i) {
			_mesh->_verticesBuffer[i] = other._verticesBuffer[i];
		}
	}
	_mesh->_indicesCount = other._indicesCount;
	if (_mesh->_indicesCount > 0) {
		// 清空之前的索引缓存
		if (_mesh->_indicesBuffer != nullptr) {
			delete[]_mesh->_indicesBuffer;
			_mesh->_indicesBuffer = nullptr;
		}
		_mesh->_indicesBuffer = new _INT[_mesh->_indicesCount];
		for (int i = 0; i < _mesh->_indicesCount; ++i) {
			_mesh->_indicesBuffer[i] = other._indicesBuffer[i];
		}
	}
	else {
		if (_mesh->_verticesBuffer != nullptr) {
			delete[]_mesh->_verticesBuffer;
			_mesh->_verticesBuffer = nullptr;
		}
		if (_mesh->_indicesBuffer != nullptr) {
			delete[]_mesh->_indicesBuffer;
			_mesh->_indicesBuffer = nullptr;
		}
	}
	return true;
}

bool RenderObject::SetMaterial(const Material& material) {
	strcpy(_material->_newmtl, material._newmtl);
	_material->_ambientColor = material._ambientColor;
	_material->_diffuseColor = material._diffuseColor;
	strcpy(_material->_mapKa, material._mapKa);
	strcpy(_material->_mapKd, material._mapKd);
	return true;
}