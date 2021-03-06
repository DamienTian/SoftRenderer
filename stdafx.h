// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

//#pragma once
// #pragma comment(lib, "...")：将 ... 连入库
#pragma comment(lib, "gdi32.lib")	// gdi32.lib Win 图形界面相关程序
#pragma comment(lib, "user32.lib")	// user32.lib Win 图形界面相关程序

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
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
#include <vector>

// 在此处引用程序需要的其他头文件
// NOTE: 头文件声明顺序影响编译
//#include "Mathf.h"
////#include "Vector.h"
////#include "Matrix.h"
//#include "Transform.h"
//#include "Camera.h"
//#include "Color.h"
//#include "Vertex.h"
//#include "Triangle.h"
//#include "Bound.h"
//#include "Mesh.h"
//#include "Line.h"
//#include "Scanline.h"
//#include "Trapezoid.h"
//#include "Light.h"
//#include "Renderer.h"
//#include "Window.h"
