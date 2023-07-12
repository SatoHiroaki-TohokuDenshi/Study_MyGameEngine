#include "Model.h"
#include "Transform.h"

int Model::Load(string fileName) {
	//ファイルの名前を探索して、同じものがあったらモデル番号-1を返す
	//なかった場合はモデルを読み込んで、ベクター配列に追加して、モデル番号を返す
	for (auto itr = data_.begin(); itr != data_.end();) {
		if (true)	return;
		else		itr++;
	}

}

void Model::SetTransform(int hModel, Transform t) {

}

void Model::Draw(int hModel) {

}
