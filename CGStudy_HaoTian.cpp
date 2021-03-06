// CGStudy_HaoTian.cpp: 定义控制台应用程序的入口点。
//

#include <tchar.h>
#include <stdlib.h>
//#include "stdafx.h"
#include "Renderer.h"
#include "Camera.h"
#include "Object.h"
#include "Window.h"

// Global Variables
Vector3 _cameraPos;
Mesh _mesh = Mesh(24, 24);

// Debug：OBJ 贴图 debug
Mesh _trianglePlane = Mesh(3, 3);

// NOTE：因为 Scene 是整个渲染器的渲染世界，所有的被渲染物体都要放在这里
//		所以在此将其作为一个全局变量存储在此
Scene _scene;

// Prototype
bool BoundInCVV(Transform* transform, Mesh& mesh);
void InitBMPTexture_MapKd(Renderer& renderer, RenderObject * object);

// 建立一个有 24 个顶点的 BoxMesh
void CreateBoxMesh() {
	// NOTE：原 Mesh Build 参考 ===========================================================
	// 制造一个 Box Mesh
	//mesh._verticesBuffer[0] = Vertex(Vector4(1, -1, 1, 1), 0, 0, Color(1.0f, 0.0f, 0.0f));	// 红
	//mesh._verticesBuffer[1] = Vertex(Vector4(-1, -1, 1, 1), 0, 1, Color(0.0f, 1.0f, 0.0f));	// 绿
	//mesh._verticesBuffer[2] = Vertex(Vector4(-1, 1, 1, 1), 1, 1, Color(0.0f, 0.0f, 1.0f));	// 蓝
	//mesh._verticesBuffer[3] = Vertex(Vector4(1, 1, 1, 1), 1, 0, Color(1.0f, 0.0f, 1.0f));		// 紫
	//mesh._verticesBuffer[4] = Vertex(Vector4(1, -1, -1, 1), 0, 0, Color(0.0f, 0.0f, 0.0f));	// 黑
	//mesh._verticesBuffer[5] = Vertex(Vector4(-1, -1, -1, 1), 0, 1, Color(1.0f, 1.0f, 1.0f));	// 白 
	//mesh._verticesBuffer[6] = Vertex(Vector4(-1, 1, -1, 1), 1, 1, Color(1.0f, 1.0f, 0.0f));	// 黄
	//mesh._verticesBuffer[7] = Vertex(Vector4(1, 1, -1, 1), 1, 0, Color(0.0f, 1.0f, 1.0f));	// 青
	//mesh._verticesCount = 8;
	// ===================================================================================

// 在模型空间中，总共有六个法向量方向（以左手坐标系为准）
	Vector4 left(-1.0f, 0.0f, 0.0f, 0.0f);	// x 轴负方向 左面
	Vector4 right(1.0f, 0.0f, 0.0f, 0.0f);	// x 轴正方向 右面
	Vector4 up(0.0f, 1.0f, 0.0f, 0.0f);		// y 轴负方向 下面
	Vector4 down(0.0f, -1.0f, 0.0f, 0.0f);	// y 轴正方向 上面
	Vector4 out(0.0f, 0.0f, -1.0f, 0.0f);	// z 轴负方向 正对面
	Vector4 in(0.0f, 0.0f, 1.0f, 0.0f);		// z 轴正方向 背对面


	// 填充顶点缓冲（之前的每个顶点都写三遍，三遍赋予不同的法向量）
	//	按面进行分割
	//	左面 left
	_mesh._verticesBuffer[0] = Vertex(Vector4(-1, -1, 1, 1), left, 0, 0, Color(0.0f, 1.0f, 0.0f));	// 绿 left
	_mesh._verticesBuffer[1] = Vertex(Vector4(-1, -1, -1, 1), left, 1, 0, Color(1.0f, 1.0f, 1.0f));	// 白 left
	_mesh._verticesBuffer[2] = Vertex(Vector4(-1, 1, -1, 1), left, 1, 1, Color(1.0f, 1.0f, 0.0f));	// 黄 left
	_mesh._verticesBuffer[3] = Vertex(Vector4(-1, 1, 1, 1), left, 0, 1, Color(0.0f, 0.0f, 1.0f));	// 蓝 left

	//	右面 right
	_mesh._verticesBuffer[4] = Vertex(Vector4(1, -1, -1, 1), right, 0, 0, Color(0.0f, 0.0f, 0.0f));	// 黑 right
	_mesh._verticesBuffer[5] = Vertex(Vector4(1, -1, 1, 1), right, 1, 0, Color(1.0f, 0.0f, 0.0f));	// 红 right
	_mesh._verticesBuffer[6] = Vertex(Vector4(1, 1, 1, 1), right, 1, 1, Color(1.0f, 0.0f, 1.0f));	// 紫 right
	_mesh._verticesBuffer[7] = Vertex(Vector4(1, 1, -1, 1), right, 0, 1, Color(0.0f, 1.0f, 1.0f));	// 青 right

	//	上面 up
	_mesh._verticesBuffer[8] = Vertex(Vector4(-1, 1, -1, 1), up, 0, 0, Color(1.0f, 1.0f, 0.0f));	// 黄 up
	_mesh._verticesBuffer[9] = Vertex(Vector4(1, 1, -1, 1), up, 1, 0, Color(0.0f, 1.0f, 1.0f));		// 青 up
	_mesh._verticesBuffer[10] = Vertex(Vector4(1, 1, 1, 1), up, 1, 1, Color(1.0f, 0.0f, 1.0f));		// 紫 up
	_mesh._verticesBuffer[11] = Vertex(Vector4(-1, 1, 1, 1), up, 0, 1, Color(0.0f, 0.0f, 1.0f));	// 蓝 up

	//	下面 down
	_mesh._verticesBuffer[12] = Vertex(Vector4(-1, -1, 1, 1), down, 0, 0, Color(0.0f, 1.0f, 0.0f));	// 绿 down
	_mesh._verticesBuffer[13] = Vertex(Vector4(1, -1, 1, 1), down, 1, 0, Color(1.0f, 0.0f, 0.0f));	// 红 down
	_mesh._verticesBuffer[14] = Vertex(Vector4(1, -1, -1, 1), down, 1, 1, Color(0.0f, 0.0f, 0.0f));	// 黑 down
	_mesh._verticesBuffer[15] = Vertex(Vector4(-1, -1, -1, 1), down, 0, 1, Color(1.0f, 1.0f, 1.0f));// 白 down

	//	正对面 out
	_mesh._verticesBuffer[16] = Vertex(Vector4(-1, -1, -1, 1), out, 0, 0, Color(1.0f, 1.0f, 1.0f));	// 白 out
	_mesh._verticesBuffer[17] = Vertex(Vector4(1, -1, -1, 1), out, 1, 0, Color(0.0f, 0.0f, 0.0f));	// 黑 out
	_mesh._verticesBuffer[18] = Vertex(Vector4(1, 1, -1, 1), out, 1, 1, Color(0.0f, 1.0f, 1.0f));	// 青 out
	_mesh._verticesBuffer[19] = Vertex(Vector4(-1, 1, -1, 1), out, 0, 1, Color(1.0f, 1.0f, 0.0f));	// 黄 out

	// 背对面 in
	_mesh._verticesBuffer[20] = Vertex(Vector4(1, -1, 1, 1), in, 0, 0, Color(1.0f, 0.0f, 0.0f));	// 红 in
	_mesh._verticesBuffer[21] = Vertex(Vector4(-1, -1, 1, 1), in, 1, 0, Color(0.0f, 1.0f, 0.0f));	// 绿 in
	_mesh._verticesBuffer[22] = Vertex(Vector4(-1, 1, 1, 1), in, 1, 1, Color(0.0f, 0.0f, 1.0f));	// 蓝 in
	_mesh._verticesBuffer[23] = Vertex(Vector4(1, 1, 1, 1), in, 0, 1, Color(1.0f, 0.0f, 1.0f));		// 紫 in

	// 填充顶点索引缓冲
	for (auto i = 0; i < _mesh._indicesCount; i++) {
		_mesh._indicesBuffer[i] = i;
	}
}

