/*
Scene.h ��Ⱦ����
ͼ��ѧ��ѧ����
author�����

* �ο�������� NB��
*/

#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include "Object.h"

class Scene
{
public:
	// ����Ⱦ�������
	std::vector<RenderObject*> _renderObjects;
	_INT _renderObjectCount;

	// ���� + ����
	Scene();
	~Scene();

	// ��ȡһ�� Vector<RenderObject>��д�� _renderObjects ��
	void GetRenderObjects(std::vector<RenderObject*>& renderObjects);
};

#endif // !__SCENE_H

