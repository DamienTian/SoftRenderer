/*
Renderer.h ��Ⱦ��
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#pragma once
#ifndef __RENDERER_H
#define __RENDERER_H

#define RENDER_STATE_WIREFRAME 0x01
#define RENDER_STATE_TEXTURE 0x02
#define RENDER_STATE_COLOR 0x04

// Windows ͷ�ļ�: 
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
	// ���� Device Context
	HDC * _hdc;
	// �任���󷽷�����
	Transform * _transform;
	// ���ڴ�С
	_INT _width, _height;
	// ��ͼ����
	_INT _textureWidth, _textureHeight;
	// uv ������꣨u ��Ӧ����v ��Ӧ�ߣ�
	_FLOAT _maxU, _maxV;
	// ��Ⱦģʽ��color, texture, wireframe��
	_INT _renderMode;
	// ����ɫ��ǰ��ɫ
	_UINT _background, _foreground;
	// ����
	//	������
	AmbientLight _ambientLight;
	//	ƽ�й�
	DirectionalLight _directionalLight;
	//	ƽ�й�Դ�Ƿ��
	bool _isDirectionalLightOn = false;
	// ƽ�й�Դ����ϵ��������ӳ��ʹ�ã�
	Color _directionalLightOnTexture = Color(1.0f, 1.0f, 1.0f);

	// Ӧ���Ȼ���֡�������ӳ�䵽��Ļ��
	// ------------------------------------------------------
	// �ܻ��壺���а�����Ȼ��壬֡���壬��ͼ��Ϣ
	_PVOID _buffer;
	// ֡��������ָ�루˫ָ��������������ָ�� _buffer �Ķ�ά�����ڵ����ݣ�
	_UINT** _frameBuffer;
	// ��Ȼ�������ָ�루˫ָ��������������ָ�� _buffer �Ķ�ά�����ڵ����ݣ�
	_FLOAT** _zBuffer;
	// ��ͼ��Ϣ����ָ�루˫ָ��������������ָ�� _buffer �Ķ�ά�����ڵ����ݣ�
	_UINT** _texture;
	// ------------------------------------------------------

	// ���� + ��������
	Renderer() { _transform = new Transform(); }
	Renderer(Transform * transform);
	~Renderer();

	// ��ʼ����������
	void Init(_INT width, _INT height, _PVOID buffer);
	// ɾ����Ⱦ��
	void Destroy();
	// ��ջ���
	// ��ÿ�� Mainloop �ﶼҪ����֡������׼����һ֡�Ļ�ͼ
	void CleanBuffer();

	// ������ͼ
	void SetTexture(_PVOID bit, _LONG pitch, _INT textureWidth, _INT textureHeight);
	// �������������ȡ��Ӧ��ͼ��������ɫ��
	_UINT ReadTexture(_FLOAT u, _FLOAT v);

	// ���㷽��
	void DrawPixel(_INT x, _INT y, _UINT color);
	// ���߷���
	void DrawLine(Vector2i& v1, Vector2i& v2, _UINT color);
	// ��ɨ���߷���
	void DrawScanline(Scanline& scanline, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
	// ��Ⱦ����η���
	void RenderTrapezoid(Trapezoid& trapezoid, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
	// ��Ⱦ�����η���
	//	TODO�����ϲ����еĻ�������ɫ�����������ɫ
	void RenderTriangle(Vertex& v1, Vertex& v2, Vertex& v3, Color materialAmbientColor = Color(1.0f, 1.0f, 1.0f), Color materialDiffuseColor = Color(1.0f, 1.0f, 1.0f));
};

#endif // !__RENDERER_H