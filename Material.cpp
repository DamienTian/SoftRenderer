/*
Material.cpp 材质（读取 .mtl 的数据）
图形学自学任务
author：田昊

* 参考：晓峰哥 NB！
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

// 读取 MTL 信息，提取到 Material 中 
bool Material::ReadInMTL(const char * path) {
	using std::cout;
	using std::endl;
	using std::vector;
	using std::regex;
	using std::string;
	
	// 读取文件中的每一行
	// 打开文件并读取
	FILE * file = fopen(path, "r");
	if (file == nullptr) {
		cout << ".mtl 文件打开失败" << endl;
		return false;
	}
	else {
		char lineReader[256];
		while (true) {
			int scanResult = fscanf(file, "%s", &lineReader);
			if (scanResult == EOF) {
				break;
			}
			// 制造一个 newmtl
			if (strcmp(lineReader, "newmtl") == 0) {
				char newMtl[256];
				scanResult = fscanf(file, "%s", newMtl);
				if (scanResult != 1) {
					cout << "一个 MTL 只能有一个名称" << endl;
					return false;
				}
				strcpy(_newmtl, newMtl);
			}
			// 读取环境光颜色
			else if (strcmp(lineReader, "Ka") == 0) {
				_FLOAT a_r, a_g, a_b;
				scanResult = fscanf(file, "%f %f %f", &a_r, &a_g, &a_b);
				if (scanResult != 3) {
					cout << "材质环境光系数格式错误" << endl;
					return false;
				}
				_ambientColor._r = a_r;
				_ambientColor._g = a_g;
				_ambientColor._b = a_b;
				cout << _newmtl << " 的环境光颜色：" << _ambientColor << endl;
			}
			// 读取漫反射光颜色
			else if (strcmp(lineReader, "Kd") == 0) {
				_FLOAT d_r, d_g, d_b;
				scanResult = fscanf(file, "%f %f %f", &d_r, &d_g, &d_b);
				if (scanResult != 3) {
					cout << "材质漫反射光系数格式错误" << endl;
					return false;
				}
				_diffuseColor._r = d_r;
				_diffuseColor._g = d_g;
				_diffuseColor._b = d_b;
				cout << _newmtl << " 的漫反射光颜色：" << _diffuseColor << endl;
			}
			// 读取环境光光照纹理贴图
			else if (strcmp(lineReader, "map_Ka") == 0) {
				char kaPath[256];
				scanResult = fscanf(file, "%s", kaPath);

				// 在读取 OBJ 中重构地址
				//	NOTE：目前默认将 OBJ 和 MTL 文件放在同一文件夹
				string tempPath(path);
				const auto pos = tempPath.find_last_of("/");
				tempPath = tempPath.substr(0, pos).append("/").append(kaPath);
				strcpy(_mapKa ,tempPath.c_str());
			}
			// 读取漫反射光光照纹理贴图
			else if (strcmp(lineReader, "map_Kd") == 0) {
				char kaPath[256];
				scanResult = fscanf(file, "%s", kaPath);

				// 在读取 OBJ 中重构地址
				//	NOTE：目前默认将 OBJ 和 MTL 文件放在同一文件夹
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

	cout << "材料名称：" << _newmtl << endl;
	cout << "材料环境光：" << _ambientColor << endl;
	cout << "材料漫反射光：" << _diffuseColor << endl;
	cout << "材料的 map_Ka 数据地址是 " << _mapKa << endl;
	cout << "材料的 map_Kd 数据地址是 " << _mapKd << endl;
}