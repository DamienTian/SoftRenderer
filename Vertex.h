/*
Vertex.h ����
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

#ifndef __VERTEX_H
#define __VERTEX_H

#include <deque>

//#include "Vector.h"
#include "Color.h"

class Vertex
{
public:
	// ����ļ�������
	Vector4 _position;
	// ��¼�ö���Ķ��㷨��
	Vector4 _vertexNormal;

	// NOTE��tangent

	// ������������� 
	//	NOTE��UV ��ֹһ�ף���һ��ģ���ж���������ͼʱ��UV ������Ҫ�ж���
	_FLOAT _u, _v;

	// ������ɫ 
	Color _color;

	// QUESTION���ڡ�Math of 3D game programming�����ᵽ��
	//			��Vertices carry information such as lighting colors and texture...��
	//		�������ܷ��� Vertex �м����йع���Ӱ��Ĳ�����
	// ANSWER��Ŀǰ��Ϊ���������ؽ׶δ�������

	// ���� + ��������
	Vertex();
	Vertex(Vector4 position, Vector4 vertexNormal, _FLOAT u, _FLOAT v, Color color);
	Vertex(const Vertex& other);
	Vertex& operator = (const Vertex& other);
	~Vertex() {}

	// ����Ӽ�����
	Vertex operator + (const Vertex& other) const;
	Vertex operator - (const Vertex& other) const;
	Vertex operator * (_FLOAT scale) const;

	// ��ʼ��
	// �����������꣬�������������͸��У����ֵ
	// ԭ���ο����γ� --- ͸��У����ֵ��perspective correct interpolation��
	void Init();

	// ������Ϣ
	void Info();
};

// �����ֵ
Vertex Interpolate(Vertex& v1, Vertex& v2, _FLOAT t);

#endif // !__VERTEX_H


