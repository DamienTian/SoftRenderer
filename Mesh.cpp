/*
Mesh.cpp 渲染结构
图形学自学任务
author：田昊

* 参考：BlauHimmel 一个简单光栅器的实现
		OpenGL-tutorial --- OBJ
		R. Diane etc. --- MTL material format (Lightwave OBJ)
*/

//#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() {
	_verticesBuffer = nullptr;
	_verticesCount = 0;
	_indicesBuffer = nullptr;
	_indicesCount = 0;
	_bound = nullptr;
}

Mesh::Mesh(_INT verticesCount, _INT indicesCount) {
	_verticesCount = verticesCount;
	_verticesBuffer = new Vertex[_verticesCount];
	_indicesCount = indicesCount;
	_indicesBuffer = new _INT[_indicesCount];
	_bound = nullptr;
}

Mesh::Mesh(const Mesh& other) {
	_verticesCount = other._verticesCount;
	if (_verticesCount > 0) {
		// 清空之前的顶点缓存
		if (_verticesBuffer != nullptr) {
			delete[]_verticesBuffer;
			_verticesBuffer = nullptr;
		}
		_verticesBuffer = new Vertex[_verticesCount];
		for (int i = 0; i < _verticesCount; ++i) {
			_verticesBuffer[i] = other._verticesBuffer[i];
		}
	}
	_indicesCount = other._indicesCount;
	if (_indicesCount > 0) {
		// 清空之前的索引缓存
		if (_indicesBuffer != nullptr) {
			delete[]_indicesBuffer;
			_indicesBuffer = nullptr;
		}
		_indicesBuffer = new _INT[_indicesCount];
		for (int i = 0; i < _indicesCount; ++i) {
			_indicesBuffer[i] = other._indicesBuffer[i];
		}
	}
	else {
		if (_verticesBuffer != nullptr) {
			delete[]_verticesBuffer;
			_verticesBuffer = nullptr;
		}
		if (_indicesBuffer != nullptr) {
			delete[]_indicesBuffer;
			_indicesBuffer = nullptr;
		}
	}
	_bound = nullptr;
}

Mesh::~Mesh()
{
	if (_verticesBuffer != nullptr) {
		delete[]_verticesBuffer;
		_verticesBuffer = nullptr;
	}
	if (_indicesBuffer != nullptr) {
		delete[]_indicesBuffer;
		_indicesBuffer = nullptr;
	}
	if (_bound != nullptr) {
		delete _bound;
		_bound = nullptr;
	}
}

void Mesh::InitBound(Vector3 objectPosition ) {
	_bound = new AABB();
	// 根据加入的 mesh 顶点更新包围盒的大小
	Vector4 minPos = _verticesBuffer[0]._position;
	Vector4 maxPos = _verticesBuffer[0]._position;
	for (int i = 1; i < _verticesCount; i++) {
		Vector4 curr = _verticesBuffer[i]._position;
		if (minPos._x > curr._x) { minPos._x = curr._x; }
		if (minPos._y > curr._y) { minPos._y = curr._y; }
		if (minPos._z > curr._y) { minPos._z = curr._z; }
		if (maxPos._x < curr._x) { maxPos._x = curr._x; }
		if (maxPos._y < curr._y) { maxPos._y = curr._y; }
		if (maxPos._z < curr._y) { maxPos._z = curr._z; }
	}
	_bound->_vMin = minPos + Vector4(objectPosition._x, objectPosition._y, objectPosition._z, 0.0f);
	_bound->_vMax = maxPos + Vector4(objectPosition._x, objectPosition._y, objectPosition._z, 0.0f);
}


