/*
Light.h 光与光源
图形学自学任务
author：田昊

* 参考：《3D大师》
	 CSND --- needMoreCode Mini3d 功能扩展
*/

//#pragma once
#ifndef __LIGHT_H
#define __LIGHT_H

#include "Color.h"
//#include "Vector.h"

// 环境光照影响系数
typedef struct {
	Color _color;
	_FLOAT _intensity;
} AmbientLight;

// 平行光光源
typedef struct {	
	// 平行光光源
	//	颜色
	Color _color;
	//	方向
	Vector3 _direction;
	//	光强度
	_FLOAT _intensity;
} DirectionalLight;

#endif // !__LIGHT_H

