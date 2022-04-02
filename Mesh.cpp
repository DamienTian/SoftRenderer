/*
Mesh.cpp ��Ⱦ�ṹ
ͼ��ѧ��ѧ����
author�����

* �ο���BlauHimmel һ���򵥹�դ����ʵ��
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
		// ���֮ǰ�Ķ��㻺��
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
		// ���֮ǰ����������
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
	// ���ݼ���� mesh ������°�Χ�еĴ�С
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

	// ��¼��ȡ����
	_INT linesCount = 1;

	// ��ʱ�洢�� OBJ ��ȡ������
	vector<Vertex> verticesTempBuffer;	// �ݴ�ռ䣬���洢����λ��
	vector<Vector2> textCoordsTempBuffer;
	vector<Vector4> normalsTempBuffer;

	vector<Vertex> verticesBuffer;	// �ݴ�ռ䣬�洢����λ�� + ��Ӧ�������� + ���ߵ�
	vector<_INT> indicesBuffer;

	// ÿ������������洢
	// NOTE: ��ͬ�� OBJ ģ�͵�ÿһ f �е�������ͬ��Ҫ��һ����̬�洢
	//		ÿһ����Ķ���������v��, ��������������t���ͷ���������n��
	//		�ֱ��Ӧ vector<_INT> �� 0 1 2 λ��
	vector<vector<_INT>> faces;

	_INT verticesCount = 0, textCoordsCount = 0, normalsCount = 0, indicesCount = 0, indicesPrintCount = 0;

	// ���ļ�����ȡ
	FILE * file = fopen(path, "r");
	if (file == nullptr) {
		cout << "OBJ �ļ���ʧ��" << endl;
		return false;
	}
	else {
		char lineReader[256];
		cout << "OBJ �ļ��򿪳ɹ�����ʼд��" << endl;
		while (true) {
			int scanResult = fscanf(file, "%s", &lineReader);
			if (scanResult == EOF) {
				break;
			}
			// ����������Ϣ
			//	NOTE���������ʼ�������붥�㣬֮���ڶ��������ݣ�f��ʱ���Ķ��Ѷ���Ķ���
			else if (strcmp(lineReader, "v") == 0) {
				Vertex inputVertex;
				_FLOAT x, y, z;
				scanResult = fscanf(file, "%f %f %fn", &x, &y, &z);
				if (scanResult != 3) {
					cout << "���� - ����λ�����ݲ�������λ�ڵ� " << linesCount << " ��" << endl;
					return false;
				}

				// �����ݴ�ռ�
				inputVertex._position = Vector4(x, y, z, 1.0f);
				verticesTempBuffer.push_back(inputVertex);

				verticesCount++;
				linesCount++;
			}
			else if (strcmp(lineReader, "vt") == 0) {
				_FLOAT u, v;
				scanResult = fscanf(file, "%f %fn", &u, &v);
				if (scanResult != 2) {
					cout << "���� - �����������ݲ�������λ�ڵ� " << linesCount << " ��" << endl;
					return false;
				}
				// �����ݴ�ռ�
				textCoordsTempBuffer.push_back(Vector2(u, v));

				//cout << textCoordsCount <<" UV: " << u << "	" << v << endl;

				textCoordsCount++;
				linesCount++;
			}
			else if (strcmp(lineReader, "vn") == 0) {
				_FLOAT x, y, z;
				scanResult = fscanf(file, "%f %f %fn", &x, &y, &z);
				if (scanResult != 3) {
					cout << "���� - �������ݲ�������λ�ڵ� " << linesCount << " ��" << endl;
					return false;
				}
				// �����ݴ�ռ�
				normalsTempBuffer.push_back(Vector4(x, y, z, 0.0f));
				normalsCount++;

				//cout << "vn " << Vector4(x, y, z, 0.0f) << endl;

				linesCount++;
			}
			else if (strcmp(lineReader, "f") == 0) {
				// �ı���ȡ���棺OBJ �ļ��е�ÿ���ı��ķָ�
				vector<string> facesInput;
				// ������б�����Ķ���
				vector<vector<_INT>> facesWhiteIn;

				// ���뵱ǰ�������ı����Կո�ָ���
				fgets(lineReader, 256, file);
				string faceLine(lineReader);
				std::istringstream iss(faceLine);
				for (string s; iss >> s;) {
					facesInput.push_back(s);
				}

				// �ж�ÿһ��������ݹ���
				// NOTE����Щ OBJ �ļ��е�����Ժ���������ͼ������������������������Ҫ�����������
				//	����f 1//2 3//4 5//6 ����ֻ�����������ͷ���������
				//	* ���ݣ�����λ������������������������������
				regex faceComplete(".+\/.+\/.+");	// ��������ȫ�� 
				regex faceNoText(".+\/\/.+");		// û����������
				regex faceNoNormal(".+\/.+");		// û�з���
				regex onlyVertex(".+");				// ֻ�ж�������

													// �ж϶��������ݵĸ�ʽȻ���ȡ
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

						t = -1;	// �����ڸ�ֵ -1

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

						n = -1;	// �����ڸ�ֵ -1
					}
					else if (std::regex_match(s, onlyVertex)) {
						v = atoi(s.c_str());
						t = -1;	// �����ڸ�ֵ -1
						n = -1;	// �����ڸ�ֵ -1
					}

					// ��Ϊ f �е������Ǵ� 1 ��ʼ�ģ���������������Ҫ�� 1
					newFace.push_back(v - 1);
					newFace.push_back(t - 1);
					newFace.push_back(n - 1);

					facesWhiteIn.push_back(newFace);
				}

				if (facesWhiteIn.size() == 3) {
					indicesCount += 3;
					indicesPrintCount += 3;
				}
				// ������� 4 �����������£�������Ҫ��д���붥�����������е����ݣ�
				//	����f v1 v2 v3 v4 ===> f v1 v2 v3 v3 v4 v1
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
					cout << "�������ݸ�ʽ�쳣�޷�����" << endl;
					return false;
				}

				// ����ȡ���д�붥����������
				for (auto f : facesWhiteIn) {
					faces.push_back(f);
				}

				linesCount++;
			}
			// ���� MTL �ļ�
			else if (strcmp(lineReader, "mtllib") == 0) {
				char mtlPath[256];
				scanResult = fscanf(file, "%s", mtlPath);
				if (scanResult != 1) {
					cout << "OBJ ģ��û��ָ�� MTL ����" << endl;
				}
				else {
					// �ڶ�ȡ OBJ ���ع���ַ
					//	NOTE��ĿǰĬ�Ͻ� OBJ �� MTL �ļ�����ͬһ�ļ���
					string tempPath(path);
					const auto pos = tempPath.find_last_of("/");
					tempPath = tempPath.substr(0, pos).append("/").append(mtlPath);
					cout << "OBJ ģ�͵� MTL ���ݵ�ַ�� " << tempPath << endl;
					_mtlPath = tempPath;
					cout << "_mtlPath = " << _mtlPath << endl;
				}

				linesCount++;
			}
			// �����У�Ŀǰ���Բ�������
			else if (strcmp(lineReader, "#") == 0 || strcmp(lineReader, "g") == 0 ||
				strcmp(lineReader, "s") == 0 || strcmp(lineReader, "usefmtl") == 0) {
				linesCount++;
			}
		}

		fclose(file);

		// д���д����
		for (auto face : faces) {
			_INT v = 0, t = 1, n = 2;

			// ����������д�붥������������
			//	TODO��indicesBuffer ��ֱ�ӱ���� 0 - verticesBuffer.size() �� vector<_INT>
			//indicesBuffer.push_back(face[v]);

			verticesBuffer.push_back(verticesTempBuffer[face[v]]);

			// �¼���Ķ���Ҫ���̴�����verticesBuffer.back()
			// ������������Ӧ���ݼ��붥��
			if (face[t] > -1) {
				verticesBuffer.back()._u = textCoordsTempBuffer[face[t]]._x; // Range(textCoordsBuffer[face[t]]._x, 0.0f, 1.0f);
				verticesBuffer.back()._v = textCoordsTempBuffer[face[t]]._y; // Range(textCoordsBuffer[face[t]]._y, 0.0f, 1.0f);
			}
			else {
				verticesBuffer.back()._u = 1;
				verticesBuffer.back()._v = 1;
				//cout << "û�� UV" << endl;
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

		// ��䶥����������
		indicesCount = verticesBuffer.size();
		for (_INT i = 0; i < verticesBuffer.size(); i++) {
			indicesBuffer.push_back(i);
		}

		_verticesCount = verticesCount;
		_verticesBuffer = new Vertex[verticesCount];
		_indicesCount = indicesCount;
		_indicesBuffer = new _INT[indicesCount];

		// ��ȡ���ļ���ֵ�� Mesh
		_verticesCount = verticesBuffer.size();
		if (_verticesCount > 0) {
			// ���֮ǰ�Ķ��㻺��
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
			// ���֮ǰ����������
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

	cout << "������Ϣ���£�" << endl;
	for (auto i = 0; i < _verticesCount; i++) {
		_verticesBuffer[i].Info();
		cout << endl;
	}

	cout << "�����������£�" << endl;
	for (auto i = 0; i < _indicesCount; i += 3) {
		cout << _indicesBuffer[i] << "/" << _indicesBuffer[i + 1] << "/" << _indicesBuffer[i + 2] << endl;
	}
}
