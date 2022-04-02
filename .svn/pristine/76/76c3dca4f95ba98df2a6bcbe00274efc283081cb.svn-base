/*
Window.h 自制窗口
目的：让用户更方便的控制窗口
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
大气象 纯C++创建Windows窗体
*/

//#pragma once
// _MSC_VER：可使编译器根据编译器版本选择可以链接的库版本
#ifdef _MSC_VER
#endif

#ifndef __WINDOW_H
#define __WINDOW_H

//#pragma once
// #pragma comment(lib, "...")：将 ... 连入库
#pragma comment(lib, "gdi32.lib")	// gdi32.lib Win 图形界面相关程序
#pragma comment(lib, "user32.lib")	// user32.lib Win 图形界面相关程序

#include "targetver.h"

// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <strsafe.h>

// C++ 运行时头文件
#include <iostream>

#include "Mathf.h"

class Window
{
public:
	// 窗口是否正在运行
	bool _isRunning;
	// 用户键盘键入指令处理
	bool _keyDown[256];
	// Win 窗口 Handle
	HWND _hwnd;
	// Win Device Content Handle
	HDC _hdc;
	// 两个 Bitmap 指针
	// 他们是接受 Renderer 中的像素信息并呈现到屏幕上的
	HBITMAP _hb, _ob;

	// 窗口大小
	_INT _width, _height;
	// 窗口渲染缓冲
	_PBYTE _screenBuffer;
	// 窗口头信息
	LPTSTR _titleInfo;

	// 构造 + 析构函数
	Window();
	~Window();

	// 初始化
	_INT Init(_INT width, _INT height, LPTSTR title);

	// 窗口关闭
	_INT Close();

	// 翻译和发送信息到 Win 主程处理
	void Dispatch();

	// 更新窗口
	void Update();

	// 处理用户输入消息
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// 全局静态变量：Win 应用程序进程 + 窗口
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static Window* _window;
#endif // !__WINDOW_H