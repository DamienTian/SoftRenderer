/*
Renderer.h 渲染器
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
*/

//#include "stdafx.h"
#include "Renderer.h"

// 相机位置
extern Vector3 _cameraPos;

Renderer::Renderer(Transform * transform) {
	_transform = transform;
}

Renderer::~Renderer() {
	if (_buffer != NULL) {
		delete[] _buffer;
	}
	delete _transform;
}

void Renderer::Init(_INT width, _INT height, _PVOID buffer) {
	// 分配缓冲空间（分配方式见 BlauHimmel 代码或者自己的博客说明）
	_INT needSpace = PTR_SIZE * (height * 2 + TEXTURE_MAXSIZE) + BYTE_SIZE * width * height * 8;
	// 标记分配指针
	_PBYTE ptr = new _BYTE[needSpace + 64 * BYTE_SIZE];

	// 帧缓冲和深度缓冲的实际存储空间
	_PBYTE frameBuffer, zBuffer;

	assert(buffer != NULL);

	// 分配缓冲内容，将 _buffer 指向 ptr 头部
	_buffer = ptr;
	// 分配帧缓冲索引，深度缓冲索引，贴图信息索引的地址与空间
	_frameBuffer = (_UINT**)ptr;
	ptr += height * PTR_SIZE;
	_zBuffer = (_FLOAT**)ptr;
	ptr += height * PTR_SIZE;
	_texture = (_UINT**)ptr;
	ptr += TEXTURE_MAXSIZE * PTR_SIZE;

	// 分配帧缓冲，深度缓冲的地址与空间
	frameBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;
	zBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;

	// 若之前传递 buffer 不为空，将其付给帧缓冲
	if (buffer != NULL) {
		frameBuffer = (_PBYTE)buffer;
	}

	// 根据之前的索引列表分配内存，每一个索引为一行信息
	for (int i = 0; i < height; i++) {
		_frameBuffer[i] = (_UINT*)(frameBuffer + BYTE_SIZE * width * 4 * i);
		_zBuffer[i] = (_FLOAT*)(zBuffer + BYTE_SIZE * width * 4 * i);
	}

	// 分配贴图信息地址与空间
	_texture[0] = (_UINT*)ptr;
	memset(_texture[0], 0, 64);
	// 初始化贴图大小
	// NOTE：贴图宽高应该是 2 的倍数才能保证贴图位置正确（The 'power of two' rule）
	_textureWidth = 2;
	_textureHeight = 2;

	_maxU = 1.0f;
	_maxV = 1.0f;
	_width = width;
	_height = height;
	_transform->Init(_width, _height);
	_background = 0x999999;
	_foreground = 0;
	_renderMode = RENDER_STATE_WIREFRAME;

	// 设置光源属性
	_ambientLight._color = Color(1.0f, 1.0f, 1.0f);
	_ambientLight._intensity = 0.5f;

	_directionalLight._color = Color(1.0f, 1.0f, 1.0f);
	_directionalLight._intensity = 1.0f;
	_directionalLight._direction = Vector3(0.0f, 0.0f, 1.0f);
}

void Renderer::Destroy() {
	if (_buffer != NULL) {
		delete[] _buffer;
	}
	_frameBuffer = NULL;
	_zBuffer = NULL;
	_texture = NULL;
}

void Renderer::CleanBuffer() {
	// 清空所有帧缓存
	for (auto i = 0; i < _height; i++) {
		for (auto j = 0; j < _width; j++) {
			_frameBuffer[i][j] = _background;
		}
	}
	// 清空所有深度缓存
	for (auto i = 0; i < _height; i++) {
		for (auto j = 0; j < _width; j++) {
			_zBuffer[i][j] = 0.0f;
		}
	}
}

void Renderer::SetTexture(_PVOID bit, _LONG pitch, _INT textureWidth, _INT textureHeight) {
	_PBYTE ptr = (_PBYTE)bit;	// 贴图图元
	for (auto i = 0; i < textureHeight; i++, ptr += pitch) {
		_texture[i] = (_UINT*)ptr;
	}
	_textureWidth = textureWidth;
	_textureHeight = textureHeight;
	_maxU = (_FLOAT)(textureWidth - 1);
	_maxV = (_FLOAT)(textureHeight - 1);
}

_UINT Renderer::ReadTexture(_FLOAT u, _FLOAT v) {
	u = u * _maxU;
	v = v * _maxV;
	_INT x = (_INT)Range(u, 0, _maxU);
	_INT y = (_INT)Range(v, 0, _maxV);
	return _texture[y][x];
}

// 画点方法
void Renderer::DrawPixel(_INT x, _INT y, _UINT color) {
	// NOTE: SetPixel 使用未使用帧缓存的直接描点，
	//		下面更新为使用 frameBuffer 的瞄点方法
	//SetPixel(*_hdc, x, y, color.GetGolor());

	// 这是使用了帧缓存方法的绘画方式
	// _frameBuffer 会将里面的点传到位图上进行绘画
	// 因为之前的代码已经将 _frameBuffer 与 Window._screenBuffer 绑定
	// 所以在这里的像素操作可以映射到屏幕上
	if (x >= 0 && x < _width && y >= 0 && y < _height) {
		_frameBuffer[y][x] = color;
	}
}

