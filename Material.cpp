/*
Material.cpp ���ʣ���ȡ .mtl �����ݣ�
ͼ��ѧ��ѧ����
author�����

* �ο�������� NB��
*/

#include "Material.h"

Material::Material()
{
	_mapKaImage = nullptr;
	_mapKdImage = nullptr;
}

Material::Material(std::string newmtl, Color ambientColor, Color diffuseColor) {
	strcpy(_newmtl, newmtl.c_str());
	_ambientColor = ambientColor;
	_diffuseColor = _diffuseColor;
	_mapKaImage = nullptr;
	_mapKdImage = nullptr;
}

Material::~Material()
{

}

// ��ȡ MTL ��Ϣ����ȡ�� Material �� 
bool Material::ReadInMTL(const char * path) {
	using std::cout;
	using std::endl;
	using std::vector;
	using std::regex;
	using std::string;
	
	// ��ȡ�ļ��е�ÿһ��
	// ���ļ�����ȡ
	FILE * file = fopen(path, "r");
	if (file == nullptr) {
		cout << ".mtl �ļ���ʧ��" << endl;
		return false;
	}
	else {
		char lineReader[256];
		while (true) {
			int scanResult = fscanf(file, "%s", &lineReader);
			if (scanResult == EOF) {
				break;
			}
			// ����һ�� newmtl
			if (strcmp(lineReader, "newmtl") == 0) {
				char newMtl[256];
				scanResult = fscanf(file, "%s", newMtl);
				if (scanResult != 1) {
					cout << "һ�� MTL ֻ����һ������" << endl;
					return false;
				}
				strcpy(_newmtl, newMtl);
			}
			// ��ȡ��������ɫ
			else if (strcmp(lineReader, "Ka") == 0) {
				_FLOAT a_r, a_g, a_b;
				scanResult = fscanf(file, "%f %f %f", &a_r, &a_g, &a_b);
				if (scanResult != 3) {
					cout << "���ʻ�����ϵ����ʽ����" << endl;
					return false;
				}
				_ambientColor._r = a_r;
				_ambientColor._g = a_g;
				_ambientColor._b = a_b;
				cout << _newmtl << " �Ļ�������ɫ��" << _ambientColor << endl;
			}
			// ��ȡ���������ɫ
			else if (strcmp(lineReader, "Kd") == 0) {
				_FLOAT d_r, d_g, d_b;
				scanResult = fscanf(file, "%f %f %f", &d_r, &d_g, &d_b);
				if (scanResult != 3) {
					cout << "�����������ϵ����ʽ����" << endl;
					return false;
				}
				_diffuseColor._r = d_r;
				_diffuseColor._g = d_g;
				_diffuseColor._b = d_b;
				cout << _newmtl << " �����������ɫ��" << _diffuseColor << endl;
			}
			// ��ȡ���������������ͼ
			else if (strcmp(lineReader, "map_Ka") == 0) {
				char kaPath[256];
				scanResult = fscanf(file, "%s", kaPath);

				// �ڶ�ȡ OBJ ���ع���ַ
				//	NOTE��ĿǰĬ�Ͻ� OBJ �� MTL �ļ�����ͬһ�ļ���
				string tempPath(path);
				const auto pos = tempPath.find_last_of("/");
				tempPath = tempPath.substr(0, pos).append("/").append(kaPath);
				strcpy(_mapKa ,tempPath.c_str());
			}
			// ��ȡ����������������ͼ
			else if (strcmp(lineReader, "map_Kd") == 0) {
				char kaPath[256];
				scanResult = fscanf(file, "%s", kaPath);

				// �ڶ�ȡ OBJ ���ع���ַ
				//	NOTE��ĿǰĬ�Ͻ� OBJ �� MTL �ļ�����ͬһ�ļ���
				string tempPath(path);
				const auto pos = tempPath.find_last_of("/");
				tempPath = tempPath.substr(0, pos).append("/").append(kaPath);
				strcpy(_mapKd, tempPath.c_str());

				cout << "_mapKd: " << _mapKd << endl;
				_mapKdImage = BMPImage::ReadInBMP(_mapKd);
			}
		}
	}

	fclose(file);
	return true;
}

void Material::Info() {
	using std::cout;
	using std::endl;
	using std::vector;
	using std::regex;
	using std::string;

	cout << "�������ƣ�" << _newmtl << endl;
	cout << "���ϻ����⣺" << _ambientColor << endl;
	cout << "����������⣺" << _diffuseColor << endl;
	cout << "���ϵ� map_Ka ���ݵ�ַ�� " << _mapKa << endl;
	cout << "���ϵ� map_Kd ���ݵ�ַ�� " << _mapKd << endl;
}