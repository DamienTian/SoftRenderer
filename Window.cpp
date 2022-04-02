/*
Window.cpp ���ƴ���
Ŀ�ģ��ÿ����߸�����Ŀ��ƴ���
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
������ ��C++����Windows����
*/

//#include "stdafx.h"
#include "Window.h"

Window::Window()
{
	_width = 0;
	_height = 0;
	_screenBuffer = NULL;
	// �� KeyDown ���ÿռ�
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
	// ����һ�� Win �����ļ�
	WNDCLASS wc;
	wc.style = CS_BYTEALIGNCLIENT;	// ������ʽ
	wc.lpfnWndProc = WndProc;		// ���ô������ windows ��Ϣ����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;			// ����ʵ����
	wc.hIcon = NULL;				// ����ͼ��
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("WINDOW");

	// ����һ�� BITMAPINFO �������� Windows DIB �豸�޹�λͼ
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = width;		// ͼ��߶ȺͿ���
	bi.bmiHeader.biHeight = -height;	// NOTE: ���� DX ��׼���߶�Ϊ������DIB��������
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;		// ��ɫ��¼��Ҫ�õ���λ��
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = width * height * 4;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	// ����һ�������壨�����Ӵ���Сʹ�ã�
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
		std::cerr << "���ڳ�ʼ��ʧ�ܣ�RegisterClass(&wc) ʧ��" << std::endl;
		return -1;
	}

	// ��������ʵ��
	_hwnd = CreateWindow(_T("WINDOW"), title,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (_hwnd == NULL) {
		std::cerr << "���ڳ�ʼ��ʧ�ܣ�CreateWindow ʧ��" << std::endl;
		return -2;
	}

	_isRunning = true;

	// ���� DC ʵ��
	HDC hdc = GetDC(_hwnd);
	_hdc = CreateCompatibleDC(hdc);
	ReleaseDC(_hwnd, hdc);

	// ����λͼ���󶨵� DC ��
	_PVOID ptr;
	_hb = CreateDIBSection(_hdc, &bi, DIB_RGB_COLORS, &ptr, NULL, NULL);
	if (_hb == NULL) {
		std::cerr << "���ڳ�ʼ��ʧ�ܣ�CreateDIBSection ʧ��" << std::endl;
		return -3;
	}

	// ��λͼ�󶨵�������Ⱦ����
	_ob = (HBITMAP)SelectObject(_hdc, _hb);
	_screenBuffer = (_PBYTE)ptr;

	// ���ô��ڴ�С
	_width = width;
	_height = height;
	StringCchCopyA(_titleInfo, sizeof(title), title);
	AdjustWindowRect(&rc, GetWindowLong(_hwnd, GWL_STYLE), 0);
	// wx wy ���ڴ�С
	_INT wx = rc.right - rc.left;
	_INT wy = rc.bottom - rc.top;
	// sx sy ����λ��
	_INT sx = (GetSystemMetrics(SM_CYSCREEN) - wx) / 2;
	_INT sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) { sy = 0; }
	if (sx < 0) { sx = 0; }

	SetWindowPos(_hwnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(_hwnd);
	ShowWindow(_hwnd, SW_NORMAL);

	Dispatch();

	// ��������Ⱦ�������ռ�
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
