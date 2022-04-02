/*
Mathf.h �Խ���ѧ�⣨���������������㣩
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

#ifndef __MATHF_H
#define __MATHF_H

#include <iostream>

#include <math.h>

// �����������Ͷ���
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

// ������ֵ�ĺ�
#define PI 3.1415926f
#define HALF_PI 1.5707963f

#define COLOR_MIN 0.0f
#define COLOR_MAX 1.0f

#define PTR_SIZE sizeof(_PVOID)
#define BYTE_SIZE sizeof(_BYTE)

#define TEXTURE_MAXSIZE 1024

// ��������ֵ
_INT Abs(_INT x);

// ����������ֵ
_FLOAT Abs(_FLOAT x);

// �ж������������Ƿ����
// NOTE������ǳ���Ҫ������
//	��Ϊ�ڹ�դ�����漰�˴����ĶԸ������Ĳ��������Ǹ������ı�ʾ�ǲ�׼ȷ��
//	������ 1.0f / 3.0f * 3.0f ������ 0.1f��
//	����Ҫ�ж������������Ƿ����ֻ��Ҫ������֮��Ĳ��Ƿ��㹻С���ɡ�
bool Equal(_FLOAT x, _FLOAT y, _FLOAT epsilon = 0.000001f);

// �����������Բ�ֵ
_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t);

// ������������
_FLOAT Range(_FLOAT value, _FLOAT min, _FLOAT max);

// ����
template<class T>
void Swap(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

// Prototype�����������������࣬�Է�ֹ����������
class Vector4;
class Vector3;
class Vector2;
class Matrix4;


// ��ά���� Vector4��x,y,z,w��
//	���� x,y,z Ϊ��ά�ռ����ꡣ
//  w Ϊ������꣬�� w = 1 ʱ��ʾһ���㣬�� w = 0 ʱ��ʾ����
//	ע���󲿷������Ĭ��Ϊ��
class Vector4
{
public:
	// �����Լ��������
	_FLOAT _x, _y, _z, _w;

	// ���� + ��������
	Vector4() {}
	Vector4(_FLOAT x, _FLOAT y, _FLOAT z, _FLOAT w);
	//Vector4(const Vector3& other);
	Vector4(const Vector4& other);
	~Vector4() {}

	// ��ֵ���캯��
	Vector4& operator = (const Vector4& other);

	// ������ģ�����ȣ�
	_FLOAT Len() const;
	// ������λ��
	Vector4 Normalize();
	// ���
	_FLOAT Dot(const Vector4& v) const;
	// ���
	Vector4 Cross(const Vector4& v)	const;
	// �����ļӼ��˳�
	Vector4 operator + (const Vector4& v)	const;
	Vector4 operator - (const Vector4& v)	const;
	Vector4 operator * (const Vector4& v)	const;	// ��������
	Vector4 operator * (_FLOAT scale)	const;		// ����
	Vector4 operator * (const Matrix4& m)	const;	// ������˾���

													// ��
	Vector4 operator - ()	const;
	// �ж���ֵ���
	bool operator == (const Vector4& other) const;

	// ������������ӡ��Ϣ
	friend std::ostream& operator << (std::ostream& o, const Vector4& v);
};

// ��ά���� Vector3��x,y��
//	���� x,y,z Ϊ��ά�ռ����ꡣ��������ɫ RGB ����ά���ݱ�ʾ
class Vector3
{
public:
	// �����Լ��������
	_FLOAT _x, _y, _z;

	// ���� + ��������
	Vector3() {}
	Vector3(_FLOAT x, _FLOAT y, _FLOAT z);
	Vector3(const Vector4& other);
	Vector3(const Vector3& other);
	Vector3& operator = (const Vector3& other);
	~Vector3() {}

	// ������ģ�����ȣ�
	_FLOAT Len() const;
	// ������λ��
	Vector3 Normalize();
	// ���
	_FLOAT Dot(const Vector3& v) const;
	// ���
	Vector3 Cross(const Vector3& v)	const;
	// �����ļӼ��˳�
	Vector3 operator + (const Vector3& v)	const;
	Vector3 operator - (const Vector3& v)	const;
	Vector3 operator * (const Vector3& v)	const;	// ��������
	Vector3 operator * (_FLOAT scale)	const;		// ����

													// ��
	Vector3 operator - ()	const;
	// �ж����
	bool operator == (const Vector3& other) const;

	// ������������ӡ��Ϣ
	friend std::ostream& operator << (std::ostream& o, const Vector3& v);
};

// ��ά���� Vector2��x,y��
//	���� x,y Ϊ��ά�ռ����ꡣ��������Ļ�����ʾ
class Vector2 {
public:
	// �����Լ��������
	_FLOAT _x, _y;

	// ���� + ��������
	Vector2() {}
	Vector2(_FLOAT x, _FLOAT y);
	Vector2(const Vector4& other);
	Vector2(const Vector2& other);
	Vector2& operator = (const Vector2& other);
	~Vector2() {}

	// ������ģ�����ȣ�
	_FLOAT Len() const;
	// ������λ��
	Vector2 Normalize();
	// ���
	_FLOAT Dot(const Vector2& v) const;
	// ��� (��ά�����Ĳ�˽����һ������Ϊ������������ɵ�ƽ���ı������)
	_FLOAT Cross(const Vector2& v)	const;
	// �����ļӼ��˳�
	Vector2 operator + (const Vector2& v)	const;
	Vector2 operator - (const Vector2& v)	const;
	Vector2 operator * (const Vector2& v)	const;	// ��������
	Vector2 operator * (_FLOAT scale)	const;		// ����

													// ��
	Vector2 operator - ()	const;
	// �ж����
	bool operator == (const Vector2& other) const;
	// ������������ӡ��Ϣ
	friend std::ostream& operator << (std::ostream& o, const Vector2& v);

};

// ������ά���� Vector2��x,y��
//	���� x,y Ϊ��ά�ռ����ꡣ������ֱ���㷨����
class Vector2i {
public:
	// �����Լ��������
	_INT _x, _y;

	// ���� + ��������
	Vector2i() {}
	Vector2i(_INT x, _INT y);
	Vector2i(const Vector4& other);
	Vector2i(const Vector2i& other);
	Vector2i& operator = (const Vector2i& other);
	~Vector2i() {}

	// ������ģ�����ȣ�
	_FLOAT Len() const;
	// ���
	_INT Dot(const Vector2i& v) const;
	// ��� (��ά�����Ĳ�˽����һ������Ϊ������������ɵ�ƽ���ı������)
	_INT Cross(const Vector2i& v)	const;

	// �����ļӼ��˳�
	Vector2i operator + (const Vector2i& v)	const;
	Vector2i operator - (const Vector2i& v)	const;
	Vector2i operator * (const Vector2i& v)	const;	// ��������
	Vector2i operator * (_INT scale)	const;		// ����

													// ��
	Vector2i operator - ()	const;
	// �ж����
	bool operator == (const Vector2i& other) const;

	// ������������ӡ��Ϣ
	friend std::ostream& operator << (std::ostream& o, const Vector2i& v);
};

// ���������Բ�ֵ
Vector4 Interpolate(Vector4& v1, Vector4& v2, _FLOAT t);
Vector3 Interpolate(Vector3& v1, Vector3& v2, _FLOAT t);
Vector2 Interpolate(Vector2& v1, Vector2& v2, _FLOAT t);
Vector2i Interpolate(Vector2i& v1, Vector2i& v2, _FLOAT t);

// 4*4 ����
class Matrix4
{
public:
	// ����
	_FLOAT _data[4][4];

	// ��������������
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

	// ȡ Matrix4[i][j] ֵ
	_FLOAT& operator () (_INT i, _INT j);

	// ���� & ��Ϊ��λ����
	static Matrix4 Identity();
	void SetIdentity();
	// ���� & ��Ϊ�����
	static Matrix4 Zero();
	void SetZero();
	// ���þ�����ƽ�Ʊ任����
	void SetTranslation(_FLOAT x, _FLOAT y, _FLOAT z);
	// ���þ��������ű任����
	void SetScale(_FLOAT x, _FLOAT y, _FLOAT z);
	// ���þ�������ת�任�������У�
	//	* aixs: ��ת��
	//	* theta: ��ת�Ƕ�
	void SetRotation(Vector4& axis, _FLOAT theta);

	// ����ļӼ��˳�
	Matrix4 operator + (const Matrix4& m) const;
	Matrix4 operator - (const Matrix4& m) const;
	Matrix4 operator * (_FLOAT scale) const;		// ����
	Vector4 operator * (const Vector4& v) const;	// �����ҳ˾���
	Matrix4 operator * (const Matrix4& m) const;	// ����

													// NOTE: Ҳ����Ҫ����

													// ��
	Matrix4 operator - () const;
	// �жϾ�����ֵ���
	bool operator == (const Matrix4& other) const;
};
#endif // !__MATHF_H