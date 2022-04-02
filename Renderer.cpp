/*
Renderer.h ��Ⱦ��
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
*/

//#include "stdafx.h"
#include "Renderer.h"

// ���λ��
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
	// ���仺��ռ䣨���䷽ʽ�� BlauHimmel ��������Լ��Ĳ���˵����
	_INT needSpace = PTR_SIZE * (height * 2 + TEXTURE_MAXSIZE) + BYTE_SIZE * width * height * 8;
	// ��Ƿ���ָ��
	_PBYTE ptr = new _BYTE[needSpace + 64 * BYTE_SIZE];

	// ֡�������Ȼ����ʵ�ʴ洢�ռ�
	_PBYTE frameBuffer, zBuffer;

	assert(buffer != NULL);

	// ���仺�����ݣ��� _buffer ָ�� ptr ͷ��
	_buffer = ptr;
	// ����֡������������Ȼ�����������ͼ��Ϣ�����ĵ�ַ��ռ�
	_frameBuffer = (_UINT**)ptr;
	ptr += height * PTR_SIZE;
	_zBuffer = (_FLOAT**)ptr;
	ptr += height * PTR_SIZE;
	_texture = (_UINT**)ptr;
	ptr += TEXTURE_MAXSIZE * PTR_SIZE;

	// ����֡���壬��Ȼ���ĵ�ַ��ռ�
	frameBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;
	zBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;

	// ��֮ǰ���� buffer ��Ϊ�գ����丶��֡����
	if (buffer != NULL) {
		frameBuffer = (_PBYTE)buffer;
	}

	// ����֮ǰ�������б������ڴ棬ÿһ������Ϊһ����Ϣ
	for (int i = 0; i < height; i++) {
		_frameBuffer[i] = (_UINT*)(frameBuffer + BYTE_SIZE * width * 4 * i);
		_zBuffer[i] = (_FLOAT*)(zBuffer + BYTE_SIZE * width * 4 * i);
	}

	// ������ͼ��Ϣ��ַ��ռ�
	_texture[0] = (_UINT*)ptr;
	memset(_texture[0], 0, 64);
	// ��ʼ����ͼ��С
	// NOTE����ͼ����Ӧ���� 2 �ı������ܱ�֤��ͼλ����ȷ��The 'power of two' rule��
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

	// ���ù�Դ����
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
	// �������֡����
	for (auto i = 0; i < _height; i++) {
		for (auto j = 0; j < _width; j++) {
			_frameBuffer[i][j] = _background;
		}
	}
	// ���������Ȼ���
	for (auto i = 0; i < _height; i++) {
		for (auto j = 0; j < _width; j++) {
			_zBuffer[i][j] = 0.0f;
		}
	}
}

