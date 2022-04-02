/*
Pixel.h	���أ�����ɨ���ߣ�
ͼ��ѧ��ѧ����
author�����

* �ο�������� NB��
*/

#ifndef __PIXEL_H
#define __PIXEL_H

#include "Mathf.h"
#include "Color.h"
#include "Vertex.h"

class Pixel
{
public:
	// λ�ã�����ƽ���У�
	Vector2 _position;
	// ���ط�����
	Vector3 _normal;
	// ��������
	//	NOTE������һ�� Vector2, ���� x �� u, y �� v
	Vector2 _textureCoord;
	// ������ɫ
	Color _color;
	// ���������Ϣ
	_FLOAT _depth;

	// ���� + ��������
	Pixel();
	Pixel(Vector2 position, Vector3 normal, Vector2 textureCoord, Color color, _FLOAT depth);
	Pixel(Vector4 position, Vector4 normal, _FLOAT u, _FLOAT v, Color color);
	Pixel(Vertex v);
	~Pixel();

	// ���ؼӼ�����
	Pixel operator + (const Pixel& other) const;
	Pixel operator - (const Pixel& other) const;
	Pixel operator * (_FLOAT scale) const;
};

// �����ֵ
Pixel Interpolate(Pixel& p1, Pixel& p2, _FLOAT t);

#endif // !__PIXEL_H