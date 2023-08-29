#pragma once
#include <vector>
#include "Engine/GameObject.h"

using std::vector;

//Stageを管理するクラス
class Stage : public GameObject
{
private:
	enum BOX_TYPE {
		BOX_DEFAULT = 0,
		BOX_BRICK,
		BOX_GRASS,
		BOX_SAND,
		BOX_WATER,
		BOX_MAX,
	};
	const int sizeX = 15;
	const int sizeZ = 15;
	
	vector<int> hModel_;		//モデル番号
	vector<vector<int>> table_;	//表示内容
public:
	//コンストラクタ
	Stage(GameObject* parent);

	//デストラクタ
	~Stage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};