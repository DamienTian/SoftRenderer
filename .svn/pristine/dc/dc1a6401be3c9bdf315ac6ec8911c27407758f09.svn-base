/*
Scene.h 渲染场景
图形学自学任务
author：田昊

* 参考：晓峰哥 NB！
*/

#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include "Object.h"

class Scene
{
public:
	// 被渲染物体队列
	std::vector<RenderObject*> _renderObjects;
	_INT _renderObjectCount;

	// 构造 + 析构
	Scene();
	~Scene();

	// 读取一个 Vector<RenderObject>，写入 _renderObjects 中
	void GetRenderObjects(std::vector<RenderObject*>& renderObjects);
};

#endif // !__SCENE_H

