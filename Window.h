/*
Window.h ���ƴ���
Ŀ�ģ����û�������Ŀ��ƴ���
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
������ ��C++����Windows����
*/

//#pragma once
// _MSC_VER����ʹ���������ݱ������汾ѡ��������ӵĿ�汾
#ifdef _MSC_VER
#endif

#ifndef __WINDOW_H
#define __WINDOW_H

//#pragma once
// #pragma comment(lib, "...")���� ... �����
#pragma comment(lib, "gdi32.lib")	// gdi32.lib Win ͼ�ν�����س���
#pragma comment(lib, "user32.lib")	// user32.lib Win ͼ�ν�����س���

#include "targetver.h"

// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <strsafe.h>

// C++ ����ʱͷ�ļ�
#include <iostream>

#include "Mathf.h"

class Window
{
public:
	// �����Ƿ���������
	bool _isRunning;
	// �û����̼���ָ���
	bool _keyDown[256];
	// Win ���� Handle
	HWND _hwnd;
	// Win Device Content Handle
	HDC _hdc;
	// ���� Bitmap ָ��
	// �����ǽ��� Renderer �е�������Ϣ�����ֵ���Ļ�ϵ�
	HBITMAP _hb, _ob;

	// ���ڴ�С
	_INT _width, _height;
	// ������Ⱦ����
	_PBYTE _screenBuffer;
	// ����ͷ��Ϣ
	LPTSTR _titleInfo;

	// ���� + ��������
	Window();
	~Window();

	// ��ʼ��
	_INT Init(_INT width, _INT height, LPTSTR title);

	// ���ڹر�
	_INT Close();

	// ����ͷ�����Ϣ�� Win ���̴���
	void Dispatch();

	// ���´���
	void Update();

	// �����û�������Ϣ
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// ȫ�־�̬������Win Ӧ�ó������ + ����
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static Window* _window;
#endif // !__WINDOW_H