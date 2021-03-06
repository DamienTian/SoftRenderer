/*
Renderer.h 渲染器
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#pragma once
#ifndef __RENDERER_H
#define __RENDERER_H

#define RENDER_STATE_WIREFRAME 0x01
#define RENDER_STATE_TEXTURE 0x02
#define RENDER_STATE_COLOR 0x04

// Windows 头文件: 
#include <windows.h>

// C++ include 
#include <cassert>

#include "Transform.h"
#include "Light.h"
#include "Trapezoid.h"
#include "Scene.h"
#include "Image.h"

class Renderer
{
public:
	// 窗口 Device Context
	HDC * _hdc;
	// 变换矩阵方法集合
	Transform * _transform;
	// 窗口大小
	_INT _width, _height;
	// 贴图长宽
	_INT _textureWidth, _textureHeight;
	// uv 最大坐标（u 对应宽，v 对应高）
	_FLOAT _maxU, _maxV;
	// 渲染模式（color, texture, wireframe）
	_INT _renderMode;
	// 背景色和前景色
	_UINT _background, _foreground;
	// 光照
	//	环境光
	AmbientLight _ambientLight;
	//	平行光
	DirectionalLight _directionalLight;
	//	平行光源是否打开
	bool _isDirectionalLightOn = false;
	// 平行光源照射系数（纹理映射使用）
	Color _directionalLightOnTexture = Color(1.0f, 1.0f, 1.0f);

	// 应该先画到帧缓冲里，在映射到屏幕上
	// ------------------------------------------------------
	// 总缓冲：其中包括深度缓冲，帧缓冲，贴图信息
	_PVOID _buffer;
	// 帧缓冲索引指针（双指针用来索引存在指针 _buffer 的二维数组内的内容）
	_UINT** _frameBuffer;
	// 深度缓冲索引指针（双指针用来索引存在指针 _buffer 的二维数组内的内容）
	_FLOAT** _zBuffer;
	// 贴图信息索引指针（双指针用来索引存在指针 _buffer 的二维数组内的内容）
	_UINT** _texture;
	// ------------------------------------------------------

	// 构造 + 析构函数
	Renderer() { _transform = new Transform(); }
	Renderer(Transform * transform);
	~Renderer();

	// 初始化窗口引用
	void Init(_INT width, _INT height, _PVOID buffer);
	// 删除渲染器
	void Destroy();
	// 清空缓冲
	// 在每次 Mainloop 里都要清理帧缓冲以准备下一帧的绘图
	void CleanBuffer();

	// 设置贴图
	void SetTexture(_PVOID bit, _LONG pitch, _INT textureWidth, _INT textureHeight);
	// 根据纹理坐标读取对应贴图（像素颜色）
	_UINT ReadTexture(_FLOAT u, _FLOAT v);

	// 画点方法
	void DrawPixel(_INT x, _INT y, _UINT color);
	// 画线方法
	void DrawLine(Vector2i& v1, Vector2i& v2, _UINT color);
	// 画扫描线方法
	void DrawScanline(Scanline& scanline, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
	// 渲染多边形方法
	void RenderTrapezoid(Trapezoid& trapezoid, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
	// 渲染三角形方法
	//	TODO：加上材质中的环境光颜色和漫反射光颜色
	void RenderTriangle(Vertex& v1, Vertex& v2, Vertex& v3, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
};

#endif // !__RENDERER_H