// 画每一个正方形的面
void DrawBoxPlane(Renderer& renderer, _INT i1, _INT i2, _INT i3, _INT i4) {
	// 设置贴图坐标
	_mesh._verticesBuffer[i1]._u = 0; _mesh._verticesBuffer[i1]._v = 0;
	_mesh._verticesBuffer[i2]._u = 1; _mesh._verticesBuffer[i2]._v = 0;
	_mesh._verticesBuffer[i3]._u = 1; _mesh._verticesBuffer[i3]._v = 1;
	_mesh._verticesBuffer[i4]._u = 0; _mesh._verticesBuffer[i4]._v = 1;

	renderer.RenderTriangle(_mesh._verticesBuffer[i1], _mesh._verticesBuffer[i2], _mesh._verticesBuffer[i3]);
	renderer.RenderTriangle(_mesh._verticesBuffer[i3], _mesh._verticesBuffer[i4], _mesh._verticesBuffer[i1]);
}

// 绘制 Box
void DrawBox(Renderer& renderer, _FLOAT theta, _FLOAT x, _FLOAT y, _FLOAT z) {
	Matrix4 worldTransform1;
	Vector4 rotation = Vector4(-1.0f, -0.5f, 1.0f, 0.0f);
	worldTransform1.SetRotation(rotation, theta);
	Matrix4 worldTransform2;
	worldTransform2.SetTranslation(x, y, z);
	renderer._transform->_worldTransform = worldTransform1 * worldTransform2;
	renderer._transform->UpdateTransform();

	// 检查包围盒决定是否进行渲染
	if (!BoundInCVV(renderer._transform, _mesh)) { return; }

	// 画正方形的面
	DrawBoxPlane(renderer, 0, 1, 2, 3);
	DrawBoxPlane(renderer, 4, 5, 6, 7);
	DrawBoxPlane(renderer, 8, 9, 10, 11);
	DrawBoxPlane(renderer, 12, 13, 14, 15);
	DrawBoxPlane(renderer, 16, 17, 18, 19);
	DrawBoxPlane(renderer, 20, 21, 22, 23);
}

