/*
Mathf.cpp �Խ���ѧ��
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#include "stdafx.h"
#include "Mathf.h"

// ��������ֵ
_INT Abs(_INT x) {
	return x > 0 ? x : -x;
}

// ����������ֵ
_FLOAT Abs(_FLOAT x) {
	return x > 0 ? x : -x;
}

// �ж������������Ƿ����
bool Equal(_FLOAT x, _FLOAT y, _FLOAT epsilon) {
	return Abs(x - y) < epsilon ? true : false;
}

// �����������Բ�ֵ
_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t) {
	return x + (y - x) * t;
}

// ������������
_FLOAT Range(_FLOAT value, _FLOAT min, _FLOAT max) {
	if (value < min) { return min; }
	if (value > max) { return max; }
	return value;
}

// Vector4 ------------------------------------------------------------------
Vector4::Vector4(_FLOAT x, _FLOAT y, _FLOAT z, _FLOAT w) : _x(x), _y(y), _z(z), _w(w) {}
//Vector4::Vector4(const Vector3& other) : _x(other._x), _y(other._y), _z(other._z), _w(1.0f) {}
Vector4::Vector4(const Vector4& other) : _x(other._x), _y(other._y), _z(other._z), _w(other._w) {}

Vector4& Vector4::operator = (const Vector4& other) {
	// ʹ�õ�ַ�ж��Ƿ�����ͬ object
	if (&other != this) {
		_x = other._x;
		_y = other._y;
		_z = other._z;
		_w = other._w;
	}
	return *this;
}

// ������ģ�����ȣ�
_FLOAT Vector4::Len() const {
	_FLOAT square = _x * _x + _y * _y + _z * _z;
	return sqrtf(square);
}

// ������λ������ά���ı�������꣩
Vector4 Vector4::Normalize() {
	_FLOAT len = Len();
	if (len != 0) {
		_FLOAT inverse = 1.0f / len;
		_x *= inverse;
		_y *= inverse;
		_z *= inverse;
	}
	return *this;
}

// ��ˣ���ά���ı�������꣩
_FLOAT Vector4::Dot(const Vector4& v) const {
	return _x * v._x + _y * v._y + _z * v._z;
}

// ��ˣ����ɴ�ֱ���������������������
Vector4 Vector4::Cross(const Vector4& v) const {
	_FLOAT x = _y * v._z - _z * v._y;
	_FLOAT y = _z * v._x - _x * v._z;
	_FLOAT z = _x * v._y - _y * v._x;
	return Vector4(x, y, z, 0.0f);
}

// �����ļ�
Vector4 Vector4::operator + (const Vector4& v)	const {
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	_FLOAT z = _z + v._z;
	_FLOAT w = 1.0f;
	return Vector4(x, y, z, w);
}
// �����ļ�
Vector4 Vector4::operator - (const Vector4& v)	const {
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	_FLOAT z = _z - v._z;
	_FLOAT w = 1.0f;
	return Vector4(x, y, z, w);
}

// �����ĳˣ��������������ǵ��ͣ�
Vector4 Vector4::operator * (const Vector4& v)	const {
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	_FLOAT z = _z * v._z;
	return Vector4(x, y, z, 1.0f);
}

// �����ĳˣ��������
Vector4 Vector4::operator * (_FLOAT scale)	const {
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	_FLOAT z = _z * scale;
	return Vector4(x, y, z, _w);
}

// �����ĳˣ���������������˾���
Vector4 Vector4::operator * (const Matrix4& m) const {
	return Vector4(
		_x * m._data[0][0] + _y * m._data[1][0] + _z * m._data[2][0] + _w * m._data[3][0],
		_x * m._data[0][1] + _y * m._data[1][1] + _z * m._data[2][1] + _w * m._data[3][1],
		_x * m._data[0][2] + _y * m._data[1][2] + _z * m._data[2][2] + _w * m._data[3][2],
		_x * m._data[0][3] + _y * m._data[1][3] + _z * m._data[2][3] + _w * m._data[3][3]
	);
}

// ��
Vector4 Vector4::operator - ()	const {
	_FLOAT w = (_w == 0) ? 0 : 1;
	return Vector4(-_x, -_y, -_z, w);
}

// �ж���ֵ���
bool Vector4::operator == (const Vector4& other) const {
	return Equal(_x, other._x) && Equal(_y, other._y) && Equal(_z, other._z);
}
// Vector4 END------------------------------------------------------------------

// Vector3 ------------------------------------------------------------------
Vector3::Vector3(_FLOAT x, _FLOAT y, _FLOAT z) : _x(x), _y(y), _z(z) {}
Vector3::Vector3(const Vector4& other) : _x(other._x), _y(other._y), _z(other._z) {}
Vector3::Vector3(const Vector3& other) : _x(other._x), _y(other._y), _z(other._z) {}

Vector3& Vector3::operator = (const Vector3& other) {
	// ʹ�õ�ַ�ж��Ƿ�����ͬ object
	if (&other != this) {
		_x = other._x;
		_y = other._y;
		_z = other._z;
	}
	return *this;
}

// ������ģ�����ȣ�
_FLOAT Vector3::Len() const {
	_FLOAT square = _x * _x + _y * _y + _z * _z;
	return sqrtf(square);
}

// ������λ��
Vector3 Vector3::Normalize() {
	_FLOAT len = Len();
	if (len != 0) {
		_FLOAT inverse = 1.0f / len;
		_x *= inverse;
		_y *= inverse;
		_z *= inverse;
	}
	return *this;
}

// ���
_FLOAT Vector3::Dot(const Vector3& v) const {
	return _x * v._x + _y * v._y + _z * v._z;
}

// ���
Vector3 Vector3::Cross(const Vector3& v) const {
	_FLOAT x = _y * v._z - _z * v._y;
	_FLOAT y = _z * v._x - _x * v._z;
	_FLOAT z = _x * v._y - _y * v._x;
	return Vector3(x, y, z);
}

// �����ļ�
Vector3 Vector3::operator + (const Vector3& v)	const {
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	_FLOAT z = _z + v._z;
	return Vector3(x, y, z);
}

// �����ļ�
Vector3 Vector3::operator - (const Vector3& v)	const {
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	_FLOAT z = _z - v._z;
	return Vector3(x, y, z);
}

// �����ĳˣ��������������ǵ��ͣ�
Vector3 Vector3::operator * (const Vector3& v)	const {
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	_FLOAT z = _z * v._z;
	return Vector3(x, y, z);
}

// �����ĳˣ������֣�
Vector3 Vector3::operator * (_FLOAT scale)	const {
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	_FLOAT z = _z * scale;
	return Vector3(x, y, z);
}

// ��
Vector3 Vector3::operator - ()	const {
	return Vector3(-_x, -_y, -_z);
}

// �ж���ֵ���
bool Vector3::operator == (const Vector3& other) const {
	return Equal(_x, other._x) && Equal(_y, other._y) && Equal(_z, other._z);
}
// Vector3 END------------------------------------------------------------------

// Vector2 ------------------------------------------------------------------
Vector2::Vector2(_FLOAT x, _FLOAT y) : _x(x), _y(y) {}
Vector2::Vector2(const Vector4& other) : _x(other._x), _y(other._y) {}
Vector2::Vector2(const Vector2& other) : _x(other._x), _y(other._y) {}

Vector2& Vector2::operator = (const Vector2& other) {
	// ʹ�õ�ַ�ж��Ƿ�����ͬ object
	if (&other != this) {
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

// ������ģ�����ȣ�
_FLOAT Vector2::Len() const {
	_FLOAT square = _x * _x + _y * _y;
	return sqrtf(square);
}

// ������λ��
Vector2 Vector2::Normalize() {
	_FLOAT len = Len();
	if (len != 0) {
		_FLOAT inverse = 1.0f / len;
		_x *= inverse;
		_y *= inverse;
	}
	return *this;
}

// ���
_FLOAT Vector2::Dot(const Vector2& v) const {
	return _x * v._x + _y * v._y;
}

// ��� (��ά�����Ĳ�˽����һ������Ϊ������������ɵ�ƽ���ı������)
_FLOAT Vector2::Cross(const Vector2& v) const {
	return _x * v._y - _y * v._x;
}

// �����ļ�
Vector2 Vector2::operator + (const Vector2& v)	const {
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	return Vector2(x, y);
}

// �����ļ�
Vector2 Vector2::operator - (const Vector2& v)	const {
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	return Vector2(x, y);
}

// �����ĳˣ��������������ǵ��ͣ�
Vector2 Vector2::operator * (const Vector2& v)	const {
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	return Vector2(x, y);
}

// �����ĳˣ��������
Vector2 Vector2::operator * (_FLOAT scale)	const {
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	return Vector2(x, y);
}

// ��
Vector2 Vector2::operator - ()	const {
	return Vector2(-_x, -_y);
}

// �ж���ֵ���
bool Vector2::operator == (const Vector2& other) const {
	return Equal(_x, other._x) && Equal(_y, other._y);
}
// Vector2 END------------------------------------------------------------------


// Vector2i ------------------------------------------------------------------
Vector2i::Vector2i(_INT x, _INT y) : _x(x), _y(y) {}
Vector2i::Vector2i(const Vector4& other) : _x((_INT)other._x), _y((_INT)other._y) {}
Vector2i::Vector2i(const Vector2i& other) : _x(other._x), _y(other._y) {}

Vector2i& Vector2i::operator = (const Vector2i& other) {
	// ʹ�õ�ַ�ж��Ƿ�����ͬ object
	if (&other != this) {
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

// ������ģ�����ȣ�
_FLOAT Vector2i::Len() const {
	_INT square = _x * _x + _y * _y;
	return sqrtf(square);
}

// ���
_INT Vector2i::Dot(const Vector2i& v) const {
	return _x * v._x + _y * v._y;
}

// ��� (��ά�����Ĳ�˽����һ������Ϊ������������ɵ�ƽ���ı������)
_INT Vector2i::Cross(const Vector2i& v) const {
	return _x * v._y - _y * v._x;
}

// �����ļ�
Vector2i Vector2i::operator + (const Vector2i& v)	const {
	_INT x = _x + v._x;
	_INT y = _y + v._y;
	return Vector2i(x, y);
}

// �����ļ�
Vector2i Vector2i::operator - (const Vector2i& v)	const {
	_INT x = _x - v._x;
	_INT y = _y - v._y;
	return Vector2i(x, y);
}

// �����ĳˣ��������������ǵ��ͣ�
Vector2i Vector2i::operator * (const Vector2i& v)	const {
	_INT x = _x * v._x;
	_INT y = _y * v._y;
	return Vector2i(x, y);
}

// �����ĳˣ������֣�
Vector2i Vector2i::operator * (_INT scale)	const {
	_INT x = _x * scale;
	_INT y = _y * scale;
	return Vector2i(x, y);
}

// ��
Vector2i Vector2i::operator - ()	const {
	return Vector2i(-_x, -_y);
}

// �ж���ֵ���
bool Vector2i::operator == (const Vector2i& other) const {
	return (_x == other._x) && (_y == other._y);
}
// Vector2i END------------------------------------------------------------------

// ���������Բ�ֵ
Vector4 Interpolate(Vector4& v1, Vector4& v2, _FLOAT t) {
	return Vector4(
		Interpolate(v1._x, v2._x, t),
		Interpolate(v1._y, v2._y, t),
		Interpolate(v1._z, v2._z, t),
		//1.0f);
		(v1._w == 1.0f || v2._w == 1.0f) ? 1.0f : 0.0f);
}

Vector3 Interpolate(Vector3& v1, Vector3& v2, _FLOAT t) {
	return Vector3(
		Interpolate(v1._x, v2._x, t),
		Interpolate(v1._y, v2._y, t),
		Interpolate(v1._z, v2._z, t));
}

Vector2 Interpolate(Vector2& v1, Vector2& v2, _FLOAT t) {
	return Vector2(
		Interpolate(v1._x, v2._x, t),
		Interpolate(v1._y, v2._y, t));
}

Vector2i Interpolate(Vector2i& v1, Vector2i& v2, _FLOAT t) {
	return Vector2i(
		(_INT)Interpolate(v1._x, v2._x, t),
		(_INT)Interpolate(v1._y, v2._y, t));
}

// ������������ӡ��Ϣ
std::ostream& operator << (std::ostream& o, const Vector4& v) {
	o << v._x << ", " << v._y << ", " << v._z << ", " << v._w;
	return o;
}
std::ostream& operator << (std::ostream& o, const Vector3& v) {
	o << v._x << ", " << v._y << ", " << v._z;
	return o;
}
std::ostream& operator << (std::ostream& o, const Vector2& v) {
	o << v._x << ", " << v._y;
	return o;
}
std::ostream& operator << (std::ostream& o, const Vector2i& v) {
	o << v._x << ", " << v._y;
	return o;
}

// ��������������
Matrix4::Matrix4(
	_FLOAT n11, _FLOAT n12, _FLOAT n13, _FLOAT n14,
	_FLOAT n21, _FLOAT n22, _FLOAT n23, _FLOAT n24,
	_FLOAT n31, _FLOAT n32, _FLOAT n33, _FLOAT n34,
	_FLOAT n41, _FLOAT n42, _FLOAT n43, _FLOAT n44
) {
	_data[0][0] = n11;	_data[0][1] = n12;	_data[0][2] = n13;	_data[0][3] = n14;
	_data[1][0] = n21;	_data[1][1] = n22;	_data[1][2] = n23;	_data[1][3] = n24;
	_data[2][0] = n31;	_data[2][1] = n32;	_data[2][2] = n33;	_data[2][3] = n34;
	_data[3][0] = n41;	_data[3][1] = n42;	_data[3][2] = n43;	_data[3][3] = n44;
}

Matrix4::Matrix4(const Matrix4& other) {
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			_data[i][j] = other._data[i][j];
		}
	}
}

Matrix4& Matrix4::operator = (const Matrix4& other) {
	if (&other != this) {
		for (auto i = 0; i < 4; ++i) {
			for (auto j = 0; j < 4; ++j) {
				_data[i][j] = other._data[i][j];
			}
		}
	}
	return *this;
}

// ȡ Matrix4[i][j] ֵ
_FLOAT& Matrix4::operator () (_INT i, _INT j) {
	return _data[i][j];
}

// ���� & ��Ϊ��λ����
Matrix4 Matrix4::Identity() {
	Matrix4 res;
	res._data[0][0] = 1.0f;	res._data[0][1] = 0.0f;	res._data[0][2] = 0.0f; res._data[0][3] = 0.0f;
	res._data[1][0] = 0.0f;	res._data[1][1] = 1.0f;	res._data[1][2] = 0.0f; res._data[1][3] = 0.0f;
	res._data[2][0] = 0.0f;	res._data[2][1] = 0.0f;	res._data[2][2] = 1.0f; res._data[2][3] = 0.0f;
	res._data[3][0] = 0.0f;	res._data[3][1] = 0.0f;	res._data[3][2] = 0.0f; res._data[3][3] = 1.0f;
	return res;
}

void Matrix4::SetIdentity() {
	_data[0][0] = 1.0f;	_data[0][1] = 0.0f;	_data[0][2] = 0.0f; _data[0][3] = 0.0f;
	_data[1][0] = 0.0f;	_data[1][1] = 1.0f;	_data[1][2] = 0.0f; _data[1][3] = 0.0f;
	_data[2][0] = 0.0f;	_data[2][1] = 0.0f;	_data[2][2] = 1.0f; _data[2][3] = 0.0f;
	_data[3][0] = 0.0f;	_data[3][1] = 0.0f;	_data[3][2] = 0.0f; _data[3][3] = 1.0f;

}

// ���� & ��Ϊ�����
Matrix4 Matrix4::Zero() {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] = 0.0f;
		}
	}
	return res;
}

void Matrix4::SetZero() {
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			_data[i][j] = 0.0f;
		}
	}
}

// ���þ�����ƽ�Ʊ任����
void Matrix4::SetTranslation(_FLOAT x, _FLOAT y, _FLOAT z) {
	SetIdentity();
	_data[3][0] = x;
	_data[3][1] = y;
	_data[3][2] = z;
}

// ���þ��������ű任����
void Matrix4::SetScale(_FLOAT x, _FLOAT y, _FLOAT z) {
	SetIdentity();
	_data[0][0] = x;
	_data[1][1] = y;
	_data[2][2] = z;
}

// ���þ�������ת�任�������У�
//	* aixs: ��ת��
//	* theta: ��ת�Ƕ�
void Matrix4::SetRotation(Vector4& axis, _FLOAT theta) {
	_FLOAT halfTheta = theta * 0.5f;
	_FLOAT sinHalfTheta = sinf(halfTheta);
	_FLOAT cosHalfTheta = cosf(halfTheta);
	Vector4 axisNormal = axis.Normalize();

	// ������Ԫ��
	_FLOAT x = axisNormal._x * sinHalfTheta;
	_FLOAT y = axisNormal._y * sinHalfTheta;
	_FLOAT z = axisNormal._z * sinHalfTheta;
	_FLOAT w = cosHalfTheta;

	// ������ת����
	_FLOAT x2 = x * x; _FLOAT y2 = y * y; _FLOAT z2 = z * z;
	_FLOAT xy = x * y; _FLOAT xz = x * z; _FLOAT yz = y * z;
	_FLOAT xw = x * w; _FLOAT yw = y * w; _FLOAT zw = z * w;

	_data[0][0] = 1 - 2 * (y2 + z2);
	_data[1][0] = 2 * (xy - zw);
	_data[2][0] = 2 * (xz + yw);
	_data[3][0] = 0.0f;

	_data[0][1] = 2 * (xy + zw);
	_data[1][1] = 1 - 2 * (x2 + z2);
	_data[2][1] = 2 * (yz - xw);
	_data[3][1] = 0.0f;

	_data[0][2] = 2 * (xz - yw);
	_data[1][2] = 2 * (yz + xw);
	_data[2][2] = 1 - 2 * (x2 + y2);
	_data[3][2] = 0.0f;

	_data[0][3] = 0.0f;
	_data[1][3] = 0.0f;
	_data[2][3] = 0.0f;
	_data[3][3] = 1.0f;
}

// ����ļ�
Matrix4 Matrix4::operator + (const Matrix4& m) const {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] = _data[i][j] + m._data[i][j];
		}
	}
	return res;
}

// ����ļ�
Matrix4 Matrix4::operator - (const Matrix4& m) const {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] = _data[i][j] - m._data[i][j];
		}
	}
	return res;
}

// ����ĳˣ�������
Matrix4 Matrix4::operator * (_FLOAT scale) const {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] = _data[i][j] * scale;
		}
	}
	return res;
}

// ����ĳˣ������ҳ˾���
Vector4 Matrix4::operator * (const Vector4& v) const {
	return Vector4(
		_data[0][0] * v._x + _data[0][1] * v._y + _data[0][2] * v._z + _data[0][3] * v._w,
		_data[1][0] * v._x + _data[1][1] * v._y + _data[1][2] * v._z + _data[1][3] * v._w,
		_data[2][0] * v._x + _data[2][1] * v._y + _data[2][2] * v._z + _data[2][3] * v._w,
		_data[3][0] * v._x + _data[3][1] * v._y + _data[3][2] * v._z + _data[3][3] * v._w
	);
}

// ����ĳˣ�����
Matrix4 Matrix4::operator * (const Matrix4& m) const {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] =
				_data[i][0] * m._data[0][j] +
				_data[i][1] * m._data[1][j] +
				_data[i][2] * m._data[2][j] +
				_data[i][3] * m._data[3][j];
		}
	}
	return res;
}

// ��
Matrix4 Matrix4::operator - () const {
	Matrix4 res;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			res._data[i][j] = -_data[i][j];
		}
	}
	return res;
}

// �жϾ�����ֵ���
bool Matrix4::operator == (const Matrix4& other) const {
	bool res = true;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 0; j < 4; ++j) {
			if (Equal(_data[i][j], other._data[i][j]) == false) {
				res = false;
			}
		}
	}
	return res;
}