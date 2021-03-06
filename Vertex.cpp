/*
Vertex.cpp
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

#include "Vertex.h"

Vertex::Vertex()
{
	_u = 1.0f;
	_v = 1.0f;
	//_deepz = 0.0f;
}

Vertex::Vertex(Vector4 position, Vector4 vertexNormal, _FLOAT u, _FLOAT v, Color color) {
	_position = position;
	_vertexNormal = vertexNormal;
	_u = u;
	_v = v;
	_color = color;
	//_deepz = 0.0f;
}

Vertex::Vertex(const Vertex& other) {
	_position = other._position;
	_vertexNormal = other._vertexNormal;
	_u = other._u;
	_v = other._v;
	_color = other._color;
	//_deepz = other.//_deepz;
}

Vertex& Vertex::operator = (const Vertex& other) {
	if (&other != this) {
		_position = other._position;
		_vertexNormal = other._vertexNormal;
		_u = other._u;
		_v = other._v;
		_color = other._color;
		//_deepz = other.//_deepz;
	}
	return *this;
}

// 顶点间的加减运算
Vertex Vertex::operator + (const Vertex& other) const {
	Vertex result = Vertex(
		_position + other._position,
		_vertexNormal + other._vertexNormal,
		_u + other._u,
		_v + other._v,
		_color + other._color
	);
	result._position._w = _position._w + other._position._w;
	//result.//_deepz = //_deepz + other.//_deepz;
	return result;
}

Vertex Vertex::operator - (const Vertex& other) const {
	Vertex result = Vertex(
		_position - other._position,
		_vertexNormal - other._vertexNormal,
		_u - other._u,
		_v - other._v,
		_color - other._color
	);
	result._position._w = _position._w - other._position._w;
	//result.//_deepz = //_deepz - other.//_deepz;
	return result;
}

Vertex Vertex::operator * (_FLOAT scale) const {
	Vertex result = Vertex(
		_position * scale,
		_vertexNormal * scale,
		_u * scale,
		_v * scale,
		_color * scale
	);
	result._position._w = _position._w * scale;
	//result._deepz = _deepz * scale;
	return result;
}

// 处理纹理坐标，对纹理坐标进行透视校正插值
void Vertex::Init() {
	_FLOAT inverse = 1.0f / _position._w;
	// NOTE：因为在投影变换后，顶点的深度值 z 被存储在 w 中，且 1/z 的是按照线性方式进行插值的。
	//		所以在这里将 w 变为 1/w，并基于 w 进行透视校正
	_position._w = inverse;
	// NOTE: 纹理坐标会在后期还原以贴到正确的位置	
	_u *= inverse;
	_v *= inverse;
	_color = _color * inverse;
}

// 顶点信息
void Vertex::Info() {
	using std::cout;
	using std::endl;

	cout << "  * position: " << _position << endl;
	cout << "  * vertexNormal: " << _vertexNormal << endl;
	cout << "  * u v: " << _u << "  " << _v << endl;
	cout << "  * color: " << _color << endl;
}

// 计算差值
Vertex Interpolate(Vertex& v1, Vertex& v2, _FLOAT t) {
	//_FLOAT w = 1.0f / Interpolate(1.0f / v1._position._w, 1.0f / v2._position._w, t);
	Vertex result = Vertex(
		Interpolate(v1._position, v2._position, t),
		Interpolate(v1._vertexNormal, v2._vertexNormal, t),
		Interpolate(v1._u, v2._u, t),
		Interpolate(v1._v, v2._v, t),
		Interpolate(v1._color, v2._color, t)
	);
	result._position._w = Interpolate(v1._position._w, v2._position._w, t);
	result._vertexNormal._w = Interpolate(v1._vertexNormal._w, v2._vertexNormal._w, t);
	return result;
}