// 绘制一个 RenderObject
void DrawObject(Renderer& renderer, RenderObject& object) {
	Matrix4 worldTransform1;
	// Y 轴旋转
	Vector4 rotation = Vector4(-0.0f, -1.0f, 0.0f, 0.0f);
	//Vector4 rotation = Vector4(-1.0f, -0.5f, 1.0f, 0.0f);
	worldTransform1.SetRotation(rotation, object._theta);
	Matrix4 worldTransform2;
	worldTransform2.SetTranslation(object._position._x,
		object._position._y,
		object._position._z);
	renderer._transform->_worldTransform = worldTransform1 * worldTransform2;
	renderer._transform->UpdateTransform();

	if (!BoundInCVV(renderer._transform, *object._mesh)) {
		std::cout << object._name << " 停止渲染 " << std::endl;
		return;
	}

	// 画每一个面
	for (auto i = 0; i < object._mesh->_indicesCount; i += 3) {
		// 提取顶点索引
		_INT i1, i2, i3;
		i1 = object._mesh->_indicesBuffer[i];
		i2 = object._mesh->_indicesBuffer[i + 1];
		i3 = object._mesh->_indicesBuffer[i + 2];

		// 提取顶点
		Vertex v1, v2, v3;
		v1 = object._mesh->_verticesBuffer[i1];
		v2 = object._mesh->_verticesBuffer[i2];
		v3 = object._mesh->_verticesBuffer[i3];

		//std::cout << "顶点索引 " << i1 + 1 << " 的 u v 是：" << v1._u << "   " << v1._v << std::endl;
		//std::cout << "顶点索引 " << i2 + 1 << " 的 u v 是：" << v2._u << "   " << v2._v << std::endl;
		//std::cout << "顶点索引 " << i3 + 1 << " 的 u v 是：" << v3._u << "   " << v3._v << std::endl;

		// 画三角形面（根据三角形顶点绕序）
		if (object._isCounterClockwise) {
			renderer.RenderTriangle(v1, v2, v3, object._material->_ambientColor, object._material->_diffuseColor);
		}
		else {
			renderer.RenderTriangle(v3, v2, v1, object._material->_ambientColor, object._material->_diffuseColor);
		}
	}
}

