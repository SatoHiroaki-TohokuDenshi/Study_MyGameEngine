#pragma once
#include <string>
#include <vector>

//前方宣言
class Transform;
class Fbx;

using std::string;
using std::vector;

namespace Model {
	//データを格納する構造体
	struct ModelData {
		Fbx* pFbx_;				//FBXのアドレス
		Transform transform_;	//Transformの情報
		string fileName_;		//ファイルの名前
	};

	vector<ModelData> data_;

	//ファイルの読み込み
	int Load(string fileName);
	//位置情報を設定
	void SetTransform(int hModel, Transform t);
	//描画
	void Draw(int hModel);
}