// 画线方法
void Renderer::DrawLine(Vector2i& v1, Vector2i& v2, _UINT color) {
	// 若两点重合，只画一点
	if (v1 == v2) {
		DrawPixel(v1._x, v1._y, color);
	}
	// 两点构成直线平行于 Y 轴情况
	else if (v1._x == v2._x) {
		_INT direction = v1._y > v2._y ? -1 : 1;
		for (auto y = v1._y; y != v2._y; y += direction) {
			DrawPixel(v1._x, y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	// 两点构成直线平行于 X 轴情况
	else if (v1._y == v2._y) {
		_INT direction = v1._x > v2._x ? -1 : 1;
		for (auto x = v1._x; x != v2._x; x += direction) {
			DrawPixel(x, v1._y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	// 需要计算斜率的情况
	else {
		_INT dx = Abs(v1._x - v2._x);
		_INT dy = Abs(v1._y - v2._y);
		_INT error = 0;	// 累计变化量

		// 斜率小于 1，以 x 轴为基准计算
		if (dx > dy) {
			if (v1._x > v2._x) {
				Swap(v1._x, v2._x);
				Swap(v1._y, v2._y);
			}
			_INT direction = v1._y > v2._y ? -1 : 1;
			for (auto x = v1._x, y = v1._y; x <= v2._x; x++) {
				DrawPixel(x, y, color);
				error += dy;
				if (error >= dx) {
					error -= dx;
					y += direction;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(v2._x, v2._y, color);
		}
		// 斜率大于 1，以 y 轴为基准计算
		else {
			if (v1._y > v2._y) {
				Swap(v1._x, v2._x);
				Swap(v1._y, v2._y);
			}
			_INT direction = v1._x > v2._x ? -1 : 1;
			for (auto y = v1._y, x = v1._x; y <= v2._y; y++) {
				DrawPixel(x, y, color);
				error += dx;
				if (error >= dy) {
					error -= dy;
					x += direction;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(v2._x, v2._y, color);
		}
	}
}

// 画扫描线方法
void Renderer::DrawScanline(Scanline& scanline, Color materialAmbientColor, Color materialDiffuseColor) {
	// 获取扫描线在帧缓冲中的相关信息存储空间
	_UINT* frameBuffer = _frameBuffer[scanline._y];
	_FLOAT* zBuffer = _zBuffer[scanline._y];

	// 进行透视纹理插值
	// NOTE：注意这里的插值是非线性的，扫描线的步长和帧缓冲的步长不等
	for (auto i = 0, x = scanline._x; i < scanline._width && x < _width; i++, x++) {
		if (x >= 0 && x < _width) {
			_FLOAT ww = scanline._startPixel._depth;
			// 当新输入的深度值大于当前深度值时，更新需要渲染的像素
			if (ww >= zBuffer[x]) {
				zBuffer[x] = ww;

				// 光照处理
				//	NOTE: 因为我用的是左手坐标系，光源方向是指向 z 轴的
				//		所以这里光源方向一定要求反，否则光源等同于直射入模型内部，而夹角则会变成钝角
				Vector3 lightDir = -_directionalLight._direction.Normalize();
				Vector3 viewVertexNormal = scanline._startPixel._normal.Normalize();
				_FLOAT dp = lightDir.Dot(viewVertexNormal);
				Color lightColor = _directionalLight._color * _ambientLight._color * _directionalLight._intensity;

				// 颜色填充渲染模式
				if (_renderMode & RENDER_STATE_COLOR) {
					Color color = scanline._startPixel._color * (1 / ww) * materialAmbientColor * materialDiffuseColor;
					if (_isDirectionalLightOn) {
						color = color * lightColor * Abs(dp);
					}

					_INT R = (_INT)(color._r * 255.0f);
					_INT G = (_INT)(color._g * 255.0f);
					_INT B = (_INT)(color._b * 255.0f);

					// 限制颜色区间
					R = (_INT)Range((_FLOAT)R, 0.0f, 255.0f);
					G = (_INT)Range((_FLOAT)G, 0.0f, 255.0f);
					B = (_INT)Range((_FLOAT)B, 0.0f, 255.0f);

					// 将颜色数据通过位移形成一个 16 进制数
					frameBuffer[x] = (R << 16) | (G << 8) | (B << 0);
				}
				// 贴图模式
				else if (_renderMode & RENDER_STATE_TEXTURE) {
					// 由于之前计算 u, v 插值是根据 1/z 进行计算的，所以在这里我们进行还原
					_FLOAT u = scanline._startPixel._textureCoord._x / ww;
					_FLOAT v = scanline._startPixel._textureCoord._y / ww;
					_UINT tt = ReadTexture(u, v);

					// 将该纹理贴图对应的像素颜色提取出来
					_INT R = ((tt & 0xff0000) >> 16) * materialAmbientColor._r * materialDiffuseColor._r;
					_INT G = ((tt & 0x00ff00) >> 8) * materialAmbientColor._g * materialDiffuseColor._g;
					_INT B = ((tt & 0x0000ff) >> 0) * materialAmbientColor._b * materialDiffuseColor._b;

					if (_isDirectionalLightOn) {
						R *= lightColor._r * Abs(dp);
						G *= lightColor._g * Abs(dp);
						B *= lightColor._b * Abs(dp);
					}
					// 限制颜色区间
					R = (_INT)Range((_FLOAT)R, 0.0f, 255.0f);
					G = (_INT)Range((_FLOAT)G, 0.0f, 255.0f);
					B = (_INT)Range((_FLOAT)B, 0.0f, 255.0f);
					frameBuffer[x] = (R << 16) | (G << 8) | (B << 0);
				}
			}
		}
		// 将扫描线起始点向前移动一个步长
		scanline._startPixel = scanline._startPixel + scanline._stepPixel;
		if (x >= _width) {
			break;
		}
	}
}

// 渲染多边形方法
void Renderer::RenderTrapezoid(Trapezoid& trapezoid, Color materialAmbientColor, Color materialDiffuseColor) {
	_INT top = (_INT)(trapezoid._top + 0.5f);
	_INT bottom = (_INT)(trapezoid._bottom + 0.5f);

	for (auto i = top; i < bottom; i++) {
		if (i >= 0 && i < _height) {
			trapezoid.GetEndPoint(i + 0.5f);
			Scanline scanline = trapezoid.InitScanline(i);
			DrawScanline(scanline, materialAmbientColor, materialDiffuseColor);
		}
		if (i >= _height) break;
	}
}

void Renderer::RenderTriangle(Vertex& v1, Vertex& v2, Vertex& v3, Color materialAmbientColor, Color materialDiffuseColor) {
	// 背面剔除计算 =================================================
	// 相机视向量计算
	// 转换顶点位置到视空间
	Vector4 vv1 = _transform->ToViewSpace(v1._position);
	Vector4 vv2 = _transform->ToViewSpace(v2._position);
	Vector4 vv3 = _transform->ToViewSpace(v3._position);

	// 计算（面）法向量
	Vector3 p1 = Vector3(vv2 - vv1);
	Vector3 p2 = Vector3(vv3 - vv2);
	Vector3 normal = p1.Cross(p2);

	Vector3 viewDir = vv1 - Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	// ============================================================

	// 转换顶点位置到屏幕空间
	Vector4 c1 = _transform->ApplyTransform(v1._position);
	Vector4 c2 = _transform->ApplyTransform(v2._position);
	Vector4 c3 = _transform->ApplyTransform(v3._position);

	// 将在屏幕外的顶点剔除
	if (_transform->CheckCVV(c1) != 0 ||
		_transform->CheckCVV(c2) != 0 ||
		_transform->CheckCVV(c3) != 0) {
		return;
	}

	// 进行透视除法，将顶点映射到屏幕上（将将归一化坐标变为屏幕坐标）
	Vector4 h1 = _transform->Homogenize(c1);
	Vector4 h2 = _transform->Homogenize(c2);
	Vector4 h3 = _transform->Homogenize(c3);

	if (_renderMode & RENDER_STATE_WIREFRAME) {
		Vector2i h1i = Vector2i(h1);
		Vector2i h2i = Vector2i(h2);
		Vector2i h3i = Vector2i(h3);
		DrawLine(h1i, h2i, _foreground);
		DrawLine(h1i, h3i, _foreground);
		DrawLine(h2i, h3i, _foreground);
	}

	else if (_renderMode & (RENDER_STATE_COLOR | RENDER_STATE_TEXTURE)) {
		// 为每一个三角形生成一个多边形队列，size = 2
		Trapezoid trapezoid[2];

		// 背面剔除
		if (normal.Dot(viewDir.Normalize()) < 0) {
			return;
		}

		// 制造一个三角形面用于渲染
		Triangle triangle(v1, v2, v3);
		// 设置坐标
		triangle._v1._position = h1;
		triangle._v2._position = h2;
		triangle._v3._position = h3;
		// 设置深度坐标
		triangle._v1._position._w = c1._w;
		triangle._v2._position._w = c2._w;
		triangle._v3._position._w = c3._w;
		// 将顶点法线变换到相机空间
		triangle._v1._vertexNormal = _transform->ToViewSpace(triangle._v1._vertexNormal).Normalize();
		triangle._v2._vertexNormal = _transform->ToViewSpace(triangle._v2._vertexNormal).Normalize();
		triangle._v3._vertexNormal = _transform->ToViewSpace(triangle._v3._vertexNormal).Normalize();
		// 对纹理坐标进行透视校正插值
		triangle._v1.Init();
		triangle._v2.Init();
		triangle._v3.Init();

		// 分割 + 渲染多边形
		_INT n = Trapezoid::GetTrapezoids(triangle, trapezoid);
		if (n >= 1) {
			RenderTrapezoid(trapezoid[0]);
		}
		if (n >= 2) {
			RenderTrapezoid(trapezoid[1]);
		}
	}
}