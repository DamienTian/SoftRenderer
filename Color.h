/*
Color.h
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/
//#pragma once

#ifndef __COLOR_H
#define __COLOR_H

#include <iostream>
#include "Mathf.h"

//_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t);

class Color
{
public:
	// rgba
	_FLOAT _r, _g, _b, _a = 1.0f;

	// ���� + ��������
	Color();
	Color(_FLOAT r, _FLOAT g, _FLOAT b);
	Color(_FLOAT r, _FLOAT g, _FLOAT b, _FLOAT a);
	Color(const Color& other);
	Color& operator = (const Color& other);
	~Color() {}

	// ��ɫ�����
	Color operator + (const Color& c) const;
	Color operator + (_FLOAT offset) const;
	Color operator - (const Color& c) const;
	Color operator - (_FLOAT offset) const;
	Color operator * (const Color& c) const;
	Color operator * (_FLOAT offset) const;

	// ����ɫת����һ�� 16 �������ֱ�ʾ
	_INT ConvertToINT();

	// ������������ӡ��Ϣ
	friend std::ostream& operator << (std::ostream& o, const Color& c);
};

// ������ɫ��ֵ��ʵ����ɫ���䣩
Color Interpolate(Color& c1, Color& c2, _FLOAT t);

#endif // !__COLOR_H

