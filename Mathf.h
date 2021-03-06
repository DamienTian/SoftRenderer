/*
Mathf.h 自建数学库（向量，矩阵及其运算）
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

#ifndef __MATHF_H
#define __MATHF_H

#include <iostream>

#include <math.h>

// 常用数据类型定义
using _DOUBLE = double;
using _FLOAT = float;
using _LONG = long;
using _INT = int;
using _UINT = unsigned int;
using _CHAR = char;
using _BYTE = char;
using _PSTR = char*;	// pointer to string
using _PBYTE = char*;	// pointer to byte
using _PVOID = void*;	// pointer to void

// 常用数值的宏
#define PI 3.1415926f
#define HALF_PI 1.5707963f

#define COLOR_MIN 0.0f
#define COLOR_MAX 1.0f

#define PTR_SIZE sizeof(_PVOID)
#define BYTE_SIZE sizeof(_BYTE)

#define TEXTURE_MAXSIZE 1024

// 整数绝对值
_INT Abs(_INT x);

// 浮点数绝对值
_FLOAT Abs(_FLOAT x);

// 判断两个浮点数是否相等
// NOTE：这个非常重要！！！
//	因为在光栅器中涉及了大量的对浮点数的操作，但是浮点数的表示是不准确的
//	（比如 1.0f / 3.0f * 3.0f 不等于 0.1f）
//	所以要判断两个浮点数是否相等只需要看他们之间的差是否足够小即可。
bool Equal(_FLOAT x, _FLOAT y, _FLOAT epsilon = 0.000001f);

// 浮点数的线性插值
_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t);

// 浮点限制区间
_FLOAT Range(_FLOAT value, _FLOAT min, _FLOAT max);

// 交换
template<class T>
void Swap(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

// Prototype：在这里声明其他类，以防止编译器报错
class Vector4;
class Vector3;
class Vector2;
class Matrix4;


// 四维向量 Vector4（x,y,z,w）
//	其中 x,y,z 为三维空间坐标。
//  w 为齐次坐标，当 w = 1 时表示一个点，当 w = 0 时表示方向
//	注：大部分情况下默认为点
class Vector4
{
public:
	// 坐标以及齐次坐标
	_FLOAT _x, _y, _z, _w;

	// 构造 + 析构函数
	Vector4() {}
	Vector4(_FLOAT x, _FLOAT y, _FLOAT z, _FLOAT w);
	//Vector4(const Vector3& other);
	Vector4(const Vector4& other);
	~Vector4() {}

	// 赋值构造函数
	Vector4& operator = (const Vector4& other);

	// 向量求模（长度）
	_FLOAT Len() const;
	// 向量单位化
	Vector4 Normalize();
	// 点乘
	_FLOAT Dot(const Vector4& v) const;
	// 叉乘
	Vector4 Cross(const Vector4& v)	const;
	// 向量的加减乘除
	Vector4 operator + (const Vector4& v)	const;
	Vector4 operator - (const Vector4& v)	const;
	Vector4 operator * (const Vector4& v)	const;	// 其他向量
	Vector4 operator * (_FLOAT scale)	const;		// 标量
	Vector4 operator * (const Matrix4& m)	const;	// 向量左乘矩阵

													// 求反
	Vector4 operator - ()	const;
	// 判断数值相等
	bool operator == (const Vector4& other) const;

	// 传入数据流打印信息
	friend std::ostream& operator << (std::ostream& o, const Vector4& v);
};

// 三维向量 Vector3（x,y）
//	其中 x,y,z 为三维空间坐标。可用于颜色 RGB 等三维数据表示
class Vector3
{
public:
	// 坐标以及齐次坐标
	_FLOAT _x, _y, _z;

	// 构造 + 析构函数
	Vector3() {}
	Vector3(_FLOAT x, _FLOAT y, _FLOAT z);
	Vector3(const Vector4& other);
	Vector3(const Vector3& other);
	Vector3& operator = (const Vector3& other);
	~Vector3() {}

	// 向量求模（长度）
	_FLOAT Len() const;
	// 向量单位化
	Vector3 Normalize();
	// 点乘
	_FLOAT Dot(const Vector3& v) const;
	// 叉乘
	Vector3 Cross(const Vector3& v)	const;
	// 向量的加减乘除
	Vector3 operator + (const Vector3& v)	const;
	Vector3 operator - (const Vector3& v)	const;
	Vector3 operator * (const Vector3& v)	const;	// 其他向量
	Vector3 operator * (_FLOAT scale)	const;		// 数字

													// 求反
	Vector3 operator - ()	const;
	// 判断相等
	bool operator == (const Vector3& other) const;

	// 传入数据流打印信息
	friend std::ostream& operator << (std::ostream& o, const Vector3& v);
};

// 二维向量 Vector2（x,y）
//	其中 x,y 为二维空间坐标。可用于屏幕坐标表示
class Vector2 {
public:
	// 坐标以及齐次坐标
	_FLOAT _x, _y;

	// 构造 + 析构函数
	Vector2() {}
	Vector2(_FLOAT x, _FLOAT y);
	Vector2(const Vector4& other);
	Vector2(const Vector2& other);
	Vector2& operator = (const Vector2& other);
	~Vector2() {}

	// 向量求模（长度）
	_FLOAT Len() const;
	// 向量单位化
	Vector2 Normalize();
	// 点乘
	_FLOAT Dot(const Vector2& v) const;
	// 叉乘 (二维向量的叉乘结果是一个数，为两个向量所组成的平行四边形面积)
	_FLOAT Cross(const Vector2& v)	const;
	// 向量的加减乘除
	Vector2 operator + (const Vector2& v)	const;
	Vector2 operator - (const Vector2& v)	const;
	Vector2 operator * (const Vector2& v)	const;	// 其他向量
	Vector2 operator * (_FLOAT scale)	const;		// 数字

													// 求反
	Vector2 operator - ()	const;
	// 判断相等
	bool operator == (const Vector2& other) const;
	// 传入数据流打印信息
	friend std::ostream& operator << (std::ostream& o, const Vector2& v);

};

// 整数二维向量 Vector2（x,y）
//	其中 x,y 为二维空间坐标。可用于直线算法计算
class Vector2i {
public:
	// 坐标以及齐次坐标
	_INT _x, _y;

	// 构造 + 析构函数
	Vector2i() {}
	Vector2i(_INT x, _INT y);
	Vector2i(const Vector4& other);
	Vector2i(const Vector2i& other);
	Vector2i& operator = (const Vector2i& other);
	~Vector2i() {}

	// 向量求模（长度）
	_FLOAT Len() const;
	// 点乘
	_INT Dot(const Vector2i& v) const;
	// 叉乘 (二维向量的叉乘结果是一个数，为两个向量所组成的平行四边形面积)
	_INT Cross(const Vector2i& v)	const;

	// 向量的加减乘除
	Vector2i operator + (const Vector2i& v)	const;
	Vector2i operator - (const Vector2i& v)	const;
	Vector2i operator * (const Vector2i& v)	const;	// 其他向量
	Vector2i operator * (_INT scale)	const;		// 数字

													// 求反
	Vector2i operator - ()	const;
	// 判断相等
	bool operator == (const Vector2i& other) const;

	// 传入数据流打印信息
	friend std::ostream& operator << (std::ostream& o, const Vector2i& v);
};

// 向量的线性插值
Vector4 Interpolate(Vector4& v1, Vector4& v2, _FLOAT t);
Vector3 Interpolate(Vector3& v1, Vector3& v2, _FLOAT t);
Vector2 Interpolate(Vector2& v1, Vector2& v2, _FLOAT t);
Vector2i Interpolate(Vector2i& v1, Vector2i& v2, _FLOAT t);

// 4*4 矩阵
class Matrix4
{
public:
	// 数据
	_FLOAT _data[4][4];

	// 构造与析构函数
	Matrix4() {}
	Matrix4(
		_FLOAT n11, _FLOAT n12, _FLOAT n13, _FLOAT n14,
		_FLOAT n21, _FLOAT n22, _FLOAT n23, _FLOAT n24,
		_FLOAT n31, _FLOAT n32, _FLOAT n33, _FLOAT n34,
		_FLOAT n41, _FLOAT n42, _FLOAT n43, _FLOAT n44
	);
	Matrix4(const Matrix4& other);
	Matrix4& operator = (const Matrix4& other);
	~Matrix4() {}

	// 取 Matrix4[i][j] 值
	_FLOAT& operator () (_INT i, _INT j);

	// 生成 & 设为单位矩阵
	static Matrix4 Identity();
	void SetIdentity();
	// 生成 & 设为零矩阵
	static Matrix4 Zero();
	void SetZero();
	// 将该矩阵变成平移变换矩阵
	void SetTranslation(_FLOAT x, _FLOAT y, _FLOAT z);
	// 将该矩阵变成缩放变换矩阵
	void SetScale(_FLOAT x, _FLOAT y, _FLOAT z);
	// 将该矩阵变成旋转变换矩阵，其中：
	//	* aixs: 旋转轴
	//	* theta: 旋转角度
	void SetRotation(Vector4& axis, _FLOAT theta);

	// 矩阵的加减乘除
	Matrix4 operator + (const Matrix4& m) const;
	Matrix4 operator - (const Matrix4& m) const;
	Matrix4 operator * (_FLOAT scale) const;		// 标量
	Vector4 operator * (const Vector4& v) const;	// 向量右乘矩阵
	Matrix4 operator * (const Matrix4& m) const;	// 矩阵

													// NOTE: 也许需要求逆

													// 求反
	Matrix4 operator - () const;
	// 判断矩阵数值相等
	bool operator == (const Matrix4& other) const;
};
#endif // !__MATHF_H