bool Mesh::ReadInOBJ(const char * path) {
	using std::cout;
	using std::endl;
	using std::vector;
	using std::regex;
	using std::string;

	// 记录读取行数
	_INT linesCount = 1;

	// 临时存储从 OBJ 读取的数据
	vector<Vertex> verticesTempBuffer;	// 暂存空间，仅存储顶点位置
	vector<Vector2> textCoordsTempBuffer;
	vector<Vector4> normalsTempBuffer;

	vector<Vertex> verticesBuffer;	// 暂存空间，存储顶点位置 + 对应纹理坐标 + 法线等
	vector<_INT> indicesBuffer;

	// 每个顶点的索引存储
	// NOTE: 不同的 OBJ 模型的每一 f 行的面数不同，要做一个动态存储
	//		每一个面的顶点索引（v）, 纹理坐标索引（t）和法线索引（n）
	//		分别对应 vector<_INT> 的 0 1 2 位置
	vector<vector<_INT>> faces;

	_INT verticesCount = 0, textCoordsCount = 0, normalsCount = 0, indicesCount = 0, indicesPrintCount = 0;

	// 打开文件并读取
	FILE * file = fopen(path, "r");
	if (file == nullptr) {
		cout << "OBJ 文件打开失败" << endl;
		return false;
	}
	else {
		char lineReader[256];
		cout << "OBJ 文件打开成功，开始写入" << endl;
		while (true) {
			int scanResult = fscanf(file, "%s", &lineReader);
			if (scanResult == EOF) {
				break;
			}
			// 处理顶点信息
			//	NOTE：在这里初始化并存入顶点，之后在读到面数据（f）时，改动已读入的顶点
			else if (strcmp(lineReader, "v") == 0) {
				Vertex inputVertex;
				_FLOAT x, y, z;
				scanResult = fscanf(file, "%f %f %fn", &x, &y, &z);
				if (scanResult != 3) {
					cout << "错误 - 顶点位置数据不完整：位于第 " << linesCount << " 行" << endl;
					return false;
				}

				// 存入暂存空间
				inputVertex._position = Vector4(x, y, z, 1.0f);
				verticesTempBuffer.push_back(inputVertex);

				verticesCount++;
				linesCount++;
			}
			else if (strcmp(lineReader, "vt") == 0) {
				_FLOAT u, v;
				scanResult = fscanf(file, "%f %fn", &u, &v);
				if (scanResult != 2) {
					cout << "错误 - 纹理坐标数据不完整：位于第 " << linesCount << " 行" << endl;
					return false;
				}
				// 存入暂存空间
				textCoordsTempBuffer.push_back(Vector2(u, v));

				//cout << textCoordsCount <<" UV: " << u << "	" << v << endl;

				textCoordsCount++;
				linesCount++;
			}
			else if (strcmp(lineReader, "vn") == 0) {
				_FLOAT x, y, z;
				scanResult = fscanf(file, "%f %f %fn", &x, &y, &z);
				if (scanResult != 3) {
					cout << "错误 - 法线数据不完整：位于第 " << linesCount << " 行" << endl;
					return false;
				}
				// 存入暂存空间
				normalsTempBuffer.push_back(Vector4(x, y, z, 0.0f));
				normalsCount++;

				//cout << "vn " << Vector4(x, y, z, 0.0f) << endl;

				linesCount++;
			}
			else if (strcmp(lineReader, "f") == 0) {
				// 文本读取缓存：OBJ 文件中的每行文本的分割
				vector<string> facesInput;
				// 缓存该行被输入的顶点
				vector<vector<_INT>> facesWhiteIn;

				// 读入当前面数据文本（以空格分隔）
				fgets(lineReader, 256, file);
				string faceLine(lineReader);
				std::istringstream iss(faceLine);
				for (string s; iss >> s;) {
					facesInput.push_back(s);
				}

				// 判断每一个面的数据构成
				// NOTE：有些 OBJ 文件中的面可以忽略纹理贴图索引甚至法线索引，所以需要处理这种情况
				//	例：f 1//2 3//4 5//6 （都只有坐标索引和法线索引）
				//	* 数据：顶点位置索引，纹理坐标索引，法线索引
				regex faceComplete(".+\/.+\/.+");	// 三项数据全有 
				regex faceNoText(".+\/\/.+");		// 没有纹理坐标
				regex faceNoNormal(".+\/.+");		// 没有法线
				regex onlyVertex(".+");				// 只有顶点索引

													// 判断读入面数据的格式然后读取
				for (string s : facesInput) {
					vector<_INT> newFace;
					_INT v, t, n;
					size_t pos = 0;
					string token;

					if (std::regex_match(s, faceComplete)) {
						string delimiter = "/";

						pos = s.find(delimiter);
						token = s.substr(0, pos);
						v = atoi(token.c_str());
						s.erase(0, pos + delimiter.length());

						pos = s.find(delimiter);
						token = s.substr(0, pos);
						t = atoi(token.c_str());
						s.erase(0, pos + delimiter.length());

						pos = s.find(delimiter);
						n = atoi(s.c_str());
					}
					else if (std::regex_match(s, faceNoText)) {
						string delimiter = "//";

						pos = s.find(delimiter);
						token = s.substr(0, pos);
						v = atoi(token.c_str());
						s.erase(0, pos + delimiter.length());

						t = -1;	// 不存在赋值 -1

						pos = s.find(delimiter);
						n = atoi(s.c_str());
					}
					else if (std::regex_match(s, faceNoNormal)) {
						string delimiter = "/";

						pos = s.find(delimiter);
						token = s.substr(0, pos);
						v = atoi(token.c_str());
						s.erase(0, pos + delimiter.length());

						pos = s.find(delimiter);
						t = atoi(s.c_str());

						n = -1;	// 不存在赋值 -1
					}
					else if (std::regex_match(s, onlyVertex)) {
						v = atoi(s.c_str());
						t = -1;	// 不存在赋值 -1
						n = -1;	// 不存在赋值 -1
					}

					// 因为 f 行的索引是从 1 开始的，所以在这里我们要减 1
					newFace.push_back(v - 1);
					newFace.push_back(t - 1);
					newFace.push_back(n - 1);

					facesWhiteIn.push_back(newFace);
				}

				if (facesWhiteIn.size() == 3) {
					indicesCount += 3;
					indicesPrintCount += 3;
				}
				// 如果面有 4 个顶点的情况下，我们需要改写存入顶点索引缓存中的数据：
				//	例：f v1 v2 v3 v4 ===> f v1 v2 v3 v3 v4 v1
				else if (facesWhiteIn.size() == 4) {
					vector<_INT> tempV4 = facesWhiteIn.back();
					facesWhiteIn.pop_back();
					facesWhiteIn.push_back(facesWhiteIn[2]);
					facesWhiteIn.push_back(tempV4);
					facesWhiteIn.push_back(facesWhiteIn[0]);

					indicesCount += 6;
					indicesPrintCount += 4;
				}
				else if (facesWhiteIn.size() == 6) {
					indicesCount += 6;
					indicesPrintCount += 6;
				}
				else{
					cout << "索引数据格式异常无法处理" << endl;
					return false;
				}

				// 将读取结果写入顶点索引缓存
				for (auto f : facesWhiteIn) {
					faces.push_back(f);
				}

				linesCount++;
			}
			// 处理 MTL 文件
			else if (strcmp(lineReader, "mtllib") == 0) {
				char mtlPath[256];
				scanResult = fscanf(file, "%s", mtlPath);
				if (scanResult != 1) {
					cout << "OBJ 模型没有指定 MTL 数据" << endl;
				}
				else {
					// 在读取 OBJ 中重构地址
					//	NOTE：目前默认将 OBJ 和 MTL 文件放在同一文件夹
					string tempPath(path);
					const auto pos = tempPath.find_last_of("/");
					tempPath = tempPath.substr(0, pos).append("/").append(mtlPath);
					cout << "OBJ 模型的 MTL 数据地址是 " << tempPath << endl;
					_mtlPath = tempPath;
					cout << "_mtlPath = " << _mtlPath << endl;
				}

				linesCount++;
			}
			// 其他行（目前忽略不处理）
			else if (strcmp(lineReader, "#") == 0 || strcmp(lineReader, "g") == 0 ||
				strcmp(lineReader, "s") == 0 || strcmp(lineReader, "usefmtl") == 0) {
				linesCount++;
			}
		}

		fclose(file);

		// 写入读写缓存
		for (auto face : faces) {
			_INT v = 0, t = 1, n = 2;

			// 将顶点索引写入顶点索引缓存中
			//	TODO：indicesBuffer 将直接变成由 0 - verticesBuffer.size() 的 vector<_INT>
			//indicesBuffer.push_back(face[v]);

			verticesBuffer.push_back(verticesTempBuffer[face[v]]);

			// 新加入的顶点要立刻处理：verticesBuffer.back()
			// 将其他索引对应数据加入顶点
			if (face[t] > -1) {
				verticesBuffer.back()._u = textCoordsTempBuffer[face[t]]._x; // Range(textCoordsBuffer[face[t]]._x, 0.0f, 1.0f);
				verticesBuffer.back()._v = textCoordsTempBuffer[face[t]]._y; // Range(textCoordsBuffer[face[t]]._y, 0.0f, 1.0f);
			}
			else {
				verticesBuffer.back()._u = 1;
				verticesBuffer.back()._v = 1;
				//cout << "没有 UV" << endl;
			}
			if (face[n] > -1) {
				verticesBuffer.back()._vertexNormal = normalsTempBuffer[face[n]];
			}
			else {
				verticesBuffer.back()._vertexNormal = Vector4();
				verticesBuffer.back()._vertexNormal._x = 0.0f;
				verticesBuffer.back()._vertexNormal._y = 0.0f;
				verticesBuffer.back()._vertexNormal._z = 0.0f;
				verticesBuffer.back()._vertexNormal._w = 0.0f;
				//cout << "vertices normal : " << verticesBuffer[face[v]]._vertexNormal << endl;
			}
		}

		// 填充顶点索引缓冲
		indicesCount = verticesBuffer.size();
		for (_INT i = 0; i < verticesBuffer.size(); i++) {
			indicesBuffer.push_back(i);
		}

		_verticesCount = verticesCount;
		_verticesBuffer = new Vertex[verticesCount];
		_indicesCount = indicesCount;
		_indicesBuffer = new _INT[indicesCount];

		// 读取完文件后赋值给 Mesh
		_verticesCount = verticesBuffer.size();
		if (_verticesCount > 0) {
			// 清空之前的顶点缓存
			if (_verticesBuffer != nullptr) {
				delete[] _verticesBuffer;
				_verticesBuffer = nullptr;
			}
			_verticesBuffer = new Vertex[_verticesCount];
			for (int i = 0; i < _verticesCount; ++i) {
				_verticesBuffer[i] = verticesBuffer[i];
			}
		}
		_indicesCount = indicesCount;
		if (_indicesCount > 0) {
			// 清空之前的索引缓存
			if (_indicesBuffer != nullptr) {
				delete[] _indicesBuffer;
				_indicesBuffer = nullptr;
			}
			_indicesBuffer = new _INT[_indicesCount];
			for (int i = 0; i < _indicesCount; ++i) {
				_indicesBuffer[i] = indicesBuffer[i];
			}
		}
	}
	return true;
}

void Mesh::Info() {
	using std::cout;
	using std::endl;

	cout << "顶点信息如下：" << endl;
	for (auto i = 0; i < _verticesCount; i++) {
		_verticesBuffer[i].Info();
		cout << endl;
	}

	cout << "顶点索引如下：" << endl;
	for (auto i = 0; i < _indicesCount; i += 3) {
		cout << _indicesBuffer[i] << "/" << _indicesBuffer[i + 1] << "/" << _indicesBuffer[i + 2] << endl;
	}
}