void Renderer::SetTexture(_PVOID bit, _LONG pitch, _INT textureWidth, _INT textureHeight) {
	_PBYTE ptr = (_PBYTE)bit;	// ��ͼͼԪ
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

// ���㷽��
void Renderer::DrawPixel(_INT x, _INT y, _UINT color) {
	// NOTE: SetPixel ʹ��δʹ��֡�����ֱ����㣬
	//		�������Ϊʹ�� frameBuffer ����㷽��
	//SetPixel(*_hdc, x, y, color.GetGolor());

	// ����ʹ����֡���淽���Ļ滭��ʽ
	// _frameBuffer �Ὣ����ĵ㴫��λͼ�Ͻ��л滭
	// ��Ϊ֮ǰ�Ĵ����Ѿ��� _frameBuffer �� Window._screenBuffer ��
	// ��������������ز�������ӳ�䵽��Ļ��
	if (x >= 0 && x < _width && y >= 0 && y < _height) {
		_frameBuffer[y][x] = color;
	}
}

// ���߷���
void Renderer::DrawLine(Vector2i& v1, Vector2i& v2, _UINT color) {
	// �������غϣ�ֻ��һ��
	if (v1 == v2) {
		DrawPixel(v1._x, v1._y, color);
	}
	// ���㹹��ֱ��ƽ���� Y �����
	else if (v1._x == v2._x) {
		_INT direction = v1._y > v2._y ? -1 : 1;
		for (auto y = v1._y; y != v2._y; y += direction) {
			DrawPixel(v1._x, y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	// ���㹹��ֱ��ƽ���� X �����
	else if (v1._y == v2._y) {
		_INT direction = v1._x > v2._x ? -1 : 1;
		for (auto x = v1._x; x != v2._x; x += direction) {
			DrawPixel(x, v1._y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	// ��Ҫ����б�ʵ����
	else {
		_INT dx = Abs(v1._x - v2._x);
		_INT dy = Abs(v1._y - v2._y);
		_INT error = 0;	// �ۼƱ仯��

		// б��С�� 1���� x ��Ϊ��׼����
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
		// б�ʴ��� 1���� y ��Ϊ��׼����
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

// ��ɨ���߷���
void Renderer::DrawScanline(Scanline& scanline, Color materialAmbientColor, Color materialDiffuseColor) {
	// ��ȡɨ������֡�����е������Ϣ�洢�ռ�
	_UINT* frameBuffer = _frameBuffer[scanline._y];
	_FLOAT* zBuffer = _zBuffer[scanline._y];

	// ����͸��������ֵ
	// NOTE��ע������Ĳ�ֵ�Ƿ����Եģ�ɨ���ߵĲ�����֡����Ĳ�������
	for (auto i = 0, x = scanline._x; i < scanline._width && x < _width; i++, x++) {
		if (x >= 0 && x < _width) {
			_FLOAT ww = scanline._startPixel._depth;
			// ������������ֵ���ڵ�ǰ���ֵʱ��������Ҫ��Ⱦ������
			if (ww >= zBuffer[x]) {
				zBuffer[x] = ww;

				// ���մ���
				//	NOTE: ��Ϊ���õ�����������ϵ����Դ������ָ�� z ���
				//		���������Դ����һ��Ҫ�󷴣������Դ��ͬ��ֱ����ģ���ڲ������н�����ɶ۽�
				Vector3 lightDir = -_directionalLight._direction.Normalize();
				Vector3 viewVertexNormal = scanline._startPixel._normal.Normalize();
				_FLOAT dp = lightDir.Dot(viewVertexNormal);
				Color lightColor = _directionalLight._color * _ambientLight._color * _directionalLight._intensity;

				// ��ɫ�����Ⱦģʽ
				if (_renderMode & RENDER_STATE_COLOR) {
					Color color = scanline._startPixel._color * (1 / ww) * materialAmbientColor * materialDiffuseColor;
					if (_isDirectionalLightOn) {
						color = color * lightColor * Abs(dp);
					}

					_INT R = (_INT)(color._r * 255.0f);
					_INT G = (_INT)(color._g * 255.0f);
					_INT B = (_INT)(color._b * 255.0f);

					// ������ɫ����
					R = (_INT)Range((_FLOAT)R, 0.0f, 255.0f);
					G = (_INT)Range((_FLOAT)G, 0.0f, 255.0f);
					B = (_INT)Range((_FLOAT)B, 0.0f, 255.0f);

					// ����ɫ����ͨ��λ���γ�һ�� 16 ������
					frameBuffer[x] = (R << 16) | (G << 8) | (B << 0);
				}
				// ��ͼģʽ
				else if (_renderMode & RENDER_STATE_TEXTURE) {
					// ����֮ǰ���� u, v ��ֵ�Ǹ��� 1/z ���м���ģ��������������ǽ��л�ԭ
					_FLOAT u = scanline._startPixel._textureCoord._x / ww;
					_FLOAT v = scanline._startPixel._textureCoord._y / ww;
					_UINT tt = ReadTexture(u, v);

					// ����������ͼ��Ӧ��������ɫ��ȡ����
					_INT R = ((tt & 0xff0000) >> 16) * materialAmbientColor._r * materialDiffuseColor._r;
					_INT G = ((tt & 0x00ff00) >> 8) * materialAmbientColor._g * materialDiffuseColor._g;
					_INT B = ((tt & 0x0000ff) >> 0) * materialAmbientColor._b * materialDiffuseColor._b;

					if (_isDirectionalLightOn) {
						R *= lightColor._r * Abs(dp);
						G *= lightColor._g * Abs(dp);
						B *= lightColor._b * Abs(dp);
					}
					// ������ɫ����
					R = (_INT)Range((_FLOAT)R, 0.0f, 255.0f);
					G = (_INT)Range((_FLOAT)G, 0.0f, 255.0f);
					B = (_INT)Range((_FLOAT)B, 0.0f, 255.0f);
					frameBuffer[x] = (R << 16) | (G << 8) | (B << 0);
				}
			}
		}
		// ��ɨ������ʼ����ǰ�ƶ�һ������
		scanline._startPixel = scanline._startPixel + scanline._stepPixel;
		if (x >= _width) {
			break;
		}
	}
}

// ��Ⱦ����η���
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
	// �����޳����� =================================================
	// �������������
	// ת������λ�õ��ӿռ�
	Vector4 vv1 = _transform->ToViewSpace(v1._position);
	Vector4 vv2 = _transform->ToViewSpace(v2._position);
	Vector4 vv3 = _transform->ToViewSpace(v3._position);

	// ���㣨�棩������
	Vector3 p1 = Vector3(vv2 - vv1);
	Vector3 p2 = Vector3(vv3 - vv2);
	Vector3 normal = p1.Cross(p2);

	Vector3 viewDir = vv1 - Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	// ============================================================

	// ת������λ�õ���Ļ�ռ�
	Vector4 c1 = _transform->ApplyTransform(v1._position);
	Vector4 c2 = _transform->ApplyTransform(v2._position);
	Vector4 c3 = _transform->ApplyTransform(v3._position);

	// ������Ļ��Ķ����޳�
	if (_transform->CheckCVV(c1) != 0 ||
		_transform->CheckCVV(c2) != 0 ||
		_transform->CheckCVV(c3) != 0) {
		return;
	}

	// ����͸�ӳ�����������ӳ�䵽��Ļ�ϣ�������һ�������Ϊ��Ļ���꣩
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
		// Ϊÿһ������������һ������ζ��У�size = 2
		Trapezoid trapezoid[2];

		// �����޳�
		if (normal.Dot(viewDir.Normalize()) < 0) {
			return;
		}

		// ����һ����������������Ⱦ
		Triangle triangle(v1, v2, v3);
		// ��������
		triangle._v1._position = h1;
		triangle._v2._position = h2;
		triangle._v3._position = h3;
		// �����������
		triangle._v1._position._w = c1._w;
		triangle._v2._position._w = c2._w;
		triangle._v3._position._w = c3._w;
		// �����㷨�߱任������ռ�
		triangle._v1._vertexNormal = _transform->ToViewSpace(triangle._v1._vertexNormal).Normalize();
		triangle._v2._vertexNormal = _transform->ToViewSpace(triangle._v2._vertexNormal).Normalize();
		triangle._v3._vertexNormal = _transform->ToViewSpace(triangle._v3._vertexNormal).Normalize();
		// �������������͸��У����ֵ
		triangle._v1.Init();
		triangle._v2.Init();
		triangle._v3.Init();

		// �ָ� + ��Ⱦ�����
		_INT n = Trapezoid::GetTrapezoids(triangle, trapezoid);
		if (n >= 1) {
			RenderTrapezoid(trapezoid[0]);
		}
		if (n >= 2) {
			RenderTrapezoid(trapezoid[1]);
		}
	}
}