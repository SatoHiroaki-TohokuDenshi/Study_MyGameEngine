#pragma once
#include <string>
#include <cassert>
#include "Fbx.h"
#include "Transform.h"

using std::string;

namespace Model {
	//ファイルの読み込み
	int Load(string fileName);
	//位置情報を設定
	void SetTransform(int hModel, Transform t);
	//描画
	void Draw(int hModel);

	void Release();

	void RayCast(int hModel, RayCastData& data);
}