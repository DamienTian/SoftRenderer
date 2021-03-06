/*
Window.cpp 自制窗口
目的：让开发者更方便的控制窗口
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
大气象 纯C++创建Windows窗体
*/

//#include "stdafx.h"
#include "Window.h"

Window::Window()
{
	_width = 0;
	_height = 0;
	_screenBuffer = NULL;
	// 给 KeyDown 配置空间
	memset(_keyDown, false, sizeof(bool) * 256);
	_isRunning = true;
	_hwnd = NULL;
	_hdc = NULL;
	_hb = NULL;
	_ob = NULL;
	_window = this;
	_titleInfo = new TCHAR[512];
}

Window::~Window() {
	delete[] _titleInfo;
}

_INT Window::Init(_INT width, _INT height, LPTSTR title) {
	// 创建一个 Win 窗口文件
	WNDCLASS wc;
	wc.style = CS_BYTEALIGNCLIENT;	// 窗口样式
	wc.lpfnWndProc = WndProc;		// 设置窗体接受 windows 消息函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;			// 窗口实例名
	wc.hIcon = NULL;				// 窗口图标
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("WINDOW");

	// 创建一个 BITMAPINFO ：定义了 Windows DIB 设备无关位图
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = width;		// 图像高度和宽度
	bi.bmiHeader.biHeight = -height;	// NOTE: （以 DX 标准）高度为负数，DIB自上往下
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;		// 颜色记录需要用到的位数
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = width * height * 4;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	// 创建一个长方体（定义视窗大小使用）
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	Close();
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClass(&wc)) {
		std::cerr << "窗口初始化失败：RegisterClass(&wc) 失败" << std::endl;
		return -1;
	}

	// 创建窗口实例
	_hwnd = CreateWindow(_T("WINDOW"), title,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (_hwnd == NULL) {
		std::cerr << "窗口初始化失败：CreateWindow 失败" << std::endl;
		return -2;
	}

	_isRunning = true;

	// 创建 DC 实例
	HDC hdc = GetDC(_hwnd);
	_hdc = CreateCompatibleDC(hdc);
	ReleaseDC(_hwnd, hdc);

	// 创建位图并绑定到 DC 上
	_PVOID ptr;
	_hb = CreateDIBSection(_hdc, &bi, DIB_RGB_COLORS, &ptr, NULL, NULL);
	if (_hb == NULL) {
		std::cerr << "窗口初始化失败：CreateDIBSection 失败" << std::endl;
		return -3;
	}

	// 将位图绑定到窗口渲染缓冲
	_ob = (HBITMAP)SelectObject(_hdc, _hb);
	_screenBuffer = (_PBYTE)ptr;

	// 设置窗口大小
	_width = width;
	_height = height;
	StringCchCopyA(_titleInfo, sizeof(title), title);
	AdjustWindowRect(&rc, GetWindowLong(_hwnd, GWL_STYLE), 0);
	// wx wy 窗口大小
	_INT wx = rc.right - rc.left;
	_INT wy = rc.bottom - rc.top;
	// sx sy 窗口位置
	_INT sx = (GetSystemMetrics(SM_CYSCREEN) - wx) / 2;
	_INT sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) { sy = 0; }
	if (sx < 0) { sx = 0; }

	SetWindowPos(_hwnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(_hwnd);
	ShowWindow(_hwnd, SW_NORMAL);

	Dispatch();

	// 给窗口渲染缓冲分配空间
	memset(_screenBuffer, 0, width * height * PTR_SIZE);
	return 0;
}

_INT Window::Close() {
	if (_hdc != NULL) {
		if (_ob != NULL) {
			SelectObject(_hdc, _ob);
			_ob = NULL;
		}
		DeleteDC(_hdc);
		_hdc = NULL;
	}
	if (_hb != NULL) {
		DeleteObject(_hb);
		_hb = NULL;
	}
	if (_hwnd != NULL) {
		CloseWindow(_hwnd);
		_hwnd = NULL;
	}
	return 0;
}

void Window::Dispatch() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (_isRunning) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) { break; }
		if (!GetMessage(&msg, NULL, 0, 0)) { break; }
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::Update() {
	HDC hdc = GetDC(_hwnd);
	BitBlt(hdc, 0, 0, _width, _height, _hdc, 0, 0, SRCCOPY);
	ReleaseDC(_hwnd, hdc);
	Dispatch();
}

LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN: {
		_keyDown[(_UINT)wParam] = true;
		return 0;
	}
	case WM_KEYUP: {
		_keyDown[(_UINT)wParam] = false;
		return 0;
	}
	default: {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY: {
		_window->_isRunning = false;
		return 0;
	}
	case WM_CLOSE: {
		_window->_isRunning = false;
		return 0;
	}
	default: {
		return _window->MessageHandler(hwnd, msg, wParam, lParam);
	}
	}
	return 0;
}