// 渲染一整个场景
void DrawScene(Renderer& renderer, Scene& scene) {
	for (int i = 0; i < scene._renderObjectCount; i++) {
		if (scene._renderObjects[i]->_material->_mapKdImage != nullptr) {
			InitBMPTexture_MapKd(renderer, scene._renderObjects[i]);
		}
		DrawObject(renderer, *scene._renderObjects[i]);
	}
}

// 制作一个棋盘格贴图
void InitTexture(Renderer& renderer) {
	static _UINT texture[256][256];
	for (auto i = 0; i < 256; i++) {
		for (auto j = 0; j < 256; j++) {
			// 计算该点的坐标
			_INT x = i / 32;
			_INT y = j / 32;
			// 填充颜色
			texture[i][j] = ((x + y) & 1) ? 0xffffff : 0x000000;
		}
	}
	renderer.SetTexture(texture, 256 * 4, 256, 256);
}

// 读取 .bmp 生成一个贴图
//	Note 目前只支持 .obj 中的 map_Kd 路径信息
void InitBMPTexture_MapKd(Renderer& renderer, RenderObject * object) {
	// 读入贴图
	//BMPImage* testImage = BMPImage::ReadInBMP("models/utah_teapot/default.bmp");
	//BMPImage* testImage = BMPImage::ReadInBMP("models/dice/dice.bmp");
	BMPImage* testImage = object->_material->_mapKdImage;
	if (testImage == nullptr) {
		return;
	}
	_INT width = testImage->_width;
	_INT height = testImage->_height;

	// 初始化 texture
	//static _UINT texture[700][525];
	static _UINT texture[TEXTURE_MAXSIZE][TEXTURE_MAXSIZE];
	/*static _UINT** texture;
	texture = new _UINT*[height];
	for (int i = 0; i < height; i++) {
		texture[i] = new _UINT[width];
		memset(texture[i], 0, sizeof(_UINT) * width);
	}*/

	// 填充数据
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			texture[i][j] = testImage->_colorBuffer[i][j].ConvertToINT();
		}
	}

	renderer.SetTexture(texture, width * 4 * BYTE_SIZE, width, height);
	// 清空 texture 以防止内存泄漏
	// TODO: 很糟糕的方式，有没有什么更好的方法
	//	NOTE：目前的解决方式是直接生成一个最大数值贴图
	//for (int i = 0; i < height; i++) {
	//	delete[] texture[i];
	//}
	//delete[] texture;
}

// 相机位置调整
void CameraAdjustment(Renderer& renderer, Vector4& position, _FLOAT nearPlaneDis, _FLOAT farPlaneDis) {
	// 摄像机方向（世界原点坐标求反）
	Vector4 target = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4 direction = target - position;

	// NOTE：目前摄像机方向已经写死，以实现需要的相机移动效果
	direction = Vector4(0.0f, 0.0f, 5.5f, 1.0f);

	// 定义向上方向
	Vector4 up = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	// 调整相机窗口比例
	_FLOAT aspect = (_FLOAT)renderer._transform->_width / (_FLOAT)renderer._transform->_height;

	// 生成相机
	Camera camera(position, direction, up, aspect, HALF_PI * 0.66f, nearPlaneDis, farPlaneDis);

	// 设置渲染器变换矩阵参数
	renderer._transform->_viewTransform = camera.GetViewTransformMatrix();
	renderer._transform->_perspectiveTransform = camera.GetPerspectiveTransformMatrix();
	renderer._transform->UpdateTransform();
}

