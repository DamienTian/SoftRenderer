/*
Line.h �ߣ���������ɨ���ߣ�
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#pragma once
#ifndef __LINE_H
#define __LINE_H

#include "Vertex.h"

class Line
{
public:
	// Line ��¼���߶��ϵ�ĳһ���� _v �Լ��߶ε������˵� _end1, _end2
	Vertex _v, _end1, _end2;

	// ���� + ��������
	Line() {}
	Line(Vertex v, Vertex end1, Vertex end2);
	~Line() {}
};

#endif // !__LINE_H