// 检查 BoundingBox 是否在裁剪空间内
bool BoundInCVV(Transform* transform, Mesh& mesh) {
	Vector4* v[2] = { &mesh._bound->_vMin, &mesh._bound->_vMax };

	// 依次进行 CVV 裁剪
	for (int i = 0; i < 2; i++) {
		if (transform->CheckCVV(transform->ApplyTransform(*v[i])) == 0) {
			return true;
		}
	}
	//std::cout << "Mesh 被裁剪掉" << std::endl;
	return false;
}

int main()
{
	// 渲染模式
	_INT renderMode[] = { RENDER_STATE_WIREFRAME, RENDER_STATE_COLOR, RENDER_STATE_TEXTURE };
	_INT renderModeIndex = 0;
	// 渲染模式按键判断
	bool renderModeSwitchPressed = false;

	// 光照开关按键判断
	bool lightSwitchPressed = false;

	// 生成一个 Box
	_FLOAT alpha = 0.5f;
	CreateBoxMesh();
	_mesh.InitBound();

	// 制作 RenderObject
	Mesh temp;
	//bool readIn = temp.ReadInOBJ("models/dice/dice.obj");
	//RenderObject testObj1("Rabbit 0", Vector3(3.5f, 0.0f, 0.0f), 0.0f);
	//RenderObject testObj2("Rabbit 1", Vector3(-3.0f, -0.5f, 1.0f), 0.0f);
	RenderObject testObj3("Rabbit 2", Vector3(0.0f, 2.5f, 3.0f), 0.0f);
	RenderObject testObj4("Dice", Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	////RenderObject testObj5("My Cube", Vector3(-5.0f, -3.0f, 3.0f), 0.0f);
	RenderObject testObj6;
	testObj6.SetName("Monkey");
	testObj6.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	testObj6.SetAlpha(0.0f);
	//RenderObject testObj6("Monkey", Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	//RenderObject testObj7("UtahTeapot", Vector3(0.0f, 0.0f, 10.0f), 0.0f);

	//testObj1._mesh->ReadInOBJ("models/bunny.obj");
	//testObj2._mesh->ReadInOBJ("models/bunny.obj");
	testObj3._mesh->ReadInOBJ("models/bunny.obj");
	//testObj4.SetMesh(temp);
	testObj4._mesh->ReadInOBJ("models/dice/dice.obj");
	testObj4._mesh->Info();
	//testObj5 模型读取略过，DrawBox 使用 testObj5 的位置 
	//testObj6._mesh->ReadInOBJ("models/IronMan/IronMan.obj");
	testObj6._mesh->ReadInOBJ("models/monkey/monkey.obj");
	testObj6._material->ReadInMTL("models/monkey/monkey.mtl");
	//testObj7._mesh->ReadInOBJ("models/utah_teapot/teapot.obj");
	//testObj7._material->ReadInMTL("models/utah_teapot/default.mtl");

	//将 RenderObject 加入 Scene
	std::vector<RenderObject*> sceneObjects{
		/*&testObj1, &testObj2,*/ &testObj3,
		/*&testObj4,*/ &testObj6 };

		// 生成 Scene 中物体的包围盒
	for (int i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i]->_mesh->InitBound();
		std::cout << sceneObjects[i]->_name << " 包围盒生成完成" << std::endl;
	}
	_scene.GetRenderObjects(sceneObjects);

	// 生成渲染器
	Renderer renderer = Renderer();
	// 生成窗口
	Window window = Window();

	// 设置窗口大小
	const _INT width = 1440;
	const _INT height = 900;

	// 相机初始位置
	_FLOAT cameraX = 0.0f;
	_FLOAT cameraY = 0.0f;
	_FLOAT cameraZ = -5.5f;

	// 相机近远投影平面距离
	_FLOAT nearPlaneDis = 1.0f;
	_FLOAT farPlaneDis = 500.0f;

	// 窗口头信息
	char titleText[] = "Soft Renderer";
	LPTSTR title = titleText;
	if (window.Init(width, height, title) != 0) {
		return -1;
	}

	// 绑定窗口
	renderer.Init(width, height, window._screenBuffer);
	//InitTexture(renderer);
	renderer._renderMode = RENDER_STATE_COLOR;

	// 帧率计算参数
	SYSTEMTIME sys;
	_INT frameCount = 0;
	GetLocalTime(&sys);
	WORD lastTime = sys.wSecond;

	// DEBUG: Debug：OBJ 贴图 debug
	_FLOAT theta = 0.0f;

	// Main Loop
	while (window._isRunning == true && window._keyDown[VK_ESCAPE] == false) {
		window.Dispatch();
		renderer.CleanBuffer();
		Vector4 cameraPosition = Vector4(cameraX, cameraY, cameraZ, 1.0f);
		_cameraPos = cameraPosition;
		CameraAdjustment(renderer, cameraPosition, nearPlaneDis, farPlaneDis);

		InitTexture(renderer);
		DrawBox(renderer, theta, -3.0f, 2.0f, 1.0f);
		DrawScene(renderer, _scene);
		window.Update();

		//		Sleep(5);

				// 计算帧率
		GetLocalTime(&sys);
		frameCount++;
		WORD delta = sys.wSecond - lastTime;
		if (delta > 1) {
			_INT fps = frameCount / (_INT)delta;
			//std::cout << "FPS = " << fps << std::endl;
			frameCount = 0;
			lastTime = sys.wSecond;
		}

		// 相机位置变换
		if (window._keyDown['W']) {
			cameraY += 0.05f * 3;
		}
		if (window._keyDown['S']) {
			cameraY -= 0.05f * 3;
		}
		if (window._keyDown['A']) {
			cameraX -= 0.05f * 3;
		}
		if (window._keyDown['D']) {
			cameraX += 0.05f * 3;
		}
		if (window._keyDown[VK_DOWN]) {
			cameraZ -= 0.05f * 3;
		}
		if (window._keyDown[VK_UP]) {
			cameraZ += 0.05f * 3;
		}

		// Object 位置旋转角变换
		if (window._keyDown[VK_LEFT]) {
			theta += 0.05;
			for (int i = 0; i < _scene._renderObjectCount; i++) {
				_scene._renderObjects[i]->SetAlpha(_scene._renderObjects[i]->_theta + 0.05f);
			}
		}
		if (window._keyDown[VK_RIGHT]) {
			theta -= 0.05f;
			for (int i = 0; i < _scene._renderObjectCount; i++) {
				_scene._renderObjects[i]->SetAlpha(_scene._renderObjects[i]->_theta - 0.05f);
			}
		}

		// 灯光控制
		if (window._keyDown['F']) {
			if (lightSwitchPressed == false) {
				lightSwitchPressed = true;
				renderer._isDirectionalLightOn = (renderer._isDirectionalLightOn) ? false : true;
				if (renderer._isDirectionalLightOn) {
					std::cout << "灯光开启" << std::endl;
				}
				else {
					std::cout << "灯光关闭" << std::endl;
				}
			}
		}
		else if (!window._keyDown['F']) {
			lightSwitchPressed = false;
		}

		// 渲染模式变换
		if (window._keyDown[VK_SPACE]) {
			if (renderModeSwitchPressed == false) {
				renderModeSwitchPressed = true;
				if (++renderModeIndex >= 3) {
					renderModeIndex = 0;
				}
				renderer._renderMode = renderMode[renderModeIndex];
				std::cout << "现在的渲染模式是：";
				switch (renderer._renderMode)
				{
				case(RENDER_STATE_WIREFRAME): {
					std::cout << "线框模式" << std::endl;
					break;
				}
				case(RENDER_STATE_TEXTURE): {
					std::cout << "贴图渲染模式" << std::endl;
					break;
				}
				case(RENDER_STATE_COLOR): {
					std::cout << "填色渲染模式" << std::endl;
					break;
				}
				default:
					break;
				}
			}
		}
		else if (!window._keyDown[VK_SPACE]) {
			renderModeSwitchPressed = false;
		}
	}
	return 0